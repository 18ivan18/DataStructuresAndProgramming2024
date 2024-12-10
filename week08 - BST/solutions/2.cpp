#include <string>
#include <vector>
#include <sstream>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::string serialize(TreeNode *r)
{
    if (!r)
    {
        return "";
    }
    return std::to_string(r->val) + " " + serialize(r->left) + serialize(r->right);
}

TreeNode *deserialize(std::string data)
{
    std::vector<int> preorder;
    std::stringstream ss(data);
    for (std::string s; ss >> s;)
    {
        preorder.push_back(stoi(s));
    }
    return buildTree(preorder.begin(), preorder.end());
}

// s: preorder start; e: preorder end
TreeNode *buildTree(std::vector<int>::iterator s, std::vector<int>::iterator e)
{
    if (s == e)
    {
        return nullptr;
    }
    auto i = upper_bound(s + 1, e, *s);
    auto r = new TreeNode(*s);
    r->left = buildTree(s + 1, i);
    r->right = buildTree(i, e);
    return r;
}