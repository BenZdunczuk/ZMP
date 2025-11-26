#pragma once

#include <map>
#include <string>
#include <mutex>

#include "AbstractMobileObj.hh"
#include "AbstractScene.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Scene
 *
 *  Klasa przechowuje obiekty wyświetlane i przetwarzane na scenie.
 */

/*!
 * \brief Definiuje klasę modelującą scenę roboczą, która zawiera kolekcję obiektów mobilnych.
 */
class Scene : public AbstractScene
{

    /*!
     * \brief Mapa przechowująca obiekty wraz z ich nazwą.
     */
    std::map<std::string, AbstractMobileObj*> objects;

    /*!
     * \brief Muteks zarządzający dostępem do sceny
     */
    std::mutex lock;

public:
    ~Scene();

    /*!
     * \brief Wyszukuje obiekt o podanej nazwie.
     *
     *  \param[in] objName - nazwa obiektu.
     * 
     *  \return Wskaźnik na obiekt w przypadku znalezienia lub \p nullptr.
     */
    AbstractMobileObj *FindMobileObj(const char *objName);

    /*!
     * \brief Dodaje do sceny nowy obiekt.
     *
     *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
     */
    void AddMobileObj(AbstractMobileObj *pMobObj);
};
