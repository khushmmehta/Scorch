#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <chrono>

#include "GLErrorHandler.h"
#include <glm/gtx/quaternion.hpp>
#include "gui-implementation/GuiHandler.h"
#include "gui-implementation/GuiWrapper.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "rendering/Renderer.h"

struct GridCell
{
    glm::vec2 index;
};

class Grid
{
public:
    static constexpr uint32_t width = 35;
    static constexpr uint32_t height = 35;

    Grid()
    {
        for (uint32_t i = 0; i < width; i++)
            for (uint32_t j = 0; j < height; j++)
                gridCells[i + j * width].index = {i, j};
    }

    GridCell getCell(const uint32_t x, const uint32_t y) const { return gridCells[x + y * width]; }

private:
    GridCell gridCells[width * height] = {};
};

struct VerletObject
{
    glm::vec2 currPos      = {0.0f, 0.0f};
    glm::vec2 prevPos      = {0.0f, 0.0f};
    glm::vec2 acceleration = {0.0f, 0.0f};

    void updatePos(const float dt)
    {
        const glm::vec2 velocity = currPos - prevPos;
        prevPos = currPos;

        currPos = currPos + velocity + acceleration * dt * dt;

        acceleration = {};
    }

    void accelerate(const glm::vec2 acc)
    {
        acceleration += acc;
    }

    glm::vec2 getGridCell(const Grid& grid) const { return grid.getCell(floor((currPos.x + 350) / 20), floor((-currPos.y + 350) / 20)).index; }
};

void updatePhysics(std::vector<VerletObject>& objects, const glm::vec2 gravity, const float deltaTime, const float radius)
{
    constexpr float constraintRadius = 350.0f;
    constexpr uint32_t subSteps = 8;
    const float subDeltaTime = deltaTime / static_cast<float>(subSteps);

    for (uint32_t _i = subSteps; _i--;)
    {
        for (auto& obj : objects)
        {
            // Apply Gravity
            obj.accelerate(gravity);

            // Apply Square Constraints
            if (fabs(obj.currPos.x) > constraintRadius - radius)
                obj.currPos.x > 0 ? obj.currPos.x *= (constraintRadius - radius) / obj.currPos.x : obj.currPos.x *= (constraintRadius - radius) / -obj.currPos.x;
            if (fabs(obj.currPos.y) > constraintRadius - radius)
                obj.currPos.y > 0 ? obj.currPos.y *= (constraintRadius - radius) / obj.currPos.y : obj.currPos.y *= (constraintRadius - radius) / -obj.currPos.y;
        }

        // Object Collision Solver
        const uint32_t objCount = objects.size();
        for (uint32_t i = 0; i < objCount; ++i)
        {
            VerletObject& object1 = objects[i];
            for (uint32_t k = i + 1; k < objCount; ++k)
            {
                VerletObject& object2 = objects[k];
                const glm::vec2 collisionAxis = object1.currPos - object2.currPos;
                const float squareDistance = collisionAxis.x * collisionAxis.x + collisionAxis.y * collisionAxis.y;

                if (squareDistance < (radius + radius) * (radius + radius))
                {
                    const float distance =  sqrtf(squareDistance);
                    const glm::vec2 n = collisionAxis / distance;
                    const float delta = radius + radius - distance;
                    object1.currPos += 0.5f * delta * n;
                    object2.currPos -= 0.5f * delta * n;
                }
            }
        }

        for (auto& obj : objects) obj.updatePos(subDeltaTime);
    }
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow(700, 700, "Scorch Engine", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    GuiHandler gui(window);
    gui.SetFont("../res/fonts/JetBrainsMono-Regular.ttf", 20);

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(errorOccurredGL, nullptr);

    Grid grid;

    {
        float radius = 10;

        GLfloat vertices[] = {
            -radius, -radius, /* UV Coords: */ -1.0f, -1.0f, // 0
             radius, -radius, /* UV Coords: */  1.0f, -1.0f, // 1
             radius,  radius, /* UV Coords: */  1.0f,  1.0f, // 2
            -radius,  radius, /* UV Coords: */ -1.0f,  1.0f  // 3
        };

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        Renderer renderer;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexBuffer vbo(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        VertexArray vao;
        vao.AddBuffer(vbo, layout);
        IndexBuffer ibo(indices, sizeof(indices));

        Shader shader("../res/shaders/Basic.vert", "../res/shaders/Circle.frag");
        shader.Bind();
        // For The Circle Fragment Shader Only
        shader.SetUniform1f("u_Radius", 50.0f);
        shader.SetUniform1f("u_Smooth", 0.75f);

        float currTime(0), prevTime;
        glm::vec2 gravity(0.0f, -600.0f);

        std::vector<VerletObject> objects(0);

        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            #pragma region Declaring Variables

            prevTime = currTime;
            currTime = static_cast<float>(glfwGetTime());
            float deltaTime = currTime - prevTime;

            #pragma endregion

            #pragma region Rendering
            auto currentTime = std::chrono::high_resolution_clock::now();
            static auto lastSpawnTime = currentTime;
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSpawnTime).count();

            if (elapsedTime >= 100 && objects.size() < 1000) {
                VerletObject newObject;
                newObject.currPos.y =  0.0f;
                newObject.prevPos.y = -0.5f;
                newObject.currPos.x =  0.0f;
                newObject.prevPos.x = -1.0f;

                lastSpawnTime = currentTime;

                objects.push_back(newObject);
            }

            updatePhysics(objects, gravity, deltaTime, radius);

            for (size_t i = 0; i < objects.size(); i++)
            {
                glm::mat4 model = translate(glm::mat4(1), glm::vec3(objects[i].currPos, 0.0f));
                glm::mat4 MVP = renderer.proj * renderer.view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", MVP);
                shader.SetUniform3f("u_Color", 0.55f, 0.0f, 1.0f);
                shader.SetUniform1f("u_Smooth", 0.8f);

                renderer.Draw(vao, ibo, shader);
            }
            #pragma endregion

            #pragma region GUI Rendering

            gui.Start();

            ImGui::Begin("Scorch");

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / gui.io.Framerate, gui.io.Framerate);
            ImGui::Text("Object Count: %.u", static_cast<uint32_t>(objects.size()));
            //ImGui::Text("Object Cell: %.1f, %.1f", objects[0].getGridCell(grid).x, objects[0].getGridCell(grid).y);

            ImGui::End();

            gui.Render();

            #pragma endregion

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        gui.Destroy();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
