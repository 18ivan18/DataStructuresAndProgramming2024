// Time:
//      BSTIterator: O(H)
//      hasNext: O(1)
//      next: amortized O(1)
//      hasPrev: O(1)
//      prev: O(1)
// Space: O(N)

#include <vector>
#include <stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator
{
    std::vector<int> seen;
    int i = -1;
    std::stack<TreeNode *> s;
    void pushNodes(TreeNode *root)
    {
        while (root)
        {
            s.push(root);
            root = root->left;
        }
    }

public:
    BSTIterator(TreeNode *root)
    {
        pushNodes(root);
    }

    bool hasNext()
    {
        return i < seen.size() - 1 || s.size();
    }

    int next()
    {
        i++;
        if (i == seen.size())
        {
            TreeNode *node = s.top();
            s.pop();
            seen.push_back(node->val);
            pushNodes(node->right);
            return node->val;
        }
        return seen[i];
    }

    bool hasPrev()
    {
        return i > 0;
    }

    int prev()
    {
        return seen[--i];
    }
};