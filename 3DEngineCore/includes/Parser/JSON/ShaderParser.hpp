#pragma once
#include <memory>
#include <map>

#include <Descriptors/RendererDesc/ShaderDesc.hpp>
#include <Parser/JSON/IParserResource.hpp>

class ShaderParser : public IJSONParserResource
{
public:
    bool parse(const std::string& strToParse) override;
    std::shared_ptr<ShaderDesc> getDescriptor(const std::string& name);

private:
    std::string getFileString(const std::string& path);
    std::map<std::string, std::shared_ptr<ShaderDesc>> m_shaderDescriptorsMap;
};
