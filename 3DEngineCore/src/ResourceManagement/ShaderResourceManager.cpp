#include <ResourceManagement/ShaderResourceManager.hpp>
#include<fstream>
#include<sstream>
#include<3DEngineCore/Log.hpp>

void ShaderResourceManager::init(std::string&& mainPath) 
{
	m_path = std::move(mainPath);
}

const std::shared_ptr<Engine::ShaderProgram> const ShaderResourceManager::loadShaderProgram(
	std::string&& nameOfShaderProgram,
	std::string&& vertexPath,
	std::string&& fragmentPath)
{

	if (!vertexPath.empty() && !fragmentPath.empty())
	{
		
		const std::shared_ptr<Engine::ShaderProgram>& shaderProgram = m_shadersMap.emplace
		(std::move(nameOfShaderProgram)
	   , std::make_shared<Engine::ShaderProgram>(
		 getFileString(std::move(vertexPath)).c_str(),
		 getFileString(std::move(fragmentPath)).c_str()
			)).first->second;
				
		if (shaderProgram->checkCompileStatus())
		{
			shaderProgram->deleteShaders();
			return shaderProgram;
		}
	}

	else LOG_CRIT("Vertex path {} or(and) Fragmet path {} is(are) empty", vertexPath, fragmentPath);
	return nullptr;
}

std::string ShaderResourceManager::getFileString(std::string&& AdditionalPath)
{
	std::ifstream fileShader;
	fileShader.open(std::string(m_path + std::move(AdditionalPath)), std::ifstream::in | std::ios_base::binary);
	if (!fileShader.is_open())
	{
			LOG_CRIT("Can`t open shader`s file");
			return "";	
	}
	std::stringstream bufShader;
	bufShader << fileShader.rdbuf();
	return bufShader.str();
}