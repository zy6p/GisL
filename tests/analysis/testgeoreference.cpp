//
// Created by km on 6/17/21.
//
#include <catch2/catch.hpp>

#include "analysis/georeference.h"
#include "core/layer/layertree.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

TEST_CASE("GeoReference") {
  gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
  auto input = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
  std::string fileName1 = STRINGIFY(TEST_DATA_DIR) "rs/2/wucesource.tif";
  input->loadData(fileName1);
  layerTree->append(input->getFid(), input.get());
//  auto ref = new gisl::RasterProvider();
//  std::string fileName2 = STRINGIFY(TEST_DATA_DIR) "rs/2/wucehelo.tif";
//  input->loadData(fileName2);
//  layerTree->append(ref->getFid(), ref);
  std::string fileName3 = STRINGIFY(TEST_DATA_DIR) "rs/2/transpos.csv";

//  auto alg = gisl::GeoReference();
//  alg.realAlg(input.get(), ref, fileName3);

  CHECK(input->getLayerCount() == 3);
//  CHECK(alg.getTrans2D().trans.rows() == 6);
//  CHECK(alg.getTrans2D().trans.cols() == 2);
//  delete ref;
}
