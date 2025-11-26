#include "ComInterface.hh"

ComInterface::ComInterface(AbstractComChannel &_channel)
    : channel(_channel)
{
    // this->channel.LockAccess();
}

bool ComInterface::AddObj(const std::string &name, const Vector3D &shift, const Vector3D &scale, const Vector3D &trans, const Vector3D &rotXYZ, const Vector3D &RGB)
{
    std::string msg;

    std::ostringstream strWe;

    // this->channel.UnlockAccess();

    strWe <<"AddObj Name="<<name<<" RGB="<<RGB<<" Scale="<<scale<<" Shift="<<shift<<" RotXYZ_deg="<<rotXYZ<<" Trans_m="<<trans<<"\n";

    msg = strWe.str();

    const int socket = this->channel.GetSocket();

    // std::cout << "Sending: " << msg << "\n";

    if (write(socket, msg.c_str(), msg.length()) != msg.length())
    {
        std::cout << "Error: Adding Object failure! \n";
        // this->channel.LockAccess();
        return false;
    }

    // this->channel.LockAccess();
    return true;
}

bool ComInterface::UpdateObj(const std::string &name, const Vector3D &trans, const Vector3D &rotXYZ)
{
    std::string msg;

    std::ostringstream strWe;

    // this->channel.UnlockAccess();

    strWe <<"UpdateObj Name="<<name<<" Trans_m="<<trans<<" RotXYZ_deg="<<rotXYZ<<"\n";
    
    msg = strWe.str();

    // std::cout << "Sending: " << msg << "\n";

    const int socket = this->channel.GetSocket();

    if (write(socket, msg.c_str(), msg.length()) != msg.length())
    {
        std::cout << "Error: Updating Object failure! \n";
        // this->channel.LockAccess();
        return false;
    }

    // this->channel.LockAccess();
    return true;
}

bool ComInterface::Clear()
{
    const char *msg = "Clear \n";

    const int socket = this->channel.GetSocket();

    // this->channel.UnlockAccess();

    if (write(socket, msg, strlen(msg)) != strlen(msg))
    {
        // this->channel.LockAccess();
        return false;
    }

    // this->channel.LockAccess();
    return true;
}

bool ComInterface::Close()
{
    const char *msg = "Close \n";

    // this->channel.UnlockAccess();

    const int socket = this->channel.GetSocket();

    if (write(socket, msg, strlen(msg)) != strlen(msg))
    {
        // this->channel.LockAccess();
        return false;
    }

    // this->channel.LockAccess();
    return true;
}