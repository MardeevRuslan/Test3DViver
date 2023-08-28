#include <gtest/gtest.h>

#include <cstdint>


#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#include "3DViewer/object.h"
#include "3DViewer/parser.h"
#include "3DViewer/controller.h"
#include "3DViewer/model.h"


TEST(parser, test_1) {
  s21::Object object;
  s21::Parser parser;
  parser.ParserVetexAndFace("models_folder/4.obj", &object);
  ASSERT_EQ(object.vertex_count_, 4);
}

TEST(parser, test_2) {
  s21::Object object;
  s21::Parser parser;
  bool res = parser.ParserVetexAndFace("models_folder/4.obj", &object);
  ASSERT_TRUE(res);
}

TEST(parser, test_3) {
  s21::Object object;
  s21::Parser parser;
  parser.ParserVetexAndFace("models_folder/4.obj", &object);
  ASSERT_EQ(object.polygon_count_, 1);

}

TEST(parser, test_4) {
  s21::Object object;
  s21::Parser parser;
  parser.ParserVetexAndFace("models_folder/45.obj", &object);
  ASSERT_EQ(object.vertex_count_, 0);
}

TEST(parser, test_5) {
  s21::Object object;
  s21::Parser parser;
  parser.ParserVetexAndFace("models_folder/45.obj", &object);
  ASSERT_EQ(object.polygon_count_, 0);

}

TEST(parser, test_6) {
  s21::Object object;
  s21::Parser parser;
  bool res = parser.ParserVetexAndFace("models_folder/45.obj", &object);
  ASSERT_FALSE(res);
}

TEST(controller, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/45.obj");
  bool flag_open = controller.get_error();
  ASSERT_FALSE(flag_open);
}

TEST(controller, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  bool flag_open = controller.get_error();
  ASSERT_TRUE(flag_open);
}

TEST(controller, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("rotateX", 90);
  float rotate_x = controller.get_transform("rotateX");
  ASSERT_EQ(rotate_x, 90);
}

TEST(controller, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("scale", 2);
  float scale = controller.get_transform("scale");
  ASSERT_EQ(scale, 2);
}

TEST(controller, test_5) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  uint vertex_count = controller.get_vertex_count();
  ASSERT_EQ(vertex_count, 4);
}

TEST(controller, test_6) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  uint polygon_count = controller.get_polygon_count();
  ASSERT_EQ(polygon_count, 1);
}

TEST(controller, test_7) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/47.obj");
  uint vertex_count = controller.get_vertex_count();
  ASSERT_EQ(vertex_count, 0);
}

TEST(controller, test_8) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/46.obj");
  uint polygon_count = controller.get_polygon_count();
  ASSERT_EQ(polygon_count, 0);
}

TEST(controller, test_9) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  size_t indices_size = controller.get_indices_size();
  ASSERT_EQ(indices_size, 8);
}

TEST(model, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("scale", 2);
  float *vertices = controller.get_vertices();
  ASSERT_EQ(vertices[4], 1);
  delete[] vertices;
}

TEST(model, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("scale", 10);
  float *vertices = controller.get_vertices();
  ASSERT_EQ(vertices[4], 5);
  delete[] vertices;
}

TEST(model, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("translateX", 10);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[0], 0.4, 0.0001);
  delete[] vertices;
}

TEST(model, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("translateY", 10);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[1], 0.4, 0.0001);
  delete[] vertices;
}

TEST(model, test_5) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("translateZ", 10);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[2], 0.4, 0.0001);
  delete[] vertices;
}
TEST(model, test_6) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("rotateX", 180);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[0], 0, 0.0001);
  delete[] vertices;
}

TEST(model, test_7) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("rotateY", 180);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[1], 0, 0.0001);
  delete[] vertices;
}

TEST(model, test_8) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("rotateZ", 180);
  float *vertices = controller.get_vertices();
  EXPECT_NEAR(vertices[2], 0, 0.0001);
  delete[] vertices;
}

TEST(model, test_9) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.DataTransmission("models_folder/4.obj");
  controller.set_transform("rotateZ", 180);
  uint *incides = controller.get_indices();
  ASSERT_EQ(incides[1], 1);
  delete[] incides;
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
