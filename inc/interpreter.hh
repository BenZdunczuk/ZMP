#ifndef INTERPRETER_HH
#define INTERPRETER_HH

/*!
 * \file
 * \brief Zawiera definicję klasy interpreter
 *
 *  Klasa nadzoruje całą operacją interpretowania poleceń
 */

#include "pluginManager.hh"
#include "parser.hh"
#include "Configuration.hh"
#include "ComChannel.hh"
#include "ComInterface.hh"
#include "Scene.hh"

/*!
 * \brief Klasa reprezentująca interpreter poleceń
 *
 * Klasa nadzoruje całą operacją interpretowania poleceń
 */
class interpreter
{
private:
    /*!
     * \brief Manager wtyczek
     */
    pluginManager manager;

    /*!
     * \brief Klasa parsująca pliki wejściowe z komendami oraz z konfiguracją
     */
    Parser parser;

    /*!
     * \brief Klasa przechowująca konfigurację wczytaną z pliku xml
     */
    Configuration config;

    /*!
     * \brief Klasa reprezentująca scenę z listą obiektów
     */
    Scene scene;

    /*!
     * \brief Klasa reprezentująca połączenie z serwerem graficznym
     */
    ComChannel channel;

public:
    // interpreter() {}

    /*!
     * \brief Destruktor klasy, zwalnia połączenie z serwerem
     */
    ~interpreter();

    /*!
     * \brief Metoda otwierająca połączenie z serwerem
     */
    bool openConnection();

    /*!
     * \brief Metoda interpretująca polecenia
     *
     * Metoda wczytuje plik konfiguracyjny oraz plik z komendami i na bieżąco go interpretuje i wykonuje
     * 
     * \param[in] xmlFileName - ścieżka do pliku xml z konfiguracją
     * \param[in] cmdsFileName - ścieżka do pliku z komendami
     */
    bool interprete(const std::string xmlFileName, const std::string cmdsFileName);
};

#endif