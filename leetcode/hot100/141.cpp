// 给你一个链表的头节点 head ，判断链表中是否有环。

// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
// 为了表示给定链表中的环，评测系统内部使用整数 pos
// 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递
// 。仅仅是为了标识链表的实际情况。

// 如果链表中存在环 ，则返回 true 。 否则，返回 false 。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <cstddef>
#include <unordered_set>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  bool hasCycle(ListNode *head) {
    while (head) {
      if (head->val == 1000001)
        return true;
      head->val = 1000001;
      head = head->next;
    }
    return false;
  }
};

// class Solution2 {
// public:
//   bool hasCycle(ListNode *head) {
//     std::unordered_set<ListNode *> seen;
//     while (head != nullptr) {
//       if (seen.count(head)) {
//         return true;
//       }
//       seen.insert(head);
//       head = head->next;
//     }
//     return false;
//   }
// };

class Solution3 {
public:
  bool hasCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return false;
    }

    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != slow) {
      if (fast == nullptr || fast->next == nullptr) {
        return false;
      }
      slow = slow->next;
      fast = fast->next->next;
    }
    return true;
  }
};
