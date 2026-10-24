## Introduction

![](images/hashtable.svg)

A hash table (also called a hash map) is a data structure that stores data as "key-value" pairs. Storing data as "key-value" pairs means that each key maps uniquely to some location in memory. Given just the key to look up, we can quickly find its value. You can think of a hash table as an advanced array whose indices can be very large integers, floating-point numbers, strings, or even structs.

## Hash functions

To map keys to locations in memory, we need to compute an index for each key, that is, decide where the data should go. The function that computes an index from a key is called a hash function. For example, if the key is a person's ID number, the hash function could be the last four digits of the number, or just as well the first four digits. The "last digits of a phone number" people often use in daily life is also a kind of hash function. In real applications, keys may be more complex things, such as floating-point numbers, strings or structs, and then we need to design a suitable hash function for the specific case. A hash function should be easy to compute and should spread the computed indices as evenly as possible.

Once we can compute an index for a key, we know where each key's value should go. Suppose we store data in an array a and the hash function is f; then the key-value pair `(key, value)` should be stored at `a[f(key)]`. Whatever the type and range of the key, `f(key)` is an integer within an acceptable range and can be used as an array index.

In OI, the most common case is integer keys. When the range of keys is small, we can use the key directly as the array index. But when the range is large, for example integer keys up to $10^9$, we need a hash table. Usually we take the key modulo a fairly large prime as the index, that is, we use $f(x)=x \bmod M$ as the hash function.

Another common case is string keys. Strings can't be used as array indices, and converting strings to numbers also avoids repeated string comparisons. So in OI, we usually don't use the string directly as the key. Instead, we compute the string's hash value and insert that hash value into the hash table as the key. For string hash values, we usually use the idea of number bases: think of the string as a number in base $127$. Then for each string $s$ of length $n$:

$x = s_0 \cdot 127^0 + s_1 \cdot 127^1 + s_2 \cdot 127^2 + \dots + s_n \cdot 127^n$

We can take the resulting $x$ modulo $2^{64}$ (that is, the maximum value of `unsigned long long`). Then the natural overflow of `unsigned long long` is equivalent to taking the modulus, which makes things more convenient.

This method is simple but not perfect. Test data can be constructed to make it collide (that is, two strings whose $x$ values are equal modulo $2^{64}$).  
We can use double hashing: pick two large primes $a,b$. We consider two strings equal only if their hash values are equal both modulo $a$ and modulo $b$. This greatly reduces the probability of hash collisions.

## Collisions

If the hash function gave a different index for every key, we would just put `(key, value)` at the corresponding index. But in practice, two different keys often get the same index from the hash function. Then we need some way to handle collisions. In OI, the most common method is separate chaining.

### Separate chaining

Separate chaining is also called open hashing.

Separate chaining keeps a linked list at each storage location. If multiple keys map to the same location, we just put them all into that location's linked list. To query, we scan the whole linked list at that location and compare each entry's key with the queried key. If the index range is $1\ldots M$ and the hash table holds $N$ entries, each insertion/query takes $O(\frac{N}{M})$ comparisons in expectation.

#### Implementation

=== "C++"
    ```cpp
    constexpr int SIZE = 1000000;
    constexpr int M = 999997;
    
    struct HashTable {
      struct Node {
        int next, value, key;
      } data[SIZE];
    
      int head[M], size;
    
      int f(int key) { return (key % M + M) % M; }
    
      int get(int key) {
        for (int p = head[f(key)]; p; p = data[p].next)
          if (data[p].key == key) return data[p].value;
        return -1;
      }
    
      int modify(int key, int value) {
        for (int p = head[f(key)]; p; p = data[p].next)
          if (data[p].key == key) return data[p].value = value;
      }
    
      int add(int key, int value) {
        if (get(key) != -1) return -1;
        data[++size] = Node{head[f(key)], value, key};
        head[f(key)] = size;
        return value;
      }
    };
    ```

=== "Python"
    ```python
    M = 999997
    SIZE = 1000000
    
    
    class Node:
        def __init__(self, next=None, value=None, key=None):
            self.next = next
            self.value = value
            self.key = key
    
    
    data = [Node() for _ in range(SIZE)]
    head = [0] * M
    size = 0
    
    
    def f(key):
        return key % M
    
    
    def get(key):
        p = head[f(key)]
        while p:
            if data[p].key == key:
                return data[p].value
            p = data[p].next
        return -1
    
    
    def modify(key, value):
        p = head[f(key)]
        while p:
            if data[p].key == key:
                data[p].value = value
                return data[p].value
            p = data[p].next
    
    
    def add(key, value):
        if get(key) != -1:
            return -1
        size = size + 1
        data[size] = Node(head[f(key)], value, key)
        head[f(key)] = size
        return value
    ```

Here is also a wrapped-up template that can be used like a map, and is fairly short

```cpp
struct hash_map {  // hash table template

  struct data {
    long long u;
    int v, nex;
  };  // forward-star (linked adjacency) structure

  data e[SZ << 1];  // SZ is a const int giving the size
  int h[SZ], cnt;

  int hash(long long u) { return (u % SZ + SZ) % SZ; }

  // We use (u % SZ + SZ) % SZ instead of u % SZ because
  // the % operator in C++ does not turn negative numbers into positive ones

  int& operator[](long long u) {
    int hu = hash(u);  // get the head pointer
    for (int i = h[hu]; i; i = e[i].nex)
      if (e[i].u == u) return e[i].v;
    return e[++cnt] = data{u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  }

  hash_map() {
    cnt = 0;
    memset(h, 0, sizeof(h));
  }
};
```

Here, the hash function is designed for the key type and returns a linked-list head pointer used for queries. In this template we write a hash table with key-value types `(long long, int)`, which returns -1 when querying a key that doesn't exist. The function `hash_map()` initializes it when it is defined.

### Closed hashing

Closed hashing stores all records directly in the hash table. If a collision happens, it keeps probing in some way.

For example, linear probing: if a collision happens at `d`, check `d + 1`, `d + 2`, ... in turn.

#### Implementation

```cpp
constexpr int N = 360007;  // N is the maximum number of elements that can be stored

class Hash {
 private:
  int keys[N];
  int values[N];

 public:
  Hash() { memset(values, 0, sizeof(values)); }

  int& operator[](int n) {
    // return a reference to the corresponding Hash[Key]
    // set it to a non-zero value; a value of 0 means the slot is empty
    int idx = (n % N + N) % N, cnt = 1;
    while (keys[idx] != n && values[idx] != 0) {
      idx = (idx + cnt * cnt) % N;
      cnt += 1;
    }
    keys[idx] = n;
    return values[idx];
  }
};
```

## Example problems

["JLOI2011" Unique Numbers](https://www.luogu.com.cn/problem/P4305)
