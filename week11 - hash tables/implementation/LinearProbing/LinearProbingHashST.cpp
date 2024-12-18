#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <functional>

template <typename Key, typename Value>
class LinearProbingHashST
{
private:
    struct Pair
    {
        Key key;
        Value value;

        bool empty;

        Pair() : empty(true)
        {
        }
        Pair(Key key, const Value &value, bool empty = true) : key(key), value(value), empty(empty)
        {
        }
    };

    // must be a power of 2
    static const int INIT_CAPACITY = 4;
    int n; // number of key-value pairs in the symbol table
    int m; // size of linear probing table
    std::vector<Pair> values;

public:
    LinearProbingHashST(int capacity) : m(capacity), n(0), values(std::vector<Pair>(capacity)) {}

    LinearProbingHashST() : LinearProbingHashST(INIT_CAPACITY)
    {
    }

    int size()
    {
        return n;
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    bool contains(const Key &key)
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

private:
    void resize(int capacity)
    {
        LinearProbingHashST<Key, Value> temp(capacity);
        for (int i = 0; i < m; i++)
        {
            if (!values[i].empty)
            {
                temp.put(values[i].key, values[i].value);
            }
        }
        values = temp.values;
        m = temp.m;
    }

    int hash(Key key)
    {
        int h = std::hash<Key>{}(key);
        h ^= (h >> 20) ^ (h >> 12) ^ (h >> 7) ^ (h >> 4);
        return h & (m - 1);
    }

public:
    void put(const Key &key, const Value &val)
    {
        // double table size if 50% full
        if (n >= m / 2)
        {
            resize(2 * m);
        }

        int i;
        for (i = hash(key); !values[i].empty; i = (i + 1) % m)
        {
            if (values[i].key == key)
            {
                values[i].value = val;
                values[i].empty = false;
                return;
            }
        }
        values[i].key = key;
        values[i].value = val;
        values[i].empty = false;
        n++;
    }

    const Value &get(const Key &key)
    {
        for (int i = hash(key); !values[i].empty; i = (i + 1) % m)
        {
            if (values[i].key == key)
            {
                return values[i].value;
            }
        }
        throw std::runtime_error("No such element.");
    }

    void remove(const Key &key)
    {
        if (!contains(key))
        {
            return;
        }

        int i = hash(key);
        while (key != values[i].key)
        {
            i = (i + 1) % m;
        }

        values[i].empty = true;

        i = (i + 1) % m;
        while (!values[i].empty)
        {
            Key keyToRehash = values[i].key;
            Value valToRehash = values[i].value;
            values[i].empty = true;
            n--;
            put(keyToRehash, valToRehash);
            i = (i + 1) % m;
        }

        n--;

        // halves size of array if it's 12.5% full or less
        if (n > 0 && n <= m / 8)
        {
            resize(m / 2);
        }
    }

    std::vector<Key> keys()
    {
        std::vector<Key> v;
        for (int i = 0; i < m; i++)
        {
            if (!values[i].empty)
            {
                v.push_back(values[i].key);
            }
        }
        return v;
    }
};

int main()
{
    LinearProbingHashST<std::string, int> st;
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
    // collision
    st.put("Ivan", 24);
    st.put("Ivan1", 24);
    st.put("Ivan2", 24);
    st.put("Ivan3", 24);
    st.put("Ivan4", 24);
}