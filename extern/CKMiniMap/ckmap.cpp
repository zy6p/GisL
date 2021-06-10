#include "ckmap.h"
#include "string.h"
#include <QJsonDocument>
#include <qfile.h>
#include <iostream>
#include <qjsonarray.h>
#include "ckfeature.h"
#include <QXmlStreamReader>
#include <QDebug>
#include "ckpolygonsymbolizer.h"
#include "ckrenderrule.h"

using namespace std;

CKMap::CKMap( ) {

}

void CKMap::loadSLD( const char *path ) {
    //加载sld数据部分
    QFile file( path );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text )) {
        return;//file open error
    }

    QXmlStreamReader::TokenType token;
    QString gjsonPath;
    QXmlStreamReader sld( file.readAll());
    while ( !sld.atEnd()) {
        sld.readNext();
        token = sld.tokenType();

        switch ( token ) {
            case QXmlStreamReader::StartElement:
                //qDebug()<<sld.name()<<endl;

                if ( sld.name() == "NamedLayer" ) {
                    sld.readNextStartElement();
                    gjsonPath = sld.readElementText();//读取文件名
                    break;
                }

                if ( sld.name() == "Rule" ) {//处理要素和符号关联规则，以及符号化描述
                    pRules.push_back( new CKRenderRule( sld ));
                }

                break;
            case QXmlStreamReader::EndElement:
                break;
            case QXmlStreamReader::Characters:
                //qDebug()<<sld.text()<<endl;
                break;
            default:
                break;
        }
    }

    //读取geojson数据
    QString gpath = "D:\\workstation\\teaching\\course\\oop gis\\practice\\practise_6\\data\\";
    gpath += gjsonPath + ".geojson";
    this->loadGeoJSON( gpath.toStdString().c_str());

    this->connectFeatSymb();
}

void CKMap::loadGeoJSON( const char *path ) {
    if ( path == 0x00 || strlen( path ) == 0 )
        return;
    QFile file( path );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text )) {
        return;//file open error
    }

    QJsonDocument doc = QJsonDocument::fromJson( file.readAll());
    QJsonArray feats;
    if ( !doc["features"].isNull() && doc["features"].isArray())
        feats = doc["features"].toArray();

    feature_size = feats.size();
    pFeatures = new CKFeature *[feature_size];
    for ( int i = 0; i < feats.size(); i++ ) {
        if ( feats[i].isObject() && !feats[i].isNull()) {
            QJsonValue fv = feats[i];
            if ( fv["type"].toString().compare( "Feature" ) == 0 )
                pFeatures[i] = new CKFeature( feats[i].toObject());//所有的要素都被存储到对象指针数组pFeatures中，by kmj
        }
    }
}

/**
 * @brief CKMap::connectFeatSymb
 * 功能:根据字段名和属性值匹配对应的feature
 */
void CKMap::connectFeatSymb( ) {

}
