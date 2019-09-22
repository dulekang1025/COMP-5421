//
// Created by Lekang Du on 2019-07-30.
//

#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>
#include "AcuteTriangle.h"

AcuteTriangle::AcuteTriangle(int b):Triangle(b,b,"Acute triangle","All acute angels") {
    if(b%2 == 0){
        b = b + 1;
    }
    base = b;
    hight = (b + 1) / 2;
    Shape::identity = 3;
}

string AcuteTriangle::name_getter() {
    return Shape::user_supplied_name;
}

string AcuteTriangle::supplied_description_getter() {
    return Shape::user_supplied_description;
}

double AcuteTriangle::get_hight() {
    return hight;
}

double AcuteTriangle::get_width() {
    return base;
}

int AcuteTriangle::identity_getter() {
    return Shape::identity;
}

double AcuteTriangle::compute_area() {
    return (double)(hight * base) / 2;
}

double AcuteTriangle::compute_perimeter() {
    return (double) base + 2 * sqrt(0.25 * base * base + hight * hight);
}

int AcuteTriangle::screen_area() {
    return hight * hight;
}

int AcuteTriangle::screen_perimeter() {
    return 4 * (hight - 1);
}

string AcuteTriangle::toString() {
    ostringstream out;
    out<<"Shape Information\n";
    out<<"-----------------\n";
    out<<"id:            "<<Shape::identity<<endl;
    out<<"Shape name:    "<<Shape::user_supplied_name<<endl;
    out<<"Description:   "<<Shape::user_supplied_description<<endl;
    out<<"B. box width:  "<<base<<endl;
    out<<"B. box height: "<<hight<<endl;
    out<<"Scr area:      "<<screen_area()<<endl;
    out<<"Geo area:      "<<fixed<<setprecision(2)<<compute_area()<<endl;
    out<<"Scr perimeter: "<<screen_perimeter()<<endl;
    out<<"Geo perimeter: "<<fixed<<setprecision(2)<<compute_perimeter()<<endl;
    out<<"Static type:   "<<typeid(this).name()<<endl;
    out<<"Dynamic type:  "<<typeid(*this).name()<<endl;
    return out.str();
}

vector <vector <char >> AcuteTriangle::draw(char fChar, char bChar){
    Grid grid;
    int h = (base + 1) / 2;
    int right = (base + 1) / 2;
    int left = right;
    for(int i = 0; i < h; i++){
        vector<char> r;
        for(int k = 0; k <= base; k++){
            if(k >=left && k <= right) {
                r.push_back(fChar);
            }else{
                r.push_back(bChar);
            }
        }

        grid.push_back(r);
        left--;
        right++;
    }
    return grid;
}