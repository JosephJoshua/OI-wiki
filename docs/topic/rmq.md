## Introduction

RMQ is short for Range Maximum/Minimum Query, which means finding the maximum (or minimum) value in a range.

In the descriptions below, the initial array has size $n$ and there are $m$ queries.

In the descriptions below, time complexity is written as $O(A) \sim O(B)$, where $O(A)$ is the preprocessing time and $O(B)$ is the time for a single query.

## Monotonic stack

Since **OI Wiki** already describes this part, this article only gives a [link](../ds/monotonic-stack.md). We will not go into it here.

Time complexity $O(m\log m) \sim O(\log n)$, space complexity $O(n)$.

## Sparse table

Since **OI Wiki** already describes this part, this article only gives a [link](../ds/sparse-table.md). We will not go into it here.

Time complexity $O(n\log n) \sim O(1)$, space complexity $O(n\log n)$.

## Segment tree

Since **OI Wiki** already describes this part, this article only gives a [link](../ds/seg.md). We will not go into it here.

Time complexity $O(n) \sim O(\log n)$, space complexity $O(n)$.

## Four Russian

Four Russian is an algorithm based on the sparse table, proposed by four Russian computer scientists.

The improvement that the Four Russian algorithm makes over the sparse table is to split the sequence into blocks.

Specifically, we split the original array (call it array A) into blocks of $S$ elements each, for $n/S$ blocks in total.

For each block, we precompute the minimum of the elements in it, build an array B of length $n/S$ from these values, and preprocess array B with a sparse table.

At the same time, we also build a sparse table for each individual block of array A.

When answering a query, we can split the query range into at most 1 range of consecutive blocks in array B, plus at most 2 ranges that each lie inside a single block of array A. Clearly each of these can be answered with a range query on a sparse table.

When $S=\log n$, the preprocessing cost is optimal: $O((n / \log n)\log n+(n / \log n)\times\log n\times\log \log n)=O(n\log \log n)$.

Time complexity $O(n\log \log n) \sim O(1)$, space complexity $O(n\log \log n)$.

Of course, since a query has to use three sparse tables, this implementation has a large constant factor.

??? note "Some small improvements"
    Notice that when the two endpoints of a query fall in different blocks of array A, the queries inside the blocks of array A are always about a prefix or a suffix of a block.
    
    Clearly these queries can be answered by precomputing the answers in $O(n)$ time.
    
    This way, each query only needs at most one query on a sparse table.

