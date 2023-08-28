#include <gtest/gtest.h>



#include "3DViewer/object.h"
#include "3DViewer/parser.h"


TEST(parser, test_1) {
  s21::Object object;
  s21::Parser parser;
  bool res = parser.ParserVetexAndFace("models_folder/4.obj", &object);
  ASSERT_EQ(object.vertex_count_, 4);
  ASSERT_EQ(object.polygon_count_, 1);
  ASSERT_TRUE(res);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
