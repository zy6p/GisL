//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DAUNIT_H
#define GISL_DAUNIT_H


class DaUnit {
public:
    int index;
    char value;

    DaUnit(char value, int index);

    ~DaUnit();

    static bool isSmaller(DaUnit &unit1, DaUnit &unit2);
};


#endif //GISL_DAUNIT_H
