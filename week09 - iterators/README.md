# FAQ

## Итератори

### Какво е итератор?

- По определение итератор е шаблон за дизайн (behavioural design pattern) от групата "поведенчески". Целта му е да предостави последователен достъп до елементите на дадена структура данни без да ни интересува вътрешното ѝ представяне.
- Може да се реализира по няколко начина, най-често и като най-добър подход се приема дефинирането на нов клас итератор за дадената структура.
- Операциите, които трябва да поддържа един итератор са: оператор `++`, дереференциране `*`, сравнение с `==`
- Еквивалент на тези операции са `next`, `hasNext` и дереференциране `*`.
- Всяка структура, която поддържа тези операции технически може да се използва за итератор.

### The range-based for loop

Работи използвайки `begin()` и `end()` функциите. Ако за даден клас Х имаме дефинирани функциите `begin(X&)` и `end(X&)` `the range-based for loop` ще работи правилно. По подразбиране ще се използват `std::begin()` и `std::end()`.

Пример:

```c++
#include <iostream>

namespace Y
{
    class X
    {
    public:
        char data[14] = "This is text";
    };

    char *begin(X &obj)
    {
        return obj.data;
    }

    char *end(X &obj)
    {
        return obj.data + 10;
    }
}

int main()
{
    Y::X x;
    for (auto const &a : x)
    {
        std::cout << a;
    }
}
```

Какво става, когато нямаме написани `begin()` и `end()` функциии? `std::begin()` ще извика `begin` метода на класа, аналогично за end.

```c++
#include <iostream>

namespace Y
{
    class X
    {
        char data[14] = "This is text";

    public:
        char *begin()
        {
            return data;
        }

        char *end()
        {
            return data + 10;
        }
    };
}

int main()
{
    Y::X x;
    for (auto const &a : x)
    {
        std::cout << a;
    }
}
```

### Как да си представяме въпросния range-based for loop

```
for(<Type> <Var> : <Obj>) {
    <CODE>
}
```

Това е просто съкратен запис за

```c++
{
    using std::begin;
    using std::end;

    auto __end = end(<Obj>);

    for(auto __loop = begin(<Obj>); __loop != __end; __loop++) {
        <Type> <Var> = *__loop;
        <CODE>
    }
}
```

### Имплементация на итератори

В c++ има пет вида итератори, имплементацията им се базира на т.нар. "Iterator Concept". Тъй като разглеждаме вектор в този пример ще се спрем на "Random Access Iterator Concept".

Документация: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

Забелязваме, че трябва не само да имаме имплементирани конкретни методи, ами и конкретни типове.

### Типове:

- value_type: полученият тип, когато итераторът се дереференцира
- difference_type: полученият тип, когато извадим два итератора
- pointer: указател към value_type
- reference: тип, който може да се използва като референция към стоност от тип value_type

Което ни дава следното:

```c++
template<typename T>
class Vector
{
    class Iterator
    {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference  = T&;
    };
    ....
}
```

### Изисквания за итератор:

Основните са `Default Constructible`, `Copy Constructible`, `Copy Assignable`, `Destructible`, `Equality Comparable`, `objects returned via de-referencing need to be mutable`

```c++
class Iterator
{
public:
    using value_type = T;
    using pointer    = T*;
    using reference  = T&;
    using difference_type = std::ptrdiff_t;

    Iterator():                    v(nullptr), i(0) {}
    Iterator(Vector<T>* v, int i): v(v),       i(i) {}
    // Default Copy/Move Are Fine.
    // Default Destructor fine.

    reference       operator*()             {return (*v)[i];}
    const reference operator*()       const {return (*v)[i];}
    pointer         operator->()            {return &((*v)[i]);}
    const pointer   operator->()      const {return &((*v)[i]);}
    reference       operator[](int m)       {return (*v)[i + m];}
    const reference operator[](int m) const {return (*v)[i + m];}


    Iterator& operator++()       {++i;return *this;}
    Iterator& operator--()       {--i;return *this;}
    Iterator  operator++(int)    {Iterator r(*this);++i;return r;}
    Iterator  operator--(int)    {Iterator r(*this);--i;return r;}

    Iterator& operator+=(int n)  {i += n;return *this;}
    Iterator& operator-=(int n)  {i -= n;return *this;}

    Iterator operator+(int n)   const {Iterator r(*this);return r += n;}
    Iterator operator-(int n)   const {Iterator r(*this);return r -= n;}

    difference_type operator-(Iterator const& r) const {return i - r.i;}

    // Note: comparing iterator from different containers
    //       is undefined behavior so we don't need to check
    //       if they are the same container.
    bool operator<(Iterator const& r)  const {return i <  r.i;}
    bool operator<=(Iterator const& r) const {return i <= r.i;}
    bool operator>(Iterator const& r)  const {return i >  r.i;}
    bool operator>=(Iterator const& r) const {return i >= r.i;}
    bool operator!=(const Iterator &r) const {return i != r.i;}
    bool operator==(const Iterator &r) const {return i == r.i;}

private:
    Vector<T>* v;
    int        i;
};
```

