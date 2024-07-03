
#include <iostream>
#include <vector>
using namespace std;

// template <int M, int N> class Matrix {
//   float m_data[M * N];
//   float &operator()(int i, int j) { return m_data[i + j * M]; }
// };

// template <int M, int N>
// Matrix<M, N> operator+(const Matrix<M, N> &A, const Matrix<M, N> &B) {
//   Matrix<M, N> res;
//   for (int j = 0; j < N; ++j)
//     for (int i = 0; i < M; ++i)
//       res(i, j) = A(i, j) + B(i, j);
//   return res;
// }

template <typename ExprA, typename ExprB> class MatrixSum {
  const ExprA &lhs;
  const ExprB &rhs;

public:
  MatrixSum(const ExprA &lhs, const ExprB &rhs) : lhs(lhs), rhs(rhs) {}

  float coeff(int i, int j) { return lhs.coeff(i, j) + rhs.coeff(i, j); }

  template <typename ExprC>
  MatrixSum<MatrixSum<ExprA, ExprB>, ExprC> operator+(const ExprC &rhs) {
    return MatrixSum<MatrixSum<ExprA, ExprB>, ExprC>(*this, rhs);
  }
};

template <int M, int N> class Matrix {
  float m_data[M * N];

public:
  float &coeff(int i, int j) { return m_data[i + j * M]; }
  MatrixSum<Matrix, Matrix> operator+(const Matrix &rhs) {
    return MatrixSum<Matrix, Matrix>(*this, rhs);
  }
};

int main() {
  Matrix<3, 3> mat1;
  Matrix<3, 3> mat2;
  Matrix<3, 3> mat3;
  auto expr = mat1 + mat2 + mat3;
  cout << endl;
}
