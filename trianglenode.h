#ifndef TRIANGLENODE_H
#define TRIANGLENODE_H

#include "drawable/drawabletriangle.h"
#include "data_structures/triangle.h"
class TriangleNode
{
public:
    TriangleNode();
    TriangleNode(Triangle* triangle, unsigned  long etichetta_p, unsigned long etichetta_f1, unsigned long etichetta_f2, unsigned long etichetta_f3);
    Triangle* get_Triangle() const;

   int    getLabelF1();
    unsigned long    getLabelF2();
    unsigned long  getLabelF3();
    unsigned long getLableP();
    bool getFigli();
    void setFigli(bool set, unsigned long a, unsigned long b,  unsigned long  c);

    void setAdjacent(unsigned long i, std::vector<TriangleNode>& dag, unsigned long  loc, bool flip);
    unsigned long getAdjacent(unsigned long i);
    unsigned long getAdjacentVectorSize();
    static const cg3::Point2Dd getThirdPoint(const cg3::Point2Dd& pr, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3, unsigned long adjacent, std::vector<TriangleNode>& dag);
    void setAdjacentFlip(std::vector<TriangleNode>& dag, unsigned long size, unsigned long adjacent);
    bool assignPoint(unsigned long adjacent, std::vector<TriangleNode>& dag, unsigned long i, unsigned long loc, bool flip);
    void setSalta(std::vector<TriangleNode>& dag/*, bool exception*/);
    bool getSalta() const;
    void addAdjacent();
    void clearAdjacentVector();
   // void checkAdjacent(cg3::Point2Dd& thisA,  cg3::Point2Dd& thisB,  cg3::Point2Dd& thisC, int adjacent, std::vector<TriangleNode>& dag, unsigned i, unsigned locs);
private:
    unsigned long etichetta_p;

    int etichetta_f1;
    unsigned long  etichetta_f2;
//    unsigned long etichetta_f1;
//    unsigned long  etichetta_f2;
    unsigned long etichetta_f3=0;
    bool figli=false;
    bool salta=false;
    //std::array<int, 3> adjacent;
    std::vector<unsigned long> adjacent;
///    DrawableTriangle*  triangle;
    Triangle*  triangle;
};

#endif // TRIANGLENODE_H
