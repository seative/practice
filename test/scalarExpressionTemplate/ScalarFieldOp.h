#pragma once

#include <cassert>
#include <iostream>

namespace tf
{
  template <typename T, typename E>
  class ScalarFieldOp
  {
  public:
    const E &derived() const
    {
      return static_cast<const E &>(*this);
    }
    // virtual ~ScalarFieldOp(){};
  };

  template <typename T, typename E1, typename E2, typename Op>
  class ScalarBinaryOp : public ScalarFieldOp<T, ScalarBinaryOp<T, E1, E2, Op>>
  {
  public:
    // 场运算表达式中的二元运算，返回标量场，例如rho+rho
    ScalarBinaryOp(const E1 &u, const E2 &v) : mU(u), mV(v)
    {
      // assert(mU.size() == mV.size());
    }

    // 返回场运算中给定数据点的标量值
    T operator()(size_t id) const
    {
      std::cout << "binary happend" << std::endl;
      return mOp(mU(id), mV(id));
    }

  private:
    const E1 &mU;
    const E2 &mV;
    Op mOp;
  };

  template <typename T, typename E, typename Op>
  class ScalarConsBinaryOp : public ScalarFieldOp<T, ScalarConsBinaryOp<T, E, Op>>
  {
  public:
    // 场运算表达式中的二元运算,返回标量场,其中一元为常数,例如rho+1
    ScalarConsBinaryOp(const E &u, const T &v) : mU(u), mV(v) {}

    T operator()(size_t id) const
    {
      std::cout << "cosbinary happend" << std::endl;
      return mOp(mU(id), mV);
    }

  private:
    const E &mU;
    T mV;
    Op mOp;
  };

  // 二元运算,常用四则运算的类型别名
  template <typename T, typename E1, typename E2>
  using ScalarAdd = ScalarBinaryOp<T, E1, E2, std::plus<T>>;

  template <typename T, typename E>
  using ScalarConsAdd = ScalarConsBinaryOp<T, E, std::plus<T>>;

  template <typename T, typename E1, typename E2>
  ScalarAdd<T, E1, E2> operator+(const ScalarFieldOp<T, E1> &a,
                                 const ScalarFieldOp<T, E2> &b)
  {
    return ScalarAdd<T, E1, E2>(a.derived(), b.derived());
  }

  template <typename T, typename E>
  ScalarConsAdd<T, E> operator+(const ScalarFieldOp<T, E> &a, const T &b)
  {
    return ScalarConsAdd<T, E>(a.derived(), b);
  }

  template <typename T, typename E>
  ScalarConsAdd<T, E> operator+(const T &a, const ScalarFieldOp<T, E> &b)
  {
    return ScalarConsAdd<T, E>(b.derived(), a);
  }
} // namespace tf