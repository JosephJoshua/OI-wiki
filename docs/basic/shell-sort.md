This page gives a short introduction to Shell sort.

## Definition

Shell sort, also called the diminishing increment sort, is an improved version of [insertion sort](./insertion-sort.md). It is named after its inventor, Donald Shell.

## How it works

Shell sort compares and moves elements that are not next to each other:

1.  Split the sequence into several subsequences (the elements of each subsequence are the same distance apart in the original array);
2.  Sort each of these subsequences with insertion sort;
3.  Shrink the gap between elements in each subsequence, and repeat the steps above until the gap becomes $1$.

To make the analysis easier, here is the pseudocode for one pass of insertion sort with gap $h$, written as $\text{InsertionSort}(h)$. The array $A$ is indexed from $1$ to $n$, and $v$ holds the value currently being inserted. Shell sort calls this procedure with gaps from largest to smallest.

$$
\begin{array}{ll}
1 & \textbf{for } j\gets h+1 \textbf{ to } n\\
2 & \qquad v\gets A_j\\
3 & \qquad i\gets j-h\\
4 & \qquad \textbf{while } i\ge 1 \textbf{ and } A_i>v\\
5 & \qquad\qquad A_{i+h}\gets A_i\\
6 & \qquad\qquad i\gets i-h\\
7 & \qquad A_{i+h}\gets v
\end{array}
$$

## Properties

### Stability

Shell sort is not stable.

### Time complexity

The best-case running time of Shell sort depends on the gap sequence and on whether the algorithm can stop early. The $3h+1$ implementation given below, which has no early exit, runs in $\Theta(n\log n)$ time in the best case.

The average and worst-case time complexity of Shell sort depend on the choice of gap sequence. Let the gap sequence be $H$. Below are two classic choices of $H$; both bring the running time down to $o(n^2)$.

???+ note "Proposition 1"
    If the gap sequence is $H= \{ 2^k-1\mid k=1,2,\ldots,\lfloor\log_2 n\rfloor \}$ (used from largest to smallest), then Shell sort runs in $O(n^{3/2})$ time.

???+ note "Proposition 2"
    If the gap sequence is $H= \{ k=2^p\cdot 3^q\mid p,q\in \mathbb N,k\le n \}$ (used from largest to smallest), then Shell sort runs in $O(n\log^2 n)$ time.

To prove these two propositions, we first state and prove an important theorem. It captures the key feature of Shell sort.

???+ note "Theorem 1"
    Once the program has run $\text{InsertionSort}(h)$, no matter how $\text{InsertionSort}$ is called afterwards or how the array $A$ changes, each of the following subsequences stays sorted:
    
    $$
    \begin{array}{c}
    A_1,A_{1+h},A_{1+2h},\ldots \\
    A_2,A_{2+h},A_{2+2h},\ldots \\
    \vdots \\
    A_h,A_{h+h},A_{h+2h},\ldots
    \end{array}
    $$

Next, we prove Theorem 1.

First, we prove Lemma 1.

???+ note "Lemma 1"
    Let $n,m$ be non-negative integers, $l$ a positive integer, and let $X(x_1,x_2,\ldots,x_{n+l}),Y(y_1,y_2,\ldots,y_{m+l})$ be two arrays satisfying:
    
    $$
    y_1 \le x_{n+1},y_2 \le x_{n+2},\ldots,y_l \le x_{n+l}
    $$
    
    Then after sorting both arrays in ascending order, these inequalities still hold.

??? note "Proof of Lemma 1"
    Let $X'(x'_1,\ldots,x'_{n+l})$ be $X$ after sorting, and $Y'(y'_1,\ldots,y'_{m+l})$ be $Y$ after sorting.
    
    For any $1\le i\le l$, at most $l-i$ elements of $X$ are strictly greater than $x'_{n+i}$. So among the $l$ chosen elements $\{x_{n+1},\ldots,x_{n+l}\}$, at least $i$ are not greater than $x'_{n+i}$. Call them $x_{n+k_1},\ldots,x_{n+k_i}$. Combining this with the original paired inequalities gives:
    
    $$
    y_{k_1}\le x_{n+k_1}\le x'_{n+i},y_{k_2}\le x_{n+k_2}\le x'_{n+i},\ldots,y_{k_i}\le x_{n+k_i}\le x'_{n+i}
    $$
    
    So $x'_{n+i}$ is greater than or equal to at least $i$ elements of $Y$, and hence of $Y'$. It follows that $y'_i\le x'_{n+i}\,(1\le i\le l)$.

