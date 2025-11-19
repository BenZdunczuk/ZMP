#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <list>

// #include "libInterface.hh"
#include "Configuration.hh"
#include "pluginManager.hh"

/*!
 * \brief Klasa wykorzystywana do wczytywania i rozpoznawania komend wejściowych
 */
class Parser
{
private:
    pluginManager manager;

public:
    Parser(pluginManager pM) { manager = pM; }
    /*!
     * \brief Funkcja parsująca plik wejściowy
     */
    // bool ReadCmdsList(std::istream &IStrm, std::list<std::string> &CmdLst);

    /*!
     * \brief Funkcja do rozwijania makr i usuwania komentarzy z pliku wejściowego
     */
    std::string preprocessFile(const std::string &filename);

    bool ReadCmd(std::istream &IStrm);

    // bool ReadCmdMove(std::istream &IStrm, std::list<std::string> &CmdLst);
    // bool ReadCmdRotate(std::istream &IStrm, std::list<std::string> &CmdLst);
    // bool ReadCmdSet(std::istream &IStrm, std::list<std::string> &CmdLst);
    // bool ReadCmdPause(std::istream &IStrm, std::list<std::string> &CmdLst);

    bool ReadXMLFile(const char *sFileName, Configuration &rConfig);
};