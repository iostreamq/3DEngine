#include <Renderer/OpenGL/Shaders/Shader.hpp>
#include <3DEngineCore/Log.hpp>

namespace Engine
{
	void Shader::createShader(const ShaderDesc& shaderDesc, GLenum shaderType)
	{
			m_id = glCreateShader(shaderType);

			const char* src = shaderDesc.sourceCode.c_str();
			glShaderSource(m_id, shaderDesc.AmountOfStr, &src, nullptr);
			glCompileShader(m_id);
	}

	bool Shader::checkCompileStatus()
	{
		GLint success;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
			LOG_CRIT("ERROR::SHADER_COMPILE: vertex shader has not compiled {}", infoLog);
			m_is_shaderCompiled = false;
			return false;
		}
		m_is_shaderCompiled = true;
		return true;
	}

	void Shader::deleteShader() const
	{
		if (m_id)
			glDeleteShader(m_id);
	}

}