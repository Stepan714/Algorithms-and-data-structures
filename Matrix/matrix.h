#include <stdexcept>
#pragma once
class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};
template <class T, size_t Rows, size_t Columns>
class Matrix {

 public:
  T mas_[Rows][Columns];
  size_t RowsNumber() const {
    return Rows;
  }
  size_t ColumnsNumber() const {
    return Columns;
  }
  const T& operator()(size_t i, size_t j) const {
    return mas_[i][j];
  }
  T& operator()(size_t i, size_t j) {
    return mas_[i][j];
  }
  const T& At(size_t i, size_t j) const {
    if (i > Rows - 1 || j > Columns - 1) {
      throw MatrixOutOfRange{};
    }
    return mas_[i][j];
  }
  T& At(size_t i, size_t j) {
    if (i > Rows - 1 || j > Columns - 1) {
      throw MatrixOutOfRange{};
    }
    return mas_[i][j];
  }
  Matrix<T, Rows, Columns>& operator+=(const Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        mas_[i][j] += matrix.mas_[i][j];
      }
    }
    return *this;
  }
  Matrix<T, Rows, Columns>& operator-=(const Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        mas_[i][j] -= matrix.mas_[i][j];
      }
    }
    return *this;
  }
  Matrix<T, Rows, Columns>& operator*=(const Matrix<T, Columns, Columns>& matrix) {
    Matrix<T, Rows, Columns> res = {};
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        for (size_t k = 0; k < Columns; ++k) {
          res.mas_[i][j] += (mas_[i][k] * matrix.mas_[k][j]);
        }
      }
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        mas_[i][j] = res.mas_[i][j];
      }
    }
    return *this;
  }
  friend std::istream& operator>>(std::istream& in, Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        in >> matrix.mas_[i][j];
      }
    }
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Matrix<T, Rows, Columns>& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns - 1; ++j) {
        out << matrix.mas_[i][j] << " ";
      }
      out << matrix.mas_[i][Columns - 1] << "\n";
    }
    return out;
  }
  Matrix<T, Rows, Columns>& operator*=(const T& num) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        mas_[i][j] *= num;
      }
    }
    return *this;
  }
  Matrix<T, Rows, Columns>& operator/=(const T& num) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        mas_[i][j] /= num;
      }
    }
    return *this;
  }
};
template <class T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(Matrix<T, Rows, Columns>& matrix) {
  Matrix<T, Columns, Rows> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[j][i] = matrix.mas_[i][j];
    }
  }
  return res;
}
template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& mat1, const Matrix<T, Rows, Columns>& mat2) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = mat1.mas_[i][j] + mat2.mas_[i][j];
    }
  }
  return res;
}
template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator-(const Matrix<T, Rows, Columns>& mat1, const Matrix<T, Rows, Columns>& mat2) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = mat1.mas_[i][j] - mat2.mas_[i][j];
    }
  }
  return res;
}
template <class T, size_t Rows, size_t Columns>
bool operator==(const Matrix<T, Rows, Columns>& mat1, const Matrix<T, Rows, Columns>& mat2) {
  bool flag = false;
  if (mat1.ColumnsNumber() == mat2.ColumnsNumber() && mat1.RowsNumber() == mat2.RowsNumber()) {
    flag = true;
    for (size_t i = 0; i < mat1.RowsNumber(); ++i) {
      for (size_t j = 0; j < mat1.ColumnsNumber(); ++j) {
        if (mat1.mas_[i][j] != mat2.mas_[i][j]) {
          flag = false;
          break;
        }
      }
    }
  }
  return flag;
}
template <class T, size_t Rows, size_t Columns>
bool operator!=(const Matrix<T, Rows, Columns>& mat1, const Matrix<T, Rows, Columns>& mat2) {
  bool flag = true;
  if (mat1.ColumnsNumber() == mat2.ColumnsNumber() && mat1.RowsNumber() == mat2.RowsNumber()) {
    flag = false;
    for (size_t i = 0; i < mat1.RowsNumber(); ++i) {
      for (size_t j = 0; j < mat1.ColumnsNumber(); ++j) {
        if (mat1.mas_[i][j] == mat2.mas_[i][j]) {
          flag = true;
          break;
        }
      }
    }
    if (!flag) {
      flag = true;
    }
  }
  return flag;
}
template <class T, size_t M1, size_t M2, size_t N1, size_t N2>
Matrix<T, M1, N2> operator*(const Matrix<T, M1, M2>& mat1, const Matrix<T, N1, N2>& mat2) {
  Matrix<T, M1, N2> res{};
  for (size_t i = 0; i < M1; ++i) {
    for (size_t j = 0; j < N2; ++j) {
      for (size_t k = 0; k < M2; ++k) {
        res.mas_[i][j] += (mat1.mas_[i][k] * mat2.mas_[k][j]);
      }
    }
  }
  return res;
}
template <class T, class U, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const U& num, const Matrix<T, Rows, Columns>& matrix) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = matrix.mas_[i][j] * num;
    }
  }
  return res;
}
template <class T, class U, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, Columns>& matrix, const U& num) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = matrix.mas_[i][j] * num;
    }
  }
  return res;
}
template <class T, class U, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator/(const U& num, const Matrix<T, Rows, Columns>& matrix) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = matrix.mas_[i][j] / num;
    }
  }
  return res;
}
template <class T, class U, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator/(const Matrix<T, Rows, Columns>& matrix, const U& num) {
  Matrix<T, Rows, Columns> res;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      res.mas_[i][j] = matrix.mas_[i][j] / num;
    }
  }
  return res;
}
