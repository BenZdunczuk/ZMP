#include <iostream>
#include "Interp4Move.hh"
#include "ComInterface.hh"

using std::cout;
using std::endl;

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
bool Interp4Move::ExecCmd(AbstractScene &rScn,
                          const char *sMobObjName,
                          AbstractComChannel &rComChann)
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
    double time_step_us = (((double)distance / this->verticalSpeed) * 1000000) / N;

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
//     AbstractMobileObj * pObj = rScn.FindMobileObj(objectName.c_str());
//   if (!pObj) {
//         std::cerr << "[Interp4Move] Nie znaleziono obiektu: " << objectName.c_str() << "\n";
//         return false;
//     }

//     double speed_m_s = verticalSpeed;
//     double distance_m = distance;
//     double yaw_deg = pObj->GetAng_Yaw_deg();
//     double yaw_rad = yaw_deg * M_PI / 180.0;

//     Vector3D pos = pObj->GetPositoin_m();

//     double total_time_s = distance_m / speed_m_s;
//     const double step_time_s = 0.05;
//     int steps = static_cast<int>(total_time_s / step_time_s);

//     double step_dist = speed_m_s * step_time_s;

//     for (int i = 0; i < steps; ++i) {
//         pos[0] += step_dist * cos(yaw_rad);
//         pos[1] += step_dist * sin(yaw_rad);
//         pObj->SetPosition_m(pos);

//         std::ostringstream cmd;

//         rComChann.Send(cmd.str());

//         usleep(static_cast<useconds_t>(step_time_s * 1e6));
//     }

//     std::cout << "[Interp4Move] Zakończono ruch obiektu " << objectName.c_str() << "\n";
//     return true;
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