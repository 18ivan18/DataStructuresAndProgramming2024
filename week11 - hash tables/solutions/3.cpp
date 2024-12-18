#include <unordered_map>
#include <vector>

std::unordered_map<char, int> mp;
bool isAlienSorted(std::vector<std::string> &words, std::string order)
{
    for (int i = 0; i < size(order); i++)
        mp[order[i]] = i; // mapping letter to its corresponding index in order
    for (int i = 0; i < size(words) - 1; i++)
        if (!checkOrder(words[i], words[i + 1]))
            return false;
    return true;
}
// checking if two words are lexicographically sorted
bool checkOrder(std::string &a, std::string &b)
{
    int i = -1;
    while (++i < size(a) && i < size(b))
        if (mp[a[i]] != mp[b[i]])
            return mp[a[i]] < mp[b[i]];
    return size(a) <= size(b);
}