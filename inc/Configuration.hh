#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <list>
#include "AbstractMobileObj.hh"
#include "Vector3D.hh"

#include "ConfigurationCuboid.hh"

/*!
 * \brief Klasa przechowująca konfigurację załadowaną z pliku XML.
 * Klasa przechowująca konfigurację załadowaną z pliku XML.
 */
class Configuration
{

    /*!
     * \brief Lista z załadowanymi ścieżkami do pluginów.
     * Lista z załadowanymi ścieżkami do pluginów.
     */
    std::list<std::string> pluginPaths;

    /*!
     * \brief Lista z załadowanymi parametrami obiektów sceny Cuboid.
     * Lista z załadowanymi parametrami obiektów sceny Cuboid.
     */
    std::list<ConfigurationCuboid> objects;

public:
    /*!
     * \brief Funkcja dodająca ścieżkę do pluginu.
     * Funkcja dodająca ścieżkę do pluginu.
     */
    void addPluginPath(const std::string &path)
    {
        this->pluginPaths.push_back(path);
    }

    /*!
     * \brief Funkcja zwracająca referencję na listę z ścieżkami do pluginu.
     * Funkcja zwracająca referencję na listę z ścieżkami do pluginu.
     *
     * \return stała referencja na listę ścieżek z pluginami.
     */
    const std::list<std::string> &getPluginPath() const
    {
        return this->pluginPaths;
    }

    /*!
     * \brief Funkcja dodająca konfigurację obiektu Cuboid.
     * Funkcja dodająca konfigurację obiektu Cuboid.
     */
    void addObject(const ConfigurationCuboid &obj)
    {
        this->objects.push_back(obj);
    }

    /*!
     * \brief Funkcja zwracająca referencję na listę z konfiguracją obiektów Cuboid.
     * Funkcja zwracająca referencję na listę z konfiguracją obiektów Cuboid.
     *
     * \return stała referencja na listę z konfiguracją obiektów Cuboid.
     */
    const std::list<ConfigurationCuboid> &getObjects() const
    {
        return this->objects;
    }
};

#endif
