//
// Created by km on 6/10/21.
//

#include "rasterprovider.h"
#include <src/core/layertree.h>
void gisl::RasterProvider::loadData(std::string_view theFileName,
                                    const std::string &theFileEncoding) {
  gisl::DataProvider::loadData(theFileName, theFileEncoding);

}
