#include <System/FileSystem/DiskFileLoader.hpp>
#include "fstream"
#include <3DEngineCore/Log.hpp>
#include <filesystem>

std::vector<uint8_t> DiskFileLoader::readBytes(std::string&& virtualPath) const
{
    std::string& thePath = findNesseccaryPath(std::move(virtualPath));
    if (!thePath.empty())
    {
        std::ifstream file(thePath.c_str(), std::ios::binary);
        if (file.is_open())
        {
            return { std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>() };
        }

        else { LOG_CRIT("Can`t open the file: {}", thePath); return std::vector<uint8_t>(); }
    }

    else { LOG_CRIT("Path is empty: {}", thePath); return std::vector<uint8_t>(); }
}

bool DiskFileLoader::exists(std::string&& virtualPath)
{
    if (!virtualPath.empty())
    {
        if (!findNesseccaryPath(std::move(virtualPath)).empty()) return true;
        else return false;
    }

    LOG_CRIT("Function \"exists\": virtual path is empty!");
    return false;
}

std::string DiskFileLoader::findNesseccaryPath(std::string&& virtualPath) const
{
    if (!virtualPath.empty())
    {
        for (const auto& currentPath : m_paths)
        {
            std::string& path = currentPath + virtualPath;
            if (std::filesystem::exists(path))
                return path;
            else continue;
        }
        LOG_CRIT("Transmitted path doesn`t exist {}", std::move(virtualPath));
        return std::string();
    }

    else { LOG_CRIT("Function \"findNesseccaryPath\": the path is empty - {}", std::move(virtualPath)); return std::string(); }

}
