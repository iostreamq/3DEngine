#pragma once
#include "glad/glad.h"

class ShaderDesc;

namespace Engine
{
	class IShader
	{
	public:
		virtual ~IShader() = default;
		virtual void createShader(const ShaderDesc& shaderDesc, GLenum shaderType) = 0;
		virtual void deleteShader() const = 0;
		virtual bool checkCompileStatus()  = 0;	
		virtual GLuint getId() const  = 0;
	};
}