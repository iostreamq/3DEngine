#include <Renderer/Shaders/Shader.hpp>
#include <3DEngineCore/Log.hpp>

namespace Engine
{
		void Shader::createShader(const char* strShader, const char* shaderType)
		{
			defineShaderType(shaderType);
			m_id = glCreateShader(m_shaderType);
			glShaderSource(m_id, 1, &strShader, nullptr);
			glCompileShader(m_id);
		}

		bool Shader::checkCompileStatus()
		{
			GLint success;
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				m_is_shaderCompiled = false;
				GLchar infoLog[1024];
				glGetShaderInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
				LOG_CRIT("ERROR::SHADER_COMPILE: vertex shader has not compiled {}", infoLog);
				return false;
			}
			m_is_shaderCompiled = true;
			return true;
		}

		void Shader::deleteShader()
		{
			if(m_id)
			glDeleteShader(m_id);
		}

		void Shader::defineShaderType(const char* shaderType)
		{			
				if (shaderType == "vertex") m_shaderType = GL_VERTEX_SHADER;
				if (shaderType == "fragment") m_shaderType = GL_FRAGMENT_SHADER;			
		}
}