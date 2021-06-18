//
// Created by omega on 6/18/21.
//

#ifndef GISL_RSINDEX_H
#define GISL_RSINDEX_H

#include <Eigen/Dense>

#include "analysisalg.h"
#include "core/raster/rasterband.h"

namespace gisl {
class RsIndex : public AnalysisAlg {
public:
  enum class RsIndexMethod {
    Normal = 0,
    NDWI = 1,
    MNDWI = 2,
  };
  void execute(QWidget* parent) override;
  void execAlg() override;
  void initGui() override;
  void reverse() override;
  const std::string& output() override;
  void realAlg(RsIndexMethod m, RasterBand& band1, RasterBand& band2);

  void toImg();

private:
  Eigen::MatrixXf index;
  QImage qImage;
  std::string imgFileName;
};
} // namespace gisl
#endif // GISL_RSINDEX_H
