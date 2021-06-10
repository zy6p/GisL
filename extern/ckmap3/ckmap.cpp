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
    envelop[0] = 999999999;
    envelop[1] = 999999999;
    envelop[2] = -999999999;
    envelop[3] = -999999999;
    //初始化状态
}

void CKMap::loadSLD( const char *path ) {
    //加载sld数据部分
    QFile file( path );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text )) {
        return;//file open error
    }

    QXmlStreamReader::TokenType token;
    QString layerName;
    QXmlStreamReader sld( file.readAll());
    while ( !sld.atEnd()) {
        sld.readNext();
        token = sld.tokenType();

        switch ( token ) {
            case QXmlStreamReader::StartElement:
                //qDebug()<<sld.name()<<endl;

                if ( sld.name() == "NamedLayer" ) {
                    sld.readNextStartElement();
                    layerName = sld.readElementText();//读取文件名
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
//    QString gpath="D:\\workstation\\teaching\\course\\oop gis\\practice\\practise_6\\data\\";
    QString gpath( path );
    gpath = gpath.left( gpath.lastIndexOf( '/' ) + 1 ) + layerName + ".geojson";
//    gpath+=gjsonPath+".geojson";
    this->loadGeoJSON( gpath.toStdString().c_str());

    this->connectFeatSymb();
}

/**
 * @brief CKMap::drawMap
 * 功能:地图绘制
 */
void CKMap::drawMap( ) {
    for ( int i = 0; i < pRules.size() - 2; i++ ) {
        pRules[i]->draw();
    }
}

double *CKMap::getEnvelop( ) {

    double *te = 0x00;
    for ( int i = 0; i < feature_size; i++ ) {
        te = pFeatures[i]->getEnvelop();
        envelop[0] = envelop[0] < te[0] ? envelop[0] : te[0];
        envelop[1] = envelop[1] < te[1] ? envelop[1] : te[1];
        envelop[2] = envelop[2] > te[2] ? envelop[2] : te[2];
        envelop[3] = envelop[3] > te[3] ? envelop[3] : te[3];
    }
    return envelop;
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
    if ( feature_size < 1 ) return;
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
    for ( int i = 0; i < pRules.size(); i++ ) {
        for ( int j = 0; j < feature_size; j++ ) {
            if ( pFeatures[j]->equalTo( pRules[i]->getField_name(), pRules[i]->getField_value())) {
                pRules[i]->setPFeature( pFeatures[j] );
                break;
            }
        }
    }
}
