author: Ir1d, Anguei, hsfzLZH1

## Definition

A **system of difference constraints** is a special system of linear inequalities in $n$ variables. It has $n$ variables $x_1,x_2,\dots,x_n$ and $m$ constraints. Each constraint is a difference of two of the variables, of the form $x_i-x_j\leq c_k$, where $1 \leq i, j \leq n, i \neq j, 1 \leq k \leq m$ and $c_k$ is a constant (it can be non-negative or negative). The task is to find a solution $x_1=a_1,x_2=a_2,\dots,x_n=a_n$ that satisfies all constraints, or to report that there is none.

Each constraint $x_i-x_j\leq c_k$ can be rewritten as $x_i\leq x_j+c_k$, which looks very much like the triangle inequality $dist[y]\leq dist[x]+z$ in single-source shortest paths. So we can treat each variable $x_i$ as a vertex of a graph, and for each constraint $x_i-x_j\leq c_k$ add a directed edge of length $c_k$ from vertex $j$ to vertex $i$.

Note that if $\{a_1,a_2,\dots,a_n\}$ is a solution of the system, then for any constant $d$, $\{a_1+d,a_2+d,\dots,a_n+d\}$ is clearly also a solution, because $d$ cancels out in each difference.

## Process

Set $dist[0]=0$ and add an edge of weight $0$ from vertex 0 to every vertex, then run single-source shortest paths. If the graph has a negative cycle, the system has no solution; otherwise, $x_i=dist[i]$ is a solution.

## Properties

We usually use Bellman–Ford or queue-optimized Bellman–Ford (commonly called SPFA, which runs fast on some random graphs) to check for negative cycles. The worst-case time complexity is $O(nm)$.

## Common transformation tricks

### Example problem [Luogu P1993 Little K's Farm](https://www.luogu.com.cn/problem/P1993)

Problem summary: solve a system of difference constraints with $m$ constraints, each of the form $x_a-x_b\geq c_k$, $x_a-x_b\leq c_k$ or $x_a=x_b$, and decide whether the system has a solution.

|         Constraint         |                      Rewritten                     |               Edges              |
| :----------------: | :-----------------------------------------: | :---------------------------: |
| $x_a - x_b \geq c$ |             $x_b - x_a \leq -c$             |        `add(a, b, -c);`       |
| $x_a - x_b \leq c$ |              $x_a - x_b \leq c$             |        `add(b, a, c);`        |
|     $x_a = x_b$    | $x_a - x_b \leq 0, \space x_b - x_a \leq 0$ | `add(b, a, 0), add(a, b, 0);` |

Run a negative cycle check. If there is no negative cycle, output `Yes`; otherwise output `No`.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/diff-constraints/diff-constraints_1.cpp"
    ```

### Example problem [P4926\[1007\] The Multiple-Kill Measurer](https://www.luogu.com.cn/problem/P4926)

Ignoring binary search and the other parts, here we only discuss how to solve a system of constraints of the form $\frac{x_i}{x_j}\leq c_k$.

Taking the $\log$ of each $x_i,x_j$ and $c_k$ turns multiplication into addition: $\log x_i-\log x_j \leq \log c_k$. This can then be solved with difference constraints.

## Negative cycle detection with Bellman–Ford

Below is code that uses the Bellman–Ford algorithm to check whether the graph has a negative cycle. Make sure the graph is connected before calling it.

???+ note "Implementation"
    === "C++"
        ```cpp
        bool Bellman_Ford() {
          for (int i = 0; i < n; i++) {
            bool jud = false;
            for (int j = 1; j <= n; j++)
              for (int k = h[j]; ~k; k = nxt[k])
                if (dist[j] > dist[p[k]] + w[k])
                  dist[j] = dist[p[k]] + w[k], jud = true;
            if (!jud) break;
          }
          for (int i = 1; i <= n; i++)
            for (int j = h[i]; ~j; j = nxt[j])
              if (dist[i] > dist[p[j]] + w[j]) return false;
          return true;
        }
        ```
    
    === "Python"
        ```python
        def Bellman_Ford():
            for i in range(0, n):
                jud = False
                for j in range(1, n + 1):
                    while ~k:
                        k = h[j]
                        if dist[j] > dist[p[k]] + w[k]:
                            dist[j] = dist[p[k]] + w[k]
                            jud = True
                        k = nxt[k]
                if jud == False:
                    break
            for i in range(1, n + 1):
                while ~j:
                    j = h[i]
                    if dist[i] > dist[p[j]] + w[j]:
                        return False
                    j = nxt[j]
            return True
        ```

## Exercises

[Usaco2006 Dec Wormholes](https://loj.ac/problem/10085)

[SCOI2011 Candy](https://loj.ac/problem/2436)

[POJ 1364 King](http://poj.org/problem?id=1364)

[POJ 2983 Is the Information Reliable?](http://poj.org/problem?id=2983)
