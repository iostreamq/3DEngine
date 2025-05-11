#pragma once
#include<map>
#include<3DEngineCore/Log.hpp>
#include<ResourceManagement/IResourceManagementSystem.hpp>
#include<ResourceManagement/IResourceManager.hpp>
#include<ResourceManagement/ShaderResourceManager.hpp>


class ResourceManagementSystem : public IResourceManagementSystem
{
public:  
	ResourceManagementSystem()
	{
		get_RMS_map()[ResourceManagerType::Shader] = std::make_shared<ShaderResourceManager>();
	}
};