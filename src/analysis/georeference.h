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
    Eigen::MatrixXf i2rTrans;
    Eigen::MatrixXf i2rAdjustA;
    Eigen::MatrixXf r2iTrans;
    Eigen::MatrixXf r2iAdjustA;
    std::pair<int, int> transRecMN;
    Eigen::Matrix<float, 4, 2> inRecPos;
    Eigen::Matrix<float, 4, 2> outRecPos;

    void loadPosData(std::string_view sv);
    void adjust();
    [[nodiscard]] std::pair<float, float>
    i2rTransPoint(const std::pair<int, int>& p) const noexcept;
    [[nodiscard]] std::pair<float, float>
    r2iTransPoint(const std::pair<int, int>& p) const noexcept;
    void i2rTransRectangle(const gisl::Rectangle& in);
    [[nodiscard]] bool isIInsideR(int x, int y) const noexcept;
    [[nodiscard]] bool isRInsideI(const std::pair<int, int>& q) const noexcept;
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
     * @param posFileName
     */
    void realAlg(const RasterProvider* input, std::string_view posFileName);
    [[nodiscard]] const Trans2D& getTrans2D() const;

private:
    QComboBox* pProviderBox = nullptr;
    QLineEdit* pPosLineEdit = nullptr;

    Eigen::MatrixXf out;
    QImage outImage;

    Trans2D trans2D;
};
} // namespace gisl
#endif // GISL_GEOREFERENCE_H
