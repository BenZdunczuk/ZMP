#include "ComInterface.hh"

ComInterface::ComInterface(AbstractComChannel &_channel)
    : channel(_channel)
{
    this->channel.LockAccess();
}

bool ComInterface::AddObj(const std::string &name, const Vector3D &shift, const Vector3D &scale, const Vector3D &trans, const Vector3D &rotXYZ, const Vector3D &RGB)
{
    std::string msg;

    std::ostringstream strWe;

    strWe << "AddObj Name=" << name << " Shift=" << shift << " Scale=" << scale << " Trans_m=" << trans << " RGB=" << RGB << " RotXYZ_deg=" << rotXYZ;

    msg = strWe.str();

    const int socket = this->channel.GetSocket();

    std::cout << "Sending: " << msg << "\n";

    if (write(socket, msg.c_str(), msg.length()) != msg.length())
    {
        return false;
    }

    return true;
}

bool ComInterface::UpdateObj(const std::string &name, const Vector3D &trans, const Vector3D &rotXYZ)
{
    std::string msg;

    std::ostringstream strWe;

    strWe << "UpdateObj Name=" << name << " Trans_m=" << trans << " RotXYZ_deg=" << rotXYZ << "\n";

    msg = strWe.str();

    std::cout << "Sending: " << msg << "\n";

    const int socket = this->channel.GetSocket();

    if (write(socket, msg.c_str(), msg.length()) != msg.length())
    {
        return false;
    }

    return true;
}

bool ComInterface::Clear()
{
    const char *msg = "Clear \n";

    const int socket = this->channel.GetSocket();

    if (write(socket, msg, strlen(msg)) != strlen(msg))
    {
        return false;
    }

    return true;
}

bool ComInterface::Close()
{
    const char *msg = "Close \n";

    const int socket = this->channel.GetSocket();

    if (write(socket, msg, strlen(msg)) != strlen(msg))
    {
        return false;
    }

    return true;
}