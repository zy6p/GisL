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

#include "mainwindow.h"

/*!
 * @mainpage Object-oriented GIS software development lecture
 * @brief This program is a gis software -- practice for object-oriented GIS software development lecture.
 * @details It can encode and decode text. It can open and write .shp, .dbf, and .geojson.
 * It also can use .sld to render layer style. In a word, it is a easy-to-use software.
 * @authors Wang Zhiyuan, Lin Wei
 *
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();


    return QApplication::exec();
}

