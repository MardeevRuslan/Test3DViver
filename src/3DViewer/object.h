#ifndef CPP4_3DVIWER_3DVIEWER_OBJECT_H_
#define CPP4_3DVIWER_3DVIEWER_OBJECT_H_

#include <vector>

namespace s21 {
struct Poligon {
  std::vector<int> vertexes;
};

struct Object {
  int polygon_count_ = 0;
  int vertex_count_ = 0;
  std::vector<float> vertexes_;
  std::vector<Poligon> polygons_;
};

}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_OBJECT_H_
