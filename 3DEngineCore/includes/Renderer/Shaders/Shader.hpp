#pragma once
#include <Renderer/Shaders/IShader.hpp>

namespace Engine
{
	class Shader : public IShader
	{
	public:
		void createShader(const char* strShader, GLenum shaderType)  override;
		bool checkCompileStatus() override;
		void deleteShader() const override;
		GLuint getId() const override { return m_id; };
	private:
		bool m_is_shaderCompiled;
		GLuint m_id;
		GLenum m_shaderType;
	};
}