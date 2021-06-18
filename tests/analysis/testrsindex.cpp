//
// Created by omega on 6/18/21.
//
#include <catch2/catch.hpp>

#include "analysis/rsindex.h"
#include "core/layer/layertree.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

TEST_CASE("RsIndex-GaoJing") {
    gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
    auto input = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
    std::string fileName1 = STRINGIFY(TEST_DATA_DIR) "rs/1/gaojing_subset.tif";
    input->loadData(fileName1);
    layerTree->append(input->getFid(), input.get());

    gisl::RsIndex alg{};
    alg.realAlg(
        gisl::RsIndex::RsIndexMethod::NDWI,
        *input->getPmBand()[0],
        *input->getPmBand()[1]);
    alg.realAlg(
        gisl::RsIndex::RsIndexMethod::NDWI,
        *input->getPmBand()[0],
        *input->getPmBand()[2]);
    alg.realAlg(
        gisl::RsIndex::RsIndexMethod::NDWI,
        *input->getPmBand()[0],
        *input->getPmBand()[3]);
}

TEST_CASE("RsIndex") {
    gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
    auto input = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
    std::string fileName1 = STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF";
    input->loadData(fileName1);
    layerTree->append(input->getFid(), input.get());
    auto input2 = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
    std::string fileName2 = STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B4.TIF";
    input2->loadData(fileName2);
    layerTree->append(input2->getFid(), input2.get());

    gisl::RsIndex alg{};
    alg.realAlg(
        gisl::RsIndex::RsIndexMethod::NDWI,
        *input->getPmBand()[0],
        *input2->getPmBand()[0]);
}
