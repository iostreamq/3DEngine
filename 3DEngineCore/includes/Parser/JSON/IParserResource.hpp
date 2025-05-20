#pragma once
#include <Descriptors/IDescriptor.hpp>
#include <string>

class IJSONParserResource
{
public:
	virtual ~IJSONParserResource() = default;
	virtual bool parse(const std::string& strToParse) = 0;
};