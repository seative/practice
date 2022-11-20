#ifndef VECTOR3_H_
#define VECTOR3_H_
#include "vector.h"
namespace test
{
    template <typename T>
    class Vector<T, 3> final
    {
    public:
        T x;
        T y;
        T z;
        constexpr Vector() : x(0), y(0), z(0) {}
        constexpr Vector(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
        template <typename U>
        Vector(const std::initializer_list<U> lst);
        constexpr Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}
        void set(T s);
        void set(T x, T y, T z);
        // void set(const Vector2<T> &pt, T z);
        template <typename U>
        void set(const std::initializer_list<U> &lst);
        void set(const Vector &v);
        void setZero();
        void normalize();
        Vector add(T v) const;
        Vector add(const Vector &v) const;
        Vector sub(T v) const;
        Vector sub(const Vector &v) const;
        Vector mul(T v) const;
        Vector mul(const Vector &v) const;
        Vector div(T v) const;
        Vector div(const Vector &v) const;
        T length() const;
    };
    template <typename T>
    using Vector3 = Vector<T, 3>;

    //! Float-type 3D vector.
    typedef Vector3<float> Vector3F;

    //! Double-type 3D vector.
    typedef Vector3<double> Vector3D;

    //! Returns float-type zero vector.
    // template <>
    // constexpr Vector3F zero<Vector3F>()
    // {
    //     return Vector3F(0.f, 0.f, 0.f);
    // }

    // //! Returns double-type zero vector.
    // template <>
    // constexpr Vector3D zero<Vector3D>()
    // {
    //     return Vector3D(0.0, 0.0, 0.0);
    // }

    template <typename T>
    struct ScalarType<Vector3<T>>
    {
        typedef T value;
    };
} // namespace test

#include "vector_3_inl.h"

#endif