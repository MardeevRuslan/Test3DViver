#include "myglwidget.h"

#include "./ui_mainwindow.h"
#include "mainwindow.h"

using s21::ElementType::kElementBack;
using s21::ElementType::kElementLine;
using s21::ElementType::kElementTop;

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  rotationX = 0;
  rotationY = 0;
  rotationZ = 0;
  scale = 1;
}

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
    draw();
  }
}

void MyGLWidget::draw() {
  s21::FactoryColorSetting factory_color_setting;
  factory_color_setting.SelectElementType(
      kElementBack, controller_->get_settings_color("color_back"));
  GLfloat *vertices = controller_->get_vertices();
  GLuint *indices = controller_->get_indices();
   std::cout << "=====================================================" <<
   std::endl; std::cout << "vertices.size() = " <<
   controller_->get_vertex_count() * 3 << std::endl; std::cout <<
   "indices.size() = " << controller_->get_indices_size() << std::endl; for
   (size_t i = 0; i < controller_->get_vertex_count() * 3; i++)
   {
     std::cout << "vertices  " << i << " =  " << vertices[i] << std::endl;
   }
   for (size_t i = 0; i < controller_->get_indices_size(); i++)
   {
     std::cout << "indices  " << i << " = " << indices[i] << std::endl;
   }
     std::cout << "=====================================================" <<
     std::endl;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  ProjectionDisplayMethod();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glPointSize(controller_->get_settings("point_size"));
  glLineWidth(controller_->get_settings("line_width"));
  LineDisplayMethod();
  PointDisplayMethod();
  glEnableClientState(GL_VERTEX_ARRAY);
  factory_color_setting.SelectElementType(
      kElementTop, controller_->get_settings_color("color_top"));
  if (controller_->get_settings("vertex_display_method") != 2) {
    glDrawArrays(GL_POINTS, 0, controller_->get_vertex_count());
  }
  factory_color_setting.SelectElementType(
      kElementLine, controller_->get_settings_color("color_line"));
  glDrawElements(GL_LINES, controller_->get_indices_size(), GL_UNSIGNED_INT,
                 indices);
  glDisableClientState(GL_VERTEX_ARRAY);
  delete[] vertices;
  delete[] indices;
}

void MyGLWidget::LineDisplayMethod() {
  if (controller_->get_settings("line_display_method") == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyGLWidget::PointDisplayMethod() {
  if (controller_->get_settings("vertex_display_method") == 0) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
}

void MyGLWidget::ProjectionDisplayMethod() {
  int w = this->width();
  int h = this->height();
  QVector2D prop = QVector2D(w, h).normalized();
//  int side = fmax(w, h);
//  int x = 0;
//  int y = 0;
//  if (w < h) {
//    x = (w - h) / 2;
//  }
//  if (h < w) {
//    y = (h - w) / 2;
//  }
//  glViewport(x, y, side * 2, side * 2);
  if (controller_->get_settings("type_of_projection") == 0) {
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
