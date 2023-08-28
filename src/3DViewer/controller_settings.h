#ifndef CPP4_3DVIWER_3DVIEWER_CONTROLLER_SETTINGS_H_
#define CPP4_3DVIWER_3DVIEWER_CONTROLLER_SETTINGS_H_

#include <cstdio>
#include <string>

#include "model.h"
#include "object.h"
#include "parser.h"
#include "setting.h"

namespace s21 {
class ControllerSettings {
 public:
  ControllerSettings() = default;
  ControllerSettings(const ControllerSettings &) = delete;
  ControllerSettings(ControllerSettings &&) = delete;
  ControllerSettings &operator=(const ControllerSettings &) = delete;
  ControllerSettings &operator=(ControllerSettings &&) = delete;
  
  ~ControllerSettings() = default;
  inline void set_settings(std::string key, int value) {
    setting_.set_settings(key, value);
  }
  inline int get_settings(std::string key) const {
    return setting_.get_settings(key);
  }
  inline void set_settings_color(std::string key, QColor color) const {
    setting_.set_settings_color(key, color);
  }
  inline std::vector<float> get_settings_color(std::string key) const {
    return setting_.get_settings_color(key);
  }

 private:
  Setting &setting_ = s21::Setting::get_instance();
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_CONTROLLER_SETTINGS_H_
