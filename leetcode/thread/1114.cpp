#include <printf.h>

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

using namespace std;

void first() { printf("first"); }
void second() { printf("second"); }
void third() { printf("third"); }

// class Foo {
//   std::atomic<int> order = 0;

//  public:
//   Foo() {}

//   void first(function<void()> printFirst) {
//     while (order != 0) {
//       this_thread::yield();
//     }
//     printFirst();
//     order = 1;
//   }

//   void second(function<void()> printSecond) {
//     while (order != 1) {
//       this_thread::yield();
//     }
//     printSecond();
//     order = 2;
//   }

//   void third(function<void()> printThird) {
//     while (order != 2) {
//       this_thread::yield();
//     }
//     printThird();
//   }
// };

// wrong
class Foo {
  std::condition_variable cv;
  std::mutex mtx;
  int order = 0;

 public:
  Foo() {}

  void first(function<void()> printFirst) {
    std::unique_lock lck(mtx);
    cv.wait(lck, [&] { return order == 0; });
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    order = 1;
    lck.unlock();
    cv.notify_all();  // 注意要用notify_all
  }

  void second(function<void()> printSecond) {
    std::unique_lock lck(mtx);
    cv.wait(lck, [&] { return order == 1; });
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    order = 2;
    lck.unlock();
    cv.notify_all();
  }

  void third(function<void()> printThird) {
    std::unique_lock lck(mtx);
    cv.wait(lck, [&] { return order == 2; });
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }
};

int main() {
  Foo foo;
  std::thread t1(&Foo::first, &foo, first);
  std::thread t2(&Foo::second, &foo, second);
  std::thread t3(&Foo::third, &foo, third);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
