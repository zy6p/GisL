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

#include "ui_mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "glcanvas.h"
#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "../utils/gislobject.h"
#include "../core/vector.h"
#include "sld.h"

//QT_BEGIN_NAMESPACE
//namespace GisL { class MenuBar; }
//QT_END_NAMESPACE

class MenuBar : public QMenuBar {
Q_OBJECT
public:
    MenuBar( QWidget *parent );

    ~MenuBar( ) override;

    void connectMenu( );

private slots:

    void aCodecvtDecodeOpen( );

    void aCodecvtDecodeDecode( );

    void aCodecvtDecodeSave( );

    void aCodecvtEncodeOpen( );

    void aCodecvtEncodeEncode( );

    void aCodecvtEncodeSave( );

    void aVectorOpen( );

    void aVectorSldOpen( );

private:

    QWidget *pmWidget;

    GisL::DaDecoder *pDecoder;
    GisL::DaEncoder *pEncoder;

    GisL::Vector *pVector;
    GisL::Sld *pSld;
};

}

#endif //GISL_MENUBAR_H
