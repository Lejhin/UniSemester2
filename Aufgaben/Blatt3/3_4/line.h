//
// Created by Julius on 20.10.2022.
//

#ifndef SEMESTER_2_LINE_H
#define SEMESTER_2_LINE_H

#include "Point.h"

class Line{


private:
    Point p1;
    Point p2;
   Line* l;


public:
    Line(Point p1 = Point(0,0), Point p2 = Point(1,0)): l(new Line(p1,p2)){
    }

    Point get_Start(){return p1;}
    Point get_end(){return p2;}

    Line& operator+=(Point p2){
        p1 = Point(p1.get_x()+p2.get_x(), p1.get_y()+p2.get_y());
        this->p2 = Point(this->p2.get_x()+p2.get_x(), this->p2.get_y()+p2.get_y());


        return *this;
    }


    bool operator==(Line l2) const{
        if(p1.get_x() == l2.get_Start().get_x() && p1.get_x() == l2.get_Start().get_y()){
            if(p2.get_x() == l2.get_Start().get_x() && p2.get_x() == l2.get_Start().get_y()){
                return true;
            }
        }
        return false;
    }

};
#endif //SEMESTER_2_LINE_H
