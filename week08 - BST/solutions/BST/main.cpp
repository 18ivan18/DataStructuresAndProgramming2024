#include <iostream>
#include "BST.cpp"
#include <string>

#define TYPE char

void test1()
{
    BST<TYPE, int> bst;
    TYPE word;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> word;
        bst.put(word, i);
    }
    std::cin >> word;
    BST<char, int>::Iterator result = bst.get(word);
    if (result == bst.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << (*result).second << std::endl;
    }
    bst.traverseInorder();
    bst.remove('s');
    bst.traverseInorder();
}

int main()
{
    std::vector<std::pair<int, std::string>> v = {{5, "Burgas"}, {10, "Plovdiv"}, {15, "Silistra"}, {20, "Pleven"}, {25, "Stara Zagora"}};
    BST<int, std::string> bst(v);
    bst.prettyPrint();
    // for (auto it = bst.begin(); it != bst.end(); it++)
    // {
    //     std::cout << (*it).first << " " << (*it).second << "\n";
    // }

    for (auto &&i : bst)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

    BST<int, std::string>::Iterator result = bst.get(10);
    if (result == bst.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << (*result).second << std::endl;
    }
    bst.remove(15);
    result++;
    std::cout << "Iterator is now working with mutations " << (*result).first << ' ' << (*result).second << std::endl;
}