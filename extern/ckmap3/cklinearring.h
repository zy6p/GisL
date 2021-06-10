#ifndef CKPOLYGONSEGMENT_H
#define CKPOLYGONSEGMENT_H

#include "ckpolygonsymbolizer.h"
#include <GL/glu.h>
#include <QJsonArray>
#include <QOpenGLFunctions_3_2_Core>
#include <ckpoint.h>
#include <qlist.h>

class CKLinearRing : public CKGeometry {
public:
  CKLinearRing();

  ~CKLinearRing();

  CKLinearRing(const QJsonArray &seg);

private:
  CKPoint **pts;
  int pt_size;

  void StartTess();

  static void CALLBACK vertexCallback(GLvoid *vertex);
  static void CALLBACK beginCallback(GLenum which);
  static void CALLBACK

  endCallback();

  static void CALLBACK errorCallback(GLenum errorCode);
  static void CALLBACK combineCallback(GLdouble coords[3],
                                       GLdouble *vertex_data[4],
                                       GLfloat weight[4], GLdouble **dataOut);
  // CKGeometry interface
public:
  double *getEnvelop() override;

  // CKGeometry interface
public:
  void draw(CKSymbolizer *pSymb) override;
};

#endif // CKPOLYGONSEGMENT_H
