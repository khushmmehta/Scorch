#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader-objects/Shader.h"
#include "mesh-objects/VertexArray.h"
#include "mesh-objects/IndexBuffer.h"

class Renderer
{
public:
    glm::mat4 proj = glm::ortho(-350.0f, 350.0f, -350.0f, 350.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    static void Clear() ;
    static void Draw(VertexArray& va, IndexBuffer& ib, const Shader& shader) ;
};
