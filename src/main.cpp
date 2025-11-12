#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "parser.hh"
#include "pluginManager.hh"
#include "Configuration.hh"

#define PLUGIN_NAME__move "libInterp4Move.so"
#define PLUGIN_NAME__rotate "home/ben/ZMP/libs/libInterp4Rotate.so"
#define PLUGIN_NAME__set "./plugin/libInterp4Set.so"
#define PLUGIN_NAME__pause "libInterp4Pause.so"

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

  if (argc < 2)
  {
    cout << "No input file!" << endl;
    return 1;
  }

  // if (!p.ReadFile(argv[1], config))
  // {
  //   return 1;
  // }

  list<string> cmdList;
  // std::istringstream inputFile;

  // if (p.preprocessFile(argv[1]))
  // {
  //   std::cout << "preprocess file" << std::endl;
  //   return 1;
  // }

  std::string preprocessedFile = p.preprocessFile(argv[1]);
  std::ifstream file(preprocessedFile);
  if (!p.ReadCmd(file))
  {
    std::cout << "read file" << std::endl;
    return 1;
  }
}
