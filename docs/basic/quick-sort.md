This page gives a short introduction to quicksort.

## Definition

Quicksort, also called partition-exchange sort, is a widely used sorting algorithm.

## Basic idea and implementation

### How it works

Quicksort sorts an array using [divide and conquer](./divide-and-conquer.md).

Quicksort has three steps:

1.  Split the sequence into two parts (keeping the required order between the parts);
2.  Recursively quicksort each of the two subsequences;
3.  No merging is needed, because the sequence is now fully sorted.

Unlike merge sort, the first step does not just cut the sequence into a front half and a back half. Instead, the split has to respect the relative order of values. Specifically, the first step divides the sequence into two parts so that every number in the first part is no greater than every number in the second part. To keep the average running time low, we usually pick a random number $m$ as the boundary between the two parts.

Then, we keep two pointers, $p$ at the front and $q$ at the back, and check one by one whether each number is on the correct side (front or back). If a number is on the wrong side, for example if the back pointer $q$ finds a number smaller than $m$, we swap the numbers at $p$ and $q$ and move $p$ forward by one. Once the current numbers are all in the right place, we move the pointers on and keep going until the two pointers meet.

In fact, quicksort does not say exactly how the first step must be done. Both choosing $m$ and partitioning can be done in more than one way.

In the third step, the two parts are each sorted, and every number in the first part is no greater than every number in the second part, so we simply put them side by side.

Below are basic implementations with a fixed choice of pivot: the non-recursive C++ version picks the last element of the current subarray, while the recursive C++ version and the Python version pick the first element. They do not choose the pivot randomly, so they may degrade to $O(n^2)$ on inputs such as already-sorted arrays.

=== "C++"
    === " Non-recursive[^ref2]"
        ```cpp
        --8<-- "docs/basic/code/quick-sort/quick-sort_1.cpp:sort"
        ```
    
    === "Recursive"
        ```cpp
        --8<-- "docs/basic/code/quick-sort/quick-sort_2.cpp:sort"
        ```

=== "Python[^ref2]"
    ```python
    --8<-- "docs/basic/code/quick-sort/quick-sort_2.py:sort"
    ```

## Properties

### Stability

Quicksort is not stable.

### Time complexity

Quicksort runs in $O(n\log n)$ time in the best and average cases, and $O(n^2)$ time in the worst case.

In the best case, the chosen boundary value is always the median of the sequence. The running time then satisfies $T(n) = 2T(\dfrac{n}{2}) + \Theta(n)$, and by the master theorem, $T(n) = \Theta(n\log n)$.

In the worst case, the chosen boundary value is always the minimum or maximum of the sequence. The running time then satisfies $T(n) = T(n - 1) + \Theta(n)$, and adding it up gives $T(n) = \Theta(n^2)$.

The expected-time analysis below assumes all keys are distinct and that each pivot is chosen uniformly at random from the current subarray.

