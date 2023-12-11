#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>
#include <assert.h>

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	unsigned char normalized;

	static GLuint GetTypeSize(const unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
			default: ;
		}
		assert(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;

public:
	VertexBufferLayout() : m_Stride(0)
	{
	}

	template<typename T>
	void Push(GLuint count) { throw std::runtime_error(nullptr); }

	template<>
	void Push<float>(const GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(const GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(const GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}

	std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
	unsigned int GetStride() const { return m_Stride; };
};
