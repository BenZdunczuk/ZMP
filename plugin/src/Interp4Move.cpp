#include <iostream>
#include "Interp4Move.hh"

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
Interp4Move::Interp4Move() : verticalSpeed(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << verticalSpeed << " 10  2" << endl;
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
bool Interp4Move::ExecCmd(AbstractScene &rScn,
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
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> objectName))
  {
    std::cout << "Interp4Move: Niepoprawne wczytanie nazwy obiektu" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> verticalSpeed))
  {
    std::cout << "Interp4Move: Niepoprawne wczytanie prędkości obiektu" << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> distance))
  {
    std::cout << "Interp4Move: Niepoprawne wczytanie dystansu" << std::endl;
    return false;
  }

  return true;
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
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
