//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_RIGHTTRIANGLE_H
#define A4_RIGHTTRIANGLE_H


#include "Triangle.h"

class RightTriangle: public Triangle {
protected:
    int base;
    int hight;
public:
    RightTriangle(int b);
    RightTriangle(int b, string name);
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


#endif //A4_RIGHTTRIANGLE_H
