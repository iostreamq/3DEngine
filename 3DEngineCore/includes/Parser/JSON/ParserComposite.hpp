#pragma once
#include <Parser/JSON/ShaderParser.hpp>
#include <Parser/JSON/MeshParser.hpp>
#include <3DEngineCore/Log.hpp>


class ParserComposite
{
public:
	enum class ParserType { Shader, Mesh };

	ParserComposite()
	{

		m_parsers[ParserType::Shader] = std::make_shared<ShaderParser>();
		m_parsers[ParserType::Mesh] = std::make_shared<MeshParser>();
	}
	
	template<typename parser>
	bool parse(const ParserType& parser_type, const std::string& strToParse)
	{
		const auto& itParser = m_parsers.find(parser_type);
		if (itParser != m_parsers.end() && !strToParse.empty())
		{
			const auto p_casted = std::dynamic_pointer_cast<parser>(itParser->second);
			if (p_casted)
			{
				if (p_casted->parse(strToParse)) return true;

				else {
					LOG_CRIT("Failed to parse! The str is - {}", strToParse);
					return false;
				}
			}

			else { LOG_CRIT("Can`t perform a down-cast!"); return false; }
		}
	}

	template<typename parser, typename desc_returnValue>
	desc_returnValue getNesseccaryDesc(const ParserType& parserT,const std::string& descName)
	{
		const auto& itParser = m_parsers.find(parserT);
		if (itParser != m_parsers.end() && !descName.empty())
		{
			const auto p_casted = std::dynamic_pointer_cast<parser>(itParser->second);
			if (p_casted)
			{
				const auto desc = p_casted->getDescriptor(descName);
				if (desc) return desc;
				else {
					LOG_CRIT("The desc {} hasn`t found!", std::move(descName));  return desc_returnValue();
				}
			}

			else { LOG_CRIT("Can`t perform a down-cast!"); return desc_returnValue(); }
		}

		return desc_returnValue();
	}

private:
	std::map<ParserType, std::shared_ptr<IJSONParserResource>> m_parsers;
};