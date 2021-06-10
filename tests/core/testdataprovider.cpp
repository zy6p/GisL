//
// Created by km on 6/10/21.
//

#define CATCH_CONFIG_MAIN

#include <string>
#include <catch2/catch.hpp>
#include <absl/strings/string_view.h>

#include "../../src/core/provider/dataprovider.h"
#include "../../src/core/provider/vectorprovider.h"

TEST_CASE("VectorProvider::loadData") {
  gisl::DataProvider* pVectorProvider = new gisl::VectorProvider();
  std::string fileName = "/home/km/dev/gisl/tests/data/qu.geojson";
  absl::string_view sv = fileName;
  pVectorProvider->loadData(sv);

  CHECK(pVectorProvider->hasError());

}
