#ifndef CPP4_3DVIWER_3DVIEWER_SETTING_H_
#define CPP4_3DVIWER_3DVIEWER_SETTING_H_

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QVariant>
#include <cstdio>

#include "object.h"

namespace s21 {
class Setting : public QSettings {
 public:
  static inline Setting &get_instance() {
    static Setting instance;
    instance.ReadSettings();
    return instance;
  }
  void inline set_settings(std::string key, int value) noexcept {
    settings_[key] = value;
    setValue(QString::fromStdString(key), value);
  }
  void inline set_settings_color(std::string key, QColor color) noexcept {
    color_[key] = color;
    setValue(QString::fromStdString(key), color);
  }
  std::vector<float> inline get_settings_color(std::string key) noexcept {
    QColor color = color_[key];
    return {color.redF(), color.greenF(), color.blueF()};
  }
  int inline get_settings(std::string key) noexcept { return settings_[key]; }

 private:
  std::map<std::string, int> settings_;
  std::map<std::string, QColor> color_;
  explicit Setting() noexcept : QSettings("Sommerha", "3DViewer") {}
  Setting(const Setting &) = delete;
  Setting &operator=(const Setting &) = delete;
  Setting(Setting &&) = delete;
  Setting &operator=(Setting &&) = delete;
  ~Setting() = default;

  void inline ReadSettings() noexcept {
    settings_.clear();
    settings_["vertex_display_method"] =
        this->value("vertex_display_method", 0).toInt();
    settings_["line_display_method"] =
        this->value("line_display_method", 0).toInt();
    settings_["point_size"] = this->value("point_size", 1).toInt();
    settings_["line_width"] = this->value("line_width", 1).toInt();
    settings_["type_of_projection"] =
        this->value("type_of_projection", 0).toInt();
    color_["color_back"] =
        this->value("color_back", QColor(Qt::black)).value<QColor>();
    color_["color_line"] =
        this->value("color_line", QColor(Qt::red)).value<QColor>();
    color_["color_top"] =
        this->value("color_top", QColor(Qt::blue)).value<QColor>();
  }
};
}  // namespace s21
#endif  // CPP4_3DVIWER_3DVIEWER_SETTING_H_
