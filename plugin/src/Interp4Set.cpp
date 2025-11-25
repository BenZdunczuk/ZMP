#include <iostream>

#include "ComInterface.hh"
#include "Interp4Set.hh"

using std::cout;
using std::endl;

extern "C"
{
    AbstractInterp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
    return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : objectName(" ")
{
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
    return ::GetCmdName();
}

const char *Interp4Set::GetObjName() const{
    return this->objectName.c_str();
}

bool Interp4Set::ExecCmd(AbstractScene &rScn,
                         const char *sMobObjName,
                         AbstractComChannel &rComChann)
{
    AbstractMobileObj *wObMob = rScn.FindMobileObj(this->objectName.c_str());

    if (wObMob == nullptr)
    {
        std::cerr << "Error: Object not found: " << this->objectName.c_str() << "\n";
        return false;
    }

    wObMob->LockAccess();

    wObMob->SetPosition_m(Vector3D(Xpos, Ypos, Zpos));
    wObMob->SetAng_Yaw_deg(Xrot);
    wObMob->SetAng_Roll_deg(Yrot);
    wObMob->SetAng_Roll_deg(Yrot);

    ComInterface interface(rComChann);

    std::cout << "123\n";
    if (!interface.UpdateObj(wObMob->GetName(), wObMob->GetPositoin_m(), Vector3D(wObMob->GetAng_Roll_deg(), wObMob->GetAng_Pitch_deg(), wObMob->GetAng_Yaw_deg())))
    {
        std::cerr << "Error: Failed to update object: " << wObMob->GetName() << "\n";
        wObMob->UnLockAccess();

        return false;
    }

    wObMob->UnLockAccess();

    return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
    if (!(Strm_CmdsList >> objectName))
    {
        std::cout << "Interp4Set: Error when loading objectName\n";
        return false;
    }

    if (!(Strm_CmdsList >> Xpos))
    {
        std::cout << "Interp4Set: Error when loading position on X axis\n";
        return false;
    }

    if (!(Strm_CmdsList >> Ypos))
    {
        std::cout << "Interp4Set: NError when loading position on Y axis\n";
        return false;
    }

    if (!(Strm_CmdsList >> Zpos))
    {
        std::cout << "Interp4Set: Error when loading position on Z axis\n";
        return false;
    }

    if (!(Strm_CmdsList >> Xrot))
    {
        std::cout << "Interp4Set: Error when rotation position on X axis\n";
        return false;
    }

    if (!(Strm_CmdsList >> Yrot))
    {
        std::cout << "Interp4Set: Error when loading rotation on Y axis\n";
        return false;
    }

    if (!(Strm_CmdsList >> Zrot))
    {
        std::cout << "Interp4Set: Error when loading rotation on Z axis\n";
        return false;
    }

    return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Set::CreateCmd()
{
    return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
    std::cout << "Set" << " object_name" << " Xpos" << " Ypos" << " Zpos" << " Xrot" << " Yrot" << " Zrot\n";
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
    cout << this->GetCmdName() << " " << objectName << " " << Xpos << " " << Ypos << " " << Zpos << " " << Xrot << " " << Yrot << " " << Zrot << "\n";
}