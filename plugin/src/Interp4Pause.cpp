#include <iostream>

#include "Interp4Pause.hh"

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}


Interp4Pause::Interp4Pause():  pauseTime(0)
{
}

Interp4Pause::~Interp4Pause()
{

}

AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}



void Interp4Pause::PrintCmd() const
{
   std::cout <<"    " <<this->GetCmdName() << " " << pauseTime << std::endl;
}


void Interp4Pause::PrintSyntax() const
{
    /*Wyswietl skladnie polecenia*/
    std::cout << "    Pause time[s]" << std::endl;
}


const char* Interp4Pause::GetCmdName() const
{
    /*Wyswietla nazwe polecenia*/
    return "Pause";
}

bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann )
{
    
    return true;
}

bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
    if(!(Strm_CmdsList >> pauseTime))
    {
        std::cerr << "Interp4Pause: Niepoprawnie wczytano czas zatrzymania"<< std::endl;
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

void Interp4Pause::PrintSyntax() const
{
    std::cerr<<"Czas: "<<pauseTime <<" ms"<<std::endl;   
}