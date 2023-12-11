#pragma once

#include <iostream>
#include <glad/glad.h>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_VertPath;
	std::string m_FragPath;
	GLuint m_RendererID;
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

public:
	Shader(const std::string& vertdir, const std::string& fragdir);
	~Shader();


	void Bind() const;
	static void Unbind() ;

	/* Set Uniforms */
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	static ShaderProgramSource ParseShader(const std::string& vertDir, const std::string& fragDir);
	static GLuint CompileShader(unsigned int type, const std::string& source);
	static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLint GetUniformLocation(const std::string& name) const;
};
