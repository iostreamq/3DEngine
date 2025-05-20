#include <ResourceManagement/ShaderResourceManager.hpp>
#include<fstream>
#include<sstream>
#include<3DEngineCore/Log.hpp>


const std::shared_ptr<Engine::ShaderProgram> const ShaderResourceManager::loadShaderProgram(
	std::string&& nameOfShaderProgram,
	const ShaderDesc& vertexDesc,
	const ShaderDesc& fragmentDesc)
{		
		const std::shared_ptr<Engine::ShaderProgram>& shaderProgram = m_shadersMap.emplace
		(std::move(nameOfShaderProgram)
	   , std::make_shared<Engine::ShaderProgram>(
		 vertexDesc,
		fragmentDesc
	     )).first->second;
				
		if (shaderProgram->checkCompileStatus())
		{
			shaderProgram->deleteShaders();
			return shaderProgram;
		}
	return nullptr;
}
