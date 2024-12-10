#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <vector>
#include <iostream>

template <typename Key, typename Value>
class BST
{
private:
    struct Node;

    Node *root;

    void del();
    void del(Node *);

    Node *put(Node *, const Key &, const Value &);
    void traverseInorder(Node *);

    int size(Node *);
    Node *remove(const Key &, Node *);
    Node *deleteMin(Node *);
    Node *min(Node *) const;

    Node *create(std::vector<std::pair<Key, Value>> vals, int start, int end);

    void printHelper(Node *node, int spaces = 0);

public:
    class Iterator;

    BST();
    // sorted array!
    BST(const std::vector<std::pair<Key, Value>> &);
    void prettyPrint();
    bool contains(const Key &) const;
    Iterator get(const Key &) const;
    void put(const Key &, const Value &);
    void remove(const Key &);
    void remove(Iterator &iter);
    void traverseInorder();
    ~BST();

    // iterator
    Iterator begin() const;
    Iterator end() const;
};

#endif