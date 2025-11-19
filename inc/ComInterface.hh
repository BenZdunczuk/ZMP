#pragma once

#include <string>
#include <sstream>

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ComChannel.hh"
#include "Vector3D.hh"

/*!
 * \brief Klasa zapewniająca podstawowe polecenie dla serwera graficznego.
 * Klasa zapewniająca podstawowe polecenie dla serwera graficznego.
 */
class ComInterface
{
    AbstractComChannel &channel;

public:
    /*!
     * \brief Konstruktor klasy
     * Konstruktor klasy, blokuje on muteks kanału komunikacyjnego
     * \param _channel - referencja na kanał komunikacyjny z serwerem
     */
    ComInterface(AbstractComChannel &_channel);

    /*!
     * \brief Funkcja dodająca obiekt do serwera
     * Funkcja dodająca obiekt do serwera
     * \param shift - przesunięcie obiektu
     * \param scale - skala obietku
     * \param trans - pozycja obiektu
     * \param rotXYZ - obrót obiektu względem osi roll, pitch, yaw
     * \param RGB - kolor obiektu
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool AddObj(const std::string &name, const Vector3D &shift, const Vector3D &scale, const Vector3D &trans, const Vector3D &rotXYZ, const Vector3D &RGB);

    /*!
     * \brief Funkcja aktualizująca parametry obiektu.
     * Funkcja aktualizująca parametry obiektu.
     * \param name - nazwa obiektu
     * \param trans - pozycja obiektu
     * \param rotXYZ - obrót obiektu względem osi roll, pitch, yaw
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool UpdateObj(const std::string &name, const Vector3D &trans, const Vector3D &rotXYZ);

    /*!
     * \brief Funkcja czyszcząca zawartość sceny serwera.
     * Funkcja czyszcząca zawartość sceny serwera.
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool Clear();

    /*!
     * \brief Funkcja zamykająca połączenie z serwerem.
     * Funkcja zamykająca połączenie z serwerem.
     *
     * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
     */
    bool Close();

    /*!
     * \brief Funkcja zwalniająca muteks kanału komunikacyjnego.
     * Funkcja zwalniająca muteks kanału komunikacyjnego.
     */
    void Release()
    {
        this->channel.UnlockAccess();
    }

    ~ComInterface()
    {
        this->channel.UnlockAccess();
    }
};