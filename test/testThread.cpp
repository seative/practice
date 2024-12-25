#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class SomeClass {
 public:
  void data_transfer() {
    // 模拟数据传输操作
    std::cout << "Data transfer" << std::endl;
  }
};

class MyClass {
 public:
  MyClass() : mStat(std::make_unique<SomeClass>()), lck(mtx, std::defer_lock) {}

  void prepare() {
    // std::unique_lock<std::mutex> tempLck(mtx);
    // lck = std::move(tempLck);
    mtx.lock();
    callNum++;
    std::cout << "callNum: " << callNum << std::endl;
    mStat->data_transfer();
    std::cout << "lck owns lock: " << lck.owns_lock() << std::endl;
  }

  void clear() {
    // if (lck.owns_lock()) {
    //   lck.unlock();
    //   callNum--;
    //   std::cout << callNum << "  own lock" << std::endl;
    // } else {
    //   std::cout << "lck does not own lock" << std::endl;
    // }
    mtx.unlock();
  }

 private:
  std::unique_lock<std::mutex> lck;
  std::mutex mtx;
  int callNum = 0;
  std::unique_ptr<SomeClass> mStat;
};

void threadFunction(MyClass& obj) {
  obj.prepare();
  obj.clear();
};

int main() {
  MyClass obj;

  std::thread t1(threadFunction, std::ref(obj));
  std::thread t2(threadFunction, std::ref(obj));

  t1.join();
  t2.join();

  return 0;
}