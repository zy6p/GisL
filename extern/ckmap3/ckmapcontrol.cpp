#include "ckmapcontrol.h"
#include <GL/glu.h>
#include <QDebug>
#include <QOpenGLFunctions_3_2_Core>

CKMapControl::CKMapControl() { pMap = 0x00; }

CKMapControl::CKMapControl(QWidget *&qw) : QOpenGLWidget(qw) { pMap = 0x00; }

void CKMapControl::drawMap(CKMap *pm) {
  this->pMap = pm;
  this->update();
}

void CKMapControl::initializeGL() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
}

void CKMapControl::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (pMap == 0x00)
    return;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double *envelop = pMap->getEnvelop();
  glOrtho(envelop[0], envelop[2], envelop[1], envelop[3], -100, 100);
  glMatrixMode(GL_MODELVIEW);
  pMap->drawMap();
}

void CKMapControl::resizeGL(int w, int h) {}
