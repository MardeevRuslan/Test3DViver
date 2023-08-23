#include "parser.h"

namespace s21 {
void Parser::ParserVetexAndFace(std::string filename, Object *object) {
  OpenFile(filename);
  my_object_ = object;
  if (file_.is_open()) {
    std::string line;
    while (std::getline(file_, line) && error_ >= 0) {
      if (line[0] == 'v') {
        ParserVetex(line);
      }
      if (line[0] == 'f') {
        ParserFace(line);
      }
    }
    file_.close();
    ReductionCoordinates();
  } else {
    std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
  }
}

void Parser::OpenFile(std::string filename) { file_.open(filename); }

void Parser::ParserFace(std::string line) {
  my_object_->polygon_count_++;
  Poligon poligon;
  float value;
  line = line.substr(2);
  std::istringstream iss(line);
  while (iss >> value) {
    poligon.vertexes.push_back(value - 1);
    if (iss.peek() == '/') {
      iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    if (poligon.vertexes.size() > 1) {
      poligon.vertexes.push_back(value - 1);
    }
  }
  poligon.vertexes.push_back(poligon.vertexes[0]);
  my_object_->polygons_.push_back(poligon);
}

void Parser::ParserVetex(std::string line) {
  my_object_->vertex_count_++;
  float x, y, z;
  int error_ = std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
  if (error_ == 3) {
    my_object_->vertexes_.push_back(x);
    my_object_->vertexes_.push_back(y);
    my_object_->vertexes_.push_back(z);
  }
}

void Parser::ReductionCoordinates() {
  auto maxElement = std::max_element(
      my_object_->vertexes_.begin(), my_object_->vertexes_.end(),
      [](int a, int b) { return std::abs(a) < std::abs(b); });
  int digits = static_cast<int>(std::log10(std::abs(*maxElement))) + 1;
  for (size_t i = 0; i < my_object_->vertexes_.size(); i++) {
    my_object_->vertexes_[i] /= std::pow(10, digits);
  }
}
}  // namespace s21
