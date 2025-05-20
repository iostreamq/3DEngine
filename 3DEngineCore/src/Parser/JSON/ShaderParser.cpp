#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <3DEngineCore/Log.hpp>
#include <Parser/JSON/ShaderParser.hpp>

    bool ShaderParser::parse(const std::string& strToParse)
    {   

        if (strToParse.empty())
        {
            LOG_CRIT("No resources to parse: {} ", strToParse);
            return false;
        }

        rapidjson::Document document;
        rapidjson::ParseResult parseResult = document.Parse(strToParse.c_str());
        if (!parseResult)
        {
            LOG_CRIT("JSON parse error: {} \"{}\" \n in JASON`s file: {} ",
                rapidjson::GetParseError_En(parseResult.Code()), parseResult.Offset(), strToParse);
            return false;
        }

        else
        {
            auto shaderIt = document.FindMember("shaders");

            for (const auto& currentShader : shaderIt->value.GetArray())
            {
                const auto& path = currentShader["PathSourceCode"].GetString();
                std::string nesseccaryStr = getFileString(path);
                m_shaderDescriptorsMap[currentShader["name"].GetString()] = 
                std::make_shared<ShaderDesc>(1, std::move(nesseccaryStr));
            }
            return true;
        }
    }

    std::shared_ptr<ShaderDesc> ShaderParser::getDescriptor(const std::string& name)
    {
        const auto& itDesc = m_shaderDescriptorsMap.find(name);
        if (itDesc != m_shaderDescriptorsMap.end() && itDesc->second)
        {
            return itDesc->second;
        }

        else { LOG_CRIT("The descriptor : {} hasn`t found", name); 
               return std::shared_ptr<ShaderDesc>();}
        
    }

    std::string ShaderParser::getFileString(const std::string & path)
    {
        std::ifstream fileShader;
        fileShader.open(path, std::ifstream::in | std::ios_base::binary);
        if (!fileShader.is_open())
        {
            LOG_CRIT("Can`t open shader`s file");
            return "";
        }
        std::stringstream bufShader;
        bufShader << fileShader.rdbuf();
        return bufShader.str();
    }
