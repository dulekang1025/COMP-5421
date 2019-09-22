//
// Created by Lekang Du on 2019-07-30.
//

#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "Rectangle.h"
using namespace std;
using Grid = vector <vector <char >>;

Rectangle::Rectangle(int w, int h):Shape("Four-sided","Four right angles") {
    width = w;
    hight = h;
    Shape::identity = 1;
}

Rectangle::Rectangle(int w, int h, string name, string description):Shape(name,description) {
    width = w;
    hight = h;
    Shape::identity = 1;
}

string Rectangle::name_getter() {
    return Shape::user_supplied_name;
}

string Rectangle::supplied_description_getter() {
    return Shape::user_supplied_description;
}

double Rectangle::get_hight() {
    return hight;
}

double Rectangle::get_width() {
    return width;
}

int Rectangle::identity_getter() {
    return Shape::identity;
}

double Rectangle::compute_area() {
    return hight * width;
}

double Rectangle::compute_perimeter() {
    return 2 * (hight + width);
}

int Rectangle::screen_area() {
    return hight * width;
}

int Rectangle::screen_perimeter() {
    return 2 * (hight + width) - 4;
}

string Rectangle::toString() {
    ostringstream out;
    out<<"Shape Information\n";
    out<<"-----------------\n";
    out<<"id:            "<<Shape::identity<<endl;
    out<<"Shape name:    "<<Shape::user_supplied_name<<endl;
    out<<"Description:   "<<Shape::user_supplied_description<<endl;
    out<<"B. box width:  "<<width<<endl;
    out<<"B. box height: "<<hight<<endl;
    out<<"Scr area:      "<<screen_area()<<endl;
    out<<"Geo area:      "<<fixed<<setprecision(2)<<compute_area()<<endl;
    out<<"Scr perimeter: "<<screen_perimeter()<<endl;
    out<<"Geo perimeter: "<<fixed<<setprecision(2)<<compute_perimeter()<<endl;
    out<<"Static type:   "<<typeid(this).name()<<endl;
    out<<"Dynamic type:  "<<typeid(*this).name()<<endl;
    return out.str();
}

vector <vector <char >> Rectangle::draw(char fChar, char bChar){
    Grid grid;
    for(int i = 0; i < hight; i++){
        vector<char> r;
        for(int j = 0; j < width; j++){
            r.push_back(fChar);
        }
        grid.push_back(r);
    }
    return grid;
}

ostream & operator<<(ostream & out, Rectangle & rectangle){
    out<<rectangle.toString();
    return out;
}