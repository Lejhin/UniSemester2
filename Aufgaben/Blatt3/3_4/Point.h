//
// Created by Julius on 20.10.2022.
//

#ifndef SEMESTER_2_POINT_H
#define SEMESTER_2_POINT_H

class Point{

private:
    int x;
    int y;
public:
    Point(int x = 0, int y= 0): x(x), y(y){
    }
    int get_x()const {return x;}
    int get_y()const {return y;}

    Point& operator+=(const Point p2){
        this->x += p2.x;
        this->y += p2.y;
        return *this;
    }

    bool operator==(const Point p2){
        if(this->x == p2.x && this->y == p2.y){
            return true;
        }
        return false;
    }
};

#endif //SEMESTER_2_POINT_H
