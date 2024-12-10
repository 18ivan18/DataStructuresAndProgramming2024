#include "BST.h"
#include <cassert>
#include <iomanip>
#include <queue>

#include "./utils.cpp"

template <typename Key, typename Value>
struct BST<Key, Value>::Node
{
    Key key;
    Value value;
    // parent is a modification needed for the iterator
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    int count = 1;

    Node(const Key &key, const Value &value) : key{key}, value{value}
    {
    }
};

template <typename Key, typename Value>
BST<Key, Value>::BST(const std::vector<std::pair<Key, Value>> &v)
{
    assert(isSorted(v));

    root = create(v, 0, v.size() - 1);
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node *BST<Key, Value>::create(std::vector<std::pair<Key, Value>> vals, int start, int end)
{
    // create a node to store the value of arr acc. to its index
    Node *p;

    // go for the condition if it passes then go for other nodes
    // if not then simply return NULL
    if (start <= end)
    {
        int mid = (start + end) / 2;
        p = new Node(vals[mid].first, vals[mid].second); // store the value in Node of current mid of array
        p->left = create(vals, start, mid - 1);          // recursive call of function for its left child
        p->right = create(vals, mid + 1, end);           // recursive call of function for its right child
        if (p->left)
        {
            p->left->parent = p;
        }
        if (p->right)
        {
            p->right->parent = p;
        }

        return p; // after execution of all recursive calls simply return p it is containing
                  // the address of root node
    }

    return nullptr; // if start>end then simply return nullptr then that nullptr be the child of Node
}

template <typename Key, typename Value>
BST<Key, Value>::BST() : root{nullptr}
{
}

template <typename Key, typename Value>
void BST<Key, Value>::put(const Key &key, const Value &val)
{
    root = put(root, key, val);
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node *BST<Key, Value>::put(Node *x, const Key &key, const Value &value)
{
    if (!x)
    {
        return new Node(key, value);
    }
    if (key < x->key)
    {
        x->left = put(x->left, key, value);
        x->left->parent = x;
    }
    else if (key > x->key)
    {
        x->right = put(x->right, key, value);
        x->right->parent = x;
    }
    else if (key == x->key)
    {
        x->value = value;
    }
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::get(const Key &key) const
{
    Node *x = root;
    while (x)
    {
        if (key < x->key)
        {
            x = x->left;
        }
        else if (key > x->key)
        {
            x = x->right;
        }
        else
        {
            return Iterator(x);
        }
    }
    return this->end();
}

template <typename Key, typename Value>
bool BST<Key, Value>::contains(const Key &key) const
{
    return get(key);
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(const Key &key)
{
    root = remove(key, root);
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(Iterator &iter)
{
    root = remove(iter.root->key, root);
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node *BST<Key, Value>::remove(const Key &key, Node *x)
{
    if (!x)
    {
        return nullptr;
    }
    if (x->key == key)
    {
        auto toDelete = x;
        if (!x->left)
        {
            auto toReturn = x->right;
            toReturn->parent = x->parent;
            delete toDelete;
            return toReturn;
        }
        if (!x->right)
        {
            auto toReturn = x->left;
            toReturn->parent = x->parent;
            delete toDelete;
            return toReturn;
        }
        Node *t = x;
        x = min(t->right);
        x->right = deleteMin(t->right);
        x->left = t->left;
        x->parent = t->parent;
        t->left->parent = x;
        delete toDelete;
    }
    else if (x->key < key)
    {
        x->right = remove(key, x->right);
    }
    else if (x->key > key)
    {
        x->left = remove(key, x->left);
    }
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node *BST<Key, Value>::min(Node *x) const
{
    if (x->left == nullptr)
    {
        return x;
    }
    return min(x->left);
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node *BST<Key, Value>::deleteMin(Node *x)
{
    if (x->left == nullptr)
    {
        return x->right;
    }
    x->left = deleteMin(x->left);
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}

template <typename Key, typename Value>
BST<Key, Value>::~BST()
{
    del();
}

template <typename Key, typename Value>
void BST<Key, Value>::del()
{
    del(root);
}

template <typename Key, typename Value>
void BST<Key, Value>::del(Node *node)
{
    if (!node)
    {
        return;
    }
    del(node->left);
    del(node->right);
    delete node;
}

template <typename Key, typename Value>
void BST<Key, Value>::traverseInorder()
{
    traverseInorder(root);
    std::cout << std::endl;
}

template <typename Key, typename Value>
void BST<Key, Value>::traverseInorder(Node *node)
{
    if (!node)
    {
        return;
    }
    traverseInorder(node->left);
    std::cout << node->key;
    traverseInorder(node->right);
}

template <typename Key, typename Value>
int BST<Key, Value>::size(Node *x)
{
    if (!x)
    {
        return 0;
    }
    return x->count;
}

template <typename Key, typename Value>
void BST<Key, Value>::prettyPrint()
{
    printHelper(root);
}

template <typename Key, typename Value>
void BST<Key, Value>::printHelper(Node *node, int spaces)
{
    if (node != nullptr)
    {
        if (node->right)
        {
            printHelper(node->right, spaces + 4);
        }
        if (spaces)
        {
            std::cout << std::setw(spaces) << ' ';
        }
        if (node->right)
        {
            std::cout << " /\n"
                      << std::setw(spaces) << ' ';
        }
        std::cout << node->key << ":" << node->value << "\n ";
        if (node->left)
        {
            std::cout << std::setw(spaces) << ' ' << " \\\n";
            printHelper(node->left, spaces + 4);
        }
    }
}

template <typename Key, typename Value>
class BST<Key, Value>::Iterator
{
    BST<Key, Value>::Node *root;

public:
    friend class BST<Key, Value>;

    Iterator(BST<Key, Value>::Node *root) : root{root}
    {
    }

    Iterator &operator++()
    {
        if (!root)
        {
            return *this;
        }

        if (root->right)
        {
            root = root->right;
            return *this;
        }

        while (root)
        {
            if (root->parent && root->parent->key > root->key)
            {
                root = root->parent;
                break;
            }
            root = root->parent;
        }
        return *this;
    }

    Iterator &operator--()
    {
        if (root->left)
        {
            root = root->left;
            return *this;
        }

        if (!root->parent || root->parent && root->parent->key < root->key)
        {
            return *this;
        }

        while (root)
        {
            if (root->parent && root->parent->key > root->key)
            {
                root = root->parent;
                break;
            }
            root = root->parent;
        }
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator save = *this;
        ++(*this);
        return save;
    }

    std::pair<Key, Value> operator*()
    {
        return std::make_pair(root->key, root->value);
    }

    bool operator==(const Iterator &rhs)
    {
        return root == rhs.root;
    }

    bool operator!=(const Iterator &rhs)
    {
        return !(*this == rhs);
    }
};

template <typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::begin() const
{
    return Iterator(min(root));
}

template <typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::end() const
{
    return Iterator(nullptr);
}