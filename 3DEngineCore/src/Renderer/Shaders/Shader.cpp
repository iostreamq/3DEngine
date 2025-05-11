#include <Renderer/Shaders/Shader.hpp>
#include <3DEngineCore/Log.hpp>

namespace Engine
{
	void Shader::createShader(const char* strShader, GLenum shaderType)
	{
		if (strShader == '\0')
		{
			LOG_CRIT(" {} shader`s str is empty! {}", shaderType, strShader);
			return;
		}

		else
		{
			m_id = glCreateShader(shaderType);
			glShaderSource(m_id, 1, &strShader, nullptr);
			glCompileShader(m_id);
		}
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