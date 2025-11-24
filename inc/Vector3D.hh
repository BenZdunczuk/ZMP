#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

class Vector3D : public geom::Vector<double, 3>
{
public:
    /*!
     * \brief Kkonstruktor bezparametryczny.
     */
    Vector3D();

    /*!
     * \brief Konstruktor parametryczny.
     *
     * \param x - parametr x wektora
     * \param y - parametr y wektora
     * \param z - parametr z wektora
     */
    Vector3D(double x, double y, double z);
};

/*!
 * \brief Funkcja czytająca wektor ze strumienia wejściowego.
 *
 * \param in - referencja na strumieni wejściowy
 * \param vec - referencja na wektor 3D
 */
std::istream &operator>>(std::istream &in, Vector3D &vec);

/*!
 * \brief Funkcja wyświetlająca wektor na strumien wyjściowy.
 *
 * \param out - referencja na strumieni wyjściowy
 * \param vec - stała referencja na wektor 3D
 */
std::ostream &operator<<(std::ostream &out, const Vector3D &vec);

#endif
