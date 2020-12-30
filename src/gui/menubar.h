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

namespace GisL {
    class MenuBar : public QMenuBar, GisLObject {
    Q_OBJECT
    public:
        explicit MenuBar( Ui_MainWindow &poUi, QWidget &poWidget, GlCanvas &pCanvas );

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

        QMenuBar *pmMenuBar;

        Ui_MainWindow *pmUi;

        QWidget *pmWidget;

        GlCanvas *pmCanvas;

        DaDecoder *pDecoder;
        DaEncoder *pEncoder;

        Vector *pVector;
        Sld *pSld;
    };
}

#endif //GISL_MENUBAR_H
