#include <iostream>
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

// /*!
//  *
//  */
// Interp4Set::Interp4Set() : verticalSpeed(0)
// {
// }

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
   cout <<this->GetCmdName() <<" "<<objectName<<" "<<Xpos<<" "<<Ypos<<" "<<Zpos<<" "<<Xrot<<" "<<Yrot<<" "<<Zrot<<endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(AbstractScene &rScn,
                          const char *sMobObjName,
                          AbstractComChannel &rComChann)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> objectName))
  {
    std::cout << "Interp4Set: Error when loading objectName" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Xpos))
  {
    std::cout << "Interp4Set: Error when loading position on X axis" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Ypos))
  {
    std::cout << "Interp4Set: NError when loading position on Y axis" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Zpos))
  {
    std::cout << "Interp4Set: Error when loading position on Z axis" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Xrot))
  {
    std::cout << "Interp4Set: Error when rotation position on X axis" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Yrot))
  {
    std::cout << "Interp4Set: Error when loading rotation on Y axis" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> Zrot))
  {
    std::cout << "Interp4Set: Error when loading rotation on Z axis" << std::endl;
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
    std::cout << "Set " << objectName << " Xpos:" << Xpos << " Ypos:" << Ypos << " Zpos:" << Zpos 
    << " Xrot" << Xrot << " Yrot" << Yrot << " Zrot" << Zrot << std::endl;
}