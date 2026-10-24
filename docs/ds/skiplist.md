A skip list is a search data structure invented by William Pugh. It supports fast search, insertion and deletion.

A skip list has expected space complexity $O(n)$, and its search, insertion and deletion all take $O(\log n)$ expected time.

## Basic idea

As the name suggests, a skip list is a data structure similar to a linked list. More precisely, a skip list is an improved sorted linked list.

For convenience, all sorted linked lists below are sorted in **ascending** order.

Searching a sorted linked list means comparing node by node from the head until the current node's value is greater than or equal to the target value. Clearly, this takes $O(n)$ time.

A skip list adds the idea of **levels** on top of a sorted linked list. Each level of a skip list is a sorted linked list, and in particular the bottom level is the original sorted linked list. Each node on level $i$ also appears on level $i+1$ with probability $p$, where $p$ is a constant.

In a skip list with $n$ nodes, let level $L(n)$ be the level that is expected to contain $\frac{1}{p}$ elements. It is easy to see that $L(n) = \log_{\frac{1}{p}}n$.

To search a skip list, start at level $L(n)$ and compare horizontally node by node until the next node is greater than or equal to the target, then move down one level. Repeat until you reach the first level and cannot go any further. At that point, if the next node is the target, the search succeeds; otherwise the element does not exist. This way the search skips some unnecessary comparisons, so searching a skip list is faster than searching a sorted linked list. One can prove that a search in a skip list takes $O(\log n)$ time on average.

## Complexity proofs

### Space complexity

For a single node, the probability that its highest level is $i$ is $p^{i-1}(1 - p)$. So the expected number of levels of a node is $\sum_{i\ge 1} ip^{i - 1}(1-p) = \frac{1}{1 - p}$, and since $p$ is a constant, the skip list has **expected space complexity** $O(n)$.

In the worst case, every level equals the original sorted linked list, so the skip list has **worst-case space complexity** $O(n \log n)$.

### Time complexity

Analyze the search path backward. The process splits into two parts: climbing from the bottom level up to level $L(n)$, and everything after that. In the analysis, assume that a node's details are unknown until it is visited.

Suppose we are at a node $x$ on level $i$. We do not know the highest level of $x$ or of the nodes to its left; we only know that the highest level of $x$ is at least $i$. If the highest level of $x$ is greater than $i$, the next step goes up, which happens with probability $p$; if the highest level of $x$ equals $i$, the next step goes left, which happens with probability $1-p$.

Let $C(i)$ be the expected cost of climbing $i$ levels in an infinitely long skip list. Then:

$$
\begin{aligned}
C(0) & = 0 \\
C(i) & = (1-p)(1+C(i)) + p(1+C(i-1))
\end{aligned}
$$

Solving gives $C(i)=\frac{i}{p}$.

So in a skip list of length $n$, the expected number of steps to climb from the bottom level to level $L(n)$ is at most $\frac{L(n) - 1}{p}$.

Now we only need to analyze how many more steps are taken after reaching level $L(n)$. Once at level $L(n)$, the number of steps to the left cannot exceed the total number of nodes on level $L(n)$ and above, whose expected value is $\frac{1}{p}$. So the expected number of steps to the left after reaching level $L(n)$ is at most $\frac{1}{p}$. Similarly, the expected number of steps up after reaching level $L(n)$ is at most $\frac{1}{p}$.

So the expected number of steps in a skip list search is $\frac{L(n) - 1}{p} + \frac{2}{p}$, and since $L(n)=\log_{\frac{1}{p}}n$, a skip list search has **expected time complexity** $O(\log n)$.

In the worst case, every level equals the original sorted linked list, and the search is the same as searching the top-level sorted linked list, so a skip list search has **worst-case time complexity** $O(n)$.

Insertion and deletion just run a search, record the nodes that need to change on the way, and finally make the changes. Clearly at most one node per level needs to change, and since a skip list has $\log_{\frac{1}{p}}n$ levels in expectation, insertion and deletion also have **expected time complexity** $O(\log n)$.

