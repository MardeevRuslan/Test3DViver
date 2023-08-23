#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <cstdio>
#include <fstream>
#include <cstring>
#include <sstream>


#include "object.h"
#include "model.h"
#include "s21_matrix_oop.h"

namespace s21
{
    class Parser
    {
    public:
        Parser() = default;
        Parser(const Parser &) = delete;
        Parser(Parser &&) = delete;
        // Parser &operator=(const Parser &) = delete;
        // Parser &operator=(Parser &&) = delete;
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
}

#endif // SRC_PARSER_H_
