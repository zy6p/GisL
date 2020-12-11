#include "StretchRenderer.h"


StretchRenderer::StretchRenderer() : min(99999999999999), max(-9999999999999) {
}

StretchRenderer::StretchRenderer(QList<float> valueDateset, QList<QColor> colors) {
    if (valueDateset.size()) {
        float result = valueDateset.at(0);
        for (int i = 0; i < valueDateset.size(); i++) {
            if (result < valueDateset.at(i)) {
                min = result;
            }
            if (result > valueDateset.at(i)) {
                max = result;
            }
        }
        dValue = max - min;
    }
    this->colors = colors;
}

StretchRenderer::~StretchRenderer() {
}

int StretchRenderer::size() {
    return colors.size();
}

QColor StretchRenderer::getColorAt(int i) {
    return colors.at(i);
}

void StretchRenderer::addColor(QColor color) {
    colors.push_back(color);
}

void StretchRenderer::setColors(QList<QColor> colors) {
    this->colors = colors;
}

void StretchRenderer::setRange(QList<float> valueDateset) {
    int idx1 = 0;
    int idx2 = 0;
    //����һ�����Զ������ָ�ֵ���ֵ
    if (valueDateset.size()) {
        min = valueDateset.at(0);
        max = valueDateset.at(0);
        for (int i = 0; i < valueDateset.size(); i++) {
            if (valueDateset.at(i) < min) {
                min = valueDateset.at(i);
                idx1 = i;
            }
            if (valueDateset.at(i) > max) {
                max = valueDateset.at(i);
                idx2 = i;
            }
        }
        valueDateset.removeAt(idx1);
        valueDateset.removeAt(idx2);

        min = valueDateset.at(0);
        max = valueDateset.at(0);
        for (int i = 0; i < valueDateset.size(); i++) {
            if (valueDateset.at(i) < min) {
                min = valueDateset.at(i);
                idx1 = i;
            }
            if (valueDateset.at(i) > max) {
                max = valueDateset.at(i);
                idx2 = i;
            }
        }
        dValue = max - min;
    }
}

void StretchRenderer::setRange(float max, float min) {
    this->max = max;
    this->min = min;
    this->dValue = max - min;
}

void StretchRenderer::insertColor(QColor color, int index) {
    QList<QColor> temp;
    for (int i = index; i < size(); i++) {
        temp.push_back(colors.at(i));
    }
    colors = colors.mid(0, index);
    colors.push_back(color);
    for (int i = 0; i < temp.size(); i++) {
        colors.push_back(temp.at(i));
    }
}

QList<QColor> StretchRenderer::getAllColors() {
    return colors;
}

QColor StretchRenderer::removeAt(int index) {
    QColor color = colors.at(index);
    colors.removeAt(index);
    return color;
}

QList<QColor> StretchRenderer::clear() {
    QList<QColor> result = colors;
    colors.clear();
    return result;
}

QColor StretchRenderer::cellColor(float value) {
    if (value >= min && value <= max) {
        if (colors.size() == 1) {
            return colors.at(0);
        } else if (colors.size() >= 2) {
            float eDValue = dValue / (colors.size() - 1);
            float indexF = (value - min) / eDValue;
            int index = qFloor(indexF);
            if (index < colors.size() - 1) {
                QColor frontColor = colors.at(index);
                QColor behindColor = colors.at(index + 1);
                return QColor(frontColor.red() + (behindColor.red() - frontColor.red()) * (indexF - index),
                              frontColor.green() + (behindColor.green() - frontColor.green()) * (indexF - index),
                              frontColor.blue() + (behindColor.blue() - frontColor.blue()) * (indexF - index));
            } else {
                return colors.at(colors.size() - 1);
            }
        }
    }
    return QColor();
}
