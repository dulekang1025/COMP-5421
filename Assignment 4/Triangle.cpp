//
// Created by Lekang Du on 2019-07-30.
//

#include "Triangle.h"

Triangle::Triangle(int d, int h): Shape("", "") {
    base = d;
    hight = h;
}

Triangle::Triangle(int b, int h, string name, string description): Shape(name, description) {
    base = b;
    hight = h;
}
