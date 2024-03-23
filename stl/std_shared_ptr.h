#pragma once

#include "std_sp_counted_base.h"

class Weak_count;
class Shared_count {
public:
  Sp_counted_base *pi;

  friend Weak_count;

  Shared_count() : pi(nullptr){};

  template <typename T> Shared_count(T *pointer) {
    pi = new Sp_counted_ptr<T>(pointer);
  }

  Shared_count(const Shared_count &other) : pi(other.pi) {
    if (pi != nullptr)
      pi->add_ref_copy();
  }

  Shared_count &operator=(const Shared_count &other) {
    Sp_counted_base *temp = other.pi;
    if (temp != pi) {
      if (temp != nullptr)
        temp->add_ref_copy();

      if (pi != nullptr)
        pi->release();

      pi = temp;
    }
    return *this;
  }

  long get_use_count() { return pi == nullptr ? 0 : pi->get_use_count(); }

  ~Shared_count() {
    if (pi != nullptr)
      pi->release();
  }
};

template <typename T> class _weak_ptr;
template <typename T> class _shared_ptr {
  T *ptr;
  Shared_count refCount;

public:
  friend class _weak_ptr<T>;
  _shared_ptr() : ptr(nullptr), refCount() {}

  _shared_ptr(T *pointer) : ptr(pointer), refCount(pointer) {}

  _shared_ptr(const _shared_ptr &other) = default;

  _shared_ptr(const _weak_ptr<T> &pointer) : ptr(pointer.ptr), refCount() {
    refCount.pi = pointer.refCount.pi;
    if (refCount.pi != nullptr)
      refCount.pi->add_ref_copy();
  }

  _shared_ptr &operator=(const _shared_ptr &other) = default;

  long use_count() { return refCount.get_use_count(); }
  T *get() { return ptr; }
};

template <typename T> class shared_ptr : public _shared_ptr<T> {
public:
  // construct
  shared_ptr() noexcept = default;
  shared_ptr(std::nullptr_t) noexcept {}
  shared_ptr(T *pointer) : _shared_ptr<T>(pointer) {}

  // copy construct
  shared_ptr(const shared_ptr &other) : _shared_ptr<T>(other) {}

  // operator =
  shared_ptr &operator=(const shared_ptr &other) {
    this->_shared_ptr<T>::operator=(other);
    return *this;
  }
};
