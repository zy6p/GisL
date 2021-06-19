/*!
 * @author tau
 * @date 12/29/20
 */

#ifndef GISL_RECTANGLE_H
#define GISL_RECTANGLE_H

#include <QPointF>
#include <QRectF>
#include <QVector4D>
#include <ogr_geometry.h>

namespace gisl {
class Rectangle : public OGREnvelope {
public:
    explicit Rectangle(OGREnvelope& envelope);
    Rectangle(float minX, float maxX, float minY, float maxY);
    Rectangle();

    void merge(Rectangle const& sOther);
    void merge(double dfX, double dfY);

    constexpr bool inside(const std::pair<float, float>& p) const noexcept;

    QRectF getQRectF() const;
    QPointF center() const;
    QVector4D center4D() const;

    float minX;
    float maxX;
    float minY;
    float maxY;

private:
    OGREnvelope* pmEnvelope;
};
} // namespace gisl

#endif // GISL_RECTANGLE_H
