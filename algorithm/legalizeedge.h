#ifndef LEGALIZEEDGE_H
#define LEGALIZEEDGE_H
#include <cg3/geometry/2d/point2d.h>
#include <algorithm/delaunayt.h>
class LegalizeEdge
{
public:
    LegalizeEdge();

    //Il metodo isLegal permette di controllare la legalità del lato effettuando flip se necessario
    static void isLegal(const cg3::Point2Dd& pr, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3, unsigned long size, Dag& dag);
};

#endif // LEGALIZEEDGE_H
