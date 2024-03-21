// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
// 输入：l1 = [1,2,4], l2 = [1,3,4]
// 输出：[1,1,2,3,4,4]
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 自己写的 没写出来 和题解不一样的是 题解构造一个新链表 我想在判断的位置，更改指针
// 细节上没写好
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {

        ListNode *dummy = list1->val > list2->val ? list2 : list1;
        ListNode *cur = list1->val > list2->val ? list1 : list2;
        ListNode *dummy1 = dummy;
        ListNode *temp;

        while (!dummy->next)
        {
            if (dummy->next->val <= cur->val)
                dummy = dummy->next;
            else
            {
                temp = dummy->next;
                dummy->next = cur;
                cur = temp;
            }
        }
        return dummy1;
    }
};

// 题解 迭代法 构造一个新链表
class Solution1
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *preHead = new ListNode(-1);

        ListNode *prev = preHead;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                prev->next = l1;
                l1 = l1->next;
            }
            else
            {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }
};