author: chu-yuehan

SAT is short for the satisfiability problem. Its general form is the k-satisfiability problem, or k-SAT for short. For $k>2$ the problem is NP-complete, so we only study the case $k=2$.

## Definition

Put simply, in 2-SAT you are given $n$ Boolean clauses. Each clause involves two variables, for example $a \vee b$, which means at least one of $a$ and $b$ must hold. You need to decide whether some assignment satisfies them all. There may be many valid assignments; problems usually ask for just one. Also, $\neg a$ means the negation of $a$.

## Approach

???+ example "[Luogu P4782 [Template] 2-SAT](https://www.luogu.com.cn/problem/P4782)"
    There are $n$ Boolean variables $x_1\sim x_n$ and $m$ conditions to satisfy. Each condition has the form "$x_i$ is `true`/`false` or $x_j$ is `true`/`false`". For example, "$x_1$ is true or $x_3$ is false", or "$x_7$ is false or $x_2$ is false".
    
    The goal of 2-SAT is to assign a value to every variable so that all conditions are satisfied.

We describe the problem with Boolean clauses. Let $a$ mean "$x_a$ is true" (so $\neg a$ means "$x_a$ is false"). Suppose someone's requirement is $a$ or $b$, that is, $(a \vee b)$ (at least one of $a, b$ holds). We build a directed graph on these variables: each of "$a$ holds" and "$a$ does not hold" is a vertex. We add the edges $\neg a\to b$ and $\neg b\to a$, meaning that if $a$ is **false**, then $b$ **must be true**; likewise, if $b$ is **false**, then $a$ **must be true**. Once the graph is built, we can solve 2-SAT with an SCC condensation algorithm.

|         Clause         |                Edges               |
| :----------------: | :-----------------------------: |
|   $\neg a \vee b$  | $a \to b$ and $\neg b \to \neg a$ |
|     $a \vee b$     | $\neg a \to b$ and $\neg b \to a$ |
| $\neg a\vee\neg b$ | $a \to \neg b$ and $b \to \neg a$ |

Many 2-SAT problems come down to finding relations like "if $a$ is **false**, then $b$ is **true**".

## Solving

Think about what it means for two vertices to be in the same strongly connected component. From the logical meaning of the edges above: if two vertices are in the same SCC, then the conditions they stand for are **either both satisfied or both unsatisfied**.

After building the graph, we use [Tarjan's algorithm to find SCCs](./scc.md). For every Boolean variable $a$, we check whether the vertex for "$a$ holds" and the vertex for "$a$ does not hold" are in the same SCC (one condition cannot be both satisfied and unsatisfied). If this happens for any variable, there is no solution; otherwise a solution exists.

To output an assignment, we decide each variable's value from the topological order of the graph. If $x$ comes after $\neg x$ in topological order, set $x$ to true. With Tarjan's condensation, this means: set $x$ to true when the SCC index of $x$ is smaller than that of $\neg x$. The reason is that Tarjan's algorithm uses a stack. A component that is later in topological order is reached later in the search, so it is popped from the stack and condensed earlier and gets a smaller index. So the SCC indices produced by Tarjan's algorithm form a **reverse topological order**.

The algorithm traverses the whole graph once. Since $n$ and $m$ are of the same order in this graph, computing the answer takes $O(n)$, so the total complexity is $O(n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_3.cpp"
    ```

## Example problems

### Example problem 1

???+ example "[HDU3062 Party](https://acm.hdu.edu.cn/showproblem.php?pid=3062)"
    $n$ couples are invited to a party. Because of limited space, only one person from each couple can attend. Among the $2n$ people, some pairs have serious conflicts (a husband and wife never conflict), and two people in conflict will never be at the party together. Is it possible for $n$ people to attend at the same time?

Following the analysis above, if the husband of couple $a_1$ conflicts with the wife of couple $a_2$, we add an edge from the husband of $a_1$ to the husband of $a_2$, and an edge from the wife of $a_2$ to the wife of $a_1$. Then condense SCCs, color them, and check.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_1.cpp"
    ```

### Example problem 2

???+ example "[2018-2019 ACM-ICPC Asia Seoul Regional K TV Show Game](https://codeforces.com/gym/101987/problem/K)"
    There are $k$ lamps. Each lamp is red or blue, but the colors are unknown at the start. There are $n$ people; each picks three lamps and guesses their colors. A person who guesses at least two of the colors correctly wins a prize. Decide whether there is a coloring of the lamps such that everyone wins a prize, and if so, output one such coloring.

From [Wu Yu, "Solving 2-SAT Problems via Symmetry"](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2003%E8%AE%BA%E6%96%87%E9%9B%86/%E4%BC%8D%E6%98%B1--%E7%94%B1%E5%AF%B9%E7%A7%B0%E6%80%A7%E8%A7%A32-SAT%E9%97%AE%E9%A2%98/%E4%BC%8D%E6%98%B1.ppt), we get the following: to output a valid solution of a 2-SAT problem, we only need to choose and delete vertices bottom-up on the DAG obtained by Tarjan's condensation.

There are two ways to implement this. One is to build the reverse graph of the DAG and topologically sort it. The other uses a property of Tarjan's condensation: the smaller a vertex's component index, the closer it is to the leaves. So we can choose vertices with smaller component indices first.

Below is code for the second method.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_2.cpp"
    ```

## Exercises

-   [Luogu P5782 Peace Committee](https://www.luogu.com.cn/problem/P5782)
-   [POJ3683 Priest John's Busiest Day](http://poj.org/problem?id=3683)
