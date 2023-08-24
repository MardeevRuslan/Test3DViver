#ifndef CPP4_3DVIWER_3DVIEWER_MODEL_H_
#define CPP4_3DVIWER_3DVIEWER_MODEL_H_

#define GL_SILENCE_DEPRECATION

#include <array>
#include <cstdio>
#include <tuple>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "object.h"
#include "parser.h"
#include "setting.h"

namespace s21 {
class Model {
 public:
  Model();
  Model(const Model &) = delete;
  Model(Model &&) = default;
  Model &operator=(const Model &) = delete;
  Model &operator=(Model &&) = default;
  ~Model();

 public:
  int get_polygon_count();
  int get_vertex_count();
  void set_transform(std::string key, float value);
  float get_transform(std::string key);
  std::vector<int> get_poligon(int i);
  float *get_vertices();
  uint *get_indices();
  size_t get_indices_size() { return vector_poligons_.size(); }
  bool get_error() { return error_; }

 public:
  void WorkingModel(std::string filename);

 private:
  Object *my_object_;
  std::map<std::string, float> transform_;
  std::vector<float> vector_koordinate_;
  std::array<float, 3> coordinates_;
  std::vector<float> vector_poligons_;
  bool error_ = true;

 private:
  void TransformVectorPolygons();
  void ModelTransform();
  void ReadMapTransform();
  void RotateTransformX();
  void RotateTransformY();
  void RotateTransformZ();
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_MODEL_H_
