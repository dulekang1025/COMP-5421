//
// Created by Lekang Du on 2019-07-30.
//

#ifndef A4_SLOTMACHINE_H
#define A4_SLOTMACHINE_H

#include <array>
#include "Shape.h"

class SlotMachine {
    std::array <std:: unique_ptr <Shape >, 3> reel{};
    void make_shapes(); // Step 4
    void make_shape(int k);
    void display();
public:
    SlotMachine () = default;
    SlotMachine(const SlotMachine&) = delete; //copy ctor
    SlotMachine(SlotMachine &&) = delete; //move ctor
    SlotMachine& operator=(const SlotMachine&) = delete; //copy assignment
    SlotMachine& operator=(SlotMachine &&) = delete; //move assignment
    virtual ~ SlotMachine () = default;
    void run();// see algorithm on page 13

};


#endif //A4_SLOTMACHINE_H
