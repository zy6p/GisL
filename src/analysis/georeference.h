//
// Created by km on 6/14/21.
//

#ifndef GISL_GEOREFERENCE_H
#define GISL_GEOREFERENCE_H

#include <Eigen/Dense>
#include <QComboBox>
#include <QLineEdit>
#include <string>

#include "analysisalg.h"

namespace gisl {
class RasterProvider;

class Trans2D {
public:
  static void loadPosData(
      std::string_view sv,
      Eigen::MatrixXf& inPos,
      Eigen::MatrixXf& refPos);
  static void adjust(
      Eigen::MatrixXf& inPos,
      Eigen::MatrixXf& refPos,
      Eigen::MatrixXf& trans);
};

class GeoReference final : public AnalysisAlg {
public:
  void execute(QWidget* parent) override;
  ~GeoReference() override;
  void initGui() override;
  void reverse() override;
  const std::string& output() override;
  void execAlg() override;

  /**
   * the real alg method, and can be called without gui
   * @param input
   * @param ref
   * @param posFileName
   */
  void realAlg(
      RasterProvider* input,
      RasterProvider* ref,
      std::string_view posFileName);

private:
  QComboBox* pProviderBox1 = nullptr;
  QComboBox* pProviderBox2 = nullptr;
  QLineEdit* pPosLineEdit = nullptr;
};
} // namespace gisl
#endif // GISL_GEOREFERENCE_H
