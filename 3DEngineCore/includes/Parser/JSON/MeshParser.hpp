#pragma once
#include <memory>
#include <map>
#include <vector>

#include <Descriptors/RendererDesc/MeshDesc.hpp>
#include <Parser/JSON/IParserResource.hpp>


class MeshParser : public IJSONParserResource
{
public:
    bool parse(const std::string& strToParse) override;
    std::vector<std::shared_ptr<MeshDesc>> getDescriptor(std::string&& name);
private:
    std::map<std::string, std::vector<std::shared_ptr<MeshDesc>>> m_meshDescriptorsMap;
};
