## Introduction

In competitive programming, some problems can be solved with binary search. But when such a problem has many queries and running a separate binary search for each query might cause TLE, we use parallel binary search (also called overall binary search). The main idea of parallel binary search is to solve many queries together. (So it is an offline algorithm.)

Problems that can be solved with parallel binary search must have the following properties[^ref1]:

1.  The answer to each query can be found by binary search.
2.  **The contributions of modifications to checking an answer are independent of each other**; modifications do not affect each other's effects.
3.  If a modification contributes to checking an answer, the contribution is a fixed value that does not depend on the checking criterion.
4.  Contributions are commutative, associative, and additive.
5.  The problem allows offline algorithms.

## Explanation

Let $[l,r]$ be the range of possible answer values, and $[L,R]$ be the domain of the answer. (That is, when finding answers we only consider operations and queries whose indices are in $[L,R]$, and the answers of these queries lie in $[l,r]$.)

-   First, store all operations in an array **in chronological order**, then start divide and conquer.
-   At each level of divide and conquer, use a data structure (commonly a Fenwick tree) to determine how each current query's answer compares with $mid$.
-   Based on that comparison (less than or equal to $mid$, or greater than $mid$), split the current sequence of operations into two parts, $q1$ and $q2$, and process each part recursively.
-   When $l=r$, the answer has been found; record it and return.

Note that during parallel binary search, if the current value range being processed is $[l,r]$, then the queries whose final answers are not in $[l,r]$ are handled at other times.

## How it works

???+ tip "Note"
    1.  For readability, the code here may not use the usual style of real contests.
    2.  If some code is hard to understand, first look at the explanations of the earlier problems. To save space, things already explained are not repeated.

Let's start with ordinary binary search:

### Global k-th smallest

???+ note "Problem 1"
    Find the $k$-th smallest number in a sequence.

??? note "Solution"
    Of course, you can just sort. What if we use binary search? We can use a data structure to record how many numbers fall in each value range, then guess with binary search and check the guess with the data structure.

???+ note "Problem 2"
    Answer many queries for the $k$-th smallest number in a sequence.

??? note "Solution"
    We could run a separate binary search for each query; but we can also binary search all the queries together.
    
    First, think about what binary search really is. Suppose we must guess a number in $[l,r]$, and after each guess we learn whether it was too large, too small, or exactly right. We could of course enumerate from $l$ to $r$, but binary search is better: guess that the answer is $m = \lfloor\frac{l + r}{2}\rfloor$, check whether $m$ is right, then adjust the bounds. Each query then costs $O(\log n)$, so with $q$ queries the time complexity is $O(q\log n)$.
    
    Back to our problem. For all current queries, we can guess that every answer is $mid$, then check each query in turn to see whether its answer should be less than or equal to $mid$ or greater than $mid$, and split the queries into two parts (not greater / greater). Then continue the binary search on each part. Note: if a query's answer is greater than $mid$, we must update its $k$ before moving it to the right side. That is, if the current sequence has $t$ numbers less than or equal to $mid$, then after the split the query actually asks for the $(k - t)$-th smallest number in the right range. When a part has $l = r$, the binary search on that part ends. By the same reasoning as for segment trees, each time we split the whole range $[1,n]$ where the answer may lie (assume values are already compressed) into several parts. This splitting happens $O(\log n)$ times, and each round of splitting processes the whole sequence of operations once. If processing the whole sequence and supporting the needed queries takes $O(T)$ time, then parallel binary search takes $O(T\log n)$ time.

