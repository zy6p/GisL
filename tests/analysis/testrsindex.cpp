//
// Created by omega on 6/18/21.
//
#include <catch2/catch.hpp>

#include "analysis/rsindex.h"
#include "core/layer/layertree.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

TEST_CASE("RsIndex") {
  gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
  auto input = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
  std::string fileName1 = STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B1.TIF";
  input->loadData(fileName1);
  layerTree->append(input->getFid(), input.get());

  gisl::RsIndex alg{};
  //  alg.realAlg(gisl::RsIndex::RsIndexMethod::NDWI, input->getPmBand()[1])
}
