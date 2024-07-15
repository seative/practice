
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

template <typename Expr>
class Evaluator;
template <int M, int N>
class Matrix {
 public:
  float m_data[M * N];

  const float &coeff(int i, int j) const { return m_data[i + j * M]; }
  float &coeff(int i, int j) { return m_data[i + j * M]; }

  template <typename Expr>
  Matrix &operator=(const Expr &expr) {
    for (int j = 0; j < N; ++j)
      for (int i = 0; i < M; ++i) coeff(i, j) = expr.coeff(i, j);
    return *this;
  }
};

template <typename ExprA, typename ExprB>
class MatrixSum {
  const ExprA &lhs;
  const ExprB &rhs;

 public:
  MatrixSum(const ExprA &lhs, const ExprB &rhs) : lhs(lhs), rhs(rhs) {}

  float coeff(int i, int j) const {
    return Evaluator<ExprA, ExprB>(lhs, rhs).coeff(i, j);
  }
};

template <int M, int N>
class MatrixSum<Matrix<M, N>, Matrix<M, N>> {
  Matrix<M, N> temp;

 public:
  MatrixSum(const Matrix<M, N> &lhs, const Matrix<M, N> &rhs) {
    for (int j = 0; j < N; ++j) {
      for (int i = 0; i < M; ++i) {
        temp.coeff(i, j) = lhs.coeff(i, j) + rhs.coeff(i, j);
      }
    }
  }

  float coeff(int i, int j) const { return temp.coeff(i, j); }
};

template <int M, int N>
MatrixSum<Matrix<M, N>, Matrix<M, N>> operator+(const Matrix<M, N> &lhs,
                                                const Matrix<M, N> &rhs) {
  return MatrixSum<Matrix<M, N>, Matrix<M, N>>(lhs, rhs);
}

template <int M, int N, typename Expr>
MatrixSum<Matrix<M, N>, Expr> operator+(const Matrix<M, N> &lhs,
                                        const Expr &rhs) {
  return MatrixSum<Matrix<M, N>, Expr>(lhs, rhs);
}

template <int M, int N, typename Expr>
MatrixSum<Expr, Matrix<M, N>> operator+(const Expr &lhs,
                                        const Matrix<M, N> &rhs) {
  return MatrixSum<Expr, Matrix<M, N>>(lhs, rhs);
}

template <typename ExprA, typename ExprB>
class Evaluator<MatrixSum<ExprA, ExprB>> {
  Evaluator<ExprA> evalA(A);
  Evaluator<ExprB> evalB(B);

  float coeff(int i, int j) const {
    return evalA.coeff(i, j) + evalB.coeff(i, j);
  }
};

template <Dest, Source>
class Evaluator<Assign<Dest, Source>> {
  Evaluator<Dest> evalDst(dest);
  Evaluator<Source> evalSrc(source);
  void run() {
    for (int i = 0; i < evalDst.size(); ++i)
      evalDst.coeff(i) = evalSrc.coeff(i);
  }
};

template <int M, int N>
class Evaluator<Matrix<M, N>> {
  const Matrix<M, N> &mat;
  float coeff(int i, int j) const { return mat.coeff(i, j); }
};

int main() {
  Matrix<3, 3> mat1 = {1, 2, 3};
  Matrix<3, 3> mat2 = {4, 5, 6};
  Matrix<3, 3> mat3 = {7, 8, 9};
  Matrix<3, 3> expr;
  expr = mat1 + mat2 + mat3;
  cout << expr.coeff(0, 0) << expr.coeff(1, 0) << expr.coeff(2, 0) << endl;
}