# Задачи за дървета

## Задача 1

### Invert Binary Tree

По даден корен на двоично дърво, обърнете дървото и върнете корена.

**Example 1:**

![](https://assets.leetcode.com/uploads/2021/03/14/invert1-tree.jpg)

```

Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

```

**Example 2:**

![](https://assets.leetcode.com/uploads/2021/03/14/invert2-tree.jpg)

```c++
Input: root = [2,1,3]
Output: [2,3,1]
```

**Example 3:**

```c++
Input: root = []
Output: []
```

**Constraints:**

The number of nodes in the tree is in the range [0, 100].

- -100 <= Node.val <= 100

## Задача 2

Допълнете класът BST с итератор.

За целта имплемнтирайте методите

- `begin()` връща итератор към началото на дървото
- `end()` връща итератор към края на дървото

Променете методът `get` така че да връща итератор.

# Задачи от минали години

## Задача 1

Двоично наредено дърво представяме чрез следната структура:

```c++
struct Node {
    int key;          // ключ
    Node* left;      // ляво поддърво
    Node* right;     // дясно поддървo
    Node* parent;    // баща
    int bFactor;     // баланс фактор
};
```

Функциите `Node* rotateLeft(Node* root)` и `Node* rotateRight(Node* root)` правят лява и дясна
ротация съответно около root на дървото с корен root и връщат корена на ротираното дърво.
Напишете функция `void balanceOnDelete(Node*& current, Node* previous)` както и функция функция `void balanceOnInsert(Node*& current, Node* previous)`, която:

- преизчислява баланс факторите на всички върхове от current до корена на дървото след като в дървото е
  било направено изтриване на непряк наследник на current. previous е наследникът на current по пътя към
  изтрития елемент.
- ако след преизчисляването, баланс факторът в някой връх стане -2 или 2, то с подходящи ротации коригира
  баланс фактора в граници -1 и 1, така че дървото да остане наредено.

## Задача 2

Даден е вектор v от цели числа. Казваме, че двоичното
дърво с положителни числа по върховете t представя v при следните
условия:

- v е празният вектор и t е празното дърво; или
- ако v = v[0],…,v[k-1], a m = ⌊k / 2⌋ (долна цяла част), то коренът
  на t съдържа числото v[m], лявото поддърво на t представя вектора
  v[0],…,v[m-1], а дясното поддърво на t представя вектора
  v[m+1],…,v[k-1].

Забележка: ако k = 2, то десния подвектор считаме за празен.

- Да се реализира функция, която построява дърво, представящо
  вектора v, и връща указател към корена му.

Упътване: Ако v е вектор, то с помощта на следния конструктор
`std::vector<unsigned> L(v.begin(), v.begin() + count)` ще получите
първите `count` елемента от v,
а с `std::vector<unsigned> R (v.begin() + start, v.end())`, ще
получите суфикса на v, започващ от елемента с индекс start.
Пример:

```
std::vector<unsigned> v{1, 2, 3, 4, 5, 6},
                      L(v.begin(), v.begin() + 3),
                      R(v.begin() + 4, v.end());
```

Тогава L е векторът 1, 2, 3, а R е векторът 5, 6.

- Да се реализира функция, която връща вектор, съставен от възлите
  по път в дървото от корен до листо, в който сумата на елементите е
  максимална.

## Задача 3

Даден е символен низ s. Казваме, че двоичното дърво със
символи по върховете t представя s при следните условия:

- s е празният низ и t е празното дърво; или
- ако s = s[0]…s[k-1], a m = ⌊k / 2⌋ (долна цяла част), то коренът
  на t съдържа символа s[m], лявото поддърво на t представя низа
  s[0]…s[m-1], а дясното поддърво на t представя низа s[m+1]…s[k-1].
  Забележка: ако k = 2, то десния низ считаме за празен.

- Да се реализира функция, която построява дърво, представящо низа
  s, и връща указател към корена му.

Упътване: Можете да ползвате метода `std::string::substr(pos, count)`,
който връща подниз, започващ със символа с индекс pos и с count на
брой елемента. Ако пропуснете параметъра count, ще получавите суфикс
на дадения низ от позиция pos до края на низа.

Пример:

```
std::string("abcde").substr(1, 3) → "bcd",
std::string("abcde").substr(3) → "de".
```

- Да се реализира функция, която връща низ, съставен от възлите по
  път в дървото от корен до листо, в който брой на срещанията на
  символа c е максимален.
