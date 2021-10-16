#include "triangle.h"

Triangle::Triangle()
{

}

//Costruttore che setta i punti del triangolo
Triangle::Triangle(const cg3::Point2Dd& first_point, const cg3::Point2Dd& second_point, const cg3::Point2Dd& third_point)
{
    this->first_point=first_point;
    this->second_point=second_point;
    this->third_point=third_point;
}

//Restituisce il primo punto
cg3::Point2Dd Triangle::getFirstPoint() const
{
    return  this->first_point;
}

//Restituisce il secondo punto
cg3::Point2Dd Triangle::getSecondPoint() const
{
    return  this->second_point;
}

//Restituisce il terzo punto
cg3::Point2Dd Triangle::getThirdPoint() const
{
    return  this->third_point;
}

//Permette di trovare il punto non in comune tra il triangolo corrente e il suo adiacente
const cg3::Point2Dd Triangle::getOppositePoint(const cg3::Point2Dd& p2, const cg3::Point2Dd& p3)
{


    if((this->getFirstPoint()==p2 && this->getSecondPoint()==p3) || (this->getFirstPoint()==p3 && this->getSecondPoint()==p2))
        return this->getThirdPoint();

    if((this->getFirstPoint()==p2 && this->getThirdPoint()==p3) || (this->getFirstPoint()==p3 && this->getThirdPoint()==p2))
        return this->getSecondPoint();

    if((this->getSecondPoint()==p2 && this->getThirdPoint()==p3) || (this->getSecondPoint()==p3 && this->getThirdPoint()==p2))
        return this->getFirstPoint();

    return cg3::Point2Dd(0,0);
}


