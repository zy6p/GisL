#pragma once

#include <QDialog>
#include "ui_LinewidthDialog.h"
namespace Ui {
	class LinewidthDialog;
}
class LinewidthDialog : public QDialog
{
	Q_OBJECT

public:
	LinewidthDialog(float width,QWidget *parent = Q_NULLPTR);
	~LinewidthDialog();
	float getWidth();
private:
	Ui::LinewidthDialog* ui;
};
