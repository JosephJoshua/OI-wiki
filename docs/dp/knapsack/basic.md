author: Ir1d, sshwy, StudyingFather, Marcythm, partychicken, H-J-Granger, NachtgeistW, countercurrent-time, Enter-tainer, Tiphereth-A, weiranfu, greyqz, iamtwz, Konano, ksyx, ouuan, paigeman, wolfdan666, AngelKitty, CCXXXI, cjsoft, diauweb, Early0v0, ezoixx130, GekkaSaori, GoodCoder666, Henry-ZHR, HeRaNO, Link-cute, LovelyBuggies, LuoshuiTianyi, Makkiy, mgt, minghu6, odeinjul, oldoldtea, P-Y-Y, PotassiumWings, SamZhangQingChuan, shenshuaijie, Suyun514, weiyong1024, Xeonacid, xyf007, Alisahhh, Alphnia, c-forrest, cbw2007, dhbloo, fps5283, GavinZhengOI, Gesrua, hsfzLZH1, hydingsy, kenlig, kxccc, lychees, Menci, Peanut-Tang, PlanariaIce, sbofgayschool, shawlleyw, Siyuan, SukkaW, TianKong-y, tLLWtG, WAAutoMaton, x4Cx58x54, xk2013, zhb2000, zhufengning, hhc0001

Prerequisites: [Introduction to dynamic programming](../index.md).

## Introduction

Before explaining what "knapsack DP" is, let's look at the following example problem:

???+ note "[USACO07 DEC Charm Bracelet](https://www.luogu.com.cn/problem/P2871)"
    Summary: there are $n$ items and a knapsack with capacity $W$. Each item has two attributes: weight $w_{i}$ and value $v_{i}$. Choose some items to put in the knapsack so that the total value of the items is as large as possible, while their total weight does not exceed the knapsack's capacity.

In the example above, each item has only two possible states (taken or not taken), which correspond to $0$ and $1$ in binary. So this kind of problem is called the "0-1 knapsack problem".

## 0-1 knapsack

### Explanation

In the example, we know the weight $w_{i}$ and value $v_{i}$ of the $i$-th item, and the total capacity $W$ of the knapsack.

Let the DP state $f_{i,j}$ be the maximum total value a knapsack of capacity $j$ can reach when only the first $i$ items can be used.

Now consider the transition. Suppose all states for the first $i-1$ items are done. For the $i$-th item, if it is not put in the knapsack, the remaining capacity and the total value stay the same, so the maximum value in this case is $f_{i-1,j}$. If it is put in, the remaining capacity decreases by $w_{i}$ and the total value increases by $v_{i}$, so the maximum value in this case is $f_{i-1,j-w_{i}}+v_{i}$.

This gives the state transition equation:

$$
f_{i,j}=\max(f_{i-1,j},f_{i-1,j-w_{i}}+v_{i})
$$

If we store the states directly in a two-dimensional array, we will get MLE. We can optimize this with a rolling array.

Since only $f_{i-1}$ affects $f_i$, we can drop the first dimension and directly use $f_{i}$ to mean the maximum value with knapsack capacity $i$ after processing the current item. This gives the following equation:

$$
f_j=\max \left(f_j,f_{j-w_i}+v_i\right)
$$

**Be sure to remember and understand this transition equation, because the transition equations of most knapsack problems are derived from it.**

### Implementation

One more thing to watch out for: it is very easy to write **wrong core code** like this:

=== "C++"
    ```cpp
    for (int i = 1; i <= n; i++)
      for (int l = 0; l <= W - w[i]; l++)
        f[l + w[i]] = max(f[l] + v[i], f[l + w[i]]);
    // simplified from f[i][l + w[i]] = max(max(f[i - 1][l + w[i]], f[i - 1][l] + v[i]),
    // f[i][l + w[i]]);
    ```

=== "Python"
    ```python
    for i in range(1, n + 1):
        for l in range(0, W - w[i] + 1):
            f[l + w[i]] = max(f[l] + v[i], f[l + w[i]])
    # simplified from f[i][l + w[i]] = max(max(f[i - 1][l + w[i]], f[i - 1][l] + v[i]),
    # f[i][l + w[i]])
    ```

What is wrong with this code? The loop order is wrong.

Looking closely at the code, for the current item $i$ and the current state $f_{i,j}$, when $j\geqslant w_{i}$, $f_{i,j}$ is affected by $f_{i,j-w_{i}}$. This is equivalent to putting item $i$ into the knapsack multiple times, which does not match the problem. (In fact, this is exactly the solution to the unbounded knapsack problem.)

To avoid this, we can change the loop order and go from $W$ down to $w_{i}$. Then the error above cannot happen, because $f_{i,j}$ is always updated before $f_{i,j-w_{i}}$.

So the correct core code is

=== "C++"
    ```cpp
    for (int i = 1; i <= n; i++)
      for (int l = W; l >= w[i]; l--) f[l] = max(f[l], f[l - w[i]] + v[i]);
    ```

=== "Python"
    ```python
    for i in range(1, n + 1):
        for l in range(W, w[i] - 1, -1):
            f[l] = max(f[l], f[l - w[i]] + v[i])
    ```

