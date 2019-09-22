//
// Created by Lekang Du on 2019-07-30.
//
#include<iostream>
#include<array>
#include <vector>
//#include "Shape.h"
//#include "Triangle"
#include "Rhombus.h"
#include "Rectangle.h"
#include "AcuteTriangle.h"
#include "RightTriangle.h"
#include "SlotMachine.h"
using std::cout;
using std::cin;
using std::endl;
using Grid = vector <vector <char >>;

void play_shape_slot_machine();
void shape_examples();
ostream & operator<<(ostream & out, Shape & shape);

ostream& operator<< (ostream& sout, const Grid& grid)
{
    for (const auto& row : grid) // for each row vector in the grid
    {
        for (const auto& element : row) // for each element (char) in the row vector
        {
            sout << element;
        }
        sout << endl; // line break
    }
    return sout;
}

void play_shape_slot_machine()
{
    SlotMachine sm;
    sm.run();
}

void shape_examples()
{

    Rectangle rect{ 5, 7 };
    cout << rect.toString() << endl;
    // or equivalently
     cout << rect << endl;
    //------------------------------------------------------------
    Rhombus ace{ 16, "Ace", "Ace of diamond" };
    cout << ace.toString() << endl;
//    // or, equivalently:
    cout << ace << endl;
//    //------------------------------------------------------------
    AcuteTriangle at{ 17 };
    cout << at << endl;
//
//    /*equivalently:
//
    Shape *atptr = &at;
    cout << *atptr << endl;

    Shape &atptrr = at;
    cout << atptrr << endl;
//
//    //------------------------------------------------------------
    RightTriangle rt{ 10, "Carpenter's square" };
    cout << rt << endl;
//    //------------------------------------------------------------
    Grid aceBox = ace.draw('+', '.');
    cout << aceBox << endl;

    Grid rectBox = rect.draw();
    cout << rectBox << endl;
//
    Grid atBox = at.draw('^');
    cout << atBox << endl;
//
    Grid rtBox = rt.draw('|');
    cout << rtBox << endl;
//
//    // draw rt and ace using different foreground and background characters
    rtBox = rt.draw('\\', 'o');
    cout << rtBox << endl;
//
    aceBox = ace.draw('o');
    cout << aceBox << endl;
}
ostream & operator<<(ostream & out, Shape & shape){
    out<<shape.toString();
    return out;
}
auto main() -> int
{
    shape_examples();
    play_shape_slot_machine();
    return 0;
}