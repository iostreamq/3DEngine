#pragma once
#include<memory>
#include<map>
#include<ResourceManagement/IResourceManager.hpp>
#include <Renderer/Shaders/ShaderProgram.hpp>


class ShaderResourceManager : public IResourceManager
{
public:
	void init(std::string&& mainPath) override;
	const std::shared_ptr<Engine::ShaderProgram> const loadShaderProgram(std::string&& nameOfShaderProgram,
																 std::string&& vertexPath,
																 std::string&& fragmentPath);
	static const unsigned int getTableNumber()  { return m_tableNumber; }
private:
	std::string getFileString(std::string&& AdditionalPath);
	std::string m_path;

	static const unsigned int m_tableNumber = 0;

	using shaders_map = std::map<std::string, std::shared_ptr<Engine::ShaderProgram>>;
	shaders_map m_shadersMap;
};

