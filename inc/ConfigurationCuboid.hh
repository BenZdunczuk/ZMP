#pragma once

#include <string>

#include "Vector3D.hh"

/*!
* \brief Struktura z konfiguracją obiektu typu Cuboid
* Struktura z konfiguracją obiektu typu Cuboid
*/
struct ConfigurationCuboid
{
    /*!
    * \brief Nazwa obiektu
    * Nazwa obiektu
    */
    std::string name = "";

    /*!
    * \brief Skala obiektu
    * Skala obiektu
    */
    Vector3D scale = Vector3D(1.f,1.f,1.f);
    /*!
    * \brief Obrót obiektu
    * Obrót obiektu
    */
    Vector3D rotation = Vector3D(0.f,0.f,0.f);
    /*!
    * \brief Pozycja obiektu
    * Pozycja obiektu
    */
    Vector3D trans = Vector3D(0.f,0.f,0.f);
    /*!
    * \brief Kolor obiektu
    * Kolor obiektu
    */
    Vector3D color = Vector3D(128,128,128);
    /*!
    * \brief Przesunięcie obiektu
    * Przesunięcie obiektu
    */
    Vector3D shift = Vector3D(0.f,0.f,0.f);   
};