## Implementation

### Getting a node's highest level

Simulate adding one level at a time with probability $p$, and finally take the minimum with the upper limit.

```cpp
int randomLevel() {
  int lv = 1;
  // MAXL = 32, S = 0xFFFF, PS = S * P, P = 1 / 4
  while ((rand() & S) < PS) ++lv;
  return min(MAXL, lv);
}
```

### Search

Check whether the skip list has a node with key `key`. In the implementation, you can use two sentinel nodes to reduce boundary cases.

```cpp
V& find(const K& key) {
  SkipListNode<K, V>* p = head;

  // Find the last node on this level whose key is less than key, then go down a level
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
  }
  // It is now less than key, so take one more step forward
  p = p->forward[0];

  // Found the node
  if (p->key == key) return p->value;

  // The node does not exist; return INVALID
  return tail->value;
}
```

### Insertion

Insert the node `(key, value)`. Insertion first runs a search, recording on the way after which nodes the new node should be inserted, and then inserts it. On each level, the last node whose key is less than `key` is the node to be modified.

```cpp
void insert(const K &key, const V &value) {
  // Records the nodes that need to be modified
  SkipListNode<K, V> *update[MAXL + 1];

  SkipListNode<K, V> *p = head;
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
    // The node to modify on level i is p
    update[i] = p;
  }
  p = p->forward[0];

  // If it already exists, update it
  if (p->key == key) {
    p->value = value;
    return;
  }

  // Get the highest level of the new node
  int lv = randomLevel();
  if (lv > level) {
    lv = ++level;
    update[lv] = head;
  }

  // Create the new node
  SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
  // Insert the new node on levels 0 to lv
  for (int i = lv; i >= 0; --i) {
    p = update[i];
    newNode->forward[i] = p->forward[i];
    p->forward[i] = newNode;
  }

  ++length;
}
```

### Deletion

Delete the node with key `key`. Deletion first runs a search, recording on the way after which nodes the node to delete lies, and then deletes it. On each level, the last node whose key is less than `key` is the node to be modified.

```cpp
bool erase(const K &key) {
  // Records the nodes that need to be modified
  SkipListNode<K, V> *update[MAXL + 1];

  SkipListNode<K, V> *p = head;
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
    // The node to modify on level i is p
    update[i] = p;
  }
  p = p->forward[0];

  // The node does not exist
  if (p->key != key) return false;

  // Delete starting from the bottom level
  for (int i = 0; i <= level; ++i) {
    // If p is not on this level, the deletion is done
    if (update[i]->forward[i] != p) {
      break;
    }
    // Unlink p
    update[i]->forward[i] = p->forward[i];
  }

  // Free the memory
  delete p;

  // Deleting a node may reduce the highest level
  while (level > 0 && head->forward[level] == tail) --level;

  // Skip list length
  --length;
  return true;
}
```

### Full code

The code below is a map implemented with a skip list. It has not been properly tested and is for reference only.