??? note "Some unusual improvements"
    Since the Four Russian algorithm is built on the sparse table, and competitive programming usually does not demand extremely tight time complexity, the Four Russian algorithm can usually be replaced by a sparse table and is not very practical in contests. Here is an improved version of Four Russian that is more practical in contests.
    
    Set the block size to $\sqrt n$. Precompute the prefix and suffix RMQ inside each block, then precompute by brute force the RMQ over every range of consecutive whole blocks. The time complexity is $O(n)$.
    
    For a query whose left and right endpoints are in different blocks, we can directly get in $O(1)$ the suffix RMQ of the left endpoint's block, the RMQ of the consecutive whole blocks between the endpoints, and the prefix RMQ of the right endpoint's block. The answer is the best of these three.
    
    For a query whose left and right endpoints are in the same block, we can compute the RMQ between the two points by brute force in $O(\sqrt n)$ time. But the expected chance that a single query has both endpoints in the same block is $O(\frac{\sqrt n}{n})$, so this method takes expected $O(n)$ time.
    
    In contests, we don't need to worry much about the problem setter breaking this algorithm: by randomly adjusting the block size slightly around $\sqrt n$, we can largely avoid worst cases in test data built for a specific block size. Also, if the problem setter wants to break this method, brute force might pass instead.
    
    This algorithm reaches the lower bound in expected time complexity, and it is easy to code with a small constant factor, so it is quite practical in contests.
    
    The method above is based on an editorial for [P3793 Yuno Saves Grandpa](https://www.luogu.com.cn/problem/P3793).

## ±1 RMQ

If adjacent elements of a sequence differ by exactly 1, RMQ on this sequence is called ±1 RMQ. Using this property, we can improve the Four Russian algorithm to reach $O(n) \sim O(1)$ time complexity and $O(n)$ space complexity.

Since the bottleneck of the Four Russian algorithm is the RMQ inside each block, we focus on optimizing the in-block RMQ.

Since adjacent numbers differ by $\pm 1$, once the leftmost number is fixed, the number of possible sequences to its right of length at most $\log n$ is $\sum_{i=1}^{\log n} 2^{i-1}$, which clearly does not exceed $n$.

This suggests that we can precompute the value of (minimum minus first element) for all of these at most $n$ cases.

During preprocessing, we compute the differences between adjacent numbers in the same block and encode them in binary.

When answering a query, we find the binary encoding for the query range and look up the answer in the table.

This way, the preprocessing time of Four Russian is reduced to $O(n)$.

## Using the Cartesian tree for RMQ

If you are not familiar with Cartesian trees, please see [Cartesian tree](../ds/cartesian-tree.md).

It is easy to see that the min/max between two positions in the original sequence equals the value of the LCA of those two nodes in the Cartesian tree. Based on this, we can solve RMQ by computing the LCA of two tree nodes in $O(n) \sim O(1)$. The $O(n) \sim O(1)$ tree LCA is already described in [LCA - Standard RMQ](../graph/lca.md#标准-rmq), so we will not go into it here.

To sum up, using the Cartesian tree for RMQ means turning a general RMQ problem into an LCA problem, and then into a ±1 RMQ problem. The time complexity is $O(n) \sim O(1)$. Of course, because of the many conversion steps, this $O(n) \sim O(1)$ RMQ has a large constant factor.

If the data is random, you can also search the Cartesian tree directly by brute force. Then the time complexity is expected $O(n) \sim O(\log n)$, and in practice this algorithm usually has a very small constant factor.

### Example problem [Luogu P3865 [Template] Sparse Table](https://www.luogu.com.cn/problem/P3865)

## A linear RMQ algorithm based on bitmasks

### Implicit requirement

-   The length $n$ of the sequence satisfies $\log_2{n} \leq 64$.

### Prerequisites

-   [Sparse Table](../ds/sparse-table.md)

-   Basic bit operations

-   Prefix and suffix maximums

### How it works

Split the original sequence $A[1\cdots n]$ into $O(\frac{n}{\log_2{n}})$ blocks, each of length $O(\log_2{n})$.

> It is said that the constant factor is smaller when the block length is $1.5\times \log_2{n}$.

Record the maximum of each block and maintain the maximum between blocks with a sparse table, in $O(n)$.

For each position, record the prefix and suffix maximums within its block, $Pre[1\cdots n], Sub[1\cdots n]$ ($Pre[i]$ is the maximum from the start of $A[i]$'s block to $A[i]$), in $O(n)$.

If the queried $l,r$ are in two different blocks, numbered $bl,br$, then the maximum is the largest of three values: the maximum over blocks $[bl+1,br-1]$, $Sub[l]$, and $Pre[r]$.

The remaining question is what to do when $l,r$ are in the same block.

Insert $A[1\cdots r]$ into a monotonic stack one by one, recording both indices and values, so that values decrease from the bottom of the stack to the top. Then the maximum of $A[l,r]$ is the first value in the monotonic stack, going up from the bottom, whose index $p$ satisfies $p \geq l$.

Since $A[p]$ is the maximum of $A[l,r]$, all of $A[l\cdots p-1]$ were popped when $A[p]$ was inserted, and inserting $A[p+1\cdots r]$ can never pop $A[p]$.

If we use $0/1$ to mark whether each number is in the stack, we can store this state as an integer bitmask. Then $p$ is the position of the first $1$ at or after bit $l$.

Since the block size is $O(\log_2{n})$, it never exceeds $64$ bits, so it fits in one integer (this is the reason for the implicit requirement).

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    
    constexpr int MAXN = 1e5 + 5;
    constexpr int MAXM = 20;
    
    struct RMQ {
      int N, A[MAXN];
      int blockSize;
      int S[MAXN][MAXM], Pow[MAXM], Log[MAXN];
      int Belong[MAXN], Pos[MAXN];
      int Pre[MAXN], Sub[MAXN];
      int F[MAXN];
    
      void buildST() {
        int cur = 0, id = 1;
        Pos[0] = -1;
        for (int i = 1; i <= N; ++i) {
          S[id][0] = std::max(S[id][0], A[i]);
          Belong[i] = id;
          if (Belong[i - 1] != Belong[i])
            Pos[i] = 0;
          else
            Pos[i] = Pos[i - 1] + 1;
          if (++cur == blockSize) {
            cur = 0;
            ++id;
          }
        }
        if (N % blockSize == 0) --id;
        Pow[0] = 1;
        for (int i = 1; i < MAXM; ++i) Pow[i] = Pow[i - 1] * 2;
        for (int i = 2; i <= id; ++i) Log[i] = Log[i / 2] + 1;
        for (int i = 1; i <= Log[id]; ++i) {
          for (int j = 1; j + Pow[i] - 1 <= id; ++j) {
            S[j][i] = std::max(S[j][i - 1], S[j + Pow[i - 1]][i - 1]);
          }
        }
      }
    
      void buildSubPre() {
        for (int i = 1; i <= N; ++i) {
          if (Belong[i] != Belong[i - 1])
            Pre[i] = A[i];
          else
            Pre[i] = std::max(Pre[i - 1], A[i]);
        }
        for (int i = N; i >= 1; --i) {
          if (Belong[i] != Belong[i + 1])
            Sub[i] = A[i];
          else
            Sub[i] = std::max(Sub[i + 1], A[i]);
        }
      }
    
      void buildBlock() {
        static int S[MAXN], top;
        for (int i = 1; i <= N; ++i) {
          if (Belong[i] != Belong[i - 1])
            top = 0;
          else
            F[i] = F[i - 1];
          while (top > 0 && A[S[top]] <= A[i]) F[i] &= ~(1 << Pos[S[top--]]);
          S[++top] = i;
          F[i] |= (1 << Pos[i]);
        }
      }
    
      void init() {
        for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
        blockSize = log2(N) * 1.5;
        buildST();
        buildSubPre();
        buildBlock();
      }
    
      int queryMax(int l, int r) {
        int bl = Belong[l], br = Belong[r];
        if (bl != br) {
          int ans1 = 0;
          if (br - bl > 1) {
            int p = Log[br - bl - 1];
            ans1 = std::max(S[bl + 1][p], S[br - Pow[p]][p]);
          }
          int ans2 = std::max(Sub[l], Pre[r]);
          return std::max(ans1, ans2);
        } else {
          return A[l + __builtin_ctz(F[r] >> Pos[l])];
        }
      }
    } R;
    
    int M;
    
    int main() {
      scanf("%d%d", &R.N, &M);
      R.init();
      for (int i = 0, l, r; i < M; ++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", R.queryMax(l, r));
      }
      return 0;
    }
    ```

### Exercises

[\[BJOI 2020\] Seal](https://loj.ac/problem/3298): SAM+RMQ