??? note "Proof"
    We now prove that in this setting the algorithm runs in $O(n\log n)$ expected time.
    
    **Lemma 1:** When quicksorting an array of $n$ elements, let $X$ be the number of distinct pairs of elements compared during partitioning. Then quicksort runs in $O(n + X)$ time.
    
    Each partition step picks one element as the boundary, so partitioning happens at most $n$ times. Also, during partitioning, each pair of elements is compared only a constant number of times, and the comparisons are of the same order as all other basic operations. So the total running time is $O(n + X)$.
    
    Let $a_i$ be the $i$-th smallest number in the original array. Define $A_{i,j}$ as $\{ a_i, a_{i+1}, \dots, a_j \}$, and let $X_{i,j}$ be a discrete random variable taking the value $0$ or $1$, indicating whether $a_i$ and $a_j$ are compared during sorting.
    
    Clearly, each chosen boundary value is different, and elements are only compared with the boundary value. So the number of distinct compared pairs is
    
    $$
    \begin{aligned} X = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n X_{i,j} \end{aligned}
    $$
    
    By linearity of expectation,
    
    $$
    \begin{aligned} E[X] & = E \left[ \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n X_{i,j} \right] \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n E[X_{i,j}] \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n P(a_i\ \text{and}\ a_j\ \text{are compared}) \end{aligned}
    $$
    
    **Lemma 2:** $a_i$ and $a_j$ are compared if and only if $a_i$ or $a_j$ is the first element of $A_{i,j}$ to be chosen as a boundary value.
    
    First, we prove necessity: if neither $a_i$ nor $a_j$ is the first element of $A_{i,j}$ chosen as a boundary value, then $a_i$ and $a_j$ are never compared.
    
    If neither $a_i$ nor $a_j$ is the first element of $A_{i,j}$ chosen as a boundary value, then there must be some $x$ with $i < x < j$ such that $a_x$ is the first element of $A_{i,j}$ chosen as a boundary value. In the partition around $a_x$, $a_i$ and $a_j$ go into two different subsequences, so they can never be compared afterwards. Also, since elements are only compared with the boundary value, $a_i$ and $a_j$ were not compared before or during this partition. So $a_i$ and $a_j$ are never compared.
    
    Next, we prove sufficiency: if $a_i$ or $a_j$ is the first element of $A_{i,j}$ chosen as a boundary value, then $a_i$ and $a_j$ are compared.
    
    Without loss of generality, suppose $a_i$ is the first element of $A_{i,j}$ chosen as a boundary value. Since no other number in $A_{i,j}$ has been chosen as a boundary value, all elements of $A_{i,j}$ are still in the same subsequence. In the partition around $a_i$, $a_i$ is compared with every element in the current subsequence, so $a_i$ and $a_j$ are compared.
    
    Now let's compute $P(a_i\ \text{and}\ a_j\ \text{are compared})$. Until some element of $A_{i,j}$ is chosen as a boundary value, all elements of $A_{i,j}$ stay in the same subsequence. So each element of $A_{i,j}$ is equally likely to be the first one chosen as a boundary value. Since $A_{i,j}$ has $j - i + 1$ elements, by Lemma 2,
    
    $$
    P(a_i \text{ and } a_j \text{ are compared}) = P(a_i \text{ or } a_j \text{ is the first element of } A_{i,j} \text{ chosen as a boundary value}) = \dfrac{2}{j-i+1}
    $$
    
    Therefore
    
    $$
    \begin{aligned} E[X] & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n P(a_i\ \text{and}\ a_j\ \text{are compared}) \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n \dfrac{2}{j - i + 1} \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {k = 2} ^ {n - i + 1} \dfrac{2}{k} \\ & = \sum \limits _ {i = 1} ^ {n - 1} O(\log n) \\ & = O(n \log n) \end{aligned}
    $$
    
    Hence the expected running time of quicksort is $O(n \log n)$.

Choosing the pivot randomly lowers the chance of running into the worst-case partition. In addition, quicksort's memory access pattern has good locality, which helps it perform well in practice.[^ref1]

## Optimization

### Basic optimization ideas

If you implement quicksort using only the basic idea above (or just copy a template), it usually won't pass the template problem [P1177 \[Template\] Quicksort](https://www.luogu.com.cn/problem/P1177), because test data can be constructed to make naive quicksort degrade to $O(n^2)$.

So we need to optimize naive quicksort. The three most common optimizations are[^ref3]:

-   Choose the boundary element (the pivot) between the two subsequences using **median of three (the median of the first, last and middle elements)**. This avoids degrading on extreme data (such as ascending or descending sequences).
-   When the sequence is short, **insertion sort** is faster.
-   After each pass, **gather the elements equal to the pivot around the pivot**. This avoids degrading on extreme data (such as sequences where most elements are equal).

Below are some well-established ways to optimize quicksort.

### 3-way quicksort

#### Definition

