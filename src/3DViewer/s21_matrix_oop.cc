#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool check = true;
  if (ValidateMatrix(other) == false || ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    check = false;
  }
  for (int i = 0; i < rows_ && check == true; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(other.matrix_[i][j] - matrix_[i][j]) > 1E-7) {
        check = false;
      }
    }
  }
  return check;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (ValidateMatrix(other) == false || ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::out_of_range("Error: different dimension of matrices");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (ValidateMatrix(other) == false || ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::out_of_range("Error: different dimension of matrices");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (ValidateMatrix(other) == false || ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Error: the number of columns of the first matrix is not equal to the "
        "number of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  if (ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (cols_ != rows_) {
    throw std::out_of_range("Error: the matrix is not square");
  }
  S21Matrix res(rows_, cols_);
  S21Matrix tmp;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp = *this;
      MinorMatrix(tmp, i, j);
      double b = tmp.Determinant();
      res.matrix_[i][j] = b * pow(-1, i + j);
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (cols_ != rows_) {
    throw std::out_of_range("Error: the matrix is not square");
  }
  double determinant = 0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix tmp(*this);
      MinorMatrix(tmp, 0, j);
      determinant += pow(-1, j) * matrix_[0][j] * tmp.Determinant();
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (ValidateMatrix(*this) == false) {
    throw std::out_of_range("Error: Matrix have 0 rows or columns");
  }
  if (cols_ != rows_) {
    throw std::out_of_range("Error: the matrix is not square");
  }
  S21Matrix tmp(*this);
  double res_determinant = tmp.Determinant();
  if (fabs(res_determinant) >= 1E-7) {
    tmp = CalcComplements();
    tmp = tmp.Transpose();
    tmp.MulNumber(1.0 / res_determinant);
  } else {
    throw std::runtime_error("Error: matrix determinant is eq 0");
  }
  return tmp;
}

bool S21Matrix::ValidateMatrix(const S21Matrix &other) {
  bool check = true;
  if (other.cols_ <= 0 || other.rows_ <= 0 || other.matrix_ == NULL) {
    check = false;
  }
  return check;
}

void S21Matrix::MinorMatrix(S21Matrix &other, int rows, int cols) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (i >= rows && j >= cols) {
        result.matrix_[i][j] = other.matrix_[i + 1][j + 1];
      } else if (i >= rows && j < cols) {
        result.matrix_[i][j] = other.matrix_[i + 1][j];
      } else if (j >= cols && i < rows) {
        result.matrix_[i][j] = other.matrix_[i][j + 1];
      } else {
        result.matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  other = result;
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows_ != rows) {
    S21Matrix copy(rows, cols_);
    int copy_rows = 0;
    if (rows < rows_)
      copy_rows = rows;
    else
      copy_rows = rows_;
    for (int i = 0; i < copy_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        copy.matrix_[i][j] = matrix_[i][j];
        if (i > rows_) {
          copy.matrix_[i][j] = 0;
        }
      }
    }
    *this = copy;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols_ != cols) {
    S21Matrix copy(rows_, cols);
    int copy_cols = 0;
    if (cols < cols_)
      copy_cols = cols;
    else
      copy_cols = cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < copy_cols; j++) {
        copy.matrix_[i][j] = matrix_[i][j];
        if (j > cols_) {
          copy.matrix_[i][j] = 0;
        }
      }
    }
    *this = copy;
  }
}