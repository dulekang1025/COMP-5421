//
// Created by Lekang Du on 2019-06-22.
//

#include "LineEd.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/**
 * Ctor of LineEd
 * @param fileName name of the file
 */
LineEd::LineEd(const string fileName) {
    LineEd::file_name = fileName;
    if(file_name == ""){
        curline = 0;
        state = false;
        buffer.clear();
        clipboard.clear();
        cout << "\"?\"" << " " << "[New File]" << endl;
        cout << "Entering command mode." << endl;
    } else{
        ifstream infile(fileName);
        if(!infile.is_open()){
            cout<<"Can not open file"<<endl;
        } else{
            string temp;
            while(getline(infile,temp)){
                //getline(infile,temp);
                Appends(temp);
            }
            state = false;
            cout<<"\""<< file_name<<"\" "<<buffer.size()<<" lines"<<endl;
            cout<<"Entering command mode."<<endl;
        }
    }
}

/**
 * function for test
 * @param command input command line
 */
void LineEd::runCommand(string command) {
    Command com;
    com.parse(command,curline,buffer.size());  //commandLine,curline,buffer.size()
    if(com.getSymbol() != ""){
        carryOut(com);
    }
}

/**
 * function to run the LineEd
 */
void LineEd::run() {
    string commandLine;
    cout<<"? ";
    getline(cin,commandLine);
    Command com;
    com.parse(commandLine,curline,buffer.size());  //commandLine,curline,buffer.size()
    while(com.getSymbol() != "q"){
        if(com.getSymbol() == ""){
            cout<<"? ";
            getline(cin,commandLine);
            com.parse(commandLine,curline,buffer.size());
            continue;
        }
        carryOut(com);
        cout<<"? ";
        getline(cin,commandLine);
        com.parse(commandLine,curline,buffer.size());
    }

    if(com.getSymbol() == "q"){
        carryOut(com);
    }
}

/**
 * function to carry out operations
 * @param com object of calss Command
 */
void LineEd::carryOut(Command &com) {
    if(com.getSymbol() == "a"){
        Appends();
        return;
    }

    if(com.getSymbol() == "p"){
        Prints(com.getAddress1(),com.getAddress2());
        return;
    }

    if(com.getSymbol() == "i"){
        if(com.getAddress1() != ""){
            Inserts(stoi(com.getAddress1()));
        } else{
            Appends();
        }

        return;
    }

    if(com.getSymbol() == "d"){
        Deletes(com.getAddress1(),com.getAddress2());
    }

    if(com.getSymbol() == "u"){
        Up();
    }

    if(com.getSymbol() == "n"){
        Down();
    }

    if(com.getSymbol() == "g"){
        Goes(com.getAddress1());
    }

    if(com.getSymbol() == "q"){
        Quit();
    }

    if(com.getSymbol() == "x"){
        Cuts(com.getAddress1(),com.getAddress2());
    }

    if(com.getSymbol() == "j"){
        Joins(com.getAddress1(),com.getAddress2());
    }

    if(com.getSymbol() == "c"){
        Changes(com.getAddress1(),com.getAddress2());
    }

    if(com.getSymbol() == "v"){
        //cout<<"LUCK"<<com.getAddress1()<<endl;
        Pastes(com.getAddress1());
    }

    if(com.getSymbol() == "w"){
        string temp;
        cout<<"Save the changes to the file: "<< file_name <<"(y or n)?"<<endl;
        cin.clear();
        getline(cin, temp);
        if (temp == "y" || temp == "Y") {
            Writes("");
        }
    }
}

/**
 * funtions to append lines in buffer after the last line
 */
void LineEd::Appends() {
    cout<<"Entering input mode."<<endl;
    int count{0};
    int size = buffer.size();
    string temp;
    cin.clear();
    getline(cin,temp);
    while(temp != "."){
        buffer.push_back(temp);
        count++;
        cin.clear();
        getline(cin,temp);
    }
    curline = size + count;
    //cout<<"Curline is "<<curline<<endl;
    state = false;
}

/**
 * functions to print lines in buffer
 * @param address1 first address
 * @param address2 second address
 */
void LineEd::Prints(string address1,string address2) {
    if(buffer.size() == 0){
        return;
    }
    if(address1 == "BAD"){
        return;///////////////////////////////////////////
    }
    if(address2 == "BAD"){
        return;///////////////////////////////////////////
    }
    if(address1 == ""){
        address1 = to_string(curline);///////////////////////////////////////////
    }
    if(address2 == ""){
        address2 = to_string(curline);///////////////////////////////////////////
    }
    auto it = buffer.begin();
    advance(it,stoi(address1)-1);
    if(address1 == address2){
        cout<<address1<< ">  " << *it<<endl;
    } else{
        for(int curr = stoi(address1);curr <= stoi(address2);curr++,it++){
            if(curr != stoi(address2)){
                cout <<curr<< ":  " << *it << endl;
            } else{
                cout <<curr<< ">  " << *it << endl;
            }
        }
    }
}

