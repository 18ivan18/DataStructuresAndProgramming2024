#include <iostream>
#include <vector>

class Vector
{
    class Iterator
    {
    public:
        Iterator() : v(nullptr), i(0) {}
        Iterator(Vector *v, int i) : v(v), i(i) {}
        Iterator &operator++()
        {
            ++i;
            return *this;
        }

        bool operator!=(const Iterator &rhs) const
        {
            return i != rhs.i;
        }

        double &operator*()
        {
            return (*v)[i];
        }

        const double &operator*() const
        {
            return (*v)[i];
        }

    private:
        Vector *v;
        int i;
    };

public:
    // using iterator = double *;
    // iterator begin() { return data; }
    // iterator end() { return data + sz; }

    Iterator begin()
    {
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, sz);
    }

    Vector(const std::vector<double> &list) : data(nullptr), sz(0)
    {
        sz = list.size();
        data = new double[sz];
        for (int i = 0; i < list.size(); i++)
        {
            data[i] = list[i];
        }
    }

    ~Vector()
    {
        delete[] data;
    }

    int size() const
    {
        return sz;
    }

    double &operator[](int n)
    {
        if (n < 0 || n >= sz)
        {
            throw std::out_of_range("Vector::operator[]");
        }
        return data[n];
    }

private:
    double *data;
    int sz;
};

int main()
{
    Vector v({1.1, 1.1, 2.2, 2.2});

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << '\n';
    }

    for (auto i = v.begin(); i != v.end(); ++i)
    {
        std::cout << *i << '\n';
    }

    for (const auto &x : v)
    {
        std::cout << x << '\n';
    }
}
