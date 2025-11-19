#include <iostream>

#include "Vector3D.hh"

Vector3D::Vector3D()
{
    (*this)[0] = 0;
    (*this)[1] = 0;
    (*this)[2] = 0;
}

Vector3D::Vector3D(double x,double y,double z)
{
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

std::istream& operator>>(std::istream& in,Vector3D& vec)
{
    in>>vec[0]>>vec[1]>>vec[2];

    return in;
}

std::ostream& operator<<(std::ostream& out,const Vector3D& vec)
{
    out<<"("<<vec[0]<<","<<vec[1]<<","<<vec[2]<<")";

    return out;
}