#include "VertexArray.h"

VertexArray::VertexArray() : m_RendererID(0)
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexBufferLayout layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	GLuint offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (const void*)(uintptr_t)(offset));
		offset += e.count * VertexBufferElement::GetTypeSize(e.type);
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
