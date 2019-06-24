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
    vector<string> clipboard;
    bool state;
public:
    LineEd(string fileName);
    void run();
};


#endif //ASSIGNMENT_2_LINEED_H
