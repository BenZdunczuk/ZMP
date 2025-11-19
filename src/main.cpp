#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <cassert>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "AbstractInterp4Command.hh"
#include "parser.hh"
#include "pluginManager.hh"
#include "Configuration.hh"
#include "Port.hh"
#include "ComChannel.hh"

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
    cout << "Missing input file/files!" << endl;
    cout << "Usage: ./cmds_intepreter [config_file_path] [commands_file_path]" << endl;
    return 1;
  }

  if(p.ReadXMLFile(argv[1],config)){
    cout << "read xml config file successful" << endl;
  }

  string preprocessedFileName = p.preprocessFile(argv[2]);
  ifstream inputFileStrm(preprocessedFileName);
  if (p.ReadCmd(inputFileStrm))
  {
    cout << "read commands file successful" << endl;
  }

  struct sockaddr_in Server = {0};
  ComChannel channel;


  Server.sin_family = AF_INET;
  Server.sin_addr.s_addr = inet_addr("127.0.0.1");
  Server.sin_port = htons(PORT);

  int Socket = socket(AF_INET,SOCK_STREAM,0);

  if (Socket < 0) {
    throw std::runtime_error("Nie mogę otworzyć gniazda sieciowego!");
  }

  if (connect(Socket,(struct sockaddr*)&Server,sizeof(Server)) < 0)
   {
     throw std::runtime_error("Nie mogę połączyć się z serwerem!");
   }

  channel.Init(Socket);



  return 0;
}
