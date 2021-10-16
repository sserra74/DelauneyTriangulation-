#include "drawabledelaunaytriangulation.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

//punti del boundingTriangle
const cg3::Point2Dd BT_P1(1e+10, 0);
const cg3::Point2Dd BT_P2(0, 1e+10);
const cg3::Point2Dd BT_P3(-1e+10, -1e+10);


DrawableDelaunayTriangulation::DrawableDelaunayTriangulation():colorT(QColor(0,0,0)), colorP(QColor(0,0,255))
{

}



void DrawableDelaunayTriangulation::setColor(const QColor& colorT, const QColor& colorP)
{
    this->colorT = colorT;
    this->colorP = colorP;
}

void DrawableDelaunayTriangulation::draw() const {

    if(drawActive==true)
        drawisVisible(); //stampo i punti e i triangoli compreso di BoundingTriangle
    else {
        drawisNotVisible();//stampo i punti e i triangoli escluso il BoundingTriangle
    }

}

//Stampa i punti e il triangoli compreso il boundingTriangle
void DrawableDelaunayTriangulation::drawisVisible() const
{
    unsigned  i;
    cg3::Point2Dd first, second, third;
    for(i=0;i<dagNode.size();i++) //scorro il vettore
    {
        first=dagNode.at(i).get_Triangle().getFirstPoint();
        second= dagNode.at(i).get_Triangle().getSecondPoint();
        third= dagNode.at(i).get_Triangle().getThirdPoint();
        if(dagNode.at(i).getSalta()==false)
        {
            cg3::viewer::drawPoint2D(first,colorP,4 );
            cg3::viewer::drawPoint2D(second,colorP,4 );
            cg3::viewer::drawPoint2D(third,colorP,4 );

            cg3::viewer::drawTriangle2D(first,second,third, colorT,1, false);
        }

    }
}

/*Stampa i punti e i triangoli senza il BoundingTriangle e i lati ad esso incidenti. In particolare, questo accade
 *se uno dei punti del triangolo preso in considerazione ha le stesse coordinate di uno dei punti del Bounding Triangle*/
void DrawableDelaunayTriangulation::drawisNotVisible() const
{
   cg3::Point2Dd first, second, third;

    unsigned  i;
    for(i=0;i<dagNode.size();i++)
    {
         first=dagNode.at(i).get_Triangle().getFirstPoint();
         second= dagNode.at(i).get_Triangle().getSecondPoint();
         third= dagNode.at(i).get_Triangle().getThirdPoint();
         if(dagNode.at(i).getSalta()==false)
         {
           if(first!=BT_P1 && first!=BT_P2 && first!=BT_P3)
                cg3::viewer::drawPoint2D(first,colorP,4 );
           if(second!=BT_P1 && second!=BT_P2 && second!=BT_P3)
                cg3::viewer::drawPoint2D(second,colorP,4 );
           if(third!=BT_P1 && third!=BT_P2 && third!=BT_P3)
                cg3::viewer::drawPoint2D(third,colorP,4 );

            if(first!=BT_P1    && second!=BT_P1 && third!=BT_P1
               && first!=BT_P2 && second!=BT_P2 && third!=BT_P2
               && first!=BT_P3 && second!=BT_P3 && third!=BT_P3)
                 cg3::viewer::drawTriangle2D(first,second,third, colorT,1, false);
           }
    }
}

//Permette di settare la variabile drawActive per capire se stampare anche il BoundingTriangle o no
void DrawableDelaunayTriangulation::isVisible(bool visible)
{
    this->drawActive=visible;

}

cg3::Pointd DrawableDelaunayTriangulation::sceneCenter() const
{

    return cg3::Pointd (0,0,0);

}

double DrawableDelaunayTriangulation::sceneRadius() const {

    cg3::Pointd center = sceneCenter();
    return center.dist(center);

}

//Aggiorna il vettore corrente con quello passato in modo da trovare i nuovi triangoli da stampare
void DrawableDelaunayTriangulation::takesNodes(std::vector<TriangleNode>dagNode)
{
    this->dagNode=dagNode;

}

//Cancella il vettore contenente i nodi e quindi i triangoli associati
void DrawableDelaunayTriangulation::clearDagNode()
{
    dagNode.clear();
}


