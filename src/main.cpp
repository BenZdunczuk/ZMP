#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "parser.hh"
#include "pluginManager.hh"
#include "Configuration.hh"

#define PLUGIN_NAME__move "libInterp4Move.so"
#define PLUGIN_NAME__rotate "libInterp4Rotate.so"
#define PLUGIN_NAME__set "libInterp4Set.so"
#define PLUGIN_NAME__pause "libInterp4Pause.so"

using namespace std;

int main(int argc, char *argv[])
{

  list<string> pluginNameList = {
      PLUGIN_NAME__move,
      PLUGIN_NAME__rotate,
      PLUGIN_NAME__pause,
      PLUGIN_NAME__set};

  pluginManager manager;
  manager.init(pluginNameList);

  Parser p;
  Configuration config;

  if (argc < 2)
  {
    cout << "No input file!" << endl;
    return 1;
  }

  if (!p.ReadFile(argv[1],config)) {return 1;}
}
