/*!
 * @file menubar.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief menubar
 * @details 
 *
 *
 */

#ifndef GISL_MENUBAR_H
#define GISL_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "../core/vector.h"
#include "sld.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class MenuBar; }
//QT_END_NAMESPACE

class MenuBar : public QMenuBar {
Q_OBJECT
public:
    explicit MenuBar( QWidget *parent );

    ~MenuBar( ) override;

//    void connectMenu( Ui::MainWindow *ui );

public slots:

    void aCodecvtDecodeOpen( );

    void aCodecvtDecodeDecode( );

    void aCodecvtDecodeSave( );

    void aCodecvtEncodeOpen( );

    void aCodecvtEncodeEncode( );

    void aCodecvtEncodeSave( );

    void on_actionVectorOpen_clicked( );

    void aVectorSldOpen( );

private:

    QWidget *pmWidget;


//    Ui::MainWindow *pmUi;
    GisL::DaDecoder *pDecoder;
    GisL::DaEncoder *pEncoder;

    GisL::Vector *pVector;
    GisL::Sld *pSld;
};


#endif //GISL_MENUBAR_H
