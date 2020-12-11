#include "TextOutWidget.h"
#include "ui_TextOutWidget.h"
#include <qwidget.h>

TextOutWidget::TextOutWidget(QWidget *parent)
        : QObject(parent) {
    connect(this, SIGNAL(textOutSignal()), parent, SLOT(on_textout_triggered()));
}

TextOutWidget::~TextOutWidget() {
}
