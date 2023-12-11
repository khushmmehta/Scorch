#include "Renderer.h"

void Renderer::Clear()
{
    glClearColor(0.102, 0.102, 0.161, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ib.GetCount()), GL_UNSIGNED_INT, nullptr);
}
