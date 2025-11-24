#pragma once

#include <string>
#include <mutex>

#include "Vector3D.hh"
#include "AbstractMobileObj.hh"

/*!
 * \brief Definiuje interfejs dla obiektów mobilnych.
 *
 * Klasa dziedziczy klasę abstrakcyjną AbstractMobileObj
 */
class mobileObj : public AbstractMobileObj
{
    /*!
     * \brief Rotacja obiektu wyrażona w stopniach wzdłuż osi x,y i z
     */
    Vector3D rotation;
    /*!
     * \brief Pozycja obiektu wyrażona w metrach w osiach x,y i z
     */
    Vector3D position;
    /*!
     * \brief Nazwa obiektu
     */
    std::string objName;
    /*!
     * \brief Muteks pilnujący dostępu do obiektu
     */
    std::mutex lock;

public:
    ~mobileObj() {}

    /*!
     * \brief Udostępnia wartość kąta \e roll.
     *
     *  \return Wartość kąta \e roll wyrażona w stopniach.
     */
    double GetAng_Roll_deg() const
    {
        return this->rotation[0];
    }
    /*!
     * \brief Udostępnia wartość kąta \e yaw.
     *
     *  \return Wartość kąta \e pitch wyrażona w stopniach.
     */
    double GetAng_Pitch_deg() const
    {
        return this->rotation[1];
    }
    /*!
     * \brief Udostępnia wartość kąta \e yaw.
     *
     *  \return Wartość kąta \e yaw wyrażona w stopniach.
     */
    double GetAng_Yaw_deg() const
    {
        return this->rotation[2];
    }

    /*!
     * \brief Modyfikuje wartość kąta \e roll.
     *
     *  \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
     */
    void SetAng_Roll_deg(double Ang_Roll_deg)
    {
        this->rotation[0] = Ang_Roll_deg;
    }
    /*!
     * \brief Modyfikuje wartość kąta \e pitch.
     *
     *  \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
     */
    void SetAng_Pitch_deg(double Ang_Pitch_deg)
    {
        this->rotation[1] = Ang_Pitch_deg;
    }
    /*!
     * \brief Modyfikuje wartość kąta \e yaw.
     *
     *  \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
     */
    void SetAng_Yaw_deg(double Ang_Yaw_deg)
    {
        this->rotation[2] = Ang_Yaw_deg;
    }

    /*!
     * \brief Udostępnia współrzędne aktualnej pozycji obiektu.
     *
     * \return Współrzędne aktualnej pozycji obiektu wyrażone w metrach.
     */
    const Vector3D &GetPositoin_m() const
    {
        return this->position;
    }
    /*!
     * \brief Modyfikuje współrzędne aktualnej pozycji obiektu.
     *
     * \param[in] newPosition - nowe współrzędne obiektu wyrażone w metrach.
     */
    void SetPosition_m(const Vector3D &newPosition)
    {
        this->position = newPosition;
    }
    /*!
     * \brief Modyfikuje nazwę obiektu.
     *
     *  \param[in]  sName - nowa nazwa obiektu.
     */
    void SetName(const char *sName)
    {
        this->objName = sName;
    }
    /*!
     * \brief Udostępnia nazwę obiektu.
     *
     *  \return Nazwa obiektu.
     */
    const std::string &GetName() const
    {
        return this->objName;
    }

    /*!
     * \brief Blokuje dostęp do obiektu.
     */
    void LockAccess()
    {
        this->lock.lock();
    }

    /*!
     * \brief Odblokowuje dostęp do obiektu.
     */
    void UnLockAccess()
    {
        this->lock.unlock();
    }
};