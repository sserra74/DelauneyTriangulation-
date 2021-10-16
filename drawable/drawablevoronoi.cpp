#include "drawablevoronoi.h"
#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableVoronoi::DrawableVoronoi():colorL(QColor(255,0,0)), colorP(QColor(255,0,0))
{

}

void DrawableVoronoi::setColor(const QColor& colorL, const QColor& colorP)
{
    this->colorL = colorL;
    this->colorP = colorP;
}

/*A partire dai triangoli ottenuti per la triangolazione di Delaunay, scorro il vettore e per ogni triangolo calcolo
 * il circocentro che verrà poi collegato al circocentro dei triangoli adiacenti a quel triangolo*/
void DrawableVoronoi::draw() const {

    cg3::Point2Dd first, second, third, circumCircle;
    cg3::Point2Dd firstAdj, secondAdj, thirdAdj, circumCircleAdj;

    if(drawActive==true && dagNode.size()==1)//stampa del circocentro del bounding triangle
    {
        first=dagNode.at(0).get_Triangle().getFirstPoint();
        second=dagNode.at(0).get_Triangle().getSecondPoint();
        third=dagNode.at(0).get_Triangle().getThirdPoint();
        circumCircle=computeCircumCircle(first,second,third);
        cg3::viewer::drawPoint2D(circumCircle,colorP,4);
    }
    else if(drawActive==true && dagNode.size()>1)
    {
        for(unsigned long i=0;i<dagNode.size();i++)//scorro il vettore dei nodi a cui, per ciascuno, corrisponde un traingolo
        {
            if(dagNode.at(i).getSalta()==false)
            {
                first=dagNode.at(i).get_Triangle().getFirstPoint();
                second=dagNode.at(i).get_Triangle().getSecondPoint();
                third=dagNode.at(i).get_Triangle().getThirdPoint();
                circumCircle=computeCircumCircle(first,second,third);
                cg3::viewer::drawPoint2D(circumCircle,colorP,4);

                if(dagNode.at(i).getAdjacent(0)!=0)
                {
                    firstAdj=dagNode.at(dagNode.at(i).getAdjacent(0)).get_Triangle().getFirstPoint();
                    secondAdj=dagNode.at(dagNode.at(i).getAdjacent(0)).get_Triangle().getSecondPoint();
                    thirdAdj=dagNode.at(dagNode.at(i).getAdjacent(0)).get_Triangle().getThirdPoint();
                    circumCircleAdj=computeCircumCircle(firstAdj,secondAdj,thirdAdj);
                    cg3::viewer::drawLine2D(circumCircle,circumCircleAdj,colorL,1);
                }
                if(dagNode.at(i).getAdjacent(1)!=0)
                {
                    firstAdj=dagNode.at(dagNode.at(i).getAdjacent(1)).get_Triangle().getFirstPoint();
                    secondAdj=dagNode.at(dagNode.at(i).getAdjacent(1)).get_Triangle().getSecondPoint();
                    thirdAdj=dagNode.at(dagNode.at(i).getAdjacent(1)).get_Triangle().getThirdPoint();
                    circumCircleAdj=computeCircumCircle(firstAdj,secondAdj,thirdAdj);
                    cg3::viewer::drawLine2D(circumCircle,circumCircleAdj,colorL,1);
                }
                if(dagNode.at(i).getAdjacentVectorSize()==3 && dagNode.at(i).getAdjacent(2)!=0)
                {
                    firstAdj=dagNode.at(dagNode.at(i).getAdjacent(2)).get_Triangle().getFirstPoint();
                    secondAdj=dagNode.at(dagNode.at(i).getAdjacent(2)).get_Triangle().getSecondPoint();
                    thirdAdj=dagNode.at(dagNode.at(i).getAdjacent(2)).get_Triangle().getThirdPoint();
                    circumCircleAdj=computeCircumCircle(firstAdj,secondAdj,thirdAdj);
                    cg3::viewer::drawLine2D(circumCircle,circumCircleAdj,colorL,1);
                }
            }
        }
    }


}

cg3::Pointd DrawableVoronoi::sceneCenter() const
{

    return cg3::Pointd (0,0,0);

}

double DrawableVoronoi::sceneRadius() const {

    cg3::Pointd center = sceneCenter();
    return center.dist(center);

}

//Aggiorna il vettore corrente con quello passato in modo da trovare i nuovi triangoli da stampare
void DrawableVoronoi::takeNodes(std::vector<TriangleNode>dagNode)
{
        this->dagNode=dagNode;
}

/*Calcola il circocentro dei triangoli dati i suoi punti
 * Link formula: https://en.wikipedia.org/wiki/Circumscribed_circle#Circumcenter_coordinates*/
cg3::Point2Dd DrawableVoronoi::computeCircumCircle(const cg3::Point2Dd& first, const cg3::Point2Dd& second, const cg3::Point2Dd& third) const
 {
     double d, u_x, u_y;

     d= 2*(first.x()*(second.y()-third.y())+ second.x()*(third.y()-first.y())+ third.x()*(first.y()-second.y()));

     u_x=(1/d)*(((pow(first.x(),2)+pow(first.y(),2))*(second.y()-third.y()))+
                ((pow(second.x(),2)+pow(second.y(),2))*(third.y()-first.y()))+
                ((pow(third.x(),2)+pow(third.y(),2))*(first.y()-second.y())));

     u_y=(1/d)*(((pow(first.x(),2)+pow(first.y(),2))*(third.x()-second.x()))+
                ((pow(second.x(),2)+pow(second.y(),2))*(first.x()-third.x()))+
                ((pow(third.x(),2)+pow(third.y(),2))*(second.x()-first.x())));

     return cg3::Point2Dd(u_x,u_y);

 }

//Cancella il vettore di nodi
void DrawableVoronoi::clearDagNode()
{
    dagNode.clear();
}

//Permette di settare la variabile drawActive per capire se stampare il diagramma di voronoi
void DrawableVoronoi::isVisible(bool visible)
{
    this->drawActive=visible;

}
