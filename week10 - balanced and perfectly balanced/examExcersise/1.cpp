#include <cstring>
#include <exception>
#include <cassert>

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;
};

bool read(const Node<char> *tree, const char *word, int len)
{
    if (len-- == 0)
    {
        return true;
    }

    if (tree and tree->data == *word++)
    {
        return read(tree->left, word, len) or read(tree->right, word, len);
    }

    return false;
}

bool readWord(const Node<char> *tree, const char *word)
{
    int size = strlen(word);
    if (size < 4)
    {
        throw std::exception();
    }

    Node<char> *left = tree->left, *right = tree->right;
    for (size_t i = 2; i < size - 1; i++)
    {
        if (word[i] == right->data)
        {
            return read(tree->left, word, i) and read(tree->right, word + i, size - i);
        }
    }
    return false;
}

int main()
{
    Node<char> c{'c'};
    Node<char> e{'e'};
    Node<char> h{'h'};
    Node<char> a{'a'};
    Node<char> d{'d', &c, &e};
    Node<char> i{'i', &h};
    Node<char> b{'b', &a, &d};
    Node<char> g{'g', &i};
    Node<char> f{'f', &b, &g};
    assert(readWord(&f, "bdcgi") == true);
    assert(readWord(&f, "bdgi") == true);
    assert(readWord(&f, "bcdgi") == false);
    assert(readWord(&f, "bdgh") == false);
}