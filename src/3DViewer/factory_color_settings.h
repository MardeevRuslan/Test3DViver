#ifndef CPP4_3DVIWER_3DVIEWER_FACTORY_COLOR_SETTING_CLASS_H_
#define CPP4_3DVIWER_3DVIEWER_FACTORY_COLOR_SETTING_CLASS_H_

#define GL_SILENCE_DEPRECATION

#include "color_setting_class.h"

namespace s21 {
enum ElementType { kElementBack, kElementLine, kElementTop };

class FactoryColorSetting {
 public:
  FactoryColorSetting() = default;
  FactoryColorSetting(const FactoryColorSetting &) = delete;
  FactoryColorSetting(FactoryColorSetting &&) = delete;
  FactoryColorSetting &operator=(const FactoryColorSetting &) = delete;
  FactoryColorSetting &operator=(FactoryColorSetting &&) = delete;
  ~FactoryColorSetting() = default;

  inline void SelectElementType(const ElementType type,
                                std::vector<float> color_vector) noexcept {
    switch (type) {
      case kElementBack: {
        ColorSettingBack color_setting_back;
        color_setting_back.SettingColor(color_vector);
        break;
      }
      case kElementLine: {
        ColorSettingLine color_setting_line;
        color_setting_line.SettingColor(color_vector);
        break;
      }
      case kElementTop: {
        ColorSettingTop color_setting_top;
        color_setting_top.SettingColor(color_vector);
        break;
      }
      default: {
        break;
      }
    }
  }
};

}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_FACTORY_COLOR_SETTING_CLASS_H_
