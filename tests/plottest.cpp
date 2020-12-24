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
    std::string sldFilename = "../data/practise_6/qu-style.sld";
    GisL::Sld *sld = new GisL::Sld(sldFilename);
//    sld->loadSldFile(sldFilename);

    printf("%s", sldFilename.c_str());


    return 1;
}

