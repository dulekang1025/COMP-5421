//
// Created by Lekang Du on 2019-07-30.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Rhombus.h"
#include "math.h"

using namespace std;
using Grid = vector <vector <char >>;

Rhombus::Rhombus(int d):Shape("Ace","Ace of diamond") {
    if(d%2 == 0){
        d = d + 1;
    }
    dim = d;
    hight = d;
    width = d;
    Shape::identity = 2;
}

Rhombus::Rhombus(int d, string name, string description):Shape(name,description) {
    if(d%2 == 0){
        d = d + 1;
    }
    dim = d;
    hight = d;
    width = d;
    Shape::identity = 2;
}

string Rhombus::name_getter() {
    return Shape::user_supplied_name;
}

string Rhombus::supplied_description_getter() {
    return Shape::user_supplied_description;
}

double Rhombus::get_hight() {
    return hight;
}

double Rhombus::get_width() {
    return width;
}

int Rhombus::identity_getter() {
    return Shape::identity;
}

double Rhombus::compute_area() {
    return (double)(hight * width) / 2;
}

double Rhombus::compute_perimeter() {
    return (double)2 * sqrt(2) * dim;
}

int Rhombus::screen_area() {
    int n;
    if((dim/2) % 2 != 0){
        n = dim/2 + 1;
    } else{
        n = dim/2;
    }
//    cout<<">>>>>> "<<dim<<"~~~"<<n<<endl;
    return 2 * n * (n + 1) + 1;
}

int Rhombus::screen_perimeter() {
    return 2 * (dim - 1 );
}

string Rhombus::toString() {
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

vector <vector <char >> Rhombus::draw(char fChar, char bChar){
    Grid grid;
    int h = hight / 2;
    int right = hight / 2;
    int left = right;
    for(int i = 0; i <= h; i++){
        vector<char> r;
        for(int k = 0; k < hight; k++){
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
    left = 1;
    right = hight-2;
    for(int i = 0; i < h; i++){
        vector<char> r;
        for(int k = 0; k < hight; k++){
            if(k >=left && k <= right) {
                r.push_back(fChar);
            }else{
                r.push_back(bChar);
            }
        }
        grid.push_back(r);
        left++;
        right--;
    }
    return grid;
}
