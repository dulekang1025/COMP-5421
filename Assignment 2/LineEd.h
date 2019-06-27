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
    void Appends();
    void Prints(string address1,string address2);
    void Inserts(int line);
    void Pastes(string address);
    void Deletes(string address1,string address2);
    void Up();
    void Down();
    void Goes(string address1);
    void Writes(string fileName);
    void Quit();
    void Appends(string line);
    void Cuts(string address1,string address2);
    void Joins(string address1,string address2);
    void Inserts(int line,string address);
    void Changes(string address1,string address2);
public:
    LineEd(const string fileName);
    void run();
    void runCommand(string command);
};


#endif //ASSIGNMENT_2_LINEED_H
