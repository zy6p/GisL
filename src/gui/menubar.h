/*!
 * @file manubar.h
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

#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "../utils/gislobject.h"

namespace GisL {
    class MenuBar : public GisLObject {
    public:
        explicit MenuBar( Ui_MainWindow &poUi, QWidget &poWidget );


    private:

        QMenuBar *pmMenuBar;

        Ui_MainWindow *pmUi;

        QWidget *pmWidget;

        GisL::DaDecoder *pDecoder;
        GisL::DaEncoder *pEncoder;

        void connectMenu( );

        void aFileDecodeOpen( );

        void aFileDecodeDecode( );

        void aFileDecodeSave( );

        void aFileEncodeOpen( );

        void aFileEncodeEncode();

        void aFileEncodeSave();

    };
}

#endif //GISL_MENUBAR_H
