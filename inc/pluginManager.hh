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
    /*!
     * \brief Aktualnie wykorzystywany (wczytywany/używany) plugin
     */
    AbstractInterp4Command *activePlugin;

    public:
    /*!
     * \brief Metoda zwracająca aktualny plugin
     *
     * \return wskażnik na plugin
     */
    AbstractInterp4Command *getActivePlugin(){
        return activePlugin;
    }

    /*!
     * \brief Metoda aktualizująca aktualny plugin
     *
     * \param[in] plugin - wskażnik na nowy aktywny plugin
     */
    void setActivePlugin(AbstractInterp4Command *plugin){
        activePlugin = plugin;
    }

    /*!
     * \brief Kolekcja bibliotek dynamicznych z poleceniami w parach nazwa polecenia - wskaźnik na interfejs biblioteki.
     */
    std::map<std::string, std::shared_ptr<LibInterface>> plugins;

    /*!
     * \brief Metoda szukająca pluginu po nazwie
     *
     * \return wskażnik na plugin w przypadku znalezienia lub nullptr w przypadku braku dopasowania
     */
    std::shared_ptr<LibInterface> findPlugin(std::string cmdName);

    /*!
     * \brief Funkcja inicjalizująca zestaw bibliotek.
     *
     * \param lib_paths lista ze ścieżkami do bibliotek
     */
    void init(std::list<std::string> lib_paths);
};