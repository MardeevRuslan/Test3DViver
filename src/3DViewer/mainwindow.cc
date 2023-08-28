#include "mainwindow.h"

#include "../gif.h"

GifWriter writer;

MainWindow::MainWindow(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), ui(new Ui::MainWindow()), controller_(controller) {
 
  ui->setupUi(this);
  DefaultSettings();
  connect(ui->XRotateDial, &QDial::valueChanged, this, &MainWindow::SetValX);
  connect(ui->XRotateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetValSpinX);
  connect(ui->YRotateDial, &QDial::valueChanged, this, &MainWindow::SetValY);
  connect(ui->YRotateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetValSpinY);
  connect(ui->ZRotateDial, &QDial::valueChanged, this, &MainWindow::SetValZ);
  connect(ui->ZRotateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetValSpinZ);
  connect(ui->XTranslateSlider, &QSlider::valueChanged, this,
          &MainWindow::SetSliMovX);
  connect(ui->XTranslateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetSpinMovX);
  connect(ui->YTranslateSlider, &QSlider::valueChanged, this,
          &MainWindow::SetSliMovY);
  connect(ui->YTranslateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetSpinMovY);
  connect(ui->ZTranslateSlider, &QSlider::valueChanged, this,
          &MainWindow::SetSliMovZ);
  connect(ui->ZTranslateSpin, &QSpinBox::valueChanged, this,
          &MainWindow::SetSpinMovZ);
  connect(ui->ScaleSpin, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::SetScale);
  connect(ui->horizontalSliderTypeLine, &QSlider::valueChanged, this,
          &MainWindow::On_horizontalSliderTypeLine_actionTriggered);
  connect(ui->spinBoxTypeLine, &QSpinBox::valueChanged, this,
          &MainWindow::On_spinBoxTypeLine_valueChanged);
  connect(ui->horizontalSliderTypeTop, &QSlider::valueChanged, this,
          &MainWindow::On_horizontalSliderTypeTop_actionTriggered);
  connect(ui->spinBoxTypeTop, &QSpinBox::valueChanged, this,
          &MainWindow::On_spinBoxTypeTop_valueChanged);
  connect(ui->pBColorTop, &QPushButton::clicked, this,
          &MainWindow::On_pBColorTop_clicked);
  connect(ui->pBColorLine, &QPushButton::clicked, this,
          &MainWindow::On_pBColorLine_clicked);
  connect(ui->pBBackground, &QPushButton::clicked, this,
          &MainWindow::On_pBColorBackground_clicked);
  connect(ui->comboBox_type_top, &QComboBox::currentIndexChanged, this,
          &MainWindow::On_comboBox_top_currentIndexChanged);
  connect(ui->cB_type_line, &QComboBox::currentIndexChanged, this,
          &MainWindow::On_comboBox_currentIndexChanged);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Open_file_clicked() {
  filename_qstring_ = QFileDialog::getOpenFileName(this, "Choose obj file",
                                                   QDir::homePath(), "*.obj");
  const std::string filename = filename_qstring_.toStdString();
  controller_->DataTransmission(filename);
  flag_open_ = controller_->get_error();
  if (flag_open_ == true) {
    SetDefaultValues();
    ui->openGLWidget->SetController(controller_);
    ui->openGLWidget->update();
  }
  DataOutputToScreen();
}

void MainWindow::SetValX() {
  if (flag_open_ == true) {
    ui->XRotateSpin->setValue(ui->XRotateDial->value());
    controller_->set_transform("rotateX", ui->XRotateDial->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetValSpinX() {
  if (flag_open_ == true) {
    ui->XRotateDial->setValue(ui->XRotateSpin->value());
    SetValX();
  }
}

void MainWindow::SetValY() {
  if (flag_open_ == true) {
    ui->YRotateSpin->setValue(ui->YRotateDial->value());
    controller_->set_transform("rotateY", ui->YRotateDial->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetValSpinY() {
  if (flag_open_ == true) {
    ui->YRotateDial->setValue(ui->YRotateSpin->value());
    SetValY();
  }
}

void MainWindow::SetValZ() {
  if (flag_open_ == true) {
    ui->ZRotateSpin->setValue(ui->ZRotateDial->value());
    controller_->set_transform("rotateZ", ui->ZRotateDial->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetValSpinZ() {
  if (flag_open_ == true) {
    ui->ZRotateDial->setValue(ui->ZRotateSpin->value());
    SetValZ();
  }
}

void MainWindow::SetSliMovX() {
  if (flag_open_ == true) {
    ui->XTranslateSpin->setValue(ui->XTranslateSlider->value());
    controller_->set_transform("translateX", ui->XTranslateSlider->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetSpinMovX() {
  if (flag_open_ == true) {
    ui->XTranslateSlider->setValue(ui->XTranslateSpin->value());
    SetSliMovX();
  }
}

void MainWindow::SetSliMovY() {
  if (flag_open_ == true) {
    ui->YTranslateSpin->setValue(ui->YTranslateSlider->value());
    controller_->set_transform("translateY", ui->YTranslateSlider->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetSpinMovY() {
  if (flag_open_ == true) {
    ui->YTranslateSlider->setValue(ui->YTranslateSpin->value());
    SetSliMovY();
  }
}

void MainWindow::SetSliMovZ() {
  if (flag_open_ == true) {
    ui->ZTranslateSpin->setValue(ui->ZTranslateSlider->value());
    controller_->set_transform("translateZ", ui->ZTranslateSlider->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::SetSpinMovZ() {
  if (flag_open_ == true) {
    ui->ZTranslateSlider->setValue(ui->ZTranslateSpin->value());
    SetSliMovZ();
  }
}

void MainWindow::SetScale() {
  if (flag_open_ == true) {
    controller_->set_transform("scale", ui->ScaleSpin->value());
    ui->openGLWidget->update();
  }
}

void MainWindow::On_comboBox_currentIndexChanged(int index) {
  // index = 0 - сплошная, = 1 - пунктирная
  if (flag_open_ == true) {
    controller_settings_.set_settings("line_display_method", index);
    ui->openGLWidget->update();
  }
}

void MainWindow::On_comboBox_top_currentIndexChanged(int index) {
  // index = 0 - круглая, = 1 - квадратная, = 2 - отсутствует
  if (flag_open_ == true) {
    controller_settings_.set_settings("vertex_display_method", index);
    ui->openGLWidget->update();
  }
}

void MainWindow::On_horizontalSliderTypeLine_actionTriggered(int action) {
  if (flag_open_ == true) {
    ui->spinBoxTypeLine->setValue(ui->horizontalSliderTypeLine->value());
    controller_settings_.set_settings("line_width",
                              ui->horizontalSliderTypeLine->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::On_spinBoxTypeLine_valueChanged(int arg1) {
  if (flag_open_ == true) {
    ui->horizontalSliderTypeLine->setValue(ui->spinBoxTypeLine->value());
  }
}

void MainWindow::On_horizontalSliderTypeTop_actionTriggered(int action) {
  if (flag_open_ == true) {
    ui->spinBoxTypeTop->setValue(ui->horizontalSliderTypeTop->value());
    controller_settings_.set_settings("point_size",
                              ui->horizontalSliderTypeTop->value());
    ui->openGLWidget->update();
  }
}
void MainWindow::On_spinBoxTypeTop_valueChanged(int arg1) {
  if (flag_open_ == true) {
    ui->horizontalSliderTypeTop->setValue(ui->spinBoxTypeTop->value());
  }
}

void MainWindow::On_pBColorTop_clicked() {
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  QPoint point = clickedButton->mapToGlobal(clickedButton->pos());
  QColor color = ShowDialog(point);
  controller_settings_.set_settings_color("color_top", color);
  ui->openGLWidget->update();
}

void MainWindow::On_pBColorLine_clicked() {
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  QPoint point = mapTo(this, clickedButton->pos());
  QColor color = ShowDialog(point);
  controller_settings_.set_settings_color("color_line", color);
  ui->openGLWidget->update();
}

void MainWindow::On_pBColorBackground_clicked() {
  if (flag_open_ == true) {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QPoint point = clickedButton->mapToGlobal(clickedButton->pos());
    QColor color = ShowDialog(point);
    controller_settings_.set_settings_color("color_back", color);
    ui->openGLWidget->update();
    ui->openGLWidget->update();
  }
}

QColor MainWindow::ShowDialog(QPoint point) {
  QColor color = QColor(1.0f, 1.0f, 1.0f);
  QColorDialog *dialog = new QColorDialog();
  dialog->move(point.x(), point.y());
  dialog->update();
  if (dialog->exec() == QColorDialog::Accepted) {
    color = dialog->currentColor();
  }
  delete dialog;
  return color;
}

void MainWindow::on_ProjTypeCombo_currentIndexChanged(int index) {
  if (flag_open_ == true) {
    controller_settings_.set_settings("type_of_projection", index);
    ui->openGLWidget->update();
  }
}

void MainWindow::DataOutputToScreen() {
  if (flag_open_ == true) {
    QString info = "info about model:";
    info.append("\nFilename: " + filename_qstring_);
    info.append("\nVertexes: " +
                QString::number(controller_->get_vertex_count()));
    info.append("\nFaces: " +
                QString::number(controller_->get_polygon_count()));
    ui->infolabel->setText(info);
  } else {
    ui->infolabel->clear();
    ui->infolabel->setText("Начальник, с Вашим файлом что-то не так");
  }
}

void MainWindow::DefaultSettings() {
  ui->spinBoxTypeTop->setValue(controller_settings_.get_settings("point_size"));
  ui->spinBoxTypeLine->setValue(controller_settings_.get_settings("line_width"));
  ui->horizontalSliderTypeTop->setValue(
      controller_settings_.get_settings("point_size"));
  ui->horizontalSliderTypeLine->setValue(
      controller_settings_.get_settings("line_width"));
  ui->comboBox_type_top->setCurrentIndex(
      controller_settings_.get_settings("vertex_display_method"));
  ui->cB_type_line->setCurrentIndex(
      controller_settings_.get_settings("line_display_method"));
  ui->ProjTypeCombo->setCurrentIndex(
      controller_settings_.get_settings("type_of_projection"));
}
void MainWindow::on_save_bmp_clicked() {
  if (flag_open_ == true) {
    QString path = SelectDir();
    ui->openGLWidget->grab().save(path + "/" + QDate::currentDate().toString() +
                                  " " + QTime::currentTime().toString() +
                                  ".bmp");
  }
}

void MainWindow::on_save_jpeg_clicked() {
  if (flag_open_ == true) {
    QString path = SelectDir();
    ui->openGLWidget->grab().save(path + "/" + QDate::currentDate().toString() +
                                  " " + QTime::currentTime().toString() +
                                  ".jpeg");
  }
}

void MainWindow::on_save_gif_clicked() {
  if (flag_open_ == true) {
    fileNameRec = QFileDialog::getSaveFileName(
        0, "Сохранить как...", QDir::currentPath(), "GIF (*.gif)");
    if (GifBegin(&writer, fileNameRec.toLatin1().data(), 640, 480, 10)) {
      time = QTime::currentTime();
      timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(ByldGif()));
      timer->start(100);
    }
  }
}

QString MainWindow::SelectDir() {
  return QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

void MainWindow::ByldGif() {
  QImage img = ui->openGLWidget->grabFramebuffer().scaled(
      640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  GifWriteFrame(&writer,
                img.convertToFormat(QImage::Format_Indexed8)
                    .convertToFormat(QImage::Format_RGBA8888)
                    .bits(),
                img.width(), img.height(), 10);

  QTime end = QTime::currentTime();
  if (time.secsTo(end) > 5) {
    GifEnd(&writer);
    timer->stop();
  }
}

void MainWindow::SetDefaultValues() {
  ui->XRotateSpin->setValue(0);
  ui->XRotateDial->setValue(0);
  ui->YRotateSpin->setValue(0);
  ui->YRotateDial->setValue(0);
  ui->ZRotateSpin->setValue(0);
  ui->ZRotateDial->setValue(0);
  ui->XTranslateSpin->setValue(0);
  ui->XTranslateSlider->setValue(0);
  ui->YTranslateSpin->setValue(0);
  ui->YTranslateSlider->setValue(0);
  ui->ZTranslateSpin->setValue(0);
  ui->ZTranslateSlider->setValue(0);
  ui->ScaleSpin->setValue(1);
}