Now back to the proof of the theorem. Let the array length be $N$. We only need to show that $\text{InsertionSort}(k)$ preserves an existing $h$-sortedness; then induction on the number of calls finishes the proof. Here $h,k$ are arbitrary positive integers. If $h\ge N$, there are no pairs of elements at distance $h$ to check, so the claim is trivially true. From now on, assume $h<N$.

Let $A$ and $A'$ be the array before and after the call. Before the call, $A_i\le A_{i+h}$ for $1\le i\le N-h$. For each $1\le w\le\min(k,N-h)$, use division with remainder to write

$$
w+h=v+tk,\qquad 1\le v\le k,\quad t\ge0.
$$

Consider the two complete subsequences with gap $k$ that start at indices $w$ and $v$:

$$
Y=(A_w,A_{w+k},A_{w+2k},\ldots),\qquad
X=(A_v,A_{v+k},A_{v+2k},\ldots).
$$

Let $l$ be the number of non-negative integers $j$ with $w+h+jk\le N$. Then $X$ has length $t+l$, and $Y$ has length at least $l$. Because the array was $h$-sorted, the first $l$ terms of $Y$ and the last $l$ terms of $X$ satisfy

$$
y_{j+1}=A_{w+jk}\le A_{w+h+jk}=x_{t+j+1},\qquad 0\le j<l.
$$

$\text{InsertionSort}(k)$ sorts exactly each such complete subsequence in ascending order. By Lemma 1, the paired inequalities still hold after sorting, that is,

$$
A'_{w+jk}\le A'_{w+h+jk},\qquad 0\le j<l.
$$

The lemma still applies even when $v=w$ and the two subsequences are actually the same. Every index $1\le i\le N-h$ can be written uniquely as $i=w+jk$ with $1\le w\le k$ and $j\ge0$, and then $w\le N-h$ must hold. So the argument above covers every $i$, giving $A'_i\le A'_{i+h}$. Hence $h$-sortedness is preserved, which proves Theorem 1.

This theorem is the key reason why Shell sort can be faster with a well-chosen set $H$: throughout the whole process, the subsequences sorted earlier stay sorted, so in later calls the pointer $i$ moves far fewer times.