3-way quicksort splits the elements into three parts based on how they compare with the pivot. The idea is based on the solution to the [Dutch national flag problem](https://en.wikipedia.org/wiki/Dutch_national_flag_problem).

#### How it works

Unlike the original quicksort, 3-way quicksort picks a random boundary value $m$ and then splits the sequence into three parts: less than $m$, equal to $m$, and greater than $m$. This achieves the goal of gathering the elements equal to the pivot around it.

#### Properties

3-way quicksort is much faster than the original quicksort on arrays with many repeated values. Its best-case running time is $O(n)$.

#### Implementation

3-way quicksort is very easy to implement. Here is a reference implementation.

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/quick-sort/quick-sort_3.cpp:sort"
    ```

=== "Python[^ref2]"
    ```python
    --8<-- "docs/basic/code/quick-sort/quick-sort_3.py:sort"
    ```

### Introsort

#### Definition

Introsort (introspective sort)[^ref4] combines quicksort with [heap sort](./heap-sort.md). It was invented by David Musser in 1997. Introsort is really an optimization of quicksort that guarantees a worst-case running time of $O(n\log n)$.

#### Properties

Introsort limits the recursion depth of quicksort's partitioning, usually to $2\lfloor \log_2n \rfloor$[^ref5]. When the limit is exceeded, it switches to heap sort. This keeps quicksort's good memory locality while preventing it from degrading to $O(n^2)$ in bad cases.

#### Implementation

Since June 2000, the `sort()` function in `stl_algo.h` of the SGI C++ STL has used introsort.

## Finding the element at ascending index k in linear time

In the code below, the element at ascending index $k$ is the number at position $k$ (counting from 0) when the sequence is sorted in ascending order.

The simplest way to find the element at ascending index $k$ (the k-th order statistic) is to sort first and then read the element at position $k$. This takes $O(n\log n)$ time, which is wasteful for this problem.

We can solve it with the idea behind quicksort. Look at quicksort's partition step: after the "partition", the sequence $A_{p} \cdots A_{r}$ has been split into $A_{p} \cdots A_{q}$ and $A_{q+1} \cdots A_{r}$. Now compare the number of elements on the left ($q - p + 1$) with $k$ to decide whether to recurse only on the left side or only on the right side.

Just like quicksort, the running time depends on the boundary value chosen at each partition. If the boundary value is chosen randomly, one can prove that the expected running time is $O(n)$.

???+ note "Reference implementation"
    ```cpp
    --8<-- "docs/basic/code/quick-sort/quick-sort_4.cpp:sort"
    ```

### Median of medians

Median of medians gives a deterministic way to choose the boundary value during partitioning, so that the algorithm for "finding the element at ascending index $k$" runs in linear time even in the worst case.

The algorithm works as follows:

1.  Split the sequence into $\lceil n/5\rceil$ groups of at most five elements each, keeping the last group even if it has fewer than five;
2.  Sort each group and take its median; for groups of even length, always take the lower median;
3.  Recursively select the median of these medians as the pivot, do a 3-way partition into less than, equal to and greater than the pivot, and recurse only into the strictly-less or strictly-greater part that contains the target.

#### Proof of the time complexity

Let $g=\lceil n/5\rceil$ be the number of groups. On each side of the pivot (counting ties), there are at least $\lfloor g/2\rfloor$ group medians. Leaving out the last group, each full group contributes at least three elements that are not greater than (or not less than) the pivot. So each side has at least $3n/10-O(1)$ such elements, and both the strictly-less and strictly-greater parts have size at most $7n/10+O(1)$. The equal part is not recursed into. Grouping, finding the group medians and partitioning take $O(n)$ in total. Putting this together, we get the inequality:

$$
T(n)\le T(\lceil n/5\rceil)+T(7n/10+O(1))+O(n).
$$

Pick fixed constants $a,b$ such that the two recursive sizes on the right add up to at most $9n/10+a$, and the non-recursive cost is at most $bn$. When $n\ge20a$, that sum is at most $19n/20$. Under the induction hypothesis $T(m)\le cm$, it is enough to choose $c\ge20b$ and make $c$ larger to cover the finitely many base cases. Then $T(n)\le19cn/20+bn\le cn$. So the worst-case running time is $O(n)$.

## References and notes

[^ref1]: [The locality principle in the C++ performance juicer - I'm Root lee !](http://irootlee.com/juicer_locality/)

[^ref2]: [Algorithm Implementation/Sorting/Quicksort - Wikibooks (Chinese)](https://zh.wikibooks.org/wiki/%E7%AE%97%E6%B3%95%E5%AE%9E%E7%8E%B0/%E6%8E%92%E5%BA%8F/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)

[^ref3]: [Three kinds of quicksort and optimizations of quicksort](https://blog.csdn.net/insistGoGo/article/details/7785038)

[^ref4]: [introsort](https://en.wikipedia.org/wiki/Introsort)

[^ref5]: For example, [libstdc++ 14.2.0: `__introsort_loop` and `__sort`](https://github.com/gcc-mirror/gcc/blob/releases/gcc-14.2.0/libstdc%2B%2B-v3/include/bits/stl_algo.h#L1876-L1908). In fact, limiting the depth to $O(\log n)$ and switching to heap sort when the limit is reached is enough to guarantee a total running time of $O(n\log n)$.
