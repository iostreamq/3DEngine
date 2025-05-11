#pragma once
#include<memory>

class IResourceManager;
class IResourceManagementSystem
{
public:
	virtual ~IResourceManagementSystem() = default;

	enum class ResourceManagerType
	{
		Shader
	};
	

    template<typename RM_type>
    const std::shared_ptr<RM_type> getNecessaryRM() 
    {
        const auto iter = m_mapRMS.find(static_cast<ResourceManagerType>(RM_type::getTableNumber()));
        if (iter != m_mapRMS.end()) {
            auto casted = std::dynamic_pointer_cast<RM_type>(iter->second);
            if (!casted) {
                LOG_CRIT("Failed to cast RM to target type!");
                throw std::runtime_error("Bad cast in getNecessaryRM");
            }
            return casted;
        }

        else {
            LOG_CRIT("Resource Manager not found!");
            throw std::runtime_error("Resource Manager not found in getNecessaryRM");
        }
    }


protected:
 std::map<ResourceManagerType, std::shared_ptr<IResourceManager>>& const get_RMS_map() { return m_mapRMS; }
 
private:                            
	using RMS_map = std::map<ResourceManagerType, std::shared_ptr<IResourceManager>>;
	RMS_map m_mapRMS;
};