??? note "Reference code"
    ```cpp
    #include <cassert>
    #include <climits>
    #include <ctime>
    #include <iostream>
    #include <map>
    using namespace std;
    
    template <typename K, typename V>
    struct SkipListNode {
      int level;
      K key;
      V value;
      SkipListNode **forward;
    
      SkipListNode() {}
    
      SkipListNode(K k, V v, int l, SkipListNode *nxt = NULL) {
        key = k;
        value = v;
        level = l;
        forward = new SkipListNode *[l + 1];
        for (int i = 0; i <= l; ++i) forward[i] = nxt;
      }
    
      ~SkipListNode() {
        if (forward != NULL) delete[] forward;
      }
    };
    
    template <typename K, typename V>
    struct SkipList {
      static constexpr int MAXL = 32;
      static constexpr int P = 4;
      static constexpr int S = 0xFFFF;
      static constexpr int PS = S / P;
      static constexpr int INVALID = INT_MAX;
    
      SkipListNode<K, V> *head, *tail;
      int length;
      int level;
    
      SkipList() {
        srand(time(nullptr));
    
        level = length = 0;
        tail = new SkipListNode<K, V>(INVALID, 0, 0);
        head = new SkipListNode<K, V>(INVALID, 0, MAXL, tail);
      }
    
      ~SkipList() {
        delete head;
        delete tail;
      }
    
      int randomLevel() {
        int lv = 1;
        while ((rand() & S) < PS) ++lv;
        return MAXL > lv ? lv : MAXL;
      }
    
      void insert(const K &key, const V &value) {
        SkipListNode<K, V> *update[MAXL + 1];
    
        SkipListNode<K, V> *p = head;
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
          update[i] = p;
        }
        p = p->forward[0];
    
        if (p->key == key) {
          p->value = value;
          return;
        }
    
        int lv = randomLevel();
        if (lv > level) {
          lv = ++level;
          update[lv] = head;
        }
    
        SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
        for (int i = lv; i >= 0; --i) {
          p = update[i];
          newNode->forward[i] = p->forward[i];
          p->forward[i] = newNode;
        }
    
        ++length;
      }
    
      bool erase(const K &key) {
        SkipListNode<K, V> *update[MAXL + 1];
        SkipListNode<K, V> *p = head;
    
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
          update[i] = p;
        }
        p = p->forward[0];
    
        if (p->key != key) return false;
    
        for (int i = 0; i <= level; ++i) {
          if (update[i]->forward[i] != p) {
            break;
          }
          update[i]->forward[i] = p->forward[i];
        }
    
        delete p;
    
        while (level > 0 && head->forward[level] == tail) --level;
        --length;
        return true;
      }
    
      V &operator[](const K &key) {
        V v = find(key);
        if (v == tail->value) insert(key, 0);
        return find(key);
      }
    
      V &find(const K &key) {
        SkipListNode<K, V> *p = head;
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
        }
        p = p->forward[0];
        if (p->key == key) return p->value;
        return tail->value;
      }
    
      bool count(const K &key) { return find(key) != tail->value; }
    };
    
    int main() {
      SkipList<int, int> L;
      map<int, int> M;
    
      clock_t s = clock();
    
      for (int i = 0; i < 1e5; ++i) {
        int key = rand(), value = rand();
        L[key] = value;
        M[key] = value;
      }
    
      for (int i = 0; i < 1e5; ++i) {
        int key = rand();
        if (i & 1) {
          L.erase(key);
          M.erase(key);
        } else {
          int r1 = L.count(key) ? L[key] : 0;
          int r2 = M.count(key) ? M[key] : 0;
          assert(r1 == r2);
        }
      }
    
      clock_t e = clock();
      cout << "Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << endl;
      // about 0.2s
    
      return 0;
    }
    ```

## Random access optimization for skip lists

Accessing the $k$-th node of a skip list is the same as accessing the $k$-th node of the original sorted linked list, which clearly takes $O(n)$ time. That is not good enough.

The random access optimization stores, for each forward pointer, the length of that pointer. Suppose $A$ and $B$ are nodes in the skip list, $A$ is the $a$-th node and $B$ is the $b$-th node $(a < b)$, and on some level the forward pointer of $A$ points to $B$. Then the length of that forward pointer is $b - a$.

To access the $k$-th node, start from the top level and walk horizontally along that level's list until the current node's position plus the length of its forward pointer on that level is at least $k$, then move down one level. Repeat until you reach the first level and cannot go any further. At that point, the current node is the $k$-th node of the skip list.

This way we can quickly access the $k$-th element of the skip list. One can prove that this takes $O(\log n)$ time.

## References

1.  [Skip Lists: A Probabilistic Alternative to Balanced Trees](https://15721.courses.cs.cmu.edu/spring2018/papers/08-oltpindexes1/pugh-skiplists-cacm1990.pdf)
2.  [Skip List](https://en.wikipedia.org/wiki/Skip_list)
3.  [A Skip List Cookbook](http://cglab.ca/~morin/teaching/5408/refs/p90b.pdf)
