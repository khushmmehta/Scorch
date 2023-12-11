#pragma once

#include <glad/glad.h>

class IndexBuffer
{
private:
	GLuint m_RendererID;
	GLuint m_Count;

public:
	IndexBuffer(const GLuint* data, GLuint size);
	~IndexBuffer();

	void Bind();
	void Unbind();

	[[nodiscard]] inline GLuint GetCount() const { return m_Count; }
};
