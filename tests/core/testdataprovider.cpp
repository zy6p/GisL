//
// Created by km on 6/10/21.
//

#define CATCH_CONFIG_MAIN

#include <absl/strings/string_view.h>
#include <catch2/catch.hpp>
#include <string>

#include "core/provider/dataprovider.h"
#include "core/provider/vectorprovider.h"

TEST_CASE("VectorProvider::loadData") {
  gisl::VectorProvider* pVectorProvider = new gisl::VectorProvider();
  std::string fileName = "../tests/data/qu.geojson";
  pVectorProvider->loadData(fileName);

  CHECK(pVectorProvider->getLayerCount() == 1);
  delete pVectorProvider;
}
