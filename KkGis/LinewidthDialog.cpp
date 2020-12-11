#include "LinewidthDialog.h"
#include "ui_LinewidthDialog.h"
#include <qdialog.h>

LinewidthDialog::LinewidthDialog(float width, QWidget *parent)
        : QDialog(parent), ui(new Ui::LinewidthDialog) {
    ui->setupUi(this);
    ui->doubleSpinBox->setValue(width);
}

LinewidthDialog::~LinewidthDialog() {
}

float LinewidthDialog::getWidth() {
    return ui->doubleSpinBox->value();
}
