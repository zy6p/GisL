/*!
 * @file manubar.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief menubar
 * @details 
 * @verbatim
 *
 */

#ifndef GISL_MENUBAR_H
#define GISL_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "../utils/gislobject.h"

namespace GisL {
    class MenuBar : public GisLObject {
    public:
        explicit MenuBar(QMenuBar &poMenuBar);


    private:

        GisL::DaDecoder daDecoder;
        GisL::DaEncoder daEncoder;

        QMenuBar *pmMenuBar;

        void connectMenu();

        void aFileDecodeOpen();

        void aFileDecodeDecode();

        void aFileDecodeSave();

        void aFileEncodeOpen();

        void aFileEncodeEncode();

        void aFileEncodeSave();

    };
}

#endif //GISL_MENUBAR_H
