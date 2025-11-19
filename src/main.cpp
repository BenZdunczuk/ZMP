#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "parser.hh"
#include "pluginManager.hh"
#include "Configuration.hh"

#define PLUGIN_NAME__move "./plugin/libInterp4Move.so"
#define PLUGIN_NAME__rotate "./plugin/libInterp4Rotate.so"
#define PLUGIN_NAME__set "./plugin/libInterp4Set.so"
#define PLUGIN_NAME__pause "./plugin/libInterp4Pause.so"

using namespace std;

int main(int argc, char **argv){

  list<string> pluginNameList = {
    PLUGIN_NAME__move,
    PLUGIN_NAME__rotate,
    PLUGIN_NAME__pause,
    PLUGIN_NAME__set
  };

  pluginManager manager;
  manager.init(pluginNameList);

  Parser p(manager);
  Configuration config;

  if (argc < 3)
  {
    cout << "No input file!" << endl;
    return 1;
  }

  std::string preprocessedFileName = p.preprocessFile(argv[1]);
  std::ifstream inputFileStrm(preprocessedFileName);
  if (p.ReadCmd(inputFileStrm))
  {
    std::cout << "read file successful" << std::endl;
  }

  if(p.ReadXMLFile(argv[2],config)){
    std::cout << "read xml config file successful" << std::endl;
  }

  return 0;
}
