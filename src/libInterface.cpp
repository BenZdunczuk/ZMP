#include <iostream>

#include "libInterface.hh"

LibInterface::LibInterface()
    : pLibHandler(NULL)
{
}

bool LibInterface::loadPlugin(const std::string &libName)
{
    std::string filename = "./plugin/" + libName;
    this->pLibHandler = dlopen(filename.c_str(), RTLD_LAZY);

    if (!this->pLibHandler)
    {
        std::cerr << "LibInterface: Error: can't find following library: " + filename << "\n";
        return false;
    }

    void *pFun;
    pFun = dlsym(this->pLibHandler, "CreateCmd");
    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no CreateCmd function found" << "\n";
        return false;
    }
    this->pCreateCMD = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(this->pLibHandler, "GetCmdName");
    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no CreateCmd function found" << "\n";
        return false;
    }

    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no GetCmdName function found!" << "\n";
        return false;
    }

    this->CmdName = reinterpret_cast<const char *(*)(void)>(pFun);

    return true;
}