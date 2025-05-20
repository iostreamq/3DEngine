#pragma once
#include <glad/glad.h>
#include <memory>
#include <Renderer/OpenGL/Shaders/Shader.hpp>
#include <Descriptors/RendererDesc/ShaderDesc.hpp>

namespace Engine
{
	class IShader;
	class ShaderProgram
	{
	public:
		ShaderProgram(const ShaderDesc& vertexDesc, const ShaderDesc& fragmentDesc);
		~ShaderProgram();
		bool checkCompileStatus();
		GLuint& getId() { return m_id; }
		void deleteShaders();
		void bind();
		void unbind();

	private:
		void createProgram();
		std::unique_ptr<IShader> m_vertexShader;
		std::unique_ptr<IShader> m_fragmentShader;
		GLuint m_id;
		bool m_isCompiled;
	};
}