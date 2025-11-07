#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
AbstractInterp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

// /*!
//  *
//  */
// Interp4Rotate::Interp4Rotate() : angularSpeed(0)
// {
// }

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << objectName << " " << angularSpeed << " " << axisName << " " << angle << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn,
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
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> objectName))
  {
    std::cerr << "Interp4Rotate: Error when loading objectName" << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> axisName))
  {
    std::cerr << "Interp4Rotate: Error when loading axis name" << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> angularSpeed))
  {
    std::cerr << "Interp4Rotate: Error when loading angularSpeed" << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> angle))
  {
    std::cerr << "Interp4Rotate: Error when loading angle" << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "Rotate " << objectName << " Axis: " << axisName << " Angular speed[degrees/s]: " << angularSpeed << " Rotation angle[degrees]: " << angle << endl;
}
