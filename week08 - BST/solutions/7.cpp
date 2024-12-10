#include <vector>

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
    int idx;
    std::vector<int> v;

    void inorder(TreeNode *root, std::vector<int> &v)
    {
        if (root == nullptr)
        {
            return;
        }

        inorder(root->left, v);
        v.push_back(root->val);
        inorder(root->right, v);
    }

public:
    BSTIterator(TreeNode *root)
    {
        inorder(root, v);
        idx = 0;
    }

    int next()
    {
        if (idx < v.size())
        {
            return v[idx++];
        }
        return -1;
    }

    bool hasNext()
    {
        return idx < v.size();
    }
};

#include <stack>

// 0(h) memory, where h is the height of the tree
class BSTIterator
{
public:
    std::stack<TreeNode *> s;
    BSTIterator(TreeNode *root)
    {
        partialInorder(root);
    }

    void partialInorder(TreeNode *root)
    {
        while (root != nullptr)
        {
            s.push(root);
            root = root->left;
        }
    }

    int next()
    {
        TreeNode *top = s.top();
        s.pop();
        partialInorder(top->right);
        return top->val;
    }

    bool hasNext()
    {
        return !s.empty();
    }
};