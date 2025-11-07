#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "parser.hh"
// #include "libInterface.hh"
#include "pluginManager.hh"

using namespace std;

#define PLUGIN_NAME__move "libInterp4Move.so"
#define PLUGIN_NAME__rotate "libInterp4Rotate.so"
#define PLUGIN_NAME__set "libInterp4Set.so"
#define PLUGIN_NAME__pause "libInterp4Pause.so"


int main(int argc, char *argv[])
{
  // Parser parser;
  // std::istringstream tmp;
  // const char *name = "123";
  // parser.preprocessFile("name",tmp);

  // LibInterface
  list<string> pluginNameList = {PLUGIN_NAME__move, PLUGIN_NAME__rotate, PLUGIN_NAME__pause, PLUGIN_NAME__set};

  pluginManager manager;
  manager.init(pluginNameList);

  // void *pLibHnd_Move = dlopen(PLUGIN_NAME__move,RTLD_LAZY);
  // AbstractInterp4Command *(*pCreateCmd_Move)(void);

  // void *pLibHnd_Rotate = dlopen(PLUGIN_NAME__rotate,RTLD_LAZY);
  // AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  // void *pLibHnd_Pause = dlopen(PLUGIN_NAME__pause,RTLD_LAZY);
  // AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  // void *pLibHnd_Set = dlopen(PLUGIN_NAME__set,RTLD_LAZY);
  // AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  // void *pFunMove;
  // void *pFunRotate;
  // void *pFunPause;
  // void *pFunSet;


  // if (!pLibHnd_Move) {
  //   cerr << "Error: " PLUGIN_NAME__move << endl;
  //   return 1;
  // }

  // if (!pLibHnd_Rotate) {
  //   cerr << "!!! Brak biblioteki: " PLUGIN_NAME__rotate << endl;
  //   return 1;
  // }

  // if (!pLibHnd_Pause) {
  //   cerr << "!!! Brak biblioteki: " PLUGIN_NAME__rotate << endl;
  //   return 1;
  // }

  // if (!pLibHnd_Set) {
  //   cerr << "!!! Brak biblioteki: " PLUGIN_NAME__rotate << endl;
  //   return 1;
  // }

  // pFunMove = dlsym(pLibHnd_Move,"CreateCmd");
  // if (!pFunMove) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pFunRotate = dlsym(pLibHnd_Rotate,"CreateCmd");
  // if (!pFunRotate) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun1);
  // pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun2);

  // AbstractInterp4Command *pCmd1 = pCreateCmd_Move();
  // AbstractInterp4Command *pCmd2 = pCreateCmd_Rotate();


  // cout << endl;
  // cout << pCmd1->GetCmdName() << endl;
  // cout << endl;
  // pCmd1->PrintSyntax();
  // cout << endl;
  // pCmd1->PrintCmd();
  // cout << endl;

  // cout << endl;
  // cout << pCmd2->GetCmdName() << endl;
  // cout << endl;
  // pCmd2->PrintSyntax();
  // cout << endl;
  // pCmd2->PrintCmd();
  // cout << endl;
  
  // delete pCmd1;
  // delete pCmd2;

  // dlclose(pLibHnd_Move);
  // dlclose(pLibHnd_Rotate);

}
