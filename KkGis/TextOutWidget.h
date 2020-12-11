#pragma once

#include <QWidget>

namespace Ui { class TextOutWidget; };

class TextOutWidget : public QObject {
Q_OBJECT

public:
    TextOutWidget(QWidget *parent = Q_NULLPTR);

    ~TextOutWidget();

private:
    Ui::TextOutWidget *ui;

signals:

    void textOutSignal(QString text);
};
