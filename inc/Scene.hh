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
    std::map<std::string, AbstractMobileObj *> objects;

    std::mutex lock;

public:
    ~Scene();

    /*!
     * \brief Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
     *
     *  \param[in] objName - pełna kwalifikowana nazwa obiektu.
     *  \return Jeśli obiekt zostanie znaleziony, to zwracany jest wskaźnik
     *          na niego. W przypadku przeciwnym zwracany jest wskaźnik \p nullptr.
     */
    AbstractMobileObj *FindMobileObj(const char *objName);

    /*!
     * \brief Dodaje do sceny nowy obiekt.
     *
     *  Nowy obiekt musi mieć poprawnie skonstruowaną pełną nazwę.
     * 
     *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
     */
    void AddMobileObj(AbstractMobileObj *pMobObj);
};