Next, we single out a number theory lemma and prove it. In the OI community, it became well known because of the problem [Xiao Kai's Puzzle](https://www.luogu.com.cn/problem/P3951). In the analysis of Shell sort, it lets us greatly extend Theorem $1$.

???+ note "Lemma 2"
    If $a,b\ge2$ are coprime integers, then the largest positive integer not in the set $\{ax+by\mid x,y\in \mathbb N \}$ is $ab-a-b$.

??? note "Proof of Lemma 2"
    We prove it in two steps:
    
    -   First, show that the equation $ax+by=ab-a-b$ has no solution where both $x,y$ are non-negative integers:
    
        Without the non-negativity requirement, two solutions are easy to find: $(b-1,-1),(-1,a-1)$.
    
        From the general solution $x=x_0+tb,y=y_0-ta$, it is easy to see that these two solutions are "adjacent" (because $b-1-b=-1$).
    
        As $t$ increases, $x$ increases and $y$ decreases. So if the equation had a non-negative integer solution, it would have to lie between these two solutions. But the two are "adjacent", so there is no solution between them.
    
        Therefore there is no non-negative integer solution.
    -   Next, show that for every integer $c > ab-a-b$, the equation $ax+by=c$ has a non-negative integer solution:
    
        Pick a solution $(x_0,y_0)$ with $0\le x_0 < b$ (the general solution shows this is always possible).
    
        Then:
    
        $$
        by_0=c-ax_0\ge c-a(b-1)>ab-a-b-ab+a=-b
        $$
    
        So $b(y_0+1) > 0$. Since $b>0$, we get $y_0+1>0$, so $y_0\ge 0$.
    
        So $(x_0,y_0)$ is a non-negative integer solution.
    
    This completes the proof.

The next theorem shows how Lemma $2$ extends Theorem $1$.

???+ note "Theorem 2"
    Let $h_{t+1}>h_t>h_{t-1}$ be positive integers. If $\gcd(h_{t+1},h_t)=1$, then after the program has run $\text{InsertionSort}(h_{t+1})$ and $\text{InsertionSort}(h_t)$, running $\text{InsertionSort}(h_{t-1})$ takes $O\left(\dfrac{nh_{t+1}h_t}{h_{t-1}} \right)$ time, and for each $j$, the pointer $i$ moves $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$ times.

??? note "Proof of Theorem 2"
    Below, $A$ denotes the array before calling $\text{InsertionSort}(h_{t-1})$. Fix the outer loop index $j$; the value to insert is $v=A_j$.
    
    For $j\le h_{t+1}h_t$, the number of moves of $i$ is clearly $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$.
    
    So from now on, assume $j>h_{t+1}h_t$.
    
    For any positive integer $k$ with $1\le k\le j-h_{t+1}h_t$, note that $h_{t+1}h_t-h_{t+1}-h_t<h_{t+1}h_t\le j-k\le j-1$.
    
    Since $\gcd(h_{t+1},h_t)=1$, Lemma $2$ tells us there exist non-negative integers $a,b$ such that $ah_{t+1}+bh_t=j-k$.
    
    That is:
    
    $$
    k=j-ah_{t+1}-bh_t
    $$
    
    By Theorem $1$:
    
    $$
    A_{j-bh_t}\le A_{j-(b-1)h_t}\le \ldots\le A_{j-h_t}\le A_j
    $$
    
    and
    
    $$
    A_{j-bh_t-ah_{t+1}}\le A_{j-bh_t-(a-1)h_{t+1}}\le \ldots\le A_{j-bh_t-h_{t+1}}\le A_{j-bh_t}
    $$
    
    Putting these together: $A_k=A_{j-ah_{t+1}-bh_t}\le A_j$.
    
    So for every $1\le k\le j-h_{t+1}h_t$, we have $A_k\le A_j$.
    
    In the already-processed prefix of the subsequence containing $v$, only elements whose original index lies in $(j-h_{t+1}h_t,j)$ can be greater than $v$, and there are at most $\left\lceil\dfrac{h_{t+1}h_t}{h_{t-1}}\right\rceil$ of them. Earlier insertions only sort this prefix of the subsequence. So in the pseudocode above, $i$ decreases by $h_{t-1}$ each step, and after passing these elements it either meets an element not greater than $v$ or runs past the left end of the array, and the while loop exits. The number of moves is $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$.
    
    Having bounded the moves for each $j$, the total time complexity is:
    
    $$
    \sum_{j=h_{t-1}+1}^n{O\left(\frac{h_{t+1}h_t}{h_{t-1}} \right)}=O\left(\frac{nh_{t+1}h_t}{h_{t-1}}\right)
    $$
    
    This completes the proof.

Looking closely at the proof of Theorem $2$, we see that Theorem 1 can be "linearly combined": if $A$ is sorted with gap $h$ and also sorted with gap $k$, then it is also sorted with any gap that is a linear combination of $h$ and $k$ with non-negative coefficients. This "linearity" is exactly what Lemma $2$ guarantees.

With these two theorems, we can prove Propositions $1$ and $2$.

??? note "Proof of Proposition 1"
    Write $H$ as a sequence:
    
    $$
    H(h_1=1,h_2=3,h_3=7,\ldots,h_{\lfloor \log_2 n\rfloor}=2^{\lfloor \log_2 n\rfloor}-1)
    $$
    
    Shell sort runs in this order: $\text{InsertionSort}(h_{\lfloor \log_2 n\rfloor}),\text{InsertionSort}(h_{\lfloor \log_2 n\rfloor-1}),\ldots,\text{InsertionSort}(h_2),\text{InsertionSort}(h_1)$.
    
    Assume $n\ge4$. We analyze the running time in two parts:
    
    -   For the first few gaps with $h_t\ge \sqrt{n}$, clearly $\text{InsertionSort}(h_t)$ takes $O\left(\dfrac{n^2}{h_t} \right)$ time.
    
        Let $k=\min\{t:h_t\ge\sqrt n\}$. Then $h_k=\Theta(\sqrt n)$, and:
    
        $$
        O\left(\frac{n^2}{h_k} \right)=O(n^{3/2})
        $$
    
        For $h_i$ with $i> k$, since $2h_i< h_{i+1}$, we get:
    
        $$
        O\left(\frac{n^2}{h_i} \right)=O(n^{3/2}/2^{i-k})\,(i>k)
        $$
    
        So the total time for gaps at least $\sqrt n$ is:
    
        $$
        \sum_{i=k}^{\lfloor \log_2 n\rfloor}{O(n^{3/2}/2^{i-k})}=O(n^{3/2})
        $$
    -   For the remaining gaps with $h_t< \sqrt{n}$, the first two still take $O(n^{3/2})$. For each later gap $h_t$, Theorem $2$ gives a running time of:
    
        $$
        O\left(\frac{nh_{t+2}h_{t+1}}{h_t} \right)=O\left(\frac{nh_{t+2}\cdot h_{t+2}/2}{h_{t+2}/4} \right)=O(nh_{t+2})
        $$
    
        Using $2h_i < h_{i+1}$ again, the total time for this part is (here $k$ has the same meaning as in the previous case):
    
        $$
        2O(n^{3/2})+\sum_{i=1}^{k-3}{O(nh_{i+1})}=O(n^{3/2})+\sum_{i=1}^{k-3}{O(nh_{k-1}/2^{k-i-3})}=O(n^{3/2})+O(nh_{k-1})=O(n^{3/2})
        $$
    
    Putting it all together, the total time complexity is $O(n^{3/2})$.

??? note "Proof of Proposition 2"
    Note this fact: if $\text{InsertionSort}(2)$ and $\text{InsertionSort}(3)$ have already been run, then since $2\cdot 3-2-3=1$, Theorem $2$ tells us that for each element, only the element right before it can be greater than it; all earlier elements are smaller. So the pointer $i$ needs at most two steps before it exits the while loop. In other words, running $\text{InsertionSort}(1)$ at this point takes only $O(n)$ time.
    
    Going further: if $\text{InsertionSort}(4)$ and $\text{InsertionSort}(6)$ have already been run, consider the subsequence of elements at odd indices and the subsequence of elements at even indices. This is the same as running $\text{InsertionSort}(2)$ and $\text{InsertionSort}(3)$ on each of these two subsequences. So, in the same way, running $\text{InsertionSort}(2)$ now is the same as running $\text{InsertionSort}(1)$ on each of the two subsequences. This takes time proportional to the total length of the two sequences, that is, $O(n)$, to make the array $2$-sorted.
    
    Continuing by induction: if $\text{InsertionSort}(2h)$ and $\text{InsertionSort}(3h)$ have already been run, then running $\text{InsertionSort}(h)$ takes only $O(n)$ time.
    
    Now we analyze the running time in two parts:
    
    -   For gaps with $h_t>n/3$, each $\text{InsertionSort}(h_t)$ takes $O(n^2/h_t)$ time.
    
        Since $n^2/h_t<3n$, each such insertion sort pass takes $O(n)$.
    
        There are $O(\log^2 n)$ such gaps, so this part takes $O(n\log^2 n)$ time.
    -   For gaps with $h_t\le n/3$, since $3h_t\le n$, both $\text{InsertionSort}(2h_t)$ and $\text{InsertionSort}(3h_t)$ have already been run, so $\text{InsertionSort}(h_t)$ takes $O(n)$ time.
    
        Again, there are $O(\log^2 n)$ such gaps, so this part takes $O(n\log^2 n)$ time.
    
    Putting it all together, the total time complexity is $O(n\log^2 n)$.

### Space complexity

Shell sort uses $O(1)$ extra space.

## Implementation

=== "C++[^ref1]"
    ```cpp
    template <typename T>
    void shell_sort(T array[], int length) {
      int h = 1;
      while (h < length / 3) {
        h = 3 * h + 1;
      }
      while (h >= 1) {
        for (int i = h; i < length; i++) {
          for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
            std::swap(array[j], array[j - h]);
          }
        }
        h = h / 3;
      }
    }
    ```

=== "Python"
    ```python
    def shell_sort(array, length):
        h = 1
        while h < length / 3:
            h = int(3 * h + 1)
        while h >= 1:
            for i in range(h, length):
                j = i
                while j >= h and array[j] < array[j - h]:
                    array[j], array[j - h] = array[j - h], array[j]
                    j -= h
            h = int(h / 3)
    ```

## References and notes

[^ref1]: [Shell sort - Wikipedia, the free encyclopedia (Chinese)](https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F)
