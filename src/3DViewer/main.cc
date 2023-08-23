#include <QApplication>
#include <QSettings>

#include "controller.h"
#include "mainwindow.h"
#include "model.h"
#include "object.h"
#include "parser.h"
#include "setting.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  MainWindow w(nullptr, &controller);
  w.show();
  return a.exec();
}
