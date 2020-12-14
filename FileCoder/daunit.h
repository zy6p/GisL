//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DAUNIT_H
#define GISL_DAUNIT_H

namespace GisL {

    class DaUnit {
    public:
        int index{};
        char value{};

        DaUnit();

        DaUnit(char value, int index);

        ~DaUnit();

        static bool isSmaller(const DaUnit &unit1, const DaUnit &unit2);
    };

}

#endif //GISL_DAUNIT_H
