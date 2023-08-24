#include "model.h"

#include "./ui_mainwindow.h"
#include "mainwindow.h"

namespace s21
{
  const float kValuePI = 3.141593;
  const float kDegreesToRadians = kValuePI / 180;
  const int kSmoothnessOfMovement = 25;

  Model::Model() { my_object_ = new Object(); };

  Model::~Model() { delete my_object_; };
  int Model::get_polygon_count() { return my_object_->polygon_count_; }
  int Model::get_vertex_count() { return my_object_->vertex_count_; }
  void Model::set_transform(std::string key, float value)
  {
    transform_[key] = value;
  }
  float Model::get_transform(std::string key) { return transform_[key]; }
  std::vector<int> Model::get_poligon(int i)
  {
    return my_object_->polygons_[i].vertexes;
  }

  GLfloat *Model::get_vertices()
  {
    vector_koordinate_ = my_object_->vertexes_;
    ModelTransform();
    GLfloat *vertices = new GLfloat[vector_koordinate_.size()];
    for (size_t i = 0; i < vector_koordinate_.size(); i++)
    {
      vertices[i] = vector_koordinate_[i];
    }
    return vertices;
  }

  GLuint *Model::get_indices()
  {
    GLuint *indices = new GLuint[vector_poligons_.size()];
    for (size_t i = 0; i < vector_poligons_.size(); i++)
    {
      indices[i] = vector_poligons_[i];
    }
    return indices;
  }
  void Model::WorkingModel(std::string filename)
  {
    Parser parser;
    this->my_object_->polygons_.clear();
    this->my_object_->vertexes_.clear();
    this->my_object_->vertex_count_ = 0;
    this->my_object_->polygon_count_ = 0;
    this->vector_koordinate_.clear();
    this->vector_poligons_.clear();
    error_ = parser.ParserVetexAndFace(filename, this->my_object_);
    if (error_ == true)
    {
      ReadMapTransform();
      TransformVectorPolygons();
    }
  }
  void Model::ReadMapTransform()
  {
    this->transform_["translateX"] = 0.0;
    this->transform_["translateY"] = 0.0;
    this->transform_["translateZ"] = 0.0;
    this->transform_["rotateX"] = 0.0;
    this->transform_["rotateY"] = 0.0;
    this->transform_["rotateZ"] = 0.0;
    this->transform_["scale"] = 1.0;
  }


  void Model::ModelTransform()
  {
    for (size_t i = 0; i < vector_koordinate_.size() - 2; i += 3)
    {
      coordinates_[0] = vector_koordinate_[i];
      coordinates_[1] = vector_koordinate_[i + 1];
      coordinates_[2] = vector_koordinate_[i + 2];
      RotateTransformX();
      RotateTransformY();
      RotateTransformZ();
      vector_koordinate_[i] = coordinates_[0] * transform_["scale"] +
                              (transform_["translateX"] / kSmoothnessOfMovement);
      vector_koordinate_[i + 1] = coordinates_[1] * transform_["scale"] +
                                  (transform_["translateY"] / kSmoothnessOfMovement);
      vector_koordinate_[i + 2] = coordinates_[2] * transform_["scale"] +
                                  (transform_["translateZ"] / kSmoothnessOfMovement);
    }
  }

  void Model::RotateTransformX()
  {
    float y = coordinates_[1];
    float z = coordinates_[2];
    coordinates_[1] = y * cos(transform_["rotateX"] * kDegreesToRadians) +
                      z * sin(transform_["rotateX"] * kDegreesToRadians);
    coordinates_[2] = -y * sin(transform_["rotateX"] * kDegreesToRadians) +
                      z * cos(transform_["rotateX"] * kDegreesToRadians);
  }

  void Model::RotateTransformY()
  {
    float x = coordinates_[0];
    float z = coordinates_[2];
    coordinates_[0] = x * cos(transform_["rotateY"] * kDegreesToRadians) +
                      z * sin(transform_["rotateY"] * kDegreesToRadians);
    coordinates_[2] = -x * sin(transform_["rotateY"] * kDegreesToRadians) +
                      z * cos(transform_["rotateY"] * kDegreesToRadians);
  }

  void Model::RotateTransformZ()
  {
    float x = coordinates_[0];
    float y = coordinates_[1];
    coordinates_[0] = x * cos(transform_["rotateZ"] * kDegreesToRadians) +
                      y * sin(transform_["rotateZ"] * kDegreesToRadians);
    coordinates_[1] = -x * sin(transform_["rotateZ"] * kDegreesToRadians) +
                      y * cos(transform_["rotateZ"] * kDegreesToRadians);
  }

  void Model::TransformVectorPolygons()
  {
    for (int i = 0; i < this->get_polygon_count(); i++)
    {
      for (size_t j = 0; j < this->get_poligon(i).size(); j++)
      {
        vector_poligons_.push_back(this->get_poligon(i)[j]);
      }
    }
  }
} // namespace s21
