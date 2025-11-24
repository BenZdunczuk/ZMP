#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <list>

#include "Configuration.hh"
#include "pluginManager.hh"
#include "ComChannel.hh"
#include "Scene.hh"

/*!
 * \brief Klasa wykorzystywana do wczytywania i rozpoznawania komend oraz konfiguracji z plików wejściowych.
 */
class Parser
{
public:
    /*!
     * \brief Konstruktor bezparametryczny.
     */
    Parser(){}
    
    /*!
     * \brief Funkcja do rozwijania makr i usuwania komentarzy z pliku wejściowego.
     *
     * \return Nazwa utworzonego nowego przepreprocessowanego pliku
     */
    std::string preprocessFile(const std::string &cmdsFileName);

    /*!
     * \brief Funkcja parsująca plik tekstowy z listą komend.
     *
     * \param[in] Config - obiekt przechowujący konfigurację
     * \param[in] Config - obiekt przechowujący konfigurację
     * 
     * \return Czy operacja się powiodła (tak - true, nie - false).
     */
    bool ReadCmd(std::istream &IStrm, pluginManager manager,Scene &scene,ComChannel &channel);

    /*!
     * \brief Funkcja parsująca plik xml z konfiguracją.
     *
     * \param[in] xmlFileName - nazwa(ścieżka) pliku xml z konfiguracją 
     * \param[in] Config - obiekt przechowujący konfigurację
     * 
     * \return Czy operacja się powiodła (tak - true, nie - false).
     */
    bool ReadXMLFile(const std::string xmlFileName, Configuration &Config);
};