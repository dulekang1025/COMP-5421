//
// Created by Lekang Du on 2019-07-30.
//

#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>
#include "RightTriangle.h"

RightTriangle::RightTriangle(int b):Triangle(b,b,"Carpenter's square","One right and two acute angles") {
    base = b;
    hight = b;
    Shape::identity = 4;
}
RightTriangle::RightTriangle(int b, string name):Triangle(b,b,name,"One right and two acute angles") {
    base = b;
    hight = b;
    Shape::identity = 4;
}
string RightTriangle::name_getter() {
    return Shape::user_supplied_name;
}

string RightTriangle::supplied_description_getter() {
    return Shape::user_supplied_description;
}

double RightTriangle::get_hight() {
    return hight;
}

double RightTriangle::get_width() {
    return base;
}

int RightTriangle::identity_getter() {
    return Shape::identity;
}

double RightTriangle::compute_area() {
    return (double)(hight * base) / 2;
}

double RightTriangle::compute_perimeter() {
    return (double)(2 + sqrt(2)) * hight;
}

int RightTriangle::screen_area() {
    return hight * (hight + 1) / 2;
}

int RightTriangle::screen_perimeter() {
    return 3 * (hight - 1);
}

string RightTriangle::toString() {
    ostringstream out;
    out<<"Shape Information\n";
    out<<"-----------------\n";
    out<<"id:            "<<Shape::identity<<endl;
    out<<"Shape name:    "<<Shape::user_supplied_name<<endl;
    out<<"Description:   "<<Shape::user_supplied_description<<endl;
    out<<"B. box width:  "<<hight<<endl;
    out<<"B. box height: "<<hight<<endl;
    out<<"Scr area:      "<<screen_area()<<endl;
    out<<"Geo area:      "<<fixed<<setprecision(2)<<compute_area()<<endl;
    out<<"Scr perimeter: "<<screen_perimeter()<<endl;
    out<<"Geo perimeter: "<<fixed<<setprecision(2)<<compute_perimeter()<<endl;
    out<<"Static type:   "<<typeid(this).name()<<endl;
    out<<"Dynamic type:  "<<typeid(*this).name()<<endl;
    return out.str();
}

vector <vector <char >> RightTriangle::draw(char fChar, char bChar){
    Grid grid;
    for(int i = 0; i < hight; i++){
        vector<char> r;
        for(int j = 0; j < hight; j++){
            if(j<=i){
                r.push_back(fChar);
            } else{
                r.push_back(bChar);
            }

        }
        grid.push_back(r);
    }
    return grid;
}