//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <string>
#include <istream>
#include <fstream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QString>

#include "../utils/stringoperate.h"
#include "../utils/merror.h"

namespace GisL {

    Sld::Sld() = default;

    Sld::Sld(const std::string &theSldFilename) {
        loadSldFile( theSldFilename );
    }

    void Sld::loadSldFile(const std::string &theSldFilename) {
        if ( theSldFilename.length() <= 4 ) {
            mError = MError::GisLError::ErrInFileName;
            mErrorMessage += "empty file name\n";
        }

        if ( StringOperate::isEndWith( theSldFilename, ".sld" )) {
            mError = MError::GisLError::ErrInFileName;
            mErrorMessage += "wrong filename\n";
        }

        QFile sldFile(QString::fromStdString(theSldFilename));
        if ( !sldFile.open(QFile::ReadOnly | QFile::Text) ) {
            mError = MError::GisLError::ErrCreateDataSource;
            mErrorMessage.append("Wrong! cannot open this file\n");
            return;
        }

        QXmlStreamReader xmlStreamReader(&sldFile);
//        xmlStreamReader.



        sldFile.close();



    }


}