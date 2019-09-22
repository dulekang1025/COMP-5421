//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_RECTANGLE_H
#define A4_RECTANGLE_H


#include "Shape.h"
using Grid = vector <vector <char >>;
class Rectangle: public Shape {
private:
    int width;
    int hight;
public:
    Rectangle(int w,int h);
    Rectangle(int w,int h, string name, string description);
    string name_getter() override;
    string supplied_description_getter() override;
    int identity_getter() override;
    string toString() override;
    double compute_area() override;
    double compute_perimeter() override;
    int screen_area() override;
    int screen_perimeter() override;
    vector <vector <char >> draw(char fChar = '*', char bChar = ' ') override;
    double get_hight() override;
    double get_width() override;
};


#endif //A4_RECTANGLE_H
