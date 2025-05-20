#pragma once
#include<System/FileSystem/IFileLoader.hpp>

class DiskFileLoader : public IFileLoader
{
public:
	DiskFileLoader(std::vector<std::string>&& paths)
		: m_paths(std::move(paths)) {}

	 std::vector<uint8_t> readBytes(std::string&& virtualPath) const override;
	 bool exists(std::string&& virtualPath)  override;

private:
	std::string findNesseccaryPath(std::string&& virtualPath) const override;
	std::vector<std::string> m_paths;
};