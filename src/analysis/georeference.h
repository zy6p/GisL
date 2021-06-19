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
#include "core/geometry/rectangle.h"

namespace gisl {
class RasterProvider;

class Trans2D {
public:
    Eigen::MatrixXf inPos;
    Eigen::MatrixXf refPos;
    Eigen::Matrix2f accuracyPos;
    Eigen::MatrixXf trans;
    Eigen::MatrixXf adjust_A;
    std::pair<float, float> transRec;
    void loadPosData(std::string_view sv);
    void adjust();
    std::pair<float, float> transPoint(float x, float y);
    void transRectangle(const gisl::Rectangle& in, gisl::Rectangle& out);
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
    void realAlg(const RasterProvider* input, std::string_view posFileName);
    const Trans2D& getTrans2D() const;

private:
    QComboBox* pProviderBox = nullptr;
    QLineEdit* pPosLineEdit = nullptr;

    Trans2D trans2D;
};
} // namespace gisl
#endif // GISL_GEOREFERENCE_H
