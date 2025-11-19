#include <iostream>
#include <unistd.h>

#include "ComInterface.hh"
#include "Interp4Pause.hh"

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}

/*!
 *
 */
AbstractInterp4Command *Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return new Interp4Pause();
}


Interp4Pause::Interp4Pause() : pauseTime(0)
{
}

const char *Interp4Pause::GetCmdName() const
{
  /*Wyswietla nazwe polecenia*/
  return "Pause";
}

bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann )
{

    usleep(pauseTime*1000);
    
    return true;
}

bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
  // if (!(Strm_CmdsList >> objectName))
  // {
  //   std::cerr << "Interp4Pause: Error when loading objectName" << std::endl;
  //   return false;
  // }
  if (!(Strm_CmdsList >> pauseTime))
  {
    std::cerr << "Interp4Pause: Error when loading pauseTime" << std::endl;
    return false;
  }

  return true;
}

void Interp4Pause::PrintSyntax() const
{
  // std::cout << "Object name: " << objectName << " Stop time[s]: " << pauseTime << std::endl;
  std::cout << "Pause" << " Stop_time[s]" << std::endl;
}

void Interp4Pause::PrintCmd() const
{
  std::cout << GetCmdName() << " " << objectName << " " << pauseTime << std::endl;
}