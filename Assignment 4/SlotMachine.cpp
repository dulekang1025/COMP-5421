//
// Created by Lekang Du on 2019-07-30.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <set>
#include "SlotMachine.h"
#include "Rhombus.h"
#include "AcuteTriangle.h"
#include "RightTriangle.h"
#include "Rectangle.h"
void SlotMachine::run() {
    int tokens = 10;
    cout << "Welcome to 3-Reel Lucky Slot Machine Game!\n"
            "Each reel will randomly display one of four shapes , each in 25 sizes.\n"
            "To win 3 x bet Get 2 similar shapes AND 2 shapes with equal Scr Areas\n"
            "To win 2 x bet Get 3 similar shapes\n"
            "To win 1 x bet Get (Middle) Scr Area > (Left + Right) Scr Areas\n"
            "To win or lose nothing Get same Left and Right shapes\n"
            "Otherwise , you lose your bet.\n"
            "You start with 10 free slot tokens!";

    // step 1
    //reel[0] =

    while (tokens > 0) {
        vector<int> type;
        set<int> stype;
        set<int> area;
        cout << "How much would you like to bet (enter 0 to quit)?";
        string input;
        cin >> input;
        if (input == "0") break;
        int num = stoi(input);
        for (int i = 0; i < 3; i++) {
            // random int(0<=n<=3)
            int n = rand() % 4;
            type.push_back(n);
            stype.insert(n);
            //cout << n << endl;
            // random width (1<= w <= 25)
            int w = rand() % 25 + 1;
            //cout<<w<<endl;
            if (n == 0) {
                reel[i].reset(new Rhombus(w));
            } else if (n == 1) {
                reel[i].reset(new AcuteTriangle(w));

            } else if (n == 2) {
                reel[i].reset(new RightTriangle(w));

            } else {
                int h = rand() % 25 + 1;
                reel[i].reset(new Rectangle(w, h));

            }
        }

        // print the three reels
        Grid box_0 = reel[0]->draw();
        Grid box_1 = reel[1]->draw();
        Grid box_2 = reel[2]->draw();
        int long_h;
        if (box_1.size() >= box_2.size() && box_1.size() >= box_0.size()) {
            long_h = box_1.size();
        } else if (box_2.size() > box_1.size() && box_2.size() >= box_0.size()) {
            long_h = box_2.size();
        } else if (box_0.size() > box_1.size() && box_0.size() > box_2.size()) {
            long_h = box_0.size();
        }

        int hh = long_h + 5;
        int ww = 10 + box_0[0].size() + box_0[1].size() + box_0[2].size();
        //cout << "hh " << hh << "ww " << ww << endl;
        Grid big;
        big.clear();
        for (int i = 0; i < hh; i++) {
            vector<char> r;
            if (i == 0 || i == hh - 1) {
                r.push_back('+');
                r.push_back(' ');
                for (int k = 0; k < box_0[0].size(); k++) {
                    r.push_back('-');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_1[0].size(); k++) {
                    r.push_back('-');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_2[0].size(); k++) {
                    r.push_back('-');
                }
                r.push_back(' ');
                r.push_back('+');
            } else if (i == 1) {
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_0[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_1[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_2[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
            } else if (i == hh - 2) {
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_0[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_1[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_2[0].size(); k++) {
                    r.push_back(' ');
                }
                r.push_back(' ');
                r.push_back('|');
            } else {

                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_0[0].size(); k++) {
                    if (i - 2 >= box_0.size()) {
                        r.push_back(' ');
                    } else {
                        r.push_back(box_0[i - 2][k]);
                    }
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_1[0].size(); k++) {
                    if (i - 2 >= box_1.size()) {
                        r.push_back(' ');
                    } else {
                        r.push_back(box_1[i - 2][k]);
                    }
                }
                r.push_back(' ');
                r.push_back('|');
                r.push_back(' ');
                for (int k = 0; k < box_2[0].size(); k++) {
                    if (i - 2 >= box_2.size()) {
                        r.push_back(' ');
                    } else {
                        r.push_back(box_2[i - 2][k]);
                    }
                }
                r.push_back(' ');
                r.push_back('|');

            }
            big.push_back(r);
            r.clear();
        }
            // print
            for (const auto &row : big) {
                for (const auto &element : row) {
                    cout << element;
                }
                cout << endl;
            }
            big.clear();

            // cul tokens
            area.insert(reel[0]->screen_area());
            area.insert(reel[1]->screen_area());
            area.insert(reel[2]->screen_area());

            if(stype.size() <= 2 && area.size() <= 2){
                num *= 3;
            }
            else if(stype.size() == 1){
                num *= 2;
            }
            else if(reel[1]->screen_area() > (reel[0]->screen_area()+reel[2]->screen_area())){
                num = num;
            } else if(type[0] == type[2]){
                num = 0;
            } else{
                num *= -1;
            }

            tokens += num;
            reel[0].release();
            reel[1].release();
            reel[2].release();
            type.clear();
            stype.clear();
            area.clear();
        }
    }

    void SlotMachine::display() {

    }

    void SlotMachine::make_shape(int k) {

    }

    void SlotMachine::make_shapes() {

    }
