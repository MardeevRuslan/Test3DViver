#ifndef CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_
#define CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_

#include <cstdio>
#include <string>

#include "model.h"
#include "object.h"
#include "parser.h"
#include "setting.h"

namespace s21 {
class Controller {
 public:
  Controller() = delete;
  inline explicit Controller(Model *model) : model_(model) {}
  Controller(const Controller &) = delete;
  Controller(Controller &&) = delete;
  ~Controller() = default;
  inline void DataTransmission(std::string filename) {
    model_->WorkingModel(filename);
  }
  inline void set_settings(std::string key, int value) {
    setting_.set_settings(key, value);
  }
  inline int get_settings(std::string key) const {
    return setting_.get_settings(key);
  }
  inline void set_settings_color(std::string key, QColor color) const {
    setting_.set_settings_color(key, color);
  }
  inline void set_transform(std::string key, float value) const {
    model_->set_transform(key, value);
  }
  inline float get_transform(std::string key) const {
    return model_->get_transform(key);
  }
  inline std::vector<float> get_settings_color(std::string key) const {
    return setting_.get_settings_color(key);
  }
  inline float *get_vertices() { return model_->get_vertices(); }
  inline uint *get_indices() const { return model_->get_indices(); }
  inline uint get_vertex_count() const { return model_->get_vertex_count(); }
  inline uint get_polygon_count() const { return model_->get_polygon_count(); }
  inline size_t get_indices_size() const { return model_->get_indices_size(); }
  inline bool get_error() const { return model_->get_error(); }

 private:
  Model *model_;
  Setting &setting_ = s21::Setting::get_instance();
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_
