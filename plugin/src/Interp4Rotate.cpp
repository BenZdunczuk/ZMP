#include <iostream>
#include "Interp4Rotate.hh"
#include "ComInterface.hh"

#define N 100       //ile krokow
#define M 1000000    //czas jednego kroku w us

using std::cout;
using std::endl;

extern "C"
{
    AbstractInterp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Rotate"; }
}

AbstractInterp4Command *CreateCmd(void)
{
    return Interp4Rotate::CreateCmd();
}

AbstractInterp4Command *Interp4Rotate::CreateCmd()
{
    return new Interp4Rotate();
}

Interp4Rotate::Interp4Rotate() : objectName(" "), angularSpeed(0), axisName(" ")
{
}

const char *Interp4Rotate::GetCmdName() const
{
    return ::GetCmdName();
}

const char *Interp4Rotate::GetObjName() const{
    return this->objectName.c_str();
}

bool Interp4Rotate::ExecCmd(AbstractScene &rScn,AbstractComChannel &rComChann)
{

    AbstractMobileObj *wObMob = rScn.FindMobileObj(this->objectName.c_str());

    if (wObMob == nullptr)
    {
        std::cerr << "Error: Object not found: " << this->objectName.c_str() << "\n";
        return false;
    }

    if (this->axisName == "OX")
    {
        double start = wObMob->GetAng_Roll_deg();
        double delta_deg = 0;
        double dist_step_deg = (double)angle / N;
        double time_step_us = ((abs((double)this->angle / this->angularSpeed)) * M) / N;

        for (int i = 0; i < N; ++i)
        {
            wObMob->LockAccess();
            delta_deg += dist_step_deg;
            wObMob->SetAng_Roll_deg(delta_deg + start);

            {
                ComInterface interface(rComChann);

                if (!interface.UpdateObj(wObMob->GetName(),wObMob->GetPositoin_m(),Vector3D(wObMob->GetAng_Roll_deg(),wObMob->GetAng_Pitch_deg(),wObMob->GetAng_Yaw_deg())))
                {
                    std::cerr << "Error: Failed to update object: " << wObMob->GetName() << "\n";
                    wObMob->UnLockAccess();

                    return false;
                }
            }

            wObMob->UnLockAccess();

            usleep(time_step_us);
        }
    }
    else if (this->axisName == "OY")
    {

        double start = wObMob->GetAng_Pitch_deg();
        double delta_deg = 0;
        double dist_step_deg = (double)angle / N;
        double time_step_us = (abs(((double)this->angle / this->angularSpeed)) * M) / N;

        for (int i = 0; i < N; ++i)
        {
            wObMob->LockAccess();
            delta_deg += dist_step_deg;
            wObMob->SetAng_Pitch_deg(delta_deg + start);

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
    }
    else if (this->axisName == "OZ")
    {
        double start = wObMob->GetAng_Yaw_deg();
        double delta_deg = 0;
        double dist_step_deg = (double)angle / N;
        double time_step_us = ((abs((double)this->angle / this->angularSpeed) * M)) / N;

        for (int i = 0; i < N; ++i)
        {
            wObMob->LockAccess();
            delta_deg += dist_step_deg;
            wObMob->SetAng_Yaw_deg(delta_deg + start);

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
    }

    return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
    if (!(Strm_CmdsList >> objectName))
    {
        std::cerr << "Interp4Rotate: Error when loading objectName\n";
        return false;
    }
    if (!(Strm_CmdsList >> axisName))
    {
        std::cerr << "Interp4Rotate: Error when loading axis name\n";
        return false;
    }
    if (!(Strm_CmdsList >> angularSpeed))
    {
        std::cerr << "Interp4Rotate: Error when loading angularSpeed\n";
        return false;
    }
    if (!(Strm_CmdsList >> angle))
    {
        std::cerr << "Interp4Rotate: Error when loading angle\n";
        return false;
    }
    return true;
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
    cout << "Rotate " << "object_name" << " Axis" << " Angular_speed[degrees/s]" << " Rotation_angle[degrees]\n";
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
    cout << GetCmdName() << " " << objectName << " " << axisName << " " << angularSpeed << " " << angle << "\n";
}