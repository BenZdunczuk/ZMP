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

/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{

  AbstractMobileObj* wObMob = rScn.FindMobileObj(this->objectName.c_str());

    if( wObMob == nullptr )
    {
        std::cerr<<"Nie mogę znaleźć obiektu: "<<this->objectName.c_str()<<std::endl;
        return false;
    }


  Vector3D startPos = wObMob->GetPositoin_m();
    double startRoll = wObMob->GetAng_Roll_deg();
    double startPitch = wObMob->GetAng_Pitch_deg();
    double startYaw = wObMob->GetAng_Yaw_deg();
    double delta_x_m, delta_y_m, delta_z_m;
    delta_x_m = delta_y_m = delta_z_m = 0;
    double dist_step_m = (double)distance/N;
    double time_step_us = (((double)distance/this->verticalSpeed)*1000000)/N;

    for(int i = 0; i<N; ++i)
    {
        wObMob->LockAccess();
  
        delta_x_m += dist_step_m*cos(startPitch*M_PI/180)*cos(startYaw*M_PI/180);
        delta_y_m += dist_step_m*(cos(startRoll*M_PI/180)*sin(startYaw*M_PI/180) + cos(startYaw*M_PI/180)*sin(startPitch*M_PI/180)*sin(startRoll*M_PI/180));
        delta_z_m += dist_step_m*(sin(startRoll*M_PI/180)*sin(startYaw*M_PI/180) - cos(startRoll*M_PI/180)*cos(startYaw*M_PI/180)*sin(startPitch*M_PI/180));
        wObMob->SetPosition_m(Vector3D(delta_x_m+startPos[0], delta_y_m+startPos[1], delta_z_m+startPos[2]));

        {
          ComInterface interface(rComChann);

          // send to server

          if(!interface.UpdateObj(wObMob->GetName(),wObMob->GetPositoin_m(),Vector3D(wObMob->GetAng_Roll_deg(),wObMob->GetAng_Pitch_deg(),wObMob->GetAng_Yaw_deg())))
          {
            std::cerr<<"Failed to update object: "<<wObMob->GetName()<<std::endl;
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
    std::cout << "Interp4Move: Error when loading objectName" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> verticalSpeed))
  {
    std::cout << "Interp4Move: Error when loading verticalSpeed" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> distance))
  {
    std::cout << "Interp4Move: Error when loading distance" << std::endl;
    return false;
  }

  return true;
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "Move" << " Object_name" << " Speed[m/s]" << " Distance[m]" << endl;
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << objectName << "  " << verticalSpeed << " " << distance << endl;
}