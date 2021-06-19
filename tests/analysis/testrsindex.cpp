//
// Created by omega on 6/18/21.
//
#include <catch2/catch.hpp>
#include <filesystem>

#include "analysis/rsindex.h"
#include "core/layer/layertree.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

TEST_CASE("RsIndex") {
  struct RsIndexTestCase {
    std::string rs1;
    std::string rs2;
    int band1;
    int band2;
    gisl::RsIndex::RsIndexMethod m;
    std::string outputFileName;
  };

  auto testCase = GENERATE(
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif",
          STRINGIFY(TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif",
          0,
          1,
          gisl::RsIndex::RsIndexMethod::NDWI,
          STRINGIFY(
              TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif.NDWI.png"},
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif",
          STRINGIFY(TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif",
          0,
          1,
          gisl::RsIndex::RsIndexMethod::MNDWI,
          STRINGIFY(
              TEST_DATA_DIR) "rs/1/combination/gaojing_subset.tif.MNDWI.png"},
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B2.TIF",
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B4.TIF",
          0,
          0,
          gisl::RsIndex::RsIndexMethod::NDWI,
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B2.TIF.NDWI.png"},
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B2.TIF",
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B5.TIF",
          0,
          0,
          gisl::RsIndex::RsIndexMethod::MNDWI,
          STRINGIFY(TEST_DATA_DIR) "rs/3/2005_09_11_B2.TIF.MNDWI.png"},
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF",
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B5.TIF",
          0,
          0,
          gisl::RsIndex::RsIndexMethod::MNDWI,
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF.MNDWI.png"},
      RsIndexTestCase{
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF",
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B4.TIF",
          0,
          0,
          gisl::RsIndex::RsIndexMethod::NDWI,
          STRINGIFY(TEST_DATA_DIR) "rs/3/1993_10_12_B2.TIF.NDWI.png"});
  gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
  auto input = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
  input->loadData(testCase.rs1);
  auto input2 = std::make_shared<gisl::RasterProvider>(gisl::RasterProvider());
  input2->loadData(testCase.rs2);
  layerTree->append(input->getFid(), input.get());
  layerTree->append(input2->getFid(), input2.get());

  gisl::RsIndex alg{};
  alg.realAlg(
      testCase.m,
      *input->getPmBand()[testCase.band1],
      *input2->getPmBand()[testCase.band2]);

  auto path = std::filesystem::path(testCase.outputFileName.c_str());
  CHECK(std::filesystem::exists(path));
}