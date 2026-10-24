The Josephus problem has a long history, and its solutions have kept improving. Still, there is no extremely efficient algorithm (within log time) for it yet.

## Problem statement

> n people are numbered $0,1,\cdots, n-1$ and stand in a circle counterclockwise. Starting from person $0$, each time count $k$ people counterclockwise from the current person, and remove that person. Who is the last one left?

This classic problem was posed by Josephus in the 1st century AD, although he only considered the case $k=2$. Today we can solve it with many efficient algorithms.

## How it works

### Naive algorithm

The most naive algorithm is plain simulation. Use a circular linked list to simulate the removals, and repeat $n-1$ times to get the answer. The complexity is $\Theta (n^2)$.

### Simple optimization

Finding the next person can be sped up with a segment tree. Specifically, build a segment tree over $0,1,\cdots, n-1$ that records how many people remain in each range. Finding the current person's position and the $k$-th person after it can be done by binary search on the segment tree.

### Linear algorithm

Let $J_{n,k}$ be the answer to the Josephus problem with parameters $n,k$. We have the recurrence

$$
J_{n,k}=(J_{n-1,k}+k)\bmod n
$$

This is easy to derive. Count $k$ people starting from $0$. After person $k-1$ is removed, $n-1$ people remain. Compute the answer for those $n-1$ people, then add the relative shift $k$ to get the real answer. This algorithm clearly runs in $\Theta (n)$ time.

???+ note "Implementation"
    ```cpp
    int josephus(int n, int k) {
      int res = 0;
      for (int i = 1; i <= n; ++i) res = (res + k) % i;
      return res;
    }
    ```

### Logarithmic algorithm

When $k$ is small and $n$ is large, there is also an algorithm with complexity $\Theta (k\log n)$.

Since we remove one person every $k$ steps, within one round we can remove $\left\lfloor\frac{n}{k}\right\rfloor$ people, leaving $n-\left\lfloor\frac{n}{k}\right\rfloor$ people. At that point we are at the position of person $\left\lfloor\frac{n}{k}\right\rfloor\cdot k$, which you can see equals $n-n\bmod k$. So we recurse, and after computing, we restore the relative position. Restoring works like this: each removal deletes the $k$-th person counted, and their numbers are inherited one by one by the people after them. That is, when computing on the circle of $n-\left\lfloor\frac{n}{k}\right\rfloor$ people, one position is lost for every $k$ people. So if the result is less than $0$, take it modulo the $n$ of the $n$-person circle in which the multiples of $k$ have not yet been removed; if the result is at least $0$, we can just multiply by $\frac{k}{k-1}$. This gives the following algorithm:

???+ note "Implementation"
    ```cpp
    int josephus(int n, int k) {
      if (n == 1) return 0;
      if (k == 1) return n - 1;
      if (k > n) return (josephus(n - 1, k) + k) % n;  // Linear algorithm
      int res = josephus(n - n / k, k);
      res -= n % k;
      if (res < 0)
        res += n;  // mod n
      else
        res += res / (k - 1);  // Restore the position
      return res;
    }
    ```

We can prove that this algorithm runs in $\Theta (k\log n)$. Let the number of recursive calls be $x$. Each time, the problem size becomes roughly $\displaystyle n\left(1-\frac{1}{k}\right)$, so

$$
n\left(1-\frac{1}{k}\right)^x=1
$$

Solving this equation gives

$$
x=-\frac{\ln n}{\ln\left(1-\frac{1}{k}\right)}
$$

Now we prove that the complexity of the algorithm is $\Theta (k\log n)$.

???+ note "Proof"
    Consider $\displaystyle \lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)$. We have
    
    $$
    \begin{aligned}
    \lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)&=\lim _{k \rightarrow \infty} \frac{\log \left(1-\frac{1}{k}\right)}{1 / k}\\
    &=\lim _{k \rightarrow \infty} \frac{\frac{\mathrm d}{\mathrm d k} \log \left(1-\frac{1}{k}\right)}{\frac{\mathrm d}{\mathrm d k}\left(\frac{1}{k}\right)}\\
    &=\lim _{k \rightarrow \infty} \frac{\frac{1}{k^{2}\left(1-\frac{1}{k}\right)}}{-\frac{1}{k^{2}}}\\
    &=\lim _{k \rightarrow \infty}-\frac{k}{k-1}\\
    &=-\lim _{k \rightarrow \infty} \frac{1}{1-\frac{1}{k}}\\
    &=-1
    \end{aligned}
    $$
    
    So $x \sim k \ln n, k\to \infty$, that is, $-\dfrac{\ln n}{\ln\left(1-\frac{1}{k}\right)}= \Theta (k\log n)$

**This page is mainly translated from the article [Задача Иосифа](https://e-maxx.ru/algo/joseph_problem) and its English translation [Josephus Problem](https://cp-algorithms.com/others/josephus_problem.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
