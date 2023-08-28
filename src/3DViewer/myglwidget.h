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
#include "controller_settings.h"
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
  void Draw();
  void LineDisplayMethod();
  void PointDisplayMethod();
  void ProjectionDisplayMethod();
  void CoordinateAxis();
  bool flag_open_ = false;
  s21::Controller *controller_;
  s21::ControllerSettings controller_settings_;
};
#endif  // CPP4_3DVIWER_3DVIEWER_MYGLWIDGET_H_
