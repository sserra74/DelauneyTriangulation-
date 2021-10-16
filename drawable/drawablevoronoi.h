#ifndef DRAWABLEVORONOI_H
#define DRAWABLEVORONOI_H
#include <cg3/geometry/point.h>
#include<cg3/geometry/2d/point2d.h>
#include <data_structures/trianglenode.h>
#include <cg3/viewer/interfaces/drawable_object.h>

class DrawableVoronoi:public cg3::DrawableObject
{
public:
    DrawableVoronoi();

      void setColor(const QColor &value, const QColor &value2);
      void draw() const;
      cg3::Pointd sceneCenter() const;
      double sceneRadius() const;

      //Aggiorna il vettore corrente con quello passato in modo da trovare i nuovi triangoli da stampare
       void takeNodes(std::vector<TriangleNode>dagNode);

       //Calcola il circocentro dei triangoli dati i suoi punti
       cg3::Point2Dd computeCircumCircle(const cg3::Point2Dd& first, const cg3::Point2Dd& second, const cg3::Point2Dd& third) const;

       //Cancella il vettore di nodi
       void clearDagNode();

       //Permette di settare la variabile drawActive per capire se stampare il diagramma di voronoi
       void isVisible(bool visible);


private:
    QColor colorL; //colore linee
    QColor colorP; //colore punti
    std::vector<TriangleNode>dagNode; //vettore di TriangleNode, contenete ognuno un triangolo
    bool drawActive;//true se l'utente vuole stampare voronoi, false altrimenti

};

#endif // DRAWABLEVORONOI_H
