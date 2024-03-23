#pragma once

#include "std_shared_ptr.h"
#include "std_sp_counted_base.h"

class Weak_count {
public:
  Sp_counted_base *pi;

  friend Shared_count;

  Weak_count() : pi(nullptr){};

  Weak_count(const Shared_count &other) : pi(other.pi) {}

  Weak_count(const Weak_count &other) : pi(other.pi) {
    if (pi != nullptr)
      pi->weak_add_ref();
  }

  Weak_count &operator=(const Weak_count &other) {
    Sp_counted_base *temp = other.pi;
    if (temp != pi) {
      if (temp != nullptr)
        temp->weak_add_ref();

      if (pi != nullptr)
        pi->weak_release();

      pi = temp;
    }
    return *this;
  }

  long get_use_count() { return pi == nullptr ? 0 : pi->get_use_count(); }

  ~Weak_count() {
    if (pi != nullptr)
      pi->weak_release();
  };
};

template <typename T> class _shared_ptr;

template <typename T> class _weak_ptr {
  T *ptr;
  Weak_count refCount;

public:
  friend class _shared_ptr<T>;

  _weak_ptr() : ptr(nullptr), refCount() {}

  _weak_ptr(const _shared_ptr<T> &pointer)
      : ptr(pointer.ptr), refCount(pointer.refCount) {}

  _weak_ptr(const _weak_ptr &other) = default;

  _weak_ptr &operator=(const _weak_ptr &other) = default;

  long use_count() { return refCount.get_use_count(); }

  bool expired() { return refCount.get_use_count() == 0; }

  _shared_ptr<T> lock() const noexcept { return _shared_ptr<T>(*this); }
};

template <typename T> class weak_ptr : public _weak_ptr<T> {
public:
  // construct
  weak_ptr() noexcept = default;
  weak_ptr(const shared_ptr<T> &other) : _weak_ptr<T>(other) {}

  // copy construct
  weak_ptr(const weak_ptr &other) : _weak_ptr<T>(other) {}

  // operator =
  weak_ptr &operator=(const weak_ptr &other) {
    this->_weak_ptr<T>::operator=(other);
    return *this;
  }
};
