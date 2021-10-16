#ifndef DRAWABLEDELAUNAYTRIANGULATION_H
#define DRAWABLEDELAUNAYTRIANGULATION_H

#include <cg3/geometry/point.h>
#include <data_structures/trianglenode.h>
#include <cg3/utilities/color.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/2d/triangle2d.h>

class DrawableDelaunayTriangulation:public cg3::DrawableObject
{
public:
    DrawableDelaunayTriangulation();


    void setColor(const QColor &value, const QColor &value2);

    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;

    //Cancella il vettore contenente i nodi e quindi i triangoli associati
    void clearDagNode();

    //Aggiorna il vettore corrente con quello passato in modo da trovare i nuovi triangoli da stampare
    void takesNodes(std::vector<TriangleNode>dagNode);

    //Permette di settare la variabile drawActive per capire se stampare anche il BoundingTriangle o no
    void isVisible(bool visible);

    //Stampa i punti e il triangoli compreso il boundingTriangle
    void drawisVisible() const;

    //Stampa i punti e i triangoli escluso il BoundingTriangle
    void drawisNotVisible() const;

private:
    QColor colorT; //colore triangolo
    QColor colorP; //colore punti
    std::vector<TriangleNode>dagNode; //vettore di TriangleNode, contenete ognuno un triangolo
    bool drawActive;//true se si deve stampare anche il boundingTriangle, false altrimenti


};

#endif // DRAWABLEDELAUNAYTRIANGULATION_H
