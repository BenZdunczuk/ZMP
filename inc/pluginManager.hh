#pragma once

#include <map>
#include <memory>
#include <string>
#include <list>

#include "AbstractInterp4Command.hh"

#include "libInterface.hh"

/*!
 * \brief Klasa przechowująca kolekcję bibliotek dynamicznych reprezentujące polecenia wykonywane przez program.
 * Klasa przechowująca kolekcję bibliotek dynamicznych reprezentujące polecenia wykonywane przez program.
 */
class pluginManager
{
    private:
    

    public:
    /*!
     * \brief Kolekcja bibliotek dynamicznych z poleceniami w parach nazwa polecenia - wskaźnik na interfejs biblioteki.
     */
    std::map<std::string, std::shared_ptr<LibInterface>> plugins;

    std::shared_ptr<LibInterface> findPlugin(std::string cmdName);

    AbstractInterp4Command *activePlugin;

    /*!
     * \brief Funkcja inicjalizująca zestaw bibliotek.
     *
     * \param lib_paths lista ze ścieżkami do bibliotek
     */
    void init(std::list<std::string> lib_paths);
};