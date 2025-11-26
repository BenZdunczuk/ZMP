#pragma once

/*!
 * \file
 * \brief Zawiera definicję klasy ComInterface
 *
 *  Klasa zapewniająca podstawowe polecenia dla serwera graficznego.
 */

#include <string>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ComChannel.hh"
#include "Vector3D.hh"

/*!
 * \brief Klasa zapewniająca podstawowe polecenia dla serwera graficznego.
 */
class ComInterface
{
    AbstractComChannel &channel;

public:
    /*!
     * \brief Konstruktor klasy
     *
     * Blokuje muteks kanału komunikacyjnego.
     * 
     * \param _channel - referencja na kanał komunikacyjny z serwerem.
     */
    ComInterface(AbstractComChannel &_channel);

    /*!
     * \brief Funkcja dodająca obiekt do serwera
     *
     * \param[in] shift - przesunięcie obiektu
     * \param[in] scale - skala obietku
     * \param[in] trans - pozycja obiektu
     * \param[in] rotXYZ - obrót obiektu względem kątów roll, pitch, yaw
     * \param[in] RGB - kolor obiektu
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool AddObj(const std::string &name, const Vector3D &shift, const Vector3D &scale, const Vector3D &trans, const Vector3D &rotXYZ, const Vector3D &RGB);

    /*!
     * \brief Funkcja aktualizująca parametry obiektu.
     *
     * \param[in] name - nazwa obiektu
     * \param[in] trans - pozycja obiektu
     * \param[in] rotXYZ - obrót obiektu względem osi roll, pitch, yaw
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool UpdateObj(const std::string &name, const Vector3D &trans, const Vector3D &rotXYZ);

    /*!
     * \brief Funkcja czyszcząca zawartość sceny serwera.
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool Clear();

    /*!
     * \brief Funkcja zamykająca połączenie z serwerem.
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool Close();

    /*!
     * \brief Funkcja zwalniająca muteks kanału komunikacyjnego.
     */
    void Release()
    {
        this->channel.UnlockAccess();
    }

    /*!
     * \brief Destruktor klasy ComInterface
     *
     *  Zwalnia muteks kanału komunikacyjnego
     */
    ~ComInterface()
    {
        // this->channel.UnlockAccess();
    }
};