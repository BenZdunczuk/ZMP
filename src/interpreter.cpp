#include "interpreter.hh"
#include "mobileObj.hh"

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6217
#define address "127.0.0.1"

bool interpreter::openConnection()
{
    struct sockaddr_in Server = {0};

    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = inet_addr(address);
    Server.sin_port = htons(PORT);

    int _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket < 0)
    {
        std::cout << "Error: Loading socket failure\n";
        return false;
    }

    if (connect(_socket, (struct sockaddr *)&Server, sizeof(Server)) < 0)
    {
        std::cout << "Error: Server connection failure\n";
        return false;
    }

    this->channel.Init(_socket);
    return true;
}

bool interpreter::interprete(const std::string xmlFileName, const std::string cmdsFileName)
{
    if(!openConnection()){
        std::cout << "Interpreter: Connection failure\n";
        return false;
    }

    if (!parser.ReadXMLFile(xmlFileName, config))
    {
        std::cout << "Interpreter: Read commands file failure\n";
        return false;
    }

    manager.init(config.getPluginPath());

    ComInterface interface(this->channel);

    interface.Clear();

    for (const auto &obj : config.getObjects())
    {
        mobileObj *object = new mobileObj();

        object->SetName(obj.name.c_str());
        object->SetPosition_m(obj.trans);
        object->SetAng_Roll_deg(obj.rotation[0]);
        object->SetAng_Pitch_deg(obj.rotation[1]);
        object->SetAng_Yaw_deg(obj.rotation[2]);

        if (interface.AddObj(obj.name, obj.shift, obj.scale, obj.trans, obj.rotation, obj.color))
        {
            this->scene.AddMobileObj(object);
            std::cout << "Interpreter: Succesfully added object: " << obj.name << "\n";
        }
        else
        {
            std::cerr << "Interpreter: Failed to add object: " << obj.name << "\n";
        }
    }

    std::string preprocessedFileName = parser.preprocessFile(cmdsFileName);
    std::ifstream inputFileStrm(preprocessedFileName);

    if (!parser.ReadAndExecCmd(inputFileStrm,manager,scene,channel))
    {
        std::cout << "Interpreter: Read commands file failure\n";
        return false;
    }

    return true;
}

interpreter::~interpreter(){
    ComInterface interface(this->channel);
    interface.Close();
    close(this->channel.GetSocket());
}