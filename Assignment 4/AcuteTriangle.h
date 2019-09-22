//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_ACUTETRIANGLE_H
#define A4_ACUTETRIANGLE_H


#include "Triangle.h"
using Grid = vector <vector <char >>;

class AcuteTriangle: public Triangle{
protected:
    int base;
    int hight;
public:
    AcuteTriangle(int b);
    AcuteTriangle(int b, string name);
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


#endif //A4_ACUTETRIANGLE_H
