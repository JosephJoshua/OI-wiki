author: Ir1d, sshwy, StudyingFather, Marcythm, partychicken, H-J-Granger, NachtgeistW, countercurrent-time, Enter-tainer, Tiphereth-A, weiranfu, greyqz, iamtwz, Konano, ksyx, ouuan, paigeman, wolfdan666, AngelKitty, CCXXXI, cjsoft, diauweb, Early0v0, ezoixx130, GekkaSaori, GoodCoder666, Henry-ZHR, HeRaNO, Link-cute, LovelyBuggies, LuoshuiTianyi, Makkiy, mgt, minghu6, odeinjul, oldoldtea, P-Y-Y, PotassiumWings, SamZhangQingChuan, shenshuaijie, Suyun514, weiyong1024, Xeonacid, xyf007, Alisahhh, Alphnia, c-forrest, cbw2007, dhbloo, fps5283, GavinZhengOI, Gesrua, hsfzLZH1, hydingsy, kenlig, kxccc, lychees, Menci, Peanut-Tang, PlanariaIce, sbofgayschool, shawlleyw, Siyuan, SukkaW, TianKong-y, tLLWtG, WAAutoMaton, x4Cx58x54, xk2013, zhb2000, zhufengning, hhc0001

## Knapsack tricks

### Knapsack with generalized items

In this kind of knapsack, a single item $i$ has no fixed cost and value. Its value depends on how much cost is assigned to it. In a knapsack problem with capacity $V$, when the cost assigned to item $i$ is $v_i$, the value obtained is $h_i\left(v_i\right)$.

