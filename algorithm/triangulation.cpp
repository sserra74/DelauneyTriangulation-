//#include "triangulation.h"
//#include <cg3/geometry/2d/triangle2d.h>
//#include <cg3/geometry/2d/utils2d.h>
//#include <utils/delaunay_checker.h>
//Triangulation::Triangulation()
//{

//}






//void Triangulation::delauneyTriangulation(const cg3::Point2Dd& point)
//{
//    bool check=false;
//    unsigned i=0;
//    unsigned k=0;
//    bool stop=false;

//    if(dag.size()==1)
//        check=inside(point, 0);
//    else
//    {
//        std::cout << "i, figli:" << i<<dag.at(i).getFigli()<<std::endl ;
//        for(i=0;dag.at(i).getFigli()==true;i=k)
//        {
//            std::cout << "i:" << i<<dag.at(i).getFigli()<<"dentro"<<std::endl ;
//            check=inside(point, dag.at(i).getLabelF1());
//            if(check==true)
//                k=dag.at(i).getLabelF1();
//            else
//            {
//                if(check==false)
//                    check=inside(point, dag.at(i).getLabelF2());
//                if(check==false)
//                {
//                    check=inside(point, dag.at(i).getLabelF3());
//                    k=dag.at(i).getLabelF3();
//                }
//                else
//                    k=dag.at(i).getLabelF2();
//            }
//        }

//    }
//   updateTriangulation(point,i);
//    /*DrawableTriangle* newTriangle1 = new DrawableTriangle(point,dag.at(i).get_Triangle()->getFirstPoint(), dag.at(i).get_Triangle()->getSecondPoint());
//    DrawableTriangle* newTriangle2 = new DrawableTriangle(point, dag.at(i).get_Triangle()->getSecondPoint(), dag.at(i).get_Triangle()->getThirdPoint());
//    DrawableTriangle* newTriangle3 = new DrawableTriangle(point, dag.at(i).get_Triangle()->getThirdPoint(), dag.at(i).get_Triangle()->getFirstPoint());
//    TriangleNode* newNode1 = new TriangleNode(newTriangle1,i, -1,-1,-1);
//    TriangleNode* newNode2 = new TriangleNode(newTriangle2,i, -1,-1,-1);
//    TriangleNode* newNode3 = new TriangleNode(newTriangle3,i, -1,-1,-1);
//    dag.push_back(*newNode1);
//    dag.push_back(*newNode2);
//    dag.push_back(*newNode3);
//    dag.at(i).setFigli(true);
//    dag.at(i).setFigli(dag.size()-3,dag.size()-2,dag.size()-1);
//    //nei parametri: padre, dag e posizione di questo nodo nel dag
//    (*newNode1).setAdjacent(i, dag, dag.size()-3);
//    (*newNode2).setAdjacent(i, dag, dag.size()-2);
//    (*newNode3).setAdjacent(i, dag, dag.size()-1);
//    //legalizeEdge(newTriangle1->getFirstPoint(), newTriangle1->getSecondPoint(), newTriangle1->getThirdPoint(), *newNode1);
//    std::cout << "i, figli:" << i<<dag.at(i).getFigli()<<std::endl */;

//}


//bool Triangulation::legalizeEdge(const cg3::Point2Dd& pr, const cg3::Point2Dd& p2, const cg3::Point2Dd& p3, const TriangleNode node)
//{
//    TriangleNode temp=node;
//    unsigned adjacent1=temp.getAdjacent(0);
//    unsigned  adjacent2=temp.getAdjacent(1);
//   // unsigned  adjacent3=temp.getAdjacent(2);
//    if((dag.at(adjacent1).get_Triangle()->getSecondPoint()==p2 || dag.at(adjacent1).get_Triangle()->getSecondPoint()==p3)
//        && (dag.at(adjacent1).get_Triangle()->getThirdPoint()==p2 || dag.at(adjacent1).get_Triangle()->getThirdPoint()==p3))
//    {
//        if( cg3::isPointLyingInCircle(pr,p2,p3, dag.at(adjacent1).get_Triangle()->getFirstPoint(), false))
//            return true;
//        else
//          return false;

//    }
//    else if ((dag.at(adjacent2).get_Triangle()->getSecondPoint()==p2 || dag.at(adjacent2).get_Triangle()->getSecondPoint()==p3)
//             && (dag.at(adjacent2).get_Triangle()->getThirdPoint()==p2 || dag.at(adjacent2).get_Triangle()->getThirdPoint()==p3)) {
//        if( cg3::isPointLyingInCircle(pr,p2,p3, dag.at(adjacent2).get_Triangle()->getFirstPoint(), false))
//            return true;
//        else
//          return false;
//    }
////    else if ((dag.at(adjacent3).get_Triangle()->getSecondPoint()==p2 || dag.at(adjacent3).get_Triangle()->getSecondPoint()==p3)
////             && (dag.at(adjacent3).get_Triangle()->getThirdPoint()==p2 || dag.at(adjacent3).get_Triangle()->getThirdPoint()==p3)) {
////        if( cg3::isPointLyingInCircle(pr,p2,p3, dag.at(adjacent3).get_Triangle()->getFirstPoint(), false))

////            return true;
////        else
////          return false;
////    }




////    cg3::isPointLyingInCircle(pr,p2,p3, p false);
//}

//void Triangulation::updateTriangulation(const cg3::Point2Dd& point, unsigned i)
//{
//    bool legal=false;
//    DrawableTriangle* newTriangle1 = new DrawableTriangle(point,dag.at(i).get_Triangle()->getFirstPoint(), dag.at(i).get_Triangle()->getSecondPoint());
//    DrawableTriangle* newTriangle2 = new DrawableTriangle(point, dag.at(i).get_Triangle()->getSecondPoint(), dag.at(i).get_Triangle()->getThirdPoint());
//    DrawableTriangle* newTriangle3 = new DrawableTriangle(point, dag.at(i).get_Triangle()->getThirdPoint(), dag.at(i).get_Triangle()->getFirstPoint());
//    TriangleNode* newNode1 = new TriangleNode(newTriangle1,i, -1,-1,-1);
//    TriangleNode* newNode2 = new TriangleNode(newTriangle2,i, -1,-1,-1);
//    TriangleNode* newNode3 = new TriangleNode(newTriangle3,i, -1,-1,-1);
//    dag.push_back(*newNode1);
//    dag.push_back(*newNode2);
//    dag.push_back(*newNode3);
//    dag.at(i).setFigli(true);
//    dag.at(i).setFigli(dag.size()-3,dag.size()-2,dag.size()-1);
//    (*newNode1).setAdjacent(i, dag, dag.size()-3);
//    (*newNode2).setAdjacent(i, dag, dag.size()-2);
//    (*newNode3).setAdjacent(i, dag, dag.size()-1);
//    //legal=legalizeEdge(point, newTriangle1->getSecondPoint(), newTriangle1->getThirdPoint(), *newNode1);
//    if(legal)
//        std::cout << "legale"<<std::endl ;
//    else {
//        std::cout << "non legale"<<std::endl ;
//    }
//}
