#pragma once

#include <atomic>

class Sp_counted_base {
  std::atomic<long> use_count;
  std::atomic<long> weak_count;

  Sp_counted_base(const Sp_counted_base &other) = delete;
  Sp_counted_base &operator=(const Sp_counted_base &other) = delete;

public:
  Sp_counted_base() : weak_count(1), use_count(1) {}

  long get_use_count() { return use_count; }

  void add_ref_copy() { ++use_count; }
  void weak_add_ref() { ++weak_count; }

  void release() {
    if (--use_count == 0) {
      dispose();
      if (--weak_count == 0) {
        destroy();
      }
    }
  };

  void weak_release() {
    if (--weak_count == 0)
      destroy();
  }

  virtual void destroy() {};
  virtual void dispose() {};
};

template <typename T> class Sp_counted_ptr : public Sp_counted_base {
  T *ptr;

  Sp_counted_ptr(const Sp_counted_ptr &other) = delete;
  Sp_counted_ptr operator=(const Sp_counted_ptr &other) = delete;

public:
  Sp_counted_ptr(T *pointer) : Sp_counted_base(), ptr(pointer) {}
  virtual void dispose() { delete ptr; }
  virtual void destroy() { delete this; };
};