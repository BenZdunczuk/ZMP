#pragma once

#include <dlfcn.h>

#include <map>
#include <string>

#include "AbstractInterp4Command.hh"

/*!
 * \brief Klasa reprezentująca interfejs biblioteki dynamicznej.
 */
class LibInterface
{
private:
    /*!
     * \brief Uchwyt na załadowaną bilioteke.
     */
    void *pLibHandler;

    /*!
     * \brief Wskażnik na funkcję zwracająca nazwę biblioteki.
     */
    const char *(*CmdName)(void);

    /*!
     * \brief Wskaźnik na funkcję tworzący nową instancję klasy z biblioteki dynamicznej.
     */
    AbstractInterp4Command *(*pCreateCMD)(void);

public:
    /*!
     * \brief Konstruktor klasy LibInterface.
     */
    LibInterface();

    /*!
     * \brief Funkcja tworząca nową instancję klasy biblioteki dynamicznej.
     *
     * \return obiekt pochodny klasy AbstractInterp4Command.
     */
    AbstractInterp4Command *getCMD()
    {
        return this->pCreateCMD();
    }

    /*!
     * \brief Funkcja zwracająca nazwę biblioteki.
     *
     * \return nazwa biblioteki.
     */
    std::string getCMDName()
    {
        return this->CmdName();
    }

    /*!
     * \brief Funkcja inicjalizująca interfejs.
     *
     * \param filename - ścieżka do pliku z biblioteką dynamiczną.
     */
    bool init(const std::string &filename);

    /*!
     * \brief Standardowy destruktor klasy.
     */
    ~LibInterface()
    {
        if (!pLibHandler)
        {
            dlclose(pLibHandler);
        }
    }
};