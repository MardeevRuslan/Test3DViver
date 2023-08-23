#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void AllocationMatrix();
  void DestroyMatrix();
  void CopyMatrix(const S21Matrix& other);
  bool ValidateMatrix(const S21Matrix& other);
  void MinorMatrix(S21Matrix& other, int rows, int cols);

 public:
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  // S21Matrix operator[](int row, int col);

  double& operator()(int row, int col);

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
};

#endif  // SRC_S21_MATRIX_OOP_H_