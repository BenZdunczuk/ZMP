#include <dlfcn.h>
#include <iostream>
#include <string>

#include "AbstractInterp4Command.hh"
#include "libInterface.hh"

LibInterface::LibInterface()
    : pLibHandler(NULL)
{
}

bool LibInterface::init(const std::string &filename)
{
    this->pLibHandler = dlopen(filename.c_str(), RTLD_LAZY);

    if (!this->pLibHandler)
    {
        std::cerr << "LibInterface: Error: can't find following library: " + filename << std::endl;
        return false;
    }

    void *pFun;
    pFun = dlsym(this->pLibHandler, "CreateCmd");
    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no CreateCmd function found" << std::endl;
        return false;
    }
    this->pCreateCMD = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(this->pLibHandler, "GetCmdName");
    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no CreateCmd function found" << std::endl;
        return false;
    }

    if (!pFun)
    {
        std::cerr << "LibInterface: Error: no GetCmdName function found!" << std::endl;
        return false;
    }

    this->CmdName = reinterpret_cast<const char *(*)(void)>(pFun);

    return true;
}