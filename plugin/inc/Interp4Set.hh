#ifndef COMMAND4SET_HH
#define COMMAND4SET_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "AbstractInterp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego zatrzymanie
 */
class Interp4Set : public AbstractInterp4Command
{
private:
    /*
     * Nazwa obiektu
     */
    std::string objectName;
    /*
     * Położenie obiektu na osi X
     */
    int Xpos;
    /*
     * Położenie obiektu na osi Y
     */
    int Ypos;
    /*
     * Położenie obiektu na osi Z
     */
    int Zpos;
    /*
     * Obrót obiektu względem osi X [stopnie]
     */
    int Xrot;
    /*
     * Obrót obiektu względem osi Y [stopnie]
     */
    int Yrot;
    /*
     * Obrót obiektu względem osi Z [stopnie]
     */
    int Zrot;

public:
    /*!
     * \brief Konstruktor klasy Interp4Pause
     */
    Interp4Set();
    /*!
     * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
     */
    virtual void PrintCmd() const override;
    /*!
     * \brief Wyświetla składnię polecenia
     */
    virtual void PrintSyntax() const override;
    /*!
     * \brief Wyświetla wartości wczytanych parametrów
     */
    virtual void PrintParams() const override {}
    /*!
     * \brief Udostępnia nazwę ostatniego obiektu wczytanego
     */
    virtual const char *GetObjName() const override;

    /*!
     * \brief Wyświetla nazwę polecenia
     */
    virtual const char *GetCmdName() const override;

    /*!
     * \brief Wykonuje polecenie oraz wizualizuje jego realizację
     *
     * Wykonuje polecenie oraz wizualizuje jego realizację.
     * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
     * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
     * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
     * \retval true - operacja powiodła się,
     * \retval false - w przypadku przeciwnym.
     */
    virtual bool ExecCmd(AbstractScene &rScn,AbstractComChannel &rComChann) override;
    /*!
     * \brief Czyta wartości parametrów danego polecenia
     */
    virtual bool ReadParams(std::istream &Strm_CmdsList) override;

    /*!
     * \brief
     *
     *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
     */
    static AbstractInterp4Command *CreateCmd();
};

#endif