/**
 * functions to insert a line at postion line
 * @param line postion which insert happens
 */
void LineEd::Inserts(int line) {
    int count{0};
    if(buffer.size() == 0){
        //cout<<"Buffer is empty, insert from line 1."<<endl;
        Appends();
    }else if(line > buffer.size()){
        cout<<"Insert line number is larger than buffer size, insert after the last line."<<endl;
        Inserts(buffer.size());
    } else{
        string temp;
        cin.clear();
        clipboard.clear();
        getline(cin,temp);
        while(temp != "."){
            clipboard.push_back(temp);
            getline(cin,temp);
        }
        auto it = buffer.begin();
        advance(it,line-1);
        buffer.insert(it, clipboard.begin(),clipboard.end());
        curline = line + clipboard.size() - 1;
    }
    clipboard.clear();
    //cout<<"Curline is "<<curline<<endl;
    state = false;
}

/**
 * funciotn to delete a range of line in buffer
 * @param address1 first address
 * @param address2 second address
 */
void LineEd::Deletes(string address1, string address2) {
    if(buffer.size() == 0){
        cout<<"Buffer is empty, can not delete.";
    } else{
        auto it1 = buffer.begin();
        auto it2 = buffer.begin();
        advance(it1,stoi(address1) - 1);
        advance(it2,stoi(address2));
        buffer.erase(it1,it2);
        if(stoi(address2) < buffer.size()){
            curline = stoi(address1);
        }
        if(stoi(address2) == 1){
            curline = 1;
        }
        if(stoi(address2) == buffer.size()){
            curline = stoi(address1) - 1;
        }
        if(buffer.size() == 0){
            curline = 0;
        }
    }
    //cout<<"Curline is "<<curline<<endl;
    state = false;

}

/**
 * functions to move curline up and print it
 */
void LineEd::Up() {
    if(curline == 1){
        cout<<"BOF reached."<<endl;
    } else{
        curline = curline - 1;
    }
    auto it = buffer.begin();
    advance(it,curline-1);
    cout<<curline<<"> "<<*it<<endl;
}
/**
 * functions to move curline down and print it
 */
void LineEd::Down() {
    if(curline == buffer.size()){
        cout<<"EOF reached."<<endl;
        return;
    } else{
        curline = curline + 1;
    }
    auto it1 = buffer.begin();
    advance(it1,curline-1);
    cout<<curline<<"> "<<*it1<<endl;
}

/**
 * functions to print a line
 * @param address1 line that need to be print
 */
void LineEd::Goes(string address1) {
    if(address1 == "0"){
        curline = 1;
        auto it = buffer.begin();
        advance(it,curline-1);
        cout<<curline<<"> "<<*it<<endl;
    } else{
        curline = stoi(address1);
        auto it = buffer.begin();
        advance(it,curline-1);
        cout<<curline<<"> "<<*it<<endl;
    }
}

/**
 * function to write buffer in to disk
 * @param fileName name of the file
 */
void LineEd::Writes(string fileName) {
    if(fileName.size() != 0){
        file_name = fileName;
        ofstream outfile (file_name);   //Assignment 2/as.txt
        auto it = buffer.begin();
        for(it;it != buffer.end();it++){
            outfile<<*it<<endl;
        }
    } else{
        ofstream outfile (file_name);
        auto it = buffer.begin();
        int count{0};
        for(it;it != buffer.end();it++){
            if(count < buffer.size()-1){
                outfile<<*it<<endl;
                count++;
            } else{
                outfile<<*it;
                count++;
            }
        }
    }
    cout<<buffer.size()<<" lines written to file "<<"\""<< file_name<<"\""<<endl;
    state = true;
}

/**
 * function to quit the program
 */
void LineEd::Quit() {
    string tempYesNo;
    if (!state) {
        if (file_name.size() == 0) {
            cout << "There are unsaved changes.\nDo you wish to save the changes (y or n)?" << endl;
            cin.clear();
            getline(cin, tempYesNo);
            if (tempYesNo == "y" || tempYesNo == "Y") {
                string temp;
                cout << "Enter the name of a file to write to: " << endl;
                cin.clear();
                getline(cin, temp);
                Writes(temp);
            }
        } else {
            cout<<"Save the changes to the file: "<< file_name <<"(y or n)?"<<endl;
            cin.clear();
            getline(cin, tempYesNo);
            if (tempYesNo == "y" || tempYesNo == "Y") {
                Writes("");
            }
        }
        cout<<"bye"<<endl;
    }
}
/**
 * overload function of append
 * @param line line need to be append
 */