??? note "Code for the example problem"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_1.cpp"
    ```

## Unbounded knapsack

### Explanation

The unbounded knapsack model is similar to the 0-1 knapsack. The only difference is that each item can be taken any number of times instead of only once.

We can borrow the idea of the 0-1 knapsack to define the state: let $f_{i,j}$ be the maximum value a knapsack of capacity $j$ can reach when only the first $i$ items can be chosen.

Note that although the definition is similar to the 0-1 knapsack, the state transition equation is different.

### Process

A naive approach: for the $i$-th item, enumerate how many copies are taken. The time complexity is $O(nW^2)$, where $n$ is the number of items and $W$ is the knapsack capacity.

The state transition equation is:

$$
f_{i,j}=\max_{k=0}^{\lfloor j/w_i\rfloor}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

Let's make a simple optimization. Notice that for $f_{i,j}$, it is enough to transition from $f_{i,j-w_i}$. So the state transition equation is:

$$
f_{i,j}=\max(f_{i-1,j},f_{i,j-w_i}+v_i)
$$

The reason is that when we transition this way, $f_{i,j-w_i}$ has already been updated from $f_{i,j-2\times w_i}$, so $f_{i,j-w_i}$ is already the best result after fully considering how many copies of item $i$ to take. In other words, we reuse the earlier enumeration through the optimal substructure property, which reduces the cost of enumeration.

As with the 0-1 knapsack, we can drop the first dimension to reduce the space complexity. If you understand how the 0-1 knapsack is optimized, it is easy to see that the compressed loop goes forward (which is exactly the "wrong optimization" mentioned above).

??? note "[Luogu P1616 Crazy Herb Gathering](https://www.luogu.com.cn/problem/P1616)"
    Summary: there are $n$ kinds of items and a knapsack with capacity $W$. Each kind of item has two attributes: weight $w_{i}$ and value $v_{i}$. Choose some items to put in the knapsack so that the total value is as large as possible, while their total weight does not exceed the knapsack's capacity.

??? note "Code for the example problem"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_2.cpp"
    ```

## Bounded knapsack

The bounded knapsack is another variant of the 0-1 knapsack. The difference is that there are $k_i$ copies of each kind of item instead of one.

A naive idea is to turn "choose an item of kind $i$ up to $k_i$ times" into "there are $k_i$ identical items, each of which can be chosen once". This turns it into a 0-1 knapsack model, which can be solved with the method above. The state transition equation is:

$$
f_{i,j}=\max_{k=0}^{k_i}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

The time complexity is $O(W\sum_{i=1}^nk_i)$.

??? note "Core code"
    ```cpp
    for (int i = 1; i <= n; i++) {
      for (int weight = W; weight >= w[i]; weight--) {
        // one extra loop over the number of copies
        for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
          dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
        }
      }
    }
    ```

### Binary splitting optimization

Now let's optimize. We still turn the bounded knapsack into a 0-1 knapsack model.

### Explanation

Clearly, the $O(nW)$ part of the complexity cannot be improved further, so we can only work on the $O(\sum k_i)$ part. For convenience, let $A_{i,j}$ denote the $j$-th item split off from the $i$-th kind of item.

In the naive approach, $A_{i,j}$ is the same item for all $j\le k_i$. The main reason for the low efficiency is that we do a lot of repeated work. For example, we consider both "choose $A_{i,1},A_{i,2}$ together" and "choose $A_{i,2},A_{i,3}$ together", which are completely equivalent. We do such repeated work many times. So a better way of splitting is the key to solving the problem.

### Process

We can make the splitting more efficient with "binary splitting".

Specifically, let $A_{i,j}\left(j\in\left[0,\lfloor \log_2(k_i+1)\rfloor-1\right]\right)$ be a big item made by "bundling" $2^{j}$ single items. In particular, if $k_i+1$ is not a power of $2$, we add one more big item at the end, made by "bundling" $k_i-2^{\lfloor \log_2(k_i+1)\rfloor}+1$ single items, to make up the difference.

A few examples:

-   $6=1+2+3$
-   $8=1+2+4+1$
-   $18=1+2+4+8+3$
-   $31=1+2+4+8+16$

Clearly, with this splitting, any choice of $\le k_i$ items can be represented equivalently. After splitting each kind of item this way, solve it with the 0-1 knapsack method.

The time complexity is $O(W\sum_{i=1}^n\log_2k_i)$

### Implementation

??? note "Binary splitting code"
    === "C++"
        ```cpp
        index = 0;
        for (int i = 1; i <= m; i++) {
          int c = 1, p, h, k;
          cin >> p >> h >> k;
          while (k > c) {
            k -= c;
            list[++index].w = c * p;
            list[index].v = c * h;
            c *= 2;
          }
          list[++index].w = p * k;
          list[index].v = h * k;
        }
        ```
    
    === "Python"
        ```python
        index = 0
        for i in range(1, m + 1):
            c = 1
            p, h, k = map(int, input().split())
            while k > c:
                k -= c
                index += 1
                list[index].w = c * p
                list[index].v = c * h
                c *= 2
            index += 1
            list[index].w = p * k
            list[index].v = h * k
        ```

### Monotonic queue optimization

See [Monotonic queue/monotonic stack optimization](../opt/monotonic-queue-stack.md).

Exercise: [Luogu P1776 Treasure Selection (NOI Guide 2010 Senior (02))](https://www.luogu.com.cn/problem/P1776)

## Counting the number of ways

Given a knapsack capacity, item costs and other constraints, count the total number of ways to fill the knapsack up to a certain capacity.

For this kind of problem, just replace taking the maximum with taking the sum.

For example, the transition equation of the 0-1 knapsack becomes:

$$
\mathit{dp}_j \leftarrow \mathit{dp}_j + \mathit{dp}_{j-c_i} \qquad (j \ge c_i)
$$

Initial condition: $\mathit{dp}_0=1$

This is because when the capacity is $0$ there is also one way: take nothing.

## References and notes

-   [Nine Lectures on Knapsack Problems - Cui Tianyi](https://github.com/tianyicui/pack).
