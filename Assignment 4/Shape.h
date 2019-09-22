//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_SHAPE_H
#define A4_SHAPE_H

#include <string>
using namespace std;
using Grid = vector <vector <char >>;

class Shape {
protected:
    int identity;
    string user_supplied_name;
    string user_supplied_description;
public:
    // methods
    Shape(string name,string description);
    virtual string name_getter() = 0;
    virtual string supplied_description_getter() = 0;
    virtual int identity_getter() = 0;
    string name_setter(string name);
    string supplied_description_setter(string description);
    virtual string toString() = 0;
    virtual double compute_area() = 0;
    virtual double compute_perimeter() = 0;
    virtual int screen_area() = 0;
    virtual int screen_perimeter() = 0;
    virtual vector <vector <char >> draw(char fChar = '*', char bChar = ' ') = 0;
    virtual double get_hight() = 0;
    virtual double get_width() = 0;
};


#endif //A4_SHAPE_H
