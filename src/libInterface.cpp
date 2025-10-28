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
    void *pFun;

    if (!this->pLibHandler)
    {
        std::cerr << "!!! Brak biblioteki: " + filename << std::endl;
        return false;
    }

    pFun = dlsym(this->pLibHandler, "CreateCmd");
    if (!pFun)
    {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
        return false;
    }
    this->pCreateCMD = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(this->pLibHandler, "GetCmdName");
    if (!pFun)
    {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
        return false;
    }

    if (!pFun)
    {
        std::cerr << "!!! Nie znalezino funkcji GetCmdName!" << std::endl;
        return false;
    }

    this->CmdName = reinterpret_cast<const char *(*)(void)>(pFun);

    return true;
}