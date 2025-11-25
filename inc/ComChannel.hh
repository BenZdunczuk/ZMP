#pragma once

/*!
 * \file
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractComChannel
 *
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

#include <mutex>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <unistd.h>

#include "AbstractComChannel.hh"

/*!
 * \brief Definiuje interfejs kanału komunikacyjnego z serwerem graficznym.
 *
 * Interfejs ma pozwalać na bezpieczną komunikację w programie wielowątkowym.
 */
class ComChannel : public AbstractComChannel
{

    std::mutex _lock;

    int _socket;

public:
    ~ComChannel() {}

    /*!
     * \brief Inicjalizuje destryptor gniazda.
     *
     * \param[in] Socket - zawiera poprawny deskryptor.
     */
    void Init(int Socket)
    {
        this->_socket = Socket;
    }
    /*!
     * \brief Udostępnia deskryptor pliku skojarzonego z połączeniem sieciowym z serwerem.
     *
     * \return Deskryptor pliku.
     */
    int GetSocket() const
    {
        return this->_socket;
    }
    /*!
     * \brief Zamyka dostęp gniazda.
     */
    void LockAccess()
    {
        this->_lock.lock();
    }
    /*!
     * \brief Otwiera dostęp do gniazda.
     */
    void UnlockAccess()
    {
        this->_lock.unlock();
    }
    /*!
     * \brief Udostępnia mutex w trybie modyfikacji.
     */
    std::mutex &UseGuard()
    {
        return this->_lock;
    }

    bool Send(const std::string &msg) {
        LockAccess();
        ssize_t toSend = msg.size();
        const char *data = msg.c_str();

        while (toSend > 0) {
            ssize_t sent = write(_socket, data, toSend);
            if (sent < 0) {
                std::cout << "[ComChannel] Błąd wysyłania danych przez socket.\n";
                UnlockAccess();
                return false;
            }
            toSend -= sent;
            data += sent;
        }

        UnlockAccess();
        return true;

    }

};
