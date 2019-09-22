//
// Created by Lekang Du on 2019-07-30.
//

#include "Shape.h"

Shape::Shape(string name, string description) {
    user_supplied_name = name;
    user_supplied_description = description;
}

string Shape::name_setter(string name) {
    user_supplied_name =name;
}

string Shape::supplied_description_setter(string description) {
    user_supplied_description = description;
}