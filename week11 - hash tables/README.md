# Хеш таблица (Hash table/Hash map)

## Въведение

Хеш таблицата е структура от данни, която се състои от наредени двойки **<ключ (key), стойност (value)>** или **само от ключове** (keys).  
При хеш таблицата имаме **хешираща функция**, която при подаден ключ генерира индекс **(хеш код/hash code)**, на който трябва да се запише съответната стойност (value). По принцип, този индекс е уникален. Може, обаче, да се случи генериране на един и същ хеш код за два различни ключа, което довежда до дублиране на индекси. Този проблем е познат като **„Колизия“ (“Collision”)**.

![alt_text](https://i.ibb.co/GtPr2ky/Hash.jpg)

## Хеш функции

Какво наричаме **"добра" хеш функция**? - функция, при която има **малка вероятност за колизия**.

- Функцията трябва да използва **всички данни от key**.
- За **"подобни" ключове**, функцията връща **"напълно различни" индекси**.
- **Равномерна функция** (Броят на колизиите на всеки индекс е относително еднакъв).
- **Бърза за изчислване**. :exclamation:

**"Перфектна" хеш функция - никога няма колизии!**  
В реалния свят, такава функция рядко е възможно да бъде създадена (възможните слотове обикновено са значително по- малко от възможните ключове).  
**_Например_**, ако множеството от ключовете са стрингове с дължина 20, съставени от буквите на английската азбука, то възможните стрингове са 26\^20, а възможните слотове - 4\*(10\^12). Следователно, по Дирихле, е невъзможно да нямаме колизия, ако хешираме повече от 4\*(10\^12) елемента.

## Хеш таблици

1. **Основни операции**

- insert(x)
- find(x)
- remove(x)

2. **Видове**

- С ключ и стойност (**map**)
- Само ключ (**set**)

3. **Предимства**

|        | Worst case complexity | Expected complexity |                    |
| ------ | --------------------- | ------------------- | ------------------ |
| insert | O(n)                  | O(1)                | :heavy_check_mark: |
| find   | O(n)                  | O(1)                | :heavy_check_mark: |
| remove | O(n)                  | O(1)                | :heavy_check_mark: |

4. **Недостатъци**

- няма наредба
- сложност на хеш-функцията
- операциите не винаги са константни
- преразход на памет
- неудобно обхождане

## Collision resolution strategies (CRS)

### Външно хеширане/Затворено адресиране (External Hashing/Closed addressing/Separate Chaining) - Данните са извън таблицата

Таблицата е масив от „кофи“ (buckets).  
Всяка кофа е отделен контейнер (най-често списък).  
**Преоразмеряване** на таблицата при запълване над 70% чрез прехеширане на всички елементи.

:question: Нарича се **_затворено адресиране_**, защото винаги x ∈ table[h(x)].

![alt_text](https://i.ibb.co/G0Sh7sj/Open-hashing.png)

:heavy_check_mark: Общ брой елементи, по- голям от размера на таблицата, е ок.  
:heavy_check_mark: Лесно намираме всички елементи с даден ключ.  
:heavy_check_mark: Изтриването е лесно.  
:x: Индиректен достъп до елементите.  
:x: Повече памет.

### Вътрешно хеширане/Отворено адресиране (Closed Hashing/Open addressing) - Данните са в таблицата

Таблицата съдържа всички елементи.  
За всяка клетка има допълнителни два флага – **empty** и **deleted**.

**Справяне с колизии**  
 • **Линейно пробване** - Стъпката S, която избираме, трябва да бъде взаимно проста с размера n на таблицата! **(S, n) = 1** :exclamation:  
 • **Квадратично пробване**  
 • **Двойно хеширане**

Други стратегии – **Ку-Ку хеширане**

**При вътрешното хеширане sizeof(table), n > броя елементи, cnt!** :exclamation:  
Препоръка: **n > 1,5\*cnt**.

![alt_text](https://i.ibb.co/F0YLZpF/Closed-hashing.png)

:heavy_check_mark: По- малко памет.  
:heavy_check_mark: Директен достъп по index.  
:x: По- трудно изтриване.  
:x: Неконсистентни позиции.

# Задачи

## Задача 1

### Two Sum

По даден масив от цели числа и цяло число `х`, да се намират дваете числа, чиято сумата е равна на `x`.

Можем да направим предположението, че всички елементи в масива са уникални и не можем да използваме един и същи елемент два пъти.

Върнете резултата като масив от две числа в произволен ред. Алгоритъмът трябва да работи в линейно време `О(n)`.

### Example 1:

```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Example 2:

```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

### Example 3:

```
Input: nums = [3,3], target = 6
Output: [0,1]
```

## Задача 2

По даден параграф текст и масив от символни низове от забранени думи да се намеи най-често срещаната дума, която не е забранена. Гарантирано е, че има поне една не-забранена дума.

Думите в един параграф не се влияят от малки и големи букви (case insensitive) и отговорът трябва да бъде изписан само с малки латински букви.

### Example 1:

```
Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
Output: "ball"
Explanation:
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph.
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"),
and that "hit" isn't the answer even though it occurs more because it is banned.
```

### Example 2:

```
Input: paragraph = "a.", banned = []
Output: "a"
```

### Constraints:

- 1 <= paragraph.length <= 1000
- paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
- 0 <= banned.length <= 100
- 1 <= banned[i].length <= 10
- banned[i] consists of only lowercase English letters.

## Задача 3

### Alien Dictionary

В езика на извънземните думите са съставени от малки латински букви, но подредени в друг ред. Редът на буквите в тяхната азбука е пермутация на латинската азбука.

По подадена последователност от извънземни думи и реда на азбуката, да се определи, дали са сортирани в лексикографски ред спрямо извънземния език.

### Example 1:

```
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
```

### Example 2:

```
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
```

### Example 3:

```
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
```

## Задача 4

### Contains Duplicate

По подаден масив от цели числа и цялото число `k` върнете true ако има два различни индекса i и j в масива, така че nums[i] == nums[j] и abs(i - j) <= k.

### Example 1:

```
Input: nums = [1,2,3,1], k = 3
Output: true
```

### Example 2:

```

Input: nums = [1,0,1,1], k = 1
Output: true
```

### Example 3:

```

Input: nums = [1,2,3,1,2,3], k = 2
Output: false
```

### Constraints:

- 1 <= nums.length <= 105
- -109 <= nums[i] <= 109
- 0 <= k <= 105
