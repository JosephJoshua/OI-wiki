author: linehk, persdre

Time complexity and space complexity are the two main ways to measure how efficient an algorithm is.

## Number of basic operations

The same algorithm runs at different speeds on different computers. Its actual running time is also hard to work out in theory, and measuring it in practice is a hassle. So instead of the real running time, we usually look at how many basic operations the algorithm needs to perform.

On an ordinary computer, things like addition, subtraction, multiplication and division, reading a variable (of a primitive data type; the same applies below), and assigning a value to a variable can all be treated as basic operations.

Counting or estimating the number of basic operations gives us a way to judge how long an algorithm takes.

## Time complexity

### Definition

To judge how fast an algorithm is, we must take the size of the input into account. The input size usually means things like how many numbers are given in the input, or how many vertices and edges the input graph has. In general, the larger the input, the longer the algorithm takes. In competitive programming, what matters most when we judge an algorithm is not how long it takes on one particular input size, but how its running time grows as the input size grows. This growth trend is called **time complexity**.

### Introduction

There are a few main reasons to look at how the running time grows with the input size:

1.  A modern computer can perform hundreds of millions of basic operations per second, or even more, so the inputs we deal with are usually large. Suppose algorithm A takes $100n$ time on an input of size $n$ and algorithm B takes $n^2$. When the input size is less than $100$, B is faster. But in one second, A can handle inputs of size in the millions, while B can only handle inputs of size in the tens of thousands. The more time the algorithm is allowed to run, the more obvious this effect becomes. The time complexity affects how large an input we can handle far more than the running time at any single input size does;
2.  We use the number of basic operations to stand for running time, but different basic operations really take different amounts of time. For example, addition and subtraction are much faster than division. Time complexity ignores the difference between kinds of basic operations, and also the difference between doing one basic operation and doing ten. This removes the effect of basic operations having different costs.

Of course, the running time is not fully decided by the input size; it also depends on what the input actually is. So there are several kinds of time complexity, for example:

1.  Worst-case time complexity: for each input size, the time complexity of the input that takes the longest. In competitive programming, the input can be anything within the given limits. To make sure the algorithm passes every possible input within those limits, we usually look at the worst-case time complexity;
2.  Average (expected) time complexity: for each input size, the complexity of the average running time over all possible inputs (more precisely, the complexity of the expected running time under a given probability distribution of inputs; the uniform average is a common special case).

"How the running time grows with the input size" is a vague idea. To describe time complexity formally, we use **asymptotic notation**, which is introduced below.

## Definitions of asymptotic notation

Asymptotic notation is a standard way to describe the order of growth of a function. Simply put, asymptotic notation ignores the slower-growing parts of a function and the coefficients of each term (in time complexity analysis, these coefficients are usually called "constants"). It keeps only the important part that shows how the function grows.

A simple way to remember them: notations that include equality (non-strict) use uppercase letters, and notations that exclude equality (strict) use lowercase letters. "Equal to" is $\Theta$, "less than" is $O$, and "greater than" is $\Omega$. Big $O$ and little $o$ were originally the Greek letter Omicron, but since they look the same, you can also think of them as the Latin letters uppercase $O$ and lowercase $o$.

In English, the roots "-micro-" and "-mega-" are often used for 10 to the power of -6 (one millionth) and 10 to the power of 6 (one million). They also mean "small" and "large". "Small" and "large" are also what the Greek letters Omicron and Omega usually stand for.

### Big Θ notation

For functions $f(n)$ and $g(n)$, $f(n)=\Theta(g(n))$ if and only if $\exists c_1,c_2,n_0>0$ such that $\forall n \ge n_0, 0\le c_1\cdot g(n)\le f(n) \le c_2\cdot g(n)$.

In other words, if $f(n)=\Theta(g(n))$, then we can find two positive numbers $c_1, c_2$ such that $f(n)$ is sandwiched between $c_1\cdot g(n)$ and $c_2\cdot g(n)$.

For example, $3n^2+5n-3=\Theta(n^2)$, where $c_1, c_2, n_0$ can be $2, 4, 100$ respectively. Also, $n\sqrt {n} + n{\log^5 n} + m{\log m} +nm=\Theta(n\sqrt {n} + m{\log m} + nm)$. This is because $\log^5 n=o(\sqrt n)$, so there is a large enough $n_0$ beyond which the dropped term is at most $n\sqrt n$.

### Big O notation

$\Theta$ notation gives both an upper bound and a lower bound of a function. If we only know an asymptotic upper bound of a function but not its asymptotic lower bound, we can use $O$ notation. $f(n)=O(g(n))$ if and only if $\exists c,n_0>0$ such that $\forall n \ge n_0,0\le f(n)\le c\cdot g(n)$.

