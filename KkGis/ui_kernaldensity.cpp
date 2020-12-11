/********************************************************************************
** Form generated from reading UI file 'kernaldensity.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KERNALDENSITY_H
#define UI_KERNALDENSITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_KernalDensity
{
public:
    QLabel *label;
    QComboBox *CB_LayerInput;
    QPushButton *PB_OK;
    QLabel *label_2;
    QComboBox *CB_Population;
    QLabel *label_3;
    QLineEdit *LE_OutRaster;
    QLabel *label_4;
    QLineEdit *LE_OutRasterSize;
    QLabel *label_5;
    QLineEdit *LE_SearchR;
    QLabel *label_6;
    QComboBox *CB_AreaUnit;
    QPushButton *PB_Cancle;
    QPushButton *PB_saveFilePath;
    QPushButton *PB_GetInputLayer;
    QLabel *label_7;
    QComboBox *CB_outValue;
    QLabel *label_8;
    QComboBox *CB_Method;
    QPushButton *PB_populationField;

    void setupUi(QDialog *KernalDensity)
    {
        if (KernalDensity->objectName().isEmpty())
            KernalDensity->setObjectName(QString::fromUtf8("KernalDensity"));
        KernalDensity->resize(582, 586);
        label = new QLabel(KernalDensity);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 271, 21));
        CB_LayerInput = new QComboBox(KernalDensity);
        CB_LayerInput->setObjectName(QString::fromUtf8("CB_LayerInput"));
        CB_LayerInput->setGeometry(QRect(40, 50, 441, 22));
        PB_OK = new QPushButton(KernalDensity);
        PB_OK->setObjectName(QString::fromUtf8("PB_OK"));
        PB_OK->setGeometry(QRect(330, 540, 93, 28));
        label_2 = new QLabel(KernalDensity);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 90, 141, 21));
        CB_Population = new QComboBox(KernalDensity);
        CB_Population->setObjectName(QString::fromUtf8("CB_Population"));
        CB_Population->setGeometry(QRect(40, 110, 441, 22));
        label_3 = new QLabel(KernalDensity);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 121, 21));
        LE_OutRaster = new QLineEdit(KernalDensity);
        LE_OutRaster->setObjectName(QString::fromUtf8("LE_OutRaster"));
        LE_OutRaster->setGeometry(QRect(40, 170, 441, 21));
        label_4 = new QLabel(KernalDensity);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 210, 221, 21));
        LE_OutRasterSize = new QLineEdit(KernalDensity);
        LE_OutRasterSize->setObjectName(QString::fromUtf8("LE_OutRasterSize"));
        LE_OutRasterSize->setGeometry(QRect(40, 230, 501, 21));
        label_5 = new QLabel(KernalDensity);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 270, 211, 21));
        LE_SearchR = new QLineEdit(KernalDensity);
        LE_SearchR->setObjectName(QString::fromUtf8("LE_SearchR"));
        LE_SearchR->setGeometry(QRect(40, 290, 501, 21));
        label_6 = new QLabel(KernalDensity);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 330, 181, 21));
        CB_AreaUnit = new QComboBox(KernalDensity);
        CB_AreaUnit->setObjectName(QString::fromUtf8("CB_AreaUnit"));
        CB_AreaUnit->setGeometry(QRect(40, 350, 501, 22));
        PB_Cancle = new QPushButton(KernalDensity);
        PB_Cancle->setObjectName(QString::fromUtf8("PB_Cancle"));
        PB_Cancle->setGeometry(QRect(450, 540, 93, 28));
        PB_saveFilePath = new QPushButton(KernalDensity);
        PB_saveFilePath->setObjectName(QString::fromUtf8("PB_saveFilePath"));
        PB_saveFilePath->setGeometry(QRect(500, 170, 31, 28));
        PB_GetInputLayer = new QPushButton(KernalDensity);
        PB_GetInputLayer->setObjectName(QString::fromUtf8("PB_GetInputLayer"));
        PB_GetInputLayer->setGeometry(QRect(500, 50, 31, 28));
        label_7 = new QLabel(KernalDensity);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 390, 221, 21));
        CB_outValue = new QComboBox(KernalDensity);
        CB_outValue->setObjectName(QString::fromUtf8("CB_outValue"));
        CB_outValue->setGeometry(QRect(40, 410, 501, 22));
        label_8 = new QLabel(KernalDensity);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 450, 171, 21));
        CB_Method = new QComboBox(KernalDensity);
        CB_Method->setObjectName(QString::fromUtf8("CB_Method"));
        CB_Method->setGeometry(QRect(40, 470, 501, 22));
        PB_populationField = new QPushButton(KernalDensity);
        PB_populationField->setObjectName(QString::fromUtf8("PB_populationField"));
        PB_populationField->setGeometry(QRect(500, 110, 31, 28));

        retranslateUi(KernalDensity);
        QObject::connect(PB_OK, SIGNAL(clicked()), KernalDensity, SLOT(accept()));
        QObject::connect(PB_Cancle, SIGNAL(clicked()), KernalDensity, SLOT(close()));
        QObject::connect(PB_GetInputLayer, SIGNAL(clicked()), KernalDensity, SLOT(getInputLayer()));
        QObject::connect(PB_saveFilePath, SIGNAL(clicked()), KernalDensity, SLOT(getRasterOut()));
        QObject::connect(PB_populationField, SIGNAL(clicked()), KernalDensity, SLOT(getPopulationField()));

        QMetaObject::connectSlotsByName(KernalDensity);
    } // setupUi

    void retranslateUi(QDialog *KernalDensity)
    {
        KernalDensity->setWindowTitle(QCoreApplication::translate("KernalDensity", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("KernalDensity", "Input point or polyline features", nullptr));
        PB_OK->setText(QCoreApplication::translate("KernalDensity", "Ok", nullptr));
        label_2->setText(QCoreApplication::translate("KernalDensity", "Population field", nullptr));
        label_3->setText(QCoreApplication::translate("KernalDensity", "Output raster", nullptr));
        label_4->setText(QCoreApplication::translate("KernalDensity", "Output cell size(optional)", nullptr));
        label_5->setText(QCoreApplication::translate("KernalDensity", "Search radius(optional)", nullptr));
        label_6->setText(QCoreApplication::translate("KernalDensity", "Area units(optional)", nullptr));
        PB_Cancle->setText(QCoreApplication::translate("KernalDensity", "Cancle", nullptr));
        PB_saveFilePath->setText(QString());
        PB_GetInputLayer->setText(QString());
        label_7->setText(QCoreApplication::translate("KernalDensity", "Output Values are(optional)", nullptr));
        label_8->setText(QCoreApplication::translate("KernalDensity", "Method(optional)", nullptr));
        PB_populationField->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KernalDensity: public Ui_KernalDensity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KERNALDENSITY_H
