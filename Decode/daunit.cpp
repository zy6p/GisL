//
// Created by beiyu on 2020-12-06.
//

#include "daunit.h"

DaUnit::DaUnit(char value, int index) {
    this->index = index;
    this->value = value;
}

bool DaUnit::isSmaller(DaUnit& unit1, DaUnit& unit2){
    return unit1.index < unit2.index;
}