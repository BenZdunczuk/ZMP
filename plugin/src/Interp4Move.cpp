#include <iostream>
#include "Interp4Move.hh"
#include "ComInterface.hh"
#include "Vector3D.hh"


using std::cout;
using std::endl;

#define N 100       //ile krokow
#define M 1000000    //czas jednego kroku w us

extern "C"
{
    AbstractInterp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
    return Interp4Move::CreateCmd();
}

/*!
 *
 */
AbstractInterp4Command *Interp4Move::CreateCmd()
{
    return new Interp4Move();
}

/*!
 *
 */
Interp4Move::Interp4Move() : verticalSpeed(0)
{
    // cout << "created move" << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
    return ::GetCmdName();
}

const char *Interp4Move::GetObjName() const{
    return this->objectName.c_str();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(AbstractScene &rScn,AbstractComChannel &rComChann)
{

    AbstractMobileObj *wObMob = rScn.FindMobileObj(this->objectName.c_str());

    if (wObMob == nullptr)
    {
        std::cerr << "Error: Object not found: " << this->objectName.c_str() << "\n";
        return false;
    }

    Vector3D startPos = wObMob->GetPositoin_m();
    double startRoll = wObMob->GetAng_Roll_deg();
    double startPitch = wObMob->GetAng_Pitch_deg();
    double startYaw = wObMob->GetAng_Yaw_deg();
    double delta_x_m, delta_y_m, delta_z_m;
    delta_x_m = delta_y_m = delta_z_m = 0;
    double dist_step_m = (double)distance / N;
    double time_step_us = (((double)distance / this->verticalSpeed) * M) / N;

    for (int i = 0; i < N; ++i)
    {
        wObMob->LockAccess();

        delta_x_m += dist_step_m * cos(startPitch * M_PI / 180) * cos(startYaw * M_PI / 180);
        delta_y_m += dist_step_m * (cos(startRoll * M_PI / 180) * sin(startYaw * M_PI / 180) + cos(startYaw * M_PI / 180) * sin(startPitch * M_PI / 180) * sin(startRoll * M_PI / 180));
        delta_z_m += dist_step_m * (sin(startRoll * M_PI / 180) * sin(startYaw * M_PI / 180) - cos(startRoll * M_PI / 180) * cos(startYaw * M_PI / 180) * sin(startPitch * M_PI / 180));
        wObMob->SetPosition_m(Vector3D(delta_x_m + startPos[0], delta_y_m + startPos[1], delta_z_m + startPos[2]));

        {
            ComInterface interface(rComChann);

            if (!interface.UpdateObj(wObMob->GetName(), wObMob->GetPositoin_m(), Vector3D(wObMob->GetAng_Roll_deg(), wObMob->GetAng_Pitch_deg(), wObMob->GetAng_Yaw_deg())))
            {
                std::cerr << "Error: Failed to update object: " << wObMob->GetName() << "\n";
                wObMob->UnLockAccess();

                return false;
            }
        }

        wObMob->UnLockAccess();

        usleep(time_step_us);
    }

    return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
    if (!(Strm_CmdsList >> objectName))
    {
        std::cout << "Interp4Move: Error when loading objectName" << "\n";
        return false;
    }

    if (!(Strm_CmdsList >> verticalSpeed))
    {
        std::cout << "Interp4Move: Error when loading verticalSpeed" << "\n";
        return false;
    }

    if (!(Strm_CmdsList >> distance))
    {
        std::cout << "Interp4Move: Error when loading distance" << "\n";
        return false;
    }

    return true;
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
    cout << "Move" << " Object_name" << " Speed[m/s]" << " Distance[m]\n";
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
    cout << GetCmdName() << " " << objectName << "  " << verticalSpeed << " " << distance << "\n";
}