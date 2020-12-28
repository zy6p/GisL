/*!
 * @file plottest.cpp
 * @author omega 
 * @date 22/12/2020
 * 
 * @brief test paint
 * @details 
 * @verbatim
 *
 */

#include <iostream>
#include <string>
#include "../src/gui/sld.h"

int main(int argc, char *argv[]) {
    std::string sldFilename = "../resource/practise_6/qu-style.sld";
    auto sld = GisL::Sld( sldFilename );
    for ( auto &i : sld ) {
        std::cout << i.first << "\t->" << i.first << "\n";
    }


    return 1;
}

