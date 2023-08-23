#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <vector>

#include "s21_matrix_oop.h"

namespace s21
{
   struct Poligon
  {
    std::vector<int> vertexes;
  } ;


  struct Object
  {
    int polygon_count_ = 0;
    int vertex_count_ = 0;
    std::vector<float> vertexes_;
    std::vector<Poligon> polygons_;
  };

} // namespace s21

#endif // SRC_OBJECT_H_
