#include "myglwidget.h"

#include "./ui_mainwindow.h"
#include "mainwindow.h"

using s21::ElementType::kElementBack;
using s21::ElementType::kElementLine;
using s21::ElementType::kElementTop;

MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), controller_(nullptr) {}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void MyGLWidget::SetController(s21::Controller *controller) {
  controller_ = controller;
  flag_open_ = true;
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  CoordinateAxis();
  if (flag_open_ == true) {
    Draw();
  }
}

void MyGLWidget::Draw() {
  s21::FactoryColorSetting::SelectElementType(
      kElementBack, controller_settings_.get_settings_color("color_back"));
  GLfloat *vertices = controller_->get_vertices();
  GLuint *indices = controller_->get_indices();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  ProjectionDisplayMethod();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glPointSize(controller_settings_.get_settings("point_size"));
  glLineWidth(controller_settings_.get_settings("line_width"));
  LineDisplayMethod();
  PointDisplayMethod();
  glEnableClientState(GL_VERTEX_ARRAY);
  s21::FactoryColorSetting::SelectElementType(
      kElementTop, controller_settings_.get_settings_color("color_top"));
  if (controller_settings_.get_settings("vertex_display_method") != 2) {
    glDrawArrays(GL_POINTS, 0, controller_->get_vertex_count());
  }
  s21::FactoryColorSetting::SelectElementType(
      kElementLine, controller_settings_.get_settings_color("color_line"));
  glDrawElements(GL_LINES, controller_->get_indices_size(), GL_UNSIGNED_INT,
                 indices);
  glDisableClientState(GL_VERTEX_ARRAY);
  delete[] vertices;
  delete[] indices;
}

void MyGLWidget::LineDisplayMethod() {
  if (controller_settings_.get_settings("line_display_method") == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyGLWidget::PointDisplayMethod() {
  if (controller_settings_.get_settings("vertex_display_method") == 0) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
}

void MyGLWidget::ProjectionDisplayMethod() {
  int w = this->width();
  int h = this->height();
  QVector2D prop = QVector2D(w, h).normalized();
  if (controller_settings_.get_settings("type_of_projection") == 0) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -5.0, 5.0);
  } else {
    const qreal zNear = 0.01, zFar = 200, fov = 45.0;
    float aspect = prop.x() / prop.y();
    gluPerspective(fov * aspect, aspect, zNear, zFar);
  }
  glTranslatef(0.0, 0.0, -2.0);
}

void MyGLWidget::CoordinateAxis() {
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(20, 0x3333);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(0.0f, -10000.0f, 0.0f);
  glVertex3f(0.0f, 10000.0f, 0.0f);
  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(0.0f, 0.0f, -10000.0f);
  glVertex3f(0.0f, 0.0f, 10000.0f);
  glColor3f(0.2, 0.8, 0.8);
  glVertex3f(-10000.0f, 0.0f, 0.0f);
  glVertex3f(10000.0f, 0.0f, .0f);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}
