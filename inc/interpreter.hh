#ifndef INTERPRETER_HH
#define INTERPRETER_HH

#include "pluginManager.hh"
#include "parser.hh"
#include "Configuration.hh"
#include "ComChannel.hh"
#include "ComInterface.hh"
#include "Scene.hh"

class interpreter
{
private:
    pluginManager manager;
    Parser parser;
    Configuration config;
    Scene scene;
    ComChannel channel;

public:
    interpreter() {}
    ~interpreter();

    bool openConnection();
    bool init(const std::string xmlFileName, const std::string cmdsFileName);
    bool exec();
};

#endif