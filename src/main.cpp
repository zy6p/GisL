/***************************************************************************
                                    GisL

                             -------------------
    begin                : 7/12/2020
    copyright            : (C) 2020 by Wang Zhiyuan
    email                : hotdry@qq.com
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is a gis software -- practice for object-oriented GIS    *
 *   software development lecture. It can encode and decode text. It can   *
 *   open and write .shp, .dbf, and .geojson. It also can use .sld to      *
 *   render layer style. In a word, it is a easy-to-use software.          *
 *                                                                         *
 ***************************************************************************/

#include <QtWidgets/QApplication>
#include <QSurfaceFormat>

#include "gui/mainwindow.h"

/*!
 * @brief This program is a gis software -- practice for object-oriented GIS software development lecture.
 *
 * @details
 * It can encode and decode text. It can open and write .shp, .dbf, and .geojson.
 * It also can use .sld to render layer style. In a word, it is a easy-to-use software.
 *
 * @mainpage Object-oriented GIS software development lecture
 * <h3>Feature</h3>
 * 1. Easy to use and similar to qgis operations
 * 2. Cross Platform
 * 3. Supported vectorfeature formats include:
        - ESRI Shapefiles
        - GeoJson
 * 4. Supported style formats include:
        - sld
 *
 * @author Wang Zhiyuan, Lin Wei
 *
 */
int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    QSurfaceFormat format;
    format.setDepthBufferSize( 24 );
    format.setStencilBufferSize( 8 );
    format.setVersion( 3, 2 );
    format.setProfile( QSurfaceFormat::CoreProfile );
    QSurfaceFormat::setDefaultFormat( format );

    MainWindow w;
    w.show();

    return QApplication::exec();
}

