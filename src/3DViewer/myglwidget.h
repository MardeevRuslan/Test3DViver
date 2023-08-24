#ifndef CPP4_3DVIWER_3DVIEWER_MYGLWIDGET_H_
#define CPP4_3DVIWER_3DVIEWER_MYGLWIDGET_H_

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QWidget>
#include <QtOpenGL>
#include <algorithm>
#include <iostream>

#include "controller.h"
#include "factory_color_settings.h"
#include "model.h"
#include "object.h"
#include "parser.h"

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  MyGLWidget(QWidget *parent = nullptr);
  ~MyGLWidget();
  void SetController(s21::Controller *controller);

 protected:
  void initializeGL() override;
  void paintGL() override;

 private:
  void draw();
  void LineDisplayMethod();
  void PointDisplayMethod();
  void ProjectionDisplayMethod();
  void CoordinateAxis();

  bool flag_open_ = false;
  s21::Controller *controller_;
  GLfloat rotationX;
  GLfloat rotationY;
  GLfloat rotationZ;
  GLfloat camX;
  GLfloat camY;
  GLfloat camZ;
  GLfloat ScrWidth;
  GLfloat ScrHeight;
  QPoint lastPos;
  int scale;
  QVector3D rotationAxis{1.0f, 1.0f, 0.0f};
  qreal rotationAngle{0.0};

  void timerEvent(QTimerEvent *event) override {
    Q_UNUSED(event);
    rotationAngle += 1.0;
    update();
  }
};
#endif  // CPP4_3DVIWER_3DVIEWER_MYGLWIDGET_H_
