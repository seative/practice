#ifndef ARRAY_2_H_
#define ARRAY_2_H_
#include "array.h"
#include <iostream>
#include <vector>

namespace test
{
    struct Size2
    {
        size_t x;
        size_t y;
    };
    template <typename T>
    class Array<T, 2> final
    {
    public:
        typedef std::vector<T> ContainerType;
        typedef typename ContainerType::iterator Iterator;
        typedef typename ContainerType::const_iterator ConstIterator;

        // 默认构造和带参构造
        Array();
        explicit Array(const Size2 &size, const T &initval = T());
        Array(size_t width, size_t height, const T &initval = T());
        Array(const std::initializer_list<std::initializer_list<T>> &lst);

        // 拷贝构造
        Array(const Array &other);
        //移动构造
        Array(Array &&other);

        void set(const T &value);
        void set(const Array &other);
        void set(const std::initializer_list<std::initializer_list<T>> &lst);

        void clear();

        void resize(const Size2 &size, const T &value = T());
        void resize(size_t width, size_t height, const T &initVal = T());

        T &at(size_t i);
        const T &at(size_t i) const;
        T &at(size_t i, size_t j);
        const T &at(size_t i, size_t j) const;

        Size2 size() const;
        size_t width() const;
        size_t height() const;

        T *data();
        const T *const data() const;

        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;

        // ArrayAccessor2<T> accessor();
        // ConstArrayAccessor<T> constaccessor() const;

        void swap(Array &other);

        template <typename Callback>
        void foreach (Callback func) const;
        template <typename Callback>
        void forEachIndex(Callback func) const;

        T &operator[](size_t i);
        const T &operator[](size_t i) const;
        T &operator()(size_t i, size_t j);
        const T &operator()(size_t i, size_t j) const;

        Array &operator=(const T &other);
        Array &operator=(const Array &other);
        Array &operator=(Array &&other);
        Array &operator=(
            const std::initializer_list<std::initializer_list<T>> &lst);

        // operator ArrayAccessor2<T>();
        // operator ConstArrayAccessor2<T>() const;

    private:
        ContainerType _data;
        Size2 _size;
    };

    template <typename T>
    using Array2 = Array<T, 2>;
    
} //namespace test

#include "array_2_inl.h"

#endif
