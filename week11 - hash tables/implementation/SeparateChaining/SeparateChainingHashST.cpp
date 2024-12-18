#include <vector>
#include <functional>
#include <list>
#include <iostream>

template <typename Key, typename Value>
class SeparateChainingHashST
{
private:
    static const int INIT_CAPACITY = 4;

    int n;                                            // number of key-value pairs
    int m;                                            // hash table size
    std::vector<std::list<std::pair<Key, Value>>> st; // array of linked-list symbol tables

    // TODO: implement SequentialSearchST
    Value getFromBucketByKey(const std::list<std::pair<Key, Value>> &l, Key key)
    {
        for (auto &&i : l)
        {
            if (i.first == key)
            {
                return i.second;
            }
        }
        throw std::exception();
    }

    bool contains(const std::list<std::pair<Key, Value>> &l, Key key)
    {
        try
        {
            getFromBucketByKey(l, key);
            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }

    void remove(std::list<std::pair<Key, Value>> &l, Key key)
    {
        for (auto &&it = l.begin(); it != l.end(); it++)
        {
            if ((*it).first == key)
            {
                l.erase(it);
                return;
            }
        }
    }

    void put(std::list<std::pair<Key, Value>> &l, Key key, Value value)
    {
        for (auto &&it = l.begin(); it != l.end(); it++)
        {
            if ((*it).first == key)
            {
                (*it).second = value;
                return;
            }
        }
        l.push_back({key, value});
    }

public:
    SeparateChainingHashST(int m) : m(m), st(std::vector<std::list<std::pair<Key, Value>>>(m))
    {
    }

    SeparateChainingHashST() : SeparateChainingHashST(INIT_CAPACITY)
    {
    }

    void resize(int chains)
    {
        SeparateChainingHashST<Key, Value> temp;
        for (int i = 0; i < m; i++)
        {
            for (auto item : st[i])
            {
                temp.put(item.first, item.second);
            }
        }
        m = temp.m;
        n = temp.n;
        st = temp.st;
    }

    int hash(Key key)
    {
        int h = std::hash<Key>{}(key);
        h ^= (h >> 20) ^ (h >> 12) ^ (h >> 7) ^ (h >> 4);
        return h & (m - 1);
    }

    int size()
    {
        return n;
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    bool contains(Key key)
    {
        try
        {
            get(key);
            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }

    // TODO: implement iterators
    Value get(const Key &key)
    {
        int i = hash(key);
        return getFromBucketByKey(st[i], key);
    }

    void put(const Key &key, const Value &val)
    {
        // double table size if average length of list >= 10
        if (n >= 10 * m)
        {
            resize(2 * m);
        }

        int i = hash(key);
        if (!contains(st[i], key))
        {
            n++;
        }
        put(st[i], key, val);
    }

    void remove(const Key &key)
    {
        int i = hash(key);
        if (contains(st[i], key))
        {
            n--;
        }
        remove(st[i], key);

        // halve table size if average length of list <= 2
        if (m > INIT_CAPACITY && n <= 2 * m)
        {
            resize(m / 2);
        }
    }

    std::vector<Key> keys()
    {
        std::vector<Key> v;
        for (int i = 0; i < m; i++)
        {
            for (auto item : st[i])
            {
                v.push_back(item.first);
            }
        }
        return v;
    }
};

int main()
{
    SeparateChainingHashST<std::string, int> st;
    st.put("Ivan", 24);
    std::cout << std::boolalpha << st.contains("Ivan") << '\n'
              << st.contains("Petar") << '\n'
              << st.get("Ivan") << '\n';
    st.put("Petar", 30);
    for (auto &&i : st.keys())
    {
        std::cout << i << ' ';
    }
    st.remove("Petar");
    std::cout << '\n';
    for (auto &&i : st.keys())
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    // collision
    st.put("Ivan", 24);
    st.put("Ivan1", 24);
    st.put("Ivan2", 24);
    st.put("Ivan3", 24);
    st.put("Ivan4", 24);
    for (auto &&i : st.keys())
    {
        std::cout << i << ' ';
    }
}