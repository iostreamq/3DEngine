#pragma once
#include <cstdint>
#include <vector>
#include <string>

class IFileLoader
{
public:
	virtual ~IFileLoader() = default;
	virtual std::vector<uint8_t> readBytes(std::string&& virtualPath) const = 0;
	virtual bool exists(std::string&&) = 0;
private:
	virtual std::string findNesseccaryPath(std::string&& virtualPath) const = 0;
};