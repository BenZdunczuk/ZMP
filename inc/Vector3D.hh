#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
//  typedef geom::Vector<double,3>  Vector3D;

class Vector3D : public geom::Vector<double,3>
{
    public:

    /*!
    * \brief Standardowy konstruktor.
    * Standardowy konstruktor.
    */
    Vector3D();

    /*!
    * \brief Standardowy konstruktor.
    * Standardowy konstruktor.
    * 
    * \param x - parametr x wektora
    * \param y - parametr y wektora
    * \param z - parametr z wektora
    */
    Vector3D(double x,double y,double z);

};

/*!
* \brief Funkcja czytająca wektor z standardowego strumienia wejściowego.
* Funkcja czytająca wektor z standardowego strumienia wejściowego.
*
* \param in - referencja na strumieni wejściowy
* \param vec - referencja na wektor 3D
*/
std::istream& operator>>(std::istream& in,Vector3D& vec);

/*!
* \brief Funkcja drukująca wektor na standardowy strumieni wyjściowy.
* Funkcja drukująca wektor na standardowy strumieni wyjściowy.
* W formie (x,y,z).
*
* \param out - referencja na strumieni wyjściowy
* \param vec - stała referencja na wektor 3D
*/
std::ostream& operator<<(std::ostream& out,const Vector3D& vec);

#endif