$O$ notation is the one most often used when studying time complexity, because we usually care about an upper bound on a program's running time, not a lower bound.

Note that "upper bound" and "lower bound" here describe how a function grows, not the algorithm itself. An upper bound on an algorithm's running time corresponds to its "worst-case time complexity", not to big $O$ notation. So it is perfectly fine to use $\Theta$ notation for the worst-case time complexity. In fact, $\Theta$ is even more precise than $O$. There are two main reasons people use $O$ notation: first, sometimes we can only prove an upper bound on the time complexity but not a lower bound (this usually happens with more complicated algorithms and complexity analyses); second, $O$ is easier to type on a computer.

### Big Ω notation

Similarly, we use $\Omega$ notation to describe an asymptotic lower bound of a function. $f(n)=\Omega(g(n))$ if and only if $\exists c,n_0>0$ such that $\forall n \ge n_0,0\le c\cdot g(n)\le f(n)$.

### Little o notation

If $O$ notation is like "less than or equal to", then $o$ notation is like "less than".

Little $o$ notation is widely used in mathematical analysis. The Taylor expansion of a function at a point has a Peano remainder term, and little $o$ is used there to mean "strictly smaller", which allows asymptotic analysis with equivalent infinitesimals.

$f(n)=o(g(n))$ if and only if for every given positive number $c$, $\exists n_0$ such that $\forall n \ge n_0,0\le f(n)< c\cdot g(n)$.

### Little ω notation

If $\Omega$ notation is like "greater than or equal to", then $\omega$ notation is like "greater than".

$f(n)=\omega(g(n))$ if and only if for every given positive number $c$, $\exists n_0$ such that $\forall n \ge n_0,0\le c\cdot g(n)< f(n)$.

![](images/order.svg)

### Common properties

-   $f(n) = \Theta(g(n))\iff f(n)=O(g(n))\land f(n)=\Omega(g(n))$.
-   $f_1(n) + f_2(n) = O(\max(f_1(n), f_2(n)))$.
-   $f_1(n) \times f_2(n) = O(f_1(n) \times f_2(n))$.
-   $\forall a>1, \log_a{n} = O(\log_2 n)$. By the change-of-base formula, logarithms with any fixed real base $a>1$ all grow at the same rate, so the base of a logarithm is usually left out in asymptotic time complexity.

## Simple examples of computing time complexity

### `for` loops

=== "C++"
    ```cpp
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < m; ++k) {
          std::cout << "hello world\n";
        }
      }
    }
    ```

=== "Python"
    ```python
    n = int(input())
    m = int(input())
    for i in range(0, n):
        for j in range(0, n):
            for k in range(0, m):
                print("hello world")
    ```

=== "Java"
    ```java
    int n, m;
    n = input.nextInt();
    m = input.nextInt();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                System.out.println("hello world");
            }
        }
    }
    ```

If we take the values of the input numbers $n$ and $m$ as the input size, then the time complexity of the code above is $\Theta(n^2m)$.

### DFS

