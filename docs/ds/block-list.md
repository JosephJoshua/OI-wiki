author: HeRaNO, konnyakuxzy, littlefrog

![./images/kuaizhuanglianbiao.png](./images/kuaizhuanglianbiao.png "./images/kuaizhuanglianbiao.png")

A block list looks roughly like this...

It is easy to see that a block list is just a linked list where each node points to an array.
We split the original array of length n into $\sqrt{n}$ nodes, and the array of each node has size $\sqrt{n}$.
So we define the struct as shown in the code below.
Here `sqn` means `sqrt(n)`, that is, $\sqrt{n}$, and `pb` means `push_back`, which appends an element to this `node`.

???+ note "Implementation"
    ```cpp
    struct node {
      node* nxt;
      int size;
      char d[(sqn << 1) + 5];
    
      node() { size = 0, nxt = NULL, memset(d, 0, sizeof(d)); }
    
      void pb(char c) { d[size++] = c; }
    };
    ```

A block list should support at least: split, insert and find.
What is a split? A split breaks one `node` into two smaller `node`s, so that the size of every `node` stays close to $\sqrt{n}$ (otherwise it may degrade into an ordinary array). We split a `node` when its size exceeds $2\times \sqrt{n}$.

How do we split? First create a new node, then `copy` the last $\sqrt{n}$ values of the node being split into the new node. Then remove those last $\sqrt{n}$ values from the node being split (`size--`). Finally, insert the new node right after the node being split.

Every block list operation takes $\sqrt{n}$ time.

One more thing.
As elements are inserted (or deleted), $n$ changes, and so does $\sqrt{n}$. Then the block size changes too. Do we really have to keep updating the block size?

Not really. Just set $\sqrt{n}$ to a fixed value. For example, if the problem's limit is $10^6$, set $\sqrt{n}$ to a constant $10^3$ and never change it.

```cpp
list<vector<char>> orz_list;
```

## `rope` in libstdc++

### Introduction

The `rope` in libstdc++ also serves as a block list. It is implemented with a persistent balanced tree and supports random access, insertion and deletion.

Since `rope` is not really implemented as a block list, its time complexity is not the same as a block list's. It matches the complexity of a persistent balanced tree instead (that is, $O(\log n)$).

You can include it like this:

```cpp
#include <ext/rope>
using namespace __gnu_cxx;
```

???+ warning "About library functions starting with double underscores"
    In OI, it used to be unclear whether library functions starting with double underscores could be used. In 2021, CCF published the [Supplementary Notes on Programming Language Restrictions in NOI Series Contests](https://www.noi.cn/xw/2021-09-01/735729.shtml), which says "library functions or macros starting with an underscore are allowed, except for those that perform explicitly prohibited operations". So `rope` can currently be used in OI as normal.

### Basic operations

|          Operation         |                    Effect                    |
| :------------------------: | :------------------------------------------: |
|       `rope<int> a`        | Initialize a `rope` (much like `vector` and other containers) |
|      `a.push_back(x)`      |       Append element `x` to the end of `a`       |
|     `a.insert(pos, x)`     |   Insert element `x` at position `pos` of `a`   |
|     `a.erase(pos, x)`      |  Delete `x` elements starting at position `pos` of `a`  |
|    `a.at(x)` or `a[x]`     |       Access the `x`-th element of `a`       |
| `a.length()` or `a.size()` |           Get the size of `a`          |

## Example problem

[POJ2887 Big String](http://poj.org/problem?id=2887)

Solution:
A very simple template problem. The code is below:

```cpp
--8<-- "docs/ds/code/block-list/block-list_1.cpp"
```
