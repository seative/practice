// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
//     输入：head = [ 1, 2, 3, 4, 5 ], n = 2
//     输出：[1, 2, 3, 5]
#include <stack>
#include <map>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 自己的解法，进行了两次链表遍历
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *first = head;
        int i = 0, j = 0;
        while (head)
        {
            head = head->next;
            i++;
        }
        int k = i - n + 1;
        head = first;
        while (head)
        {
            ListNode *temp = head->next;
            j++;
            if (k == 1)
            {
                first = head->next;
                return first;
            }
            else if (j + 1 == k)
            {
                head->next = temp->next;
                return first;
            }
            else
                head = head->next;
        }
        return head;
    }
};

// 题解一  思路基本一致 ，但引入了哑节点，从而避免了对头部节点的判断
class Solution1
{
public:
    int getLength(ListNode *head)
    {
        int length = 0;
        while (head)
        {
            ++length;
            head = head->next;
        }
        return length;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummy = new ListNode(0, head);
        int length = getLength(head);
        ListNode *cur = dummy;
        for (int i = 1; i < length - n + 1; ++i)
        {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 题解二 引入了栈的概念，先进后出
class Solution2
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummy = new ListNode(0, head);
        std::stack<ListNode *> stk;
        ListNode *cur = dummy;
        while (cur)
        {
            stk.push(cur);
            cur = cur->next;
        }
        for (int i = 0; i < n; ++i)
        {
            stk.pop();
        }
        ListNode *prev = stk.top();
        prev->next = prev->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};
// 题解三 采用双指针，即快慢指针的概念
class Solution3
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummy = new ListNode(0, head);
        ListNode *first = head;
        ListNode *second = dummy;
        for (int i = 0; i < n; ++i)
        {
            first = first->next;
        }
        while (first)
        {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 自己写一写快慢指针，灵活加入虚节点
class Solution4
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummy = new ListNode(0, head);
        ListNode *first = head;
        ListNode *second = dummy;
        for (int i = 0; i < n; ++i)
        {
            first = first->next;
        }
        while (first)
        {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};
