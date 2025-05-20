#pragma once
#include <fstream> 
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <3DEngineCore/Log.hpp>
#include <Parser/JSON/MeshParser.hpp>

bool MeshParser::parse(const std::string& strToParse)
{

    if (!strToParse.empty())
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
        auto meshIt = document.FindMember("Meshes");

        for (const auto& currentMesh : meshIt->value.GetArray())
        {
            auto& layoutArr = currentMesh["VBO_vertexCoordsLayout"].GetArray();
            for (auto& layout : layoutArr)
            {

                const auto& coordsJson = layout["coords"].GetArray();
                std::vector<float> coords;
                coords.reserve(coordsJson.Size());

                for (const auto& currrentCord : coordsJson) {
                    coords.push_back(currrentCord.GetFloat());
                }

                unsigned loc = layout["loc"].GetUint();
                int sz = layout["size"].GetInt();

                auto meshDesc = std::make_shared<MeshDesc>(std::move(coords), loc, sz);
                m_meshDescriptorsMap[currentMesh["name"].GetString()].push_back(meshDesc);
            }

            return true;
        }
    }
}

  std::vector<std::shared_ptr<MeshDesc>>MeshParser::getDescriptor(std::string&& name)
  {
      const auto& itDesc = m_meshDescriptorsMap.find(name);
      if (itDesc != m_meshDescriptorsMap.end() && !itDesc->second.empty())
      {
          return itDesc->second;
      }

      else {
          LOG_CRIT("The descriptor : {} hasn`t found"), std::move(name);
          return  std::vector<std::shared_ptr<MeshDesc>>();
      }

  }


