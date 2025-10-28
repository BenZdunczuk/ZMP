#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <list>

/*!
* \brief Klasa wykorzystywana do wczytywania i rozpoznawania komend wejściowych
*/
class Parser
{
private:


public:
    /*!
    * \brief Funkcja parsująca plik wejściowy 
    */
    bool ReadCmdsList(std::istream &IStrm, std::list<std::string> &CmdLst);

    /*!
    * \brief Funkcja do rozwijania makr i usuwania komentarzy z pliku wejściowego
    */
    bool preprocessFile(const char *fileName, std::istringstream &stream);
};