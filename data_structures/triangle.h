#ifndef TRIANGLE_H
#define TRIANGLE_H


#include<cg3/geometry/2d/point2d.h>


class Triangle
{
public:
    Triangle();

    //Costruttore che setta i punti del triangolo
    Triangle(const cg3::Point2Dd& first_point, const cg3::Point2Dd& second_point, const cg3::Point2Dd& third_point);

    //Restituisce il primo punto
    cg3::Point2Dd getFirstPoint() const;

    //Restituisce il secondo punto
    cg3::Point2Dd getSecondPoint() const;

    //Restituisce il terzo punto
    cg3::Point2Dd getThirdPoint() const;

    //Permette di trovare il punto non in comune tra il triangolo corrente e il suo adiacente
    const cg3::Point2Dd getOppositePoint(const cg3::Point2Dd& p2, const cg3::Point2Dd& p3);


private:

    //Punti del triangolo
    cg3::Point2Dd first_point;
    cg3::Point2Dd second_point;
    cg3::Point2Dd third_point;
};

#endif // TRIANGLE_H
