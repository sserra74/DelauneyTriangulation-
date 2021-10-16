//#include "drawabletriangle.h"
//#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

//DrawableTriangle::DrawableTriangle(): colorT(QColor(0,0,0)), colorP(QColor(0,0,255))
//{

//}


//DrawableTriangle::DrawableTriangle(const cg3::Point2Dd& first_point, const cg3::Point2Dd& second_point, const cg3::Point2Dd& third_point)
//{
//    cg3::Triangle2Dd(first_point, second_point, third_point);
//    this->first_point=first_point;
//    this->second_point=second_point;
//    this->third_point=third_point;
//    colorT=QColor(0,0,0);
//    colorP=QColor(0,0,255);

//}


//void DrawableTriangle::setColor(const QColor& colorT, const QColor& colorP)
//{
//    this->colorT = colorT;
//    this->colorT = colorP;
//}

//void DrawableTriangle::draw() const {

//    cg3::viewer::drawPoint2D(cg3::Point2Dd(first_point.x(),first_point.y()),colorP,4);
//    cg3::viewer::drawPoint2D(cg3::Point2Dd(second_point.x(),second_point.y()),colorP,4);
//    cg3::viewer::drawPoint2D(cg3::Point2Dd(third_point.x(),third_point.y()),colorP,4);
//    cg3::viewer::drawTriangle2D(first_point, second_point, third_point, colorT,1, false);

//}


//cg3::Pointd DrawableTriangle::sceneCenter() const
//{
//    cg3::Pointd center(0,0,0);

//    center.x() =first_point.x()+second_point.x()+third_point.x();
//    center.y() = first_point.y()+second_point.y()+third_point.y();

//    center /= 3;

//    return center;
//}

//double DrawableTriangle::sceneRadius() const {

//    cg3::Pointd center = sceneCenter();
//    cg3::Point2Dd center2D(center.x(), center.y());
//    double maxDistance = 0;
//    double dist1 = first_point.dist(center2D);
//    double dist2 = second_point.dist(center2D);
//    double dist3 = third_point.dist(center2D);
//    maxDistance = std::max(dist1, dist2);



//    return std::max(maxDistance, dist3);
//}

//cg3::Point2Dd DrawableTriangle::getFirstPoint()
//{
//    return  this->first_point;
//}
//cg3::Point2Dd DrawableTriangle::getSecondPoint()
//{
//    return  this->second_point;
//}
//cg3::Point2Dd DrawableTriangle::getThirdPoint()
//{
//    return  this->third_point;
//}