??? note "Reference code"
    ```cpp
    struct Query {
      int id, k;  // the index of this query, the k of this query
    };
    
    int ans[N], a[N];  // ans[i] is the answer of query i, a is the original sequence
    int val[N], cnt[N];  // after compression, the values and their counts (assume already computed)
    
    // return how many numbers of the original sequence have values in [l,r]
    int check(int l, int r) {
      int res = 0;
      for (int i = l; i <= r; i++) {
        res += cnt[i];
      }
      return res;
    }
    
    // parallel binary search
    void solve(int l, int r, vector<Query> q) {
      int m = (l + r) / 2;
      if (l == r) {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = val[l];
        return;
      }
      vector<Query> q1, q2;
      int t = check(l, m);
      for (unsigned i = 0; i < q.size(); i++) {
        if (q[i].k <= t)
          q1.push_back(q[i]);
        else
          q[i].k -= t, q2.push_back(q[i]);
      }
      solve(l, m, q1), solve(m + 1, r, q2);
      return;
    }
    ```

### Range k-th smallest

???+ note "Problem 3"
    Answer many queries for the $k$-th smallest number in a range of a sequence.

??? note "Solution"
    Since the queries are on given ranges, binary searching the same way as before would make the `check` function far too slow. We still look at how each query relates to the middle value $m$ of the value range: if the query range contains $t$ numbers less than or equal to $m$ and the query asks for the $k$-th smallest, then when $k \leq t$ the answer is at most $m$; otherwise the answer is greater than $m$. (Watch out for boundary cases.) Here we need to count how many numbers in a range are at most a given value, which means point additions and range sums, so a Fenwick tree handles it quickly. For efficiency, we only count the numbers of the sequence whose values lie in the value range $[l,r]$. That is, before recursing further, we split not only the queries but also the numbers being processed, into two halves by value.

??? note "Reference code (key part)"
    ```cpp
    struct Num {
      int p, x;
    };  // the number at position p of the sequence has value x
    
    struct Query {
      int l, r, k, id;
    };  // a query with index id, asking for the k-th smallest number in [l,r]
    
    int ans[N];
    void add(int p, int x);  // Fenwick tree, add x at position p
    int query(int p);        // Fenwick tree, sum of [1,p]
    void clear();            // Fenwick tree, clear
    
    void solve(int l, int r, vector<Num> a, vector<Query> q)
    // a holds the numbers of the sequence whose values are in the value range [l,r]
    {
      int m = (l + r) / 2;
      if (l == r) {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
        return;
      }
      vector<Num> a1, a2;
      vector<Query> q1, q2;
      for (unsigned i = 0; i < a.size(); i++)
        if (a[i].x <= m)
          a1.push_back(a[i]), add(a[i].p, 1);
        else
          a2.push_back(a[i]);
      for (unsigned i = 0; i < q.size(); i++) {
        int t = query(q[i].r) - query(q[i].l - 1);
        if (q[i].k <= t)
          q1.push_back(q[i]);
        else
          q[i].k -= t, q2.push_back(q[i]);
      }
      clear();
      solve(l, m, a1, q1), solve(m + 1, r, a2, q2);
      return;
    }
    ```