void LineEd::Appends(string line) {
    int count{0};
    int size = buffer.size();
    buffer.push_back(line);
    count++;
    curline = size + count;
    //cout<<"Curline is "<<curline<<endl;
    state = false;

}

/**
 * function to paste lines from clipborad
 * @param address postion where paste happens
 */
void LineEd::Pastes(string address) {
    //cout<<"LUCK"<<address<<endl;
    auto it = buffer.begin();
    advance(it,stoi(address)-1);
    buffer.insert(it, clipboard.begin(),clipboard.end());
    curline = stoi(address) + clipboard.size();
    //cout<<curline<<endl;
    clipboard.clear();
    state = false;
}
/**
 * function to cut lines from buffer
 * @param address1 first line
 * @param address2 second line
 */
void LineEd::Cuts(string address1, string address2) {
    auto it = buffer.begin();
    auto it2 = buffer.begin();
    advance(it,stoi(address1)-1);
    advance(it2,stoi(address2));
    for(int l = stoi(address1); l <= stoi(address2); it++, l++){
        clipboard.push_back(*it);
        //cout<<"LUCK   "<<*it<<endl;
    }
    it = buffer.begin();
    it2 = buffer.begin();
    advance(it,stoi(address1)-1);
    advance(it2,stoi(address2));
    buffer.erase(it,it2);
    if(stoi(address2) < buffer.size()){
        curline = stoi(address1);
        //cout<<"1111111111111"<<endl;
    }
    if(stoi(address2) == 1){
        //cout<<"2222222222222"<<endl;
        curline = 1;
    }
    if(stoi(address2) == buffer.size()){
        //cout<<"333333333333333"<<endl;
        curline = stoi(address1) - 1;
    }
    if(buffer.size() == 0){
        //cout<<"444444444444444"<<endl;
        curline = 1;
    }
    //cout<<"Luck current line "<<curline<<endl;
    state = false;

}
/**
 * function to join lines
 * @param address1 first address
 * @param address2 second address
 */
void LineEd::Joins(string address1, string address2) {
    auto it = buffer.begin();
    auto it2 = buffer.begin();
    advance(it,stoi(address1)-1);
    advance(it2,stoi(address2));
    string temp;
    for(int l = stoi(address1); l <= stoi(address2); it++, l++){
         temp += *it;
    }
    it = buffer.begin();
    it2 = buffer.begin();
    advance(it,stoi(address1)-1);
    advance(it2,stoi(address2));
    // inserts at address1
    buffer.insert(it, temp);
    //Inserts(stoi(address1), temp);
    buffer.erase(it,it2);
    curline = stoi(address1);
    //cout<<"Curline is "<<curline<<endl;
    state = false;

}
/**
 * overload function of insert()
 * @param line line need to be insert
 * @param templine helper para
 */
void LineEd::Inserts(int line, string templine) {
    int count{0};
    if(buffer.size() == 0){
        //cout<<"Buffer is empty, insert from line 1."<<endl;
        Appends(templine);
    }else if(line > buffer.size()){
        cout<<"Insert line number is larger than buffer size, insert after the last line."<<endl;
        Inserts(buffer.size());
    } else{
        cin.clear();
        //clipboard.clear();
        vector<string> temp;
        temp.push_back(templine);

        auto it = buffer.begin();
        advance(it,line-1);
        buffer.insert(it, clipboard.begin(),clipboard.end());
        //curline = line + clipboard.size() - 1;
    }
    //cout<<"Curline is "<<curline<<endl;
}

/**
 * function to change strings in the lines
 * @param address1 first address
 * @param address2 second address
 */
void LineEd::Changes(string address1, string address2) {
    string change;
    string to;
    cout<<"Change ?"<<endl;
    cin.clear();
    getline(cin,change);
    cout<<"    to ?"<<endl;
    cin.clear();
    getline(cin,to);
    auto it = buffer.begin();
    auto it2 = buffer.begin();
    advance(it,stoi(address1)-1);    // new changes ,ranges
    advance(it2,stoi(address2));
    for(int i = stoi(address1); i <= stoi(address2);i++,it++){
        int pos = 0;
        for(int j = 0; j <(*it).length();j++ ){
            pos = (*it).find(change);
            if(pos != string::npos){
                (*it).replace(pos,change.size(),to);
                j = (int)(pos + change.size());
                curline = i;
            } else{
                break;
            }

        }
    }
    state = false;
}



