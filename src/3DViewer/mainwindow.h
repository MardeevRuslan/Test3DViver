#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <iostream>

#include "./ui_mainwindow.h"
#include "controller.h"
#include "model.h"
#include "myglwidget.h"
#include "object.h"
#include "parser.h"
#include "s21_matrix_oop.h"
#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow() = default;
  MainWindow(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
  ~MainWindow();

  void SetValX();
  void SetValSpinX();

  void SetValY();
  void SetValSpinY();

  void SetValZ();
  void SetValSpinZ();

  void SetSliMovX();
  void SetSpinMovX();

  void SetSliMovY();
  void SetSpinMovY();

  void SetSliMovZ();
  void SetSpinMovZ();

  void SetScale();

 private slots:

  void on_Open_file_clicked();

  void On_comboBox_currentIndexChanged(int index);
  void On_comboBox_top_currentIndexChanged(int index);

  void On_horizontalSliderTypeLine_actionTriggered(int action);
  void On_spinBoxTypeLine_valueChanged(int arg1);

  void On_horizontalSliderTypeTop_actionTriggered(int action);
  void On_spinBoxTypeTop_valueChanged(int arg1);

  void On_pBColorTop_clicked();
  void On_pBColorLine_clicked();
  void On_pBColorBackground_clicked();

  void on_ProjTypeCombo_currentIndexChanged(int index);

  void on_save_bmp_clicked();

  void on_save_jpeg_clicked();

  void on_save_gif_clicked();

  QString select_dir();

  void byld_gif();

 private:
  Ui::MainWindow *ui;
  bool flag_open_ = false;

  QTimer *timer;
  QTime time;
  QString fileNameRec;
  s21::Controller *controller_ = nullptr;
  void DefaultSettings();
  void DataOutputToScreen(std::string filename);
  void SetDefaultValues();
  QColor ShowDialog(QPoint point);
};
#endif  // MAINWINDOW_H
