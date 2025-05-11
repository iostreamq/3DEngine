#pragma once
#include "glad/glad.h"
#include <Renderer/Shaders/IShader.hpp>

namespace Engine
{
	class Shader : public IShader
	{
	public:
		void createShader(const char* strShader, const char* shaderType) override;
		bool checkCompileStatus() override;
		void deleteShader() override;
	private:
		void defineShaderType(const char* shaderType);
		bool m_is_shaderCompiled;
		GLuint m_id;
		GLenum m_shaderType;
	};
}