#ifndef CKMAPCONTROL_H
#define CKMAPCONTROL_H

#include <QOpenGLWidget>
#include "ckmap.h"

class CKMapControl : public QOpenGLWidget {
public:
    CKMapControl( );

    CKMapControl( QWidget *& );

    void drawMap( CKMap * );

protected:
    void initializeGL( ) override;

    void paintGL( ) override;

    void resizeGL( int w, int h ) override;

    CKMap *pMap;
};

#endif // CKMAPCONTROL_H
