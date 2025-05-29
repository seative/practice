// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
// 。 void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value
// ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过
// capacity ，则应该 逐出 最久未使用的关键字。 函数 get 和 put 必须以 O(1)
// 的平均时间复杂度运行。
#include <stack>
#include <unordered_map>

struct LListNode {
  int key, val;
  LListNode* next;
  LListNode* prev;
  LListNode(int x, int y) : key(x), val(y), next(nullptr) {}
};

class LRUCache {
  int mCapacity;
  int mSize;
  std::unordered_map<int, LListNode*> mCache;
  LListNode* head;
  LListNode* tail;

  void removeNode(LListNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  LListNode* removeTail() {
    LListNode* node = tail->prev;
    removeNode(node);
    return node;
  }

  void addToHead(LListNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void moveToHead(LListNode* node) {
    removeNode(node);
    addToHead(node);
  }

 public:
  LRUCache(int capacity) {
    mCapacity = capacity;
    mSize = 0;
    mCache.reserve(capacity);
    head = new LListNode(-1, -1);
    tail = new LListNode(-1, -1);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (mCache.count(key)) {
      LListNode* node = mCache[key];
      moveToHead(node);
      return node->val;
    }
    return -1;
  }

  void put(int key, int value) {
    if (mCache.count(key)) {
      LListNode* node = mCache[key];
      node->val = value;
      moveToHead(node);
    } else {
      LListNode* node = new LListNode(key, value);
      mCache[key] = node;
      addToHead(node);
      ++mSize;
      if (mSize > mCapacity) {
        LListNode* removed = removeTail();
        mCache.erase(removed->key);
        delete removed;
        --mSize;
      }
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */