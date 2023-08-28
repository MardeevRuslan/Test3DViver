#ifndef CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_
#define CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_

#include <cstdio>
#include <string>

#include "model.h"
#include "object.h"
#include "parser.h"


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
  inline void set_transform(std::string key, float value) const {
    model_->set_transform(key, value);
  }
  inline float get_transform(std::string key) const {
    return model_->get_transform(key);
  }
  inline float *get_vertices() { return model_->get_vertices(); }
  inline uint *get_indices() const { return model_->get_indices(); }
  inline uint get_vertex_count() const { return model_->get_vertex_count(); }
  inline uint get_polygon_count() const { return model_->get_polygon_count(); }
  inline size_t get_indices_size() const { return model_->get_indices_size(); }
  inline bool get_error() const { return model_->get_error(); }

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_CONTROLLER_H_
