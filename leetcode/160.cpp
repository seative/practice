// 给你两个单链表的头节点 headA 和 headB
// ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回
// null 。

// 图示两个链表在节点 c1 开始相交：

// 题目数据 保证 整个链式结构中不存在环。

// 注意，函数返回结果后，链表必须 保持其原始结构 。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <cstddef>
#include <set>
#include <unordered_set>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    std::set<ListNode *> seen;
    while (headA != nullptr) {
      seen.insert(headA);
      headA = headA->next;
    }
    while (headB != nullptr) {
      if (seen.count(headB)) {
        return headB;
      }
      headB = headB->next;
    }
    return nullptr;
  }
};

class Solution2 {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
      return nullptr;
    }
    ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
      pA = pA == nullptr ? headB : pA->next;
      pB = pB == nullptr ? headA : pB->next;
    }
    return pA;
  }
};