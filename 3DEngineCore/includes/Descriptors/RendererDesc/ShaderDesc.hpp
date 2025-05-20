#pragma once
#include <Descriptors/IDescriptor.hpp>
#include <string>

struct ShaderDesc : public IDescriptor
{
    ShaderDesc(const unsigned int& _AmountOfStr, std::string&& _sourceCode )
        : AmountOfStr(_AmountOfStr), sourceCode(_sourceCode)
    {}

    unsigned int AmountOfStr;
    std::string sourceCode;
};