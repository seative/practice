// 给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。

// 示例 1：

// 输入：head = [1,2,3,3,4,4,5]
// 输出：[1,2,5]
// 示例 2：

// 输入：head = [1,1,1,2,3]
// 输出：[2,3]

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head)
            return nullptr;

        ListNode *preHead = new ListNode();
        ListNode *prev = preHead;

        int flag = head->val - 1;
        while (head->next)
        {
            if (head->val != head->next->val && head->val != flag)
            {
                prev->next = head;
                prev = prev->next;
            }

            flag = head->val;
            head = head->next;
        }
        if (head->val != flag)
            prev->next = head;
        else
            prev->next = nullptr;
        return preHead->next;
    }
};