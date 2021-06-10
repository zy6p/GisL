/***************************************************************************
                                    gisl

                             -------------------
    begin                : 7/12/2020
    copyright            : (C) 2020 by zy6p
    email                : goooog@88.com
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is a core software -- practice for object-oriented GIS    *
 *   software development lecture. It can encode and decode text. It can   *
 *   open and write .shp, .dbf, and .geojson. It also can use .sld to      *
 *   render layer style. In a word, it is a easy-to-use software.          *
 *                                                                         *
 ***************************************************************************/

#include <QSurfaceFormat>
#include <QtWidgets/QApplication>

#include "gui/mainwindow.h"

/*!
 * @brief This program is a core software -- practice for object-oriented GIS
 software development lecture.
 *
 * @details
 * It can encode and decode text. It can open and write .shp, .dbf, and
 .geojson.
 * It also can use .sld to render layer style. In a word, it is a easy-to-use
 software.
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
 * @author zy6p
 *
 */
int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    QSurfaceFormat format;
    format.setDepthBufferSize( 24 );
    format.setStencilBufferSize( 8 );
    format.setVersion( 3, 3 );
    format.setProfile( QSurfaceFormat::CoreProfile );
    QSurfaceFormat::setDefaultFormat( format );

    MainWindow w;
    w.show();

    return QApplication::exec();
}
