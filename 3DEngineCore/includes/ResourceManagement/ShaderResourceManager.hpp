#pragma once
#include<memory>
#include<map>
#include<ResourceManagement/IResourceManager.hpp>
#include <Renderer/OpenGL/Shaders/ShaderProgram.hpp>
#include <Descriptors/RendererDesc/ShaderDesc.hpp>


class ShaderResourceManager : public IResourceManager
{
public:
	const std::shared_ptr<Engine::ShaderProgram> const loadShaderProgram(std::string&& nameOfShaderProgram,
																		 const ShaderDesc& vertexDesc,
																		 const ShaderDesc& fragmentDesc);
	static const unsigned int getTableNumber()  { return m_tableNumber; }
private:
	static const unsigned int m_tableNumber = 0;

	using shaders_map = std::map<std::string, std::shared_ptr<Engine::ShaderProgram>>;
	shaders_map m_shadersMap;
};

