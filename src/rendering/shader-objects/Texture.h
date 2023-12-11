#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint m_RendererID;
	std::string m_FilePath;
	GLubyte* m_LocalBuffer;
	GLint m_Width, m_Height, m_BPP;

public:
	explicit Texture(const std::string& path);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;

	[[nodiscard]]  inline GLint GetWidth() const { return m_Width; }
	[[nodiscard]]  inline GLint GetHeight() const { return m_Height; }
};