When we run a [DFS](../graph/dfs.md) on a [connected graph](../graph/concept.md#连通) with $n$ vertices and $m$ edges stored as an adjacency list, every vertex and every edge is visited only a constant number of times, so the complexity is $\Theta(n+m)$.

## Which quantities are constants

When we perform some number of operations, how do we decide whether that number affects the time complexity? For example:

=== "C++"
    ```cpp
    constexpr int N = 100000;
    for (int i = 0; i < N; ++i) {
      std::cout << "hello world\n";
    }
    ```

=== "Python"
    ```python
    N = 100000
    for i in range(0, N):
        print("hello world")
    ```

=== "Java"
    ```java
    final int N = 100000;
    for (int i = 0; i < N; ++i) {
        System.out.println("hello world");
    }
    ```

If the value of $N$ is not considered part of the input size, then the time complexity of this code is $O(1)$.

When computing time complexity, it is important to decide which variables count as the input size. Every quantity that does not depend on the input size is treated as a constant, and can be treated as $1$ when computing the complexity.

Note that in theoretical discussions of time complexity, a basic assumption is that "the algorithm can solve problems of any size" (of course, in practice, time and memory are limited, so problems that are too large cannot be solved). For this reason, being able to solve a problem with a bounded input size in constant time (for example, by precomputing the answer for every possible input within the limits) does not make an algorithm's time complexity $O(1)$.

## Master theorem

We can use the master theorem to quickly find the complexity of a recursive algorithm. Assume $a\ge1$ and $b>1$ are constants, $f$ is non-negative, and $T(1)=\Theta(1)$. To keep things simple, we also assume below that $n=b^L$, where $L$ is a non-negative integer. The recurrence is:

$$
T(n) = a T\left(\frac{n}{b}\right)+f(n),\qquad \forall n=b^L,\ L\ge1.
$$

Then

$$
T(n) = \begin{cases}
    \Theta(n^{\log_b a}), & f(n) = O(n^{\log_b (a)-\epsilon}),\epsilon > 0, \\
    \Theta(f(n)), & f(n) = \Omega(n^{\log_b (a)+\epsilon}),\epsilon\ge 0, \\
    \Theta(n^{\log_b a}\log^{k+1} n), & f(n)=\Theta(n^{\log_b a}\log^k n),k\ge 0.
    \end{cases}
$$

Note that the second case also requires the regularity condition: there must be a constant $0<c<1$ such that $a f(n/b) \leq c f(n)$ for all large enough $n$.

The idea of the proof is this: a problem of size $n$ is split into $a$ problems of size $n/b$, and then the results are merged level by level until we reach the top level. Each time subproblems are merged, it costs $f(n)$ time.

??? note "Proof"
    Following the idea above, here is the detailed proof:
    
    At level $0$ (the top level), merging the subproblems costs $f(n)$ time.
    
    At level $1$ (the subproblems from the first split), there are $a$ subproblems, and merging each one costs $f\left(\dfrac{n}{b}\right)$ time, so merging costs $a f\left(\dfrac{n}{b}\right)$ time in total.
    
    Continuing level by level, we can draw the following recursion tree:
    
    ![](./images/master-theorem-proof.svg)
    
    The tree ends at level $L=\log_b n$ and has $a^L=n^{\log_b a}$ leaves. The non-leaf levels are numbered $0,\ldots,L-1$, so $T(n) = \Theta(n^{\log_b a}) + g(n)$, where $g(n) = \sum_{j = 0}^{L-1} a^{j} f(n / b^{j})$.
    
    For the first case: $f(n) = O(n^{\log_b a-\epsilon})$, so $g(n) = O(n^{\log_b a})$.
    
    For the second case: first, the cost of the root alone gives $T(n)=\Omega(f(n))$. By the regularity condition, while the subproblems are still large enough, the total cost of level $j$ is at most $c^j f(n)$, and the costs of these levels add up to $O(f(n))$. The remaining constant number of bottom levels and the leaves cost $O(n^{\log_b a})=O(f(n))$ in total, so $T(n)=\Theta(f(n))$.
    
    For the third case: let $p=\log_b a$. For subproblems that are large enough, the total cost of level $j$ is $\Theta(n^p(L-j)^k)$, where $k\ge0$ is a fixed constant. Pick a fixed $r_0\ge1$ such that $b^{r_0}$ reaches that size. Since $\sum_{r=r_0}^L r^k=\Theta(L^{k+1})$, these levels cost $\Theta(n^p\log^{k+1}n)$ in total. The remaining constant number of bottom levels and the leaves cost $O(n^p)$ in total. Adding them up gives the result.

Here are a few examples of how to use the master theorem.

1.  $T(n) = 2T\left(\dfrac{n}{2}\right) + 1$. Then $a=2, b=2, {\log_2 2} = 1$, so $\epsilon$ can be any value in $(0, 1]$. This matches the first case, so $T(n) = \Theta(n)$;

2.  $T(n) = T\left(\dfrac{n}{2}\right) + n$. Then $a=1, b=2, {\log_2 1} = 0$, so $\epsilon$ can be any value in $(0, 1]$. This matches the second case, so $T(n) = \Theta(n)$;

3.  $T(n) = T\left(\dfrac{n}{2}\right) + {\log n}$. Then $a=1, b=2, {\log_2 1}=0$, so $k$ can be $1$. This matches the third case, so $T(n) = \Theta(\log^2 n)$;

4.  $T(n) = T\left(\dfrac{n}{2}\right) + 1$. Then $a=1, b=2, {\log_2 1} = 0$, so $k$ can be $0$. This matches the third case, so $T(n) = \Theta(\log n)$.

## Amortized complexity

See [Amortized complexity](./amortized-analysis.md) for details.

## Space complexity

In the same way, the trend of how much memory an algorithm uses as the input size grows is measured by **space complexity**.

## Computational complexity

This page introduces complexity mainly from the point of view of algorithm analysis. If you are interested, you can learn more in [Computational complexity](../misc/cc-basic.md).
