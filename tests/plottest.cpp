/*!
 * @file plottest.cpp
 * @author omega 
 * @date 22/12/2020
 * 
 * @brief test plot
 * @details 
 * @verbatim
 *
 */

#include <string>
#include "../src/plot/sld.h"

int main(int argc, char *argv[]) {
    std::string sldFilename = "../data/practise_6/data/qu-style.sld";
    GisL::Sld sld = GisL::Sld(sld);

    printf("%s", sldFilename.c_str());


    return 1;
}

