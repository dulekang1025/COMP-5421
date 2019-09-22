//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_TRIANGLE_H
#define A4_TRIANGLE_H


#include "Shape.h"
using Grid = vector <vector <char >>;

class Triangle: public Shape{
public:
    int base;
    int hight;
    Triangle(int d, int h);
    Triangle(int b, int h, string name, string description);

};


#endif //A4_TRIANGLE_H
