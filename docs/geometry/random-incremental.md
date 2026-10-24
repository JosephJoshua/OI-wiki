author: Ir1d, TianyiQ, GWBailang553

## Introduction

The randomized incremental algorithm is an important technique in computational geometry. It needs little theory, has low time complexity, and applies to a wide range of problems.

The idea of the incremental algorithm is similar to ordinary mathematical induction: it reduces a problem to a subproblem that is exactly one size smaller, solves the subproblem, and then adds the current object. As a recurrence:

$$
T(n)=T(n-1)+g(n)
$$

The incremental method is simple and can be used in many geometry problems.

It is often combined with randomization, which gives the randomized incremental method.

The idea of the randomized incremental method is: each time a new object is added, if it changes the answer, recompute the answer locally. So the method usually requires that it is easy to quickly tell whether adding an element changes the answer, and that, in a random order, the expected number of times the answer changes is small.

The randomized incremental method is often used for the [smallest enclosing circle](smallest-enclosing-circle.md) problem. It can also be used for half-space intersection, higher-dimensional convex hulls, randomized Delaunay triangulation, and so on.

## Exercises

[Smallest enclosing circle](https://www.luogu.com.cn/problem/P1742)

[HNOI2012 Archery](https://www.luogu.com.cn/problem/P3222)

[CodeForces 442E](https://codeforces.com/problemset/problem/442/E)

## References and further reading

[Randomized incremental algorithms - Xie Yilun](https://github.com/hzwer/shareOI/blob/master/%E8%AE%A1%E7%AE%97%E5%87%A0%E4%BD%95/%E9%9A%8F%E6%9C%BA%E5%A2%9E%E9%87%8F%E7%AE%97%E6%B3%95_%E8%A7%A3%E8%BD%B6%E4%BC%A6.pdf)

<https://www.cnblogs.com/aininot260/p/9635757.html>

<https://blog.csdn.net/u014609452/article/details/62039612>

[Randomized Delaunay triangulation](https://zhuanlan.zhihu.com/p/364390356)
