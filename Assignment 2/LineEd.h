//
// Created by Lekang Du on 2019-06-22.
//

#ifndef ASSIGNMENT_2_LINEED_H
#define ASSIGNMENT_2_LINEED_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Command.h"

using namespace std;
class LineEd {
private:
    string file_name;
    list<string> buffer;
    int curline;
    vector<string> clipboard;
    bool state;
    void carryOut(Command &com);
public:
    LineEd(const string fileName);
    void run();
    void Appends();
};


#endif //ASSIGNMENT_2_LINEED_H
