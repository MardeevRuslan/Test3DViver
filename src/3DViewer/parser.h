#ifndef CPP4_3DVIWER_3DVIEWER_PARSER_H_
#define CPP4_3DVIWER_3DVIEWER_PARSER_H_

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "model.h"
#include "object.h"

namespace s21 {
class Parser {
 public:
  Parser() = default;
  Parser(const Parser &) = delete;
  Parser(Parser &&) = delete;
  Parser &operator=(const Parser &) = delete;
  Parser &operator=(Parser &&) = delete;
  ~Parser() = default;
  void ParserVetexAndFace(std::string filename, Object *object);

 private:
  void OpenFile(std::string filename);
  void ParserFace(std::string line);
  void ParserVetex(std::string line);
  void ReductionCoordinates();

  std::ifstream file_;
  Object *my_object_;
  int error_ = 0;
};
}  // namespace s21

#endif  // CPP4_3DVIWER_3DVIEWER_PARSER_H_