Below is a more contest-style solution of [[Template] Persistent Segment Tree 2](https://www.luogu.com.cn/problem/P3834) using parallel binary search.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/parallel-binsearch/parallel-binsearch_1.cpp"
    ```

### Range k-th smallest with modifications

???+ note "Problem 4 ([Dynamic Rankings](https://www.luogu.com.cn/problem/P2617))"
    Given a sequence, support point updates and range $k$-th smallest queries.

??? note "Solution"
    A modification can be seen as deleting one number from the sequence and adding another. For convenience, we call both queries and modifications "operations". Since later operations depend on earlier ones, we cannot separate counting from answering queries as in Problem 3. Instead, we store all operations in one array, mark their types with a flag, and process them one by one. To make the Fenwick tree easier to handle, each modification is split into an erase operation and an insert operation.
    
    **Optimization**
    
    1.  Notice that each time we classify the operations, only their order changes, so we can work directly on the original array. Concretely, replace the $q, a$ arrays used in the binary search with one large global array, and during the binary search record $L, R$ instead, meaning which range of the global array holds the operations currently being processed. Use temporary arrays to record the current classification, and write them back to the original array before recursing further.
    2.  Clearing the whole Fenwick tree each time would make the time complexity blow up. Instead, record the positions modified while using the Fenwick tree (this is already done by the temporary arrays from point 1), and after this round, add $-1$ at those same positions to reset it quickly.
    3.  The initialization of the sequence can be treated simply as insert operations.

??? note "Reference code (key part)"
    ```cpp
    struct Opt {
      int x, y, k, type, id;
      // for a query, type = 1, x, y are the range bounds, k means the k-th smallest
      // for a modification, type = 0, x is the position, y is the new value,
      // k says whether this is an insert (1) or an erase (-1), used when updating the Fenwick tree.
      // id stores the original index of each operation, since the binary search shuffles them
    };
    
    Opt q[N], q1[N], q2[N];
    // q holds all operations,
    // during the binary search, operations going left are stored in q1, those going right in q2.
    int ans[N];
    void add(int p, int x);
    int query(int p);  // Fenwick tree functions, see Problem 3
    
    void solve(int l, int r, int L, int R)
    // the current value range is [l,r], the range of operations processed is [L,R]
    {
      if (l > r || L > R) return;
      int cnt1 = 0, cnt2 = 0, m = (l + r) / 2;
      // cnt1, cnt2 are the numbers of operations going left and going right
      if (l == r) {
        for (int i = L; i <= R; i++)
          if (q[i].type == 1) ans[q[i].id] = l;
        return;
      }
      for (int i = L; i <= R; i++)
        if (q[i].type == 1) {  // a query: classify it
          int t = query(q[i].y) - query(q[i].x - 1);
          if (q[i].k <= t)
            q1[++cnt1] = q[i];
          else
            q[i].k -= t, q2[++cnt2] = q[i];
        } else
          // a modification: update the Fenwick tree & classify
          if (q[i].y <= m)
            add(q[i].x, q[i].k), q1[++cnt1] = q[i];
          else
            q2[++cnt2] = q[i];
      for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 0) add(q1[i].x, -q1[i].k);  // clear the Fenwick tree
      for (int i = 1; i <= cnt1; i++) q[L + i - 1] = q1[i];
      for (int i = 1; i <= cnt2; i++)
        q[L + cnt1 + i - 1] = q2[i];  // merge the temporary arrays back into the original array
      solve(l, m, L, L + cnt1 - 1), solve(m + 1, r, L + cnt1, R);
      return;
    }
    ```

### Optimization for static sequences

???+ note "Problem 5 ([[Template] Persistent Segment Tree 2](https://www.luogu.com.cn/problem/P3834))"
    Given a sequence, answer range $k$-th smallest queries.

??? note "Solution"
    Both tree-of-trees and parallel binary search solve range $k$-th smallest with modifications in $O(n \log^2 n)$. The static range $k$-th smallest problem can be solved with a persistent segment tree in $O(n \log n)$, but almost every parallel binary search solution to the static problem runs in $O(n \log^2 n)$, which risks TLE with large inputs. (Here we assume the value range is of the same order as the sequence length; if not, coordinate compression makes it so.)
    
    **Optimization**
    
    1.  In each round of splitting, if the current sequence has $t$ numbers less than or equal to $mid$, then after the split a query actually asks for the $(k - t)$-th smallest number in the right range, so the queries sent to the right range are modified. If the original answer range is $[L,R]$ and the answer range of some split is $[l,r]$, then for the queries in this split, the influence of all values in $[L,l)$ has already been removed earlier.
    2.  Because each round of splitting must depend only on the current answer range $[l,r]$, the Fenwick tree has to be loaded and cleared many times.
    
    What if the splitting did not depend only on the current answer range?
    
    This leads to an optimization based on the whole sequence: maintain a pointer $pos$ that follows the $mid$ (divide-and-conquer center) of each round. In the Fenwick tree, set the positions (indices) of all elements $\leq pos$ to $1$ and all other positions to $0$. Before each split, move $pos$ and update the Fenwick tree. The number of times $pos$ moves is of the order $n \log n$. When splitting, for each query look up the value of the corresponding range in the Fenwick tree; if the condition holds, send the query to the left range, otherwise to the right range. **The queries do not need to be modified**.
    
    Since $pos$ follows the divide-and-conquer center, it must update the Fenwick tree accurately. Before parallel binary search, sort the sequence by value and record each element's index; when the pointer moves, update the Fenwick tree at those indices. For the vast majority of **problems that can be solved with parallel binary search and have no modifications**, this optimization can be applied to greatly reduce how often the data structure is used.
    
    Because it removes many Fenwick tree loads and clears, this optimization usually makes parallel binary search noticeably faster (even though it is only a constant-factor optimization). For the static range $k$-th smallest problem, it is no slower than the persistent segment tree, which has a better time complexity. Note that there is also an $O(n \log n)$ parallel binary search solution to the static range $k$-th smallest problem.

??? note "Reference code (key part)"
    ```cpp
    struct Query {
      int i, l, r, k;
    };  // the i-th query asks for the k-th smallest value in [l,r]
    
    Query s[200005], t1[200005], t2[200005];
    int n, m, cnt, pos, p[200005], ans[200005];
    pair<int, int> a[200005];
    
    void add(int x, int y);  // Fenwick tree: add y at position x
    int sum(int x);          // Fenwick tree: prefix sum of [1,x]
    
    // the current queries are [l,r], the answer range is [ql,qr]
    void overall_binary(int l, int r, int ql, int qr) {
      if (l > r) return;
      if (ql == qr) {
        for (int i = l; i <= r; i++) ans[s[i].i] = ql;
        return;
      }
      int cnt1 = 0, cnt2 = 0, mid = (ql + qr) >> 1;
      // follow the divide-and-conquer center; the values in [1,pos] are loaded in the Fenwick tree
      while (pos <= n - 1 && a[pos + 1].first <= mid)
        add(a[pos + 1].second, 1), ++pos;
      while (pos >= 1 && a[pos].first > mid) add(a[pos].second, -1), --pos;
    
      for (int i = l; i <= r; i++) {
        int now = sum(s[i].r) - sum(s[i].l - 1);
        if (s[i].k <= now)
          t1[++cnt1] = s[i];
        else
          t2[++cnt2] = s[i];  // note: do not modify the query
      }
      for (int i = 1; i <= cnt1; i++) s[l + i - 1] = t1[i];
      for (int i = 1; i <= cnt2; i++) s[l + cnt1 + i - 1] = t2[i];
    
      overall_binary(l, l + cnt1 - 1, ql, mid);
      overall_binary(l + cnt1, r, mid + 1, qr);
    }
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
        p[++cnt] = a[i].first;
      }
      sort(a + 1, a + n + 1);  // sort the sequence, coordinate compression
      sort(p + 1, p + n + 1);
      cnt = unique(p + 1, p + n + 1) - p - 1;
      for (int i = 1; i <= n; i++)
        a[i].first = lower_bound(p + 1, p + cnt + 1, a[i].first) - p;
      // reading the queries is omitted
      overall_binary(1, m, 1, cnt);
      for (int i = 1; i <= n; i++) printf("%d\n", p[ans[i]]);
      return 0;
    }
    ```

### Range predecessor and successor

???+ note "Problem 6"
    Answer many queries on a sequence for the predecessor of $k$ in a range (the largest number strictly less than $k$) or its successor (the smallest number strictly greater than $k$). Such a number is guaranteed to exist.

??? note "Solution"
    Take the predecessor as an example. With data structures, the usual approach is to first count how many numbers in the range are strictly less than $k$ (say there are $x$), and then find the $x$-th smallest number in the range. For the successor, count how many numbers in the range are not greater than $k$ (say $x$), then find the $(x+1)$-th smallest number in the range.
    
    Consider solving this with parallel binary search: parallel binary search is an efficient offline algorithm for range $k$-th smallest, and [CDQ divide and conquer](./cdq-divide.md) can efficiently find ranks within a range offline. Run CDQ divide and conquer once to get the ranks, then use parallel binary search to get the predecessors and successors within the ranges.
    
    This problem can also be solved offline in one pass with CDQ divide and conquer plus a segment tree, but that is much slower than running the two passes of CDQ divide and conquer + parallel binary search.

### Constructing a monotonic sequence

???+ note "Problem 7 ([Sequence](https://www.luogu.com.cn/problem/P4597))"
    Given a sequence, each operation adds $+1$ or $−1$ to some number. You must make the sequence non-decreasing, and the modified sequence may only contain numbers that appeared before the modification. Output the minimum number of operations.

??? note "Solution"
    Problems like this can also be solved with dynamic programming or regret greedy.
    
    Among the solutions with the minimum number of operations, there is always one where every number in the final sequence existed in the original sequence; this can be proved by mathematical induction. Since the problem does not ask for the final sequence, it reduces to finding the minimum number of operations.
    
    Since the final sequence must be non-decreasing, we can use parallel binary search. Each round decides the values for the range $[l,r]$ of the final sequence, where the answer range is $[ql,qr]$. Let $mid=\lfloor\frac{ql + qr}{2}\rfloor$. At the start of each round, by default all numbers go to $[mid+1,qr]$ (the count of numbers going to $[ql,mid]$ is set to $0$), and the initial cost is the number of operations to set the whole range $[l,r]$ to $mid+1$. Then go through each number $i$ in $[l,r]$ in order and compute the total cost of setting $[l,i]$ to $mid$ and $[i+1,r]$ to $mid+1$. If it is better than before, update the minimum number of operations and the number of elements going to $[ql,mid]$.
    
    The splitting already guarantees that the final sequence stays monotonic. And since we always take the minimum number of operations, setting the numbers sent to the left range to $mid$ is always better than setting them to $mid+1$. So the sequence produced by parallel binary search is non-decreasing and uses the minimum number of operations. Just compute and output the number of operations.

??? note "Reference code (key part)"
    ```cpp
    int a[500005], ans[500005];  // a: original sequence, ans: constructed sequence
    
    void overall_binary(int l, int r, int ql, int qr) {
      if (l > r) return;
      if (ql == qr) {
        for (int i = l; i <= r; i++) ans[i] = ql;
        return;
      }
      int cnt = 0,
          mid = ql + ((qr - ql) >> 1);  // by default, fill all with mid+1 and send all to the right range
      long long res = 0ll, sum = 0ll;
      for (int i = l; i <= r; i++) sum += abs(a[i] - (mid + 1));
      res = sum;
      for (int i = l; i <= r;
           i++) {  // try changing [l,i] from mid+1 to mid and sending it to the left range
        sum -= abs(a[i] - (mid + 1));
        sum += abs(a[i] - mid);
        if (sum < res) cnt = i - l + 1, res = sum;  // [l,i] is better with mid, update
      }
      overall_binary(l, l + cnt - 1, ql, mid);
      overall_binary(l + cnt, r, mid + 1, qr);
    }
    ```

### Exercises

-   [National Training Team — Matrix Multiplication](https://www.luogu.com.cn/problem/P1527)
-   [POI2011 R3 Day2 — Meteors](https://loj.ac/p/2169)
-   [Second-Rate Balanced Tree](https://loj.ac/p/106)
-   [\[BalticOI 2004\] Sequence](https://www.luogu.com.cn/problem/P4331)

## References and notes

-   Xu Haoran. Some Non-Classical Solutions to Data Structure Problems. [Collected Papers of the 2013 China National Team Candidates for the Olympiad in Informatics](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2013%E8%AE%BA%E6%96%87%E9%9B%86.pdf).

[^ref1]: Xu Haoran. Some Non-Classical Solutions to Data Structure Problems. [Collected Papers of the 2013 China National Team Candidates for the Olympiad in Informatics](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2013%E8%AE%BA%E6%96%87%E9%9B%86.pdf).
