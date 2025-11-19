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
 *  Zawiera definicję klasy Scene.
 *  Przechowującej obiekty sceny.
 */

/*!
 * \brief Definiuje klase modelującej scenę roboczą.
 *
 * Definiuje klase modelującej scenę roboczą,
 * która zawiera kolekcję obiektów mobilnych.
 */
class Scene : public AbstractScene
{

    /*!
     * \brief Mapa przechowująca obiekty wraz z ich nazwą.
     */
    std::map<std::string, AbstractMobileObj *> _objects;

    std::mutex lock;

public:
    ~Scene();

    /*!
     * \brief Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
     *
     *  Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
     *  \param[in] sName - pełna kwalifikowana nazwa obiektu.
     *  \return Jeśli obiekt zostanie znaleziony, to zwracany jest wskaźnik
     *          na niego. W przypadku przeciwnym zwracany jest wskaźnik \p nullptr.
     */
    AbstractMobileObj *FindMobileObj(const char *sName);
    /*!
     * \brief Dodaje do sceny nowy obiekt.
     *
     *  Dodaje do sceny nowy obiekt. Obiekt ten musi mieć poprawnie
     *  skonstruowaną pełną kwalifikowaną nazwę.
     *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
     */
    void AddMobileObj(AbstractMobileObj *pMobObj);
};
