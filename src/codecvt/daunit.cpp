//
// Created by beiyu on 2020-12-06.
//

#include "daunit.h"

namespace gisl {

DaUnit::DaUnit(char value, int index) {
    this->index = index;
    this->value = value;
}

bool DaUnit::isSmaller(const DaUnit& unit1, const DaUnit& unit2) {
    return unit1.index < unit2.index;
}

DaUnit::DaUnit() = default;

DaUnit::~DaUnit() = default;

} // namespace gisl