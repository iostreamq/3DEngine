#pragma once
#include<string>

class IResourceManager
{
public:
	 virtual ~IResourceManager() = default;
	 virtual void init(std::string&& mainPath) = 0;
};	