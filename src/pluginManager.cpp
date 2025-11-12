#include "pluginManager.hh"

void pluginManager::init(std::list<std::string> lib_paths)
{
    for (const std::string &path : lib_paths)
    {
        std::shared_ptr<LibInterface> lib = std::make_shared<LibInterface>();

        std::cout << "Loading library " << path << std::endl;

        if (lib->init(path))
        {
            plugins[lib->getCMDName()] = lib;
        }
        else
        {
            std::cerr << "Error: Cannot load lib: " << path << std::endl;
        }
    }
}

std::shared_ptr<LibInterface> pluginManager::findPlugin(std::string cmdName){
    return plugins.find(cmdName)->second;
}
