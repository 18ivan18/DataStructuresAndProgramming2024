#ifndef AVL_TREE
#define AVL_TREE

#include <vector>

template <typename Key, typename Value>
class AVLTree
{
private:
    struct Node
    {
        const Key key;
        Value value;
        int size, height;
        Node *left = nullptr, *right = nullptr;

        Node(const Key &key, const Value &value, int size, int height) : key{key}, value{value}, size{size}, height{height}
        {
        }
    };

    Node *root = nullptr;

    int height(Node *x) const
    {
        if (!x)
        {
            return -1;
        }
        return x->height;
    }

    int size(Node *x) const
    {
        if (!x)
        {
            return 0;
        }
        return x->size;
    }

    Node *get(Node *x, const Key &key) const
    {
        if (!x)
        {
            return nullptr;
        }

        if (key < x->key)
        {
            return get(x->left, key);
        }

        if (key > x->key)
        {
            return get(x->right, key);
        }
        return x;
    }

    Node *put(Node *x, const Key &key, const Value &value)
    {
        if (x == nullptr)
        {
            return new Node(key, value, 0, 1);
        }
        if (key < x->key)
        {
            x->left = put(x->left, key, value);
        }
        else if (key > x->key)
        {
            x->right = put(x->right, key, value);
        }
        else
        {
            x->value = value;
            return x;
        }
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        return balance(x);
    }

    Node *balance(Node *x)
    {
        if (balanceFactor(x) < -1)
        {
            if (balanceFactor(x->right) > 0)
            {
                x->right = rotateRight(x->right);
            }
            x = rotateLeft(x);
        }
        else if (balanceFactor(x) > 1)
        {
            if (balanceFactor(x->left) < 0)
            {
                x->left = rotateLeft(x->left);
            }
            x = rotateRight(x);
        }
        return x;
    }

    int balanceFactor(Node *x)
    {
        return height(x->left) - height(x->right);
    }

    Node *rotateRight(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;
        y->size = x->size;
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));
        return y;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        y->size = x->size;
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));
        return y;
    }

    Node *remove(Node *x, const Key &key)
    {
        if (x->key < key)
        {
            x->left = remove(x->left, key);
        }
        else if (x->key > key)
        {
            x->right = remove(x->right, key);
        }
        else
        {
            if (x->left == nullptr)
            {
                Node *rightValue = x->right;
                delete x;
                return rightValue;
            }
            else if (x->right == nullptr)
            {
                Node *leftValue = x->left;
                delete x;
                return leftValue;
            }
            else
            {
                Node *y = x;
                x = min(y->right);
                x->right = deleteMin(y->right);
                x->left = y->left;
            }
        }
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        return balance(x);
    }
    Node *deleteMin(Node *x)
    {
        if (x->left == nullptr)
        {
            Node *rightValue = x->right;
            delete x;
            return rightValue;
        }
        x->left = deleteMin(x->left);
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        return balance(x);
    }

    Node *min(Node *x)
    {
        if (x->left == nullptr)
        {
            return x;
        }
        return min(x->left);
    }

    void keysInOrder(Node *x, std::vector<Key> &queue) const
    {
        if (x == nullptr)
        {
            return;
        }
        keysInOrder(x->left, queue);
        queue.push_back(x->key);
        keysInOrder(x->right, queue);
    }

    std::vector<Key> keysInOrder() const
    {
        std::vector<Key> queue;
        keysInOrder(root, queue);
        return queue;
    }

public:
    int height() const
    {
        return height(root);
    }

    int size() const
    {
        return size(root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    // TODO: use iterators here
    Value *get(const Key &key) const
    {
        Node *x = get(root, key);
        if (x == nullptr)
        {
            return nullptr;
        }
        return &x->value;
    }

    bool contains(const Key &key) const
    {
        return get(key) != nullptr;
    }

    void put(const Key &key, const Value &value)
    {
        root = put(root, key, value);
    }

    void remove(const Key &key)
    {
        if (!contains(key))
        {
            return;
        }
        root = remove(root, key);
    }

    std::vector<Key> keys() const
    {
        return keysInOrder();
    }
};

#endif