So we enumerate the weight $w'$ assigned to item $i$. The item's value is then $h_i(w')$, and the total value is $f_{i - 1, w - w'} + h_i(w')$. So the state transition equation is $f_{i, j} = \max \limits_{0 \le k \le j}(f_{i - 1, j - k} + h_i(k))$. All of this is really just $(\max, +)$ convolution.

### Group knapsack

???+ note "[Luogu P1757 Group Knapsack](https://www.luogu.com.cn/problem/P1757)"
    There are $n$ items and a knapsack of size $m$. Item $i$ has value $w_i$ and volume $v_i$. Each item belongs to a group, and you can choose at most one item from each group. Find the maximum total value the knapsack can hold.

This kind of problem just changes "choose one item from all items" into "choose one item from the current group", so we just run a 0-1 knapsack for each group.

Now about storage. Let $t_{k,i}$ be the index of the $i$-th item in group $k$, and let $\mathit{cnt}_k$ be the number of items in group $k$.

#### Implementation

=== "C++"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_4.cpp:core"
    ```

=== "Python"
    ```python
    for k in range(1, ts + 1):  # loop over each group
        for i in range(m, -1, -1):  # loop over knapsack capacity
            for j in range(1, cnt[k] + 1):  # loop over each item in the group
                if i >= w[t[k][j]]:  # enough capacity left
                    dp[i] = max(
                        dp[i], dp[i - w[t[k][j]]] + c[t[k][j]]
                    )  # transition just like in 0-1 knapsack
    ```

Note here: **you must not get the loop order wrong**; only then is the result correct.

### Rollback knapsack

Counting the number of ways in an ordinary 0-1 knapsack just needs a direct DP. But sometimes you meet cases like "all other items can be chosen, only a few items cannot", and usually different items are excluded many times within the same set of items, e.g. in some complex tree knapsacks. A direct DP may then TLE, so we introduce the rollback knapsack to handle this.

Notice that items in a knapsack are unordered: for two items, which one is put in first has no effect on the current situation, so we can regard **every item as the last one put in**. So we can first precompute the DP over all items, and then undo the contribution of one item. That is:

$$
dp_j \gets dp_j - dp_{j - w_i}
$$

Note that the loop must run from small to large; otherwise the contribution would be undone in the way of the unbounded knapsack.

## Knapsack miscellany

### Outputting the solution

Outputting the solution just means recording how a certain state in the knapsack was derived. Let $g_{i,v}$ indicate whether item $i$ was chosen when the space used is $v$. Then during the transition, record which choice was made (take it or not). Pseudocode for the output:

```cpp
int v = V;  // current remaining capacity

// The last item stores the final state, so loop starting from the last item
for (loop from the last item to the first) {
  if (g[i][v]) {
    item i was chosen;
    v -= weight of item i;
  } else {
    item i was not chosen;
  }
}
```

### Counting optimal solutions

To count the optimal solutions, we slightly change the definition of the $\mathit{dp}$ array in the 0-1 knapsack: the DP state $f_{i,j}$ is the maximum total value when only the first $i$ items can be used and the knapsack of capacity $j$ is "exactly full".

After this change, each DP state can have a $g_{i,j}$ for the number of ways.

$f_{i,j}$ is the maximum value when only the first $i$ items are considered and the volume used is "exactly" $j$.

$g_{i,j}$ is the number of ways when only the first $i$ items are considered and the volume used is "exactly" $j$.

Transition equations:

If $f_{i,j} = f_{i-1,j}$ and $f_{i,j} \neq f_{i-1,j-v}+w$, then not putting the item in is better, and the number of ways comes from $g_{i-1,j}$.

If $f_{i,j} \neq f_{i-1,j}$ and $f_{i,j} = f_{i-1,j-v}+w$, then putting the item in is better, and the number of ways comes from $g_{i-1,j-v}$.

If $f_{i,j} = f_{i-1,j}$ and $f_{i,j} = f_{i-1,j-v}+w$, then both putting it in and not putting it in give an optimal solution, and the number of ways comes from both $g_{i-1,j}$ and $g_{i-1,j-v}$.

Initial conditions:

```cpp
memset(f, 0xcf, sizeof(f));
// We want the maximum, so initialize to negative infinity to avoid transitions from states that are not exactly full
// For the minimum, initialize to positive infinity 0x3f instead
f[0] = 0;
g[0] = 1;  // taking nothing counts as one way
```

Since the knapsack may not be fillable to its maximum volume, the optimal solution is not necessarily $f_{m}$.

Finally, we find the value of the optimal solution and add up the counts in the $g_{j}$ array for all $j$ that achieve it.

???+ note "Implementation"
    ```cpp
    for (int i = 0; i < N; i++) {
      for (int j = V; j >= v[i]; j--) {
        int tmp = std::max(dp[j], dp[j - v[i]] + w[i]);
        int c = 0;
        if (tmp == dp[j]) c += cnt[j];                       // if transitioning from dp[j]
        if (tmp == dp[j - v[i]] + w[i]) c += cnt[j - v[i]];  // if transitioning from dp[j-v[i]]
        dp[j] = tmp;
        cnt[j] = c;
      }
    }
    int max = 0;  // find the optimal value
    for (int i = 0; i <= V; i++) {
      max = std::max(max, dp[i]);
    }
    int res = 0;
    for (int i = 0; i <= V; i++) {
      if (dp[i] == max) {
        res += cnt[i];  // sum the number of optimal solutions
      }
    }
    ```

### The k-th best solution of a knapsack

The ordinary 0-1 knapsack asks for the best solution. With a small change to the ordinary knapsack DP, adding one dimension to record the top k solutions for the current state, we get an algorithm for the $k$-th best solution of the 0-1 knapsack.
Specifically: $f_{i,j,k}$ records the $k$-th largest total value among the first $i$ items when the total volume of chosen items is $j$. This state can be seen as extending $f_{i,j}$ of the ordinary 0-1 knapsack, which records only one value, into an ordered sequence of best values. For the transition, the ordinary knapsack computes the best value as $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-v_i}+w_i)$. Now we instead merge the two decreasing sequences $f_{i-1,j}$ and $f_{i-1,j-v_i}+w_i$, each of size $k$, and keep the $k$ largest values of the merged result in $f_{i,j}$. This step uses the two-pointer technique and costs $O(k)$, so the overall time complexity is $O(nmk)$. For space, like the ordinary knapsack, this method can drop the first dimension, giving $O(mk)$.

??? note "Example problem [HDU 2639 Bone Collector II](https://acm.hdu.edu.cn/showproblem.php?pid=2639)"
    Find the strict $k$-th best solution of a 0-1 knapsack. $n \leq 100,v \leq 1000,k \leq 30$

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_3.cpp:core"
    ```

## Knapsack-related problems

### Mixed knapsack

The mixed knapsack combines the 0-1 knapsack, the unbounded knapsack and the bounded knapsack: some items can be taken only once, some any number of times, and some at most $k$ times.

This kind of problem looks hard, but the choice for each item is still independent. So we can check which kind of knapsack the current item belongs to and use the solution for that kind.

#### Example problem

???+ note "[Luogu P1833 Cherry Blossoms](https://www.luogu.com.cn/problem/P1833)"
    There are $n$ kinds of cherry trees and $T$ units of time. Some cherry trees can be viewed only once, some at most $A_{i}$ times, and some any number of times. Each cherry tree has an aesthetic value $C_{i}$. Find which cherry trees to view within time $T$ to maximize the total aesthetic value.

??? note "Core code"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_5.cpp:core"
    ```

Exercise: [HDU 5410 CRB and His Birthday](https://acm.hdu.edu.cn/showproblem.php?pid=5410)

### Two-dimensional cost knapsack

???+ note "[Luogu P1855 Squeezing kkksc03](https://www.luogu.com.cn/problem/P1855)"
    There are $n$ tasks to complete. Task $i$ takes $t_i$ minutes and costs $c_i$ yuan.
    
    You have $T$ minutes and $W$ yuan to handle these tasks. Find the maximum number of tasks you can complete.

This is clearly a 0-1 knapsack problem, except that choosing an item uses up two kinds of cost (money and time). We just add one more dimension to the state for the second cost. The state transition equation becomes $f_{i, j, k} = \max(f_{i - 1, j, k}, f_{i - 1, j - t_i, k - c_i} + w_i)$. In this problem all $w_i$ are $1$.

Note that here it is not a good idea to add yet another dimension for the item index, since that can easily cause MLE.

#### Implementation

=== "C++"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_6.cpp:core"
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for i in range(m, mi - 1, -1):  # enumerate the money
            for j in range(t, ti - 1, -1):  # enumerate the time
                dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1)
    ```

### Knapsack with dependencies

???+ note "[Luogu P1064 Jinming's Budget Plan](https://www.luogu.com.cn/problem/P1064)"
    Jinming has $n$ yuan and wants to buy $m$ items. Item $i$ costs $v_i$ and has importance $p_i$. Some items are accessories of a main item; to buy such an item, you must also buy its main item.
    
    The goal is to maximize the sum of $v_i \times p_i$ over all purchased items.

Just treat it as a [knapsack on a tree](../tree.md#knapsack-on-a-tree). Remember to merge all the knapsacks together at the end.

## References and notes

-   [Nine Lectures on Knapsack Problems - Cui Tianyi](https://github.com/tianyicui/pack).
