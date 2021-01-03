#include "cklinearring.h"

int FR, FG, FB;

CKLinearRing::CKLinearRing( ) {
    pts = 0x00;
    pt_size = 0;
    envelop[0] = 999999999.0;
    envelop[1] = 999999999.0;
    envelop[2] = -999999999.0;
    envelop[3] = -999999999.0;
}

CKLinearRing::~CKLinearRing( ) {
    if ( pts != 0x00 ) {
        for ( int i = 0; i < pt_size; i++ ) {
            if ( pts[i] != 0x00 ) {
                delete pts[i];
                pts[i] = 0x00;
            }
        }
        delete[] pts;
        pts = 0x00;
    }
}

CKLinearRing::CKLinearRing( const QJsonArray &seg ) {
    pt_size = seg.size();
    pts = new CKPoint *[pt_size];
    QJsonArray pta;
    for ( int i = 0; i < pt_size; i++ ) {
        pta = seg[i].toArray();
        pts[i] = new CKPoint( pta[0].toDouble(), pta[1].toDouble());
    }
}

double *CKLinearRing::getEnvelop( ) {
    double *te = 0x00;
    for ( int i = 0; i < this->pt_size; i++ ) {
        te = pts[i]->getEnvelop();
        envelop[0] = envelop[0] < te[0] ? envelop[0] : te[0];
        envelop[1] = envelop[1] < te[1] ? envelop[1] : te[1];
        envelop[2] = envelop[2] > te[2] ? envelop[2] : te[2];
        envelop[3] = envelop[3] > te[3] ? envelop[3] : te[3];
    }
    return envelop;

}

void CKLinearRing::CALLBACK
vertexCallback(GLvoid
*vertex)
{

}

void CKLinearRing::CALLBACK
beginCallback(GLenum
which)
{
glBegin(which);
glColor3d(FR
/255.0,FG/255.0,FB/255.0);
}

void CKLinearRing::CALLBACK

endCallback( ) {
    glEnd();
}

void CKLinearRing::CALLBACK
errorCallback(GLenum
errorcode)
{
const GLubyte *estring;
estring = gluErrorString( errorcode );
exit(0);
}

void CKLinearRing::CALLBACK
combineCallback(GLdouble
coords[3],
GLdouble *vertex_data[4], GLfloat
weight[4],
GLdouble **dataOut
)
{

}

void CKLinearRing::StartTess( ) {
    int Psize = pt_size;
    double **PTS = new double *[Psize];
    for ( int i = 0; i < Psize; i++ ) {
        PTS[i] = new double[3];
    }

    for ( int q = 0; q < pt_size; q++ ) {
        PTS[q][0] = pts[q]->GetX();
        PTS[q][1] = pts[q]->GetY();
        PTS[q][2] = 0.0;
    }

    GLUtesselator *tobj = gluNewTess();

    gluTessCallback( tobj, GLU_TESS_VERTEX, ( void ( __stdcall * )( )) glVertex3dv );
    gluTessCallback( tobj, GLU_TESS_BEGIN, ( void( CALLBACK * )())
    beginCallback);
    gluTessCallback( tobj, GLU_TESS_END, ( void( CALLBACK * )())
    endCallback);
    gluTessCallback( tobj, GLU_TESS_ERROR, ( void( CALLBACK * )())
    errorCallback);
    gluTessCallback( tobj, GLU_TESS_COMBINE, ( void( CALLBACK * )())
    combineCallback);
    gluTessBeginPolygon( tobj, nullptr );
    gluTessBeginContour( tobj );

    for ( int q = 0; q < pt_size; q++ ) {
        gluTessVertex( tobj, PTS[q], PTS[q] );
    }
    gluTessEndContour( tobj );
    gluTessEndPolygon( tobj );
    gluDeleteTess( tobj );


    for ( int i = 0; i < Psize; i++ ) {
        delete[] PTS[i];
        PTS[i] = nullptr;
    }
    delete[] PTS;
    PTS = nullptr;

}

void CKLinearRing::draw( CKSymbolizer *pSymb ) {
    int LR, LG, LB;
    float Width;
    static_cast<CKPolygonSymbolizer *>(pSymb)->fill_color.getRgb( &FR, &FG, &FB );
    static_cast<CKPolygonSymbolizer *>(pSymb)->stroke_color.getRgb( &LR, &LG, &LB );
    Width = static_cast<CKPolygonSymbolizer *>(pSymb)->stroke_width;

    StartTess();
    glBegin( GL_LINE_LOOP );
    glColor3d( LR / 255.0, LG / 255.0, LB / 255.0 );
    glLineWidth( Width );
    for ( int i = 0; i < this->pt_size; i++ ) {
        glVertex2d( pts[i]->GetX(), pts[i]->GetY());
    }
    glEnd();
}
