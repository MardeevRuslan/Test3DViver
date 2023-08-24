#ifndef CPP4_3DVIWER_3DVIEWER_COLOR_SETTING_CLASS_H_
#define CPP4_3DVIWER_3DVIEWER_COLOR_SETTING_CLASS_H_

#define GL_SILENCE_DEPRECATION

#include <vector>

#include "controller.h"

namespace s21 {

class ColorSetting {
 public:
  ColorSetting() = default;
  ColorSetting(const ColorSetting &) = delete;
  ColorSetting(ColorSetting &&) = delete;
  ColorSetting &operator=(const ColorSetting &) = delete;
  ColorSetting &operator=(ColorSetting &&) = delete;
  virtual ~ColorSetting() = default;

 protected:
  virtual void SettingColor(std::vector<float> color_vector){

  };
};

class ColorSettingBack : public ColorSetting {
 public:
  void SettingColor(std::vector<float> color_vector) override {
    glClearColor(color_vector[0], color_vector[1], color_vector[2], 0.0f);
  }
};

class ColorSettingLine : public ColorSetting {
 public:
  void SettingColor(std::vector<float> color_vector) override {
    glColor3d(color_vector[0], color_vector[1], color_vector[2]);
  }
};

class ColorSettingTop : public ColorSetting {
 public:
  void SettingColor(std::vector<float> color_vector) override {
    glColor3d(color_vector[0], color_vector[1], color_vector[2]);
  }
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_COLOR_SETTING_CLASS_H_
