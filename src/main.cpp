#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "parser.hh"
#include "libInterface.hh"

using namespace std;

#define PLUGIN_NAME__move "libInterp4Move.so"
#define PLUGIN_NAME__rotate "libInterp4Rotate.so"

int main(int argc, char *argv[])
{
  Parser parser;
  std::istringstream tmp;
  const char *name = "123";
  // parser.preprocessFile("name",tmp);

  void *pLibHnd_Move = dlopen(PLUGIN_NAME__move,RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);

  void *pLibHnd_Rotate = dlopen(PLUGIN_NAME__rotate,RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  void *pFun1;
  void *pFun2;


  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: " PLUGIN_NAME__move << endl;
    return 1;
  }

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: " PLUGIN_NAME__rotate << endl;
    return 1;
  }

  pFun1 = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun1) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pFun2 = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun2) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun1);
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun2);

  AbstractInterp4Command *pCmd1 = pCreateCmd_Move();
  AbstractInterp4Command *pCmd2 = pCreateCmd_Rotate();


  cout << endl;
  cout << pCmd1->GetCmdName() << endl;
  cout << endl;
  pCmd1->PrintSyntax();
  cout << endl;
  pCmd1->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmd2->GetCmdName() << endl;
  cout << endl;
  pCmd2->PrintSyntax();
  cout << endl;
  pCmd2->PrintCmd();
  cout << endl;
  
  delete pCmd1;
  delete pCmd2;

  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Rotate);

}
