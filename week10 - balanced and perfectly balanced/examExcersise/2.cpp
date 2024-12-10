#include <queue>
#include <iostream>
#include <cassert>
#include <climits>

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;
};

// minLevel
size_t maxLevel(const Node<char> *tree)
{
    std::queue<const Node<char> *> q;
    q.push(tree);
    size_t level = 1, max = 0, min = ULONG_MAX;
    while (!q.empty())
    {
        int size = q.size();
        bool descending = true, ascending = true;
        char prev = CHAR_MAX;
        for (size_t i = 0; i < size; i++)
        {
            const Node<char> *node = q.front();
            q.pop();
            if (node->data > prev)
            {
                descending = false;
            }
            if (node->data < prev)
            {
                ascending = false;
            }

            prev = node->data;

            if (node->left)
            {
                q.push(node->left);
            }

            if (node->right)
            {
                q.push(node->right);
            }
        }
        if (descending)
        {
            max = std::max(max, level);
        }
        if (ascending and level != 1)
        {
            min = std::min(min, level);
        }
        level++;
    }
    if (max == 0)
    {
        // there is no descending level
        throw std::logic_error("There is no descending level.");
    }
    // if (min == ULONG_MAX)
    // {
    //     // there is no ascending level
    //     throw std::logic_error("There is no ascending level.");
    // }
    // return min
    return max;
}

int main()
{
    Node<char> d{'d'};
    Node<char> c{'c'};
    Node<char> b{'b'};
    Node<char> a{'a'};
    Node<char> e{'e', &b, &a};
    Node<char> f{'f', &d, &c};
    Node<char> h{'h', &f, &e};
    assert(maxLevel(&h) == 3);
}