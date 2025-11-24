#include "pluginManager.hh"

void pluginManager::init(std::list<std::string> lib_paths)
{
    for (const std::string &path : lib_paths)
    {
        std::shared_ptr<LibInterface> lib = std::make_shared<LibInterface>();

        std::cout << "Loading library " << path << "\n";

        if (lib->loadPlugin(path))
        {
            plugins[lib->getCMDName()] = lib;
        }
        else
        {
            std::cerr << "Error: Cannot load lib: " << path << "\n";
        }
    }
}

std::shared_ptr<LibInterface> pluginManager::findPlugin(std::string cmdName)
{
    if(plugins.count(cmdName)){
        return plugins.at(cmdName);
    }
    return nullptr;
}
