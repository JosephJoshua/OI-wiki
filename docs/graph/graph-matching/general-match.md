author: H-J-Granger, accelsao, Ir1d, Early0v0, Henry-ZHR, HeliumOI, AntiLeaf, ShizuhaAki, pukui

## Blossom algorithm

The blossom algorithm (also known as the blossom tree algorithm) solves the maximum cardinality matching problem in general graphs. It was proposed by Jack Edmonds in 1961.
With some modifications, it can also solve the maximum weight matching problem in general graphs.
It was the first algorithm proven to find a maximum matching in polynomial time.

Unlike bipartite matching, a general graph may contain odd cycles.

![general-matching-1](./images/general-matching-1.png)

Take this graph as an example. If we simply flip the path (swap matched and unmatched edges), the flipped $M$ is not valid: some vertices would be on two matched edges. The problem comes from the odd cycle.

Now consider an augmenting algorithm for general graphs.
Start from the bipartite case. Each time, pick an unmatched vertex as the root and mark it **"o"**. Then mark vertices alternately **"o"** and **"i"**. It is easy to see that each edge from an **"i"** vertex to an **"o"** vertex is a matched edge.

Let the current vertex be $v$ and a neighbor be $u$. There are two cases:

1.  $u$ has not been visited. If $u$ is unmatched, we have found an augmenting path; otherwise, continue searching for an augmenting path from $u$'s partner.
2.  $u$ has been visited. If it is marked "o", we need to **shrink the blossom**; otherwise, we have found an even cycle and skip it.

An even cycle can be handled as in a bipartite graph, so we can ignore it. After **shrinking the blossom**, continue searching for an augmenting path in the new graph.

![general-matching-2](./images/general-matching-2.png)

Let the original graph be $G$ and the graph after **shrinking the blossom** be $G'$. We only need to prove:

1.  If $G$ has an augmenting path, so does $G'$.
2.  If $G'$ has an augmenting path, so does $G$.

![general-matching-3](./images/general-matching-3.png)

Let the non-tree edge (the edge that closes the cycle) be $(u,v)$, and define the blossom base $h=LCA(u,v)$.
The odd cycle alternates, and exactly one vertex, $h$, has two incident cycle edges of the same type; both are unmatched edges.
So the tree edge entering $h$ must be a matched edge, and every edge from a cycle vertex other than $h$ to outside the cycle is unmatched.

We can see that leaving the cycle through an outside edge can happen in two ways: clockwise or counterclockwise.

![general-matching-4](./images/general-matching-4.png)

So **shrinking** or **not shrinking** the blossom does not affect correctness.

In the implementation, after finding a **blossom** we do not need to actually **shrink** it. We can use an array to record, for each vertex, the base of the blossom it belongs to.

### Complexity analysis

Each search for an augmenting path goes through all edges, and each time a **blossom** is found we maintain the vertices on it, giving $O(|E|^2)$.

We search for an augmenting path from every unmatched vertex, so the total is $O(|V||E|^2)$.

### Reference code

??? note "Reference code"
    ```cpp
    // graph
    template <typename T>
    class graph {
     public:
      struct edge {
        int from;
        int to;
        T cost;
      };
    
      vector<edge> edges;
      vector<vector<int>> g;
      int n;
    
      graph(int _n) : n(_n) { g.resize(n); }
    
      virtual int add(int from, int to, T cost) = 0;
    };
    
    // undirectedgraph
    template <typename T>
    class undirectedgraph : public graph<T> {
     public:
      using graph<T>::edges;
      using graph<T>::g;
      using graph<T>::n;
    
      undirectedgraph(int _n) : graph<T>(_n) {}
    
      int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int)edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
      }
    };
    
    // blossom / find_max_unweighted_matching
    template <typename T>
    vector<int> find_max_unweighted_matching(const undirectedgraph<T> &g) {
      std::mt19937 rng(std::random_device{}());
      vector<int> match(g.n, -1);   // matching
      vector<int> aux(g.n, -1);     // timestamp
      vector<int> label(g.n);       // "o" or "i"
      vector<int> orig(g.n);        // blossom base
      vector<int> parent(g.n, -1);  // parent node
      queue<int> q;
      int aux_time = -1;
    
      auto lca = [&](int v, int u) {
        aux_time++;
        while (true) {
          if (v != -1) {
            if (aux[v] == aux_time) {  // found a visited vertex, which is the LCA
              return v;
            }
            aux[v] = aux_time;
            if (match[v] == -1) {
              v = -1;
            } else {
              v = orig[parent[match[v]]];  // continue from the parent of the matched vertex
            }
          }
          swap(v, u);
        }
      };  // lca
    
      auto blossom = [&](int v, int u, int a) {
        while (orig[v] != a) {
          parent[v] = u;
          u = match[v];
          if (label[u] == 1) {  // set it to "o" and search for augmenting paths from it
            label[u] = 0;
            q.push(u);
          }
          orig[v] = orig[u] = a;  // shrink the blossom
          v = parent[u];
        }
      };  // blossom
    
      auto augment = [&](int v) {
        while (v != -1) {
          int pv = parent[v];
          int next_v = match[pv];
          match[v] = pv;
          match[pv] = v;
          v = next_v;
        }
      };  // augment
    
      auto bfs = [&](int root) {
        fill(label.begin(), label.end(), -1);
        iota(orig.begin(), orig.end(), 0);
        while (!q.empty()) {
          q.pop();
        }
        q.push(root);
        // the starting vertex is marked "o"; here "0" stands for "o" and "1" for "i"
        label[root] = 0;
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (int id : g.g[v]) {
            auto &e = g.edges[id];
            int u = e.from ^ e.to ^ v;
            if (label[u] == -1) {  // found an unvisited vertex
              label[u] = 1;        // mark it "i"
              parent[u] = v;
              if (match[u] == -1) {  // found an unmatched vertex
                augment(u);          // augment along the path
                return true;
              }
              // found a matched vertex; push its partner into the queue to extend the alternating tree
              label[match[u]] = 0;
              q.push(match[u]);
              continue;
            } else if (label[u] == 0 && orig[v] != orig[u]) {
              // found a visited vertex also marked "o", which means we found a "blossom"
              int a = lca(orig[v], orig[u]);
              // find the LCA, then shrink the blossom
              blossom(u, v, a);
              blossom(v, u, a);
            }
          }
        }
        return false;
      };  // bfs
    
      auto greedy = [&]() {
        vector<int> order(g.n);
        // randomly shuffle order
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
    
        // match the vertices that can be matched
        for (int i : order) {
          if (match[i] == -1) {
            for (auto id : g.g[i]) {
              auto &e = g.edges[id];
              int to = e.from ^ e.to ^ i;
              if (match[to] == -1) {
                match[i] = to;
                match[to] = i;
                break;
              }
            }
          }
        }
      };  // greedy
    
      // start with a random greedy matching
      greedy();
      // search for augmenting paths from unmatched vertices
      for (int i = 0; i < g.n; i++) {
        if (match[i] == -1) {
          bfs(i);
        }
      }
      return match;
    }
    ```

??? note "[UOJ #79. Maximum Matching in General Graphs](https://uoj.ac/problem/79)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/general-match/general-match_1.cpp"
    ```

## A general matching algorithm based on Gaussian elimination

???+ tip "Tip"
    Before reading the following, you may want to read about matrices in the "Linear algebra" part:
    
    -   [Matrices](../../math/linear-algebra/matrix.md)
    -   [Determinants](../../math/linear-algebra/determinant.md)
    -   [Gaussian elimination](../../math/numerical/gauss.md)

This part introduces a general graph matching algorithm based on Gaussian elimination. Compared with the traditional blossom algorithm, it is easier to understand and to code, and it makes problems like "vertices that must be in every maximum matching" easy to solve. The downside is a larger constant factor, because the $O(n^3)$ of Gaussian elimination is almost always fully reached, while the blossom algorithm usually runs well below its bound.

### Prerequisite: the Tutte matrix

**Definition**: for an undirected graph $G = (V, E)$ with $n$ vertices, its Tutte matrix $\tilde{A}(G)$ is an $n \times n$ matrix where:

$$
\tilde{A}(G)_{i,j} = \begin{cases}
x_{i,j}, & i<j,\; (v_i, v_j)\in E \\
-x_{i,j}, & i > j,\; (v_i, v_j) \in E \\
0, & \text{otherwise}
\end{cases}
$$

Here $x_{i, j}$ is a variable, so $\tilde{A}(G)$ has $|E|$ variables in total.

When there is no ambiguity, we write $\tilde{A}$ for $\tilde{A}(G)$ below.

**Theorem** (Tutte's theorem): $G$ has a perfect matching if and only if $\det \tilde{A} \ne 0$.

??? note "Proof"
    We introduce the notion of an "even cycle cover": an even cycle cover of an undirected graph $G$ is a set of even cycles (including 2-cycles) that covers every vertex exactly once.
    
    It is easy to show that $G$ has a perfect matching if and only if $G$ has an even cycle cover.
    
    -   If $G$ has an even cycle cover, we just take every other edge of each cycle to get a perfect matching.
    -   If $G$ has a perfect matching, we just take the 2-cycle for each matched edge to get an even cycle cover.
    
    Next we prove that $G$ has an even cycle cover if and only if $\tilde{A} \ne 0$.
    
    Recall the definition of the determinant:
    
    $$
    \det A = \sum_{\pi} (-1)^{\pi} \prod_{i} A_{i, \pi_i}
    $$
    
    Here $\pi$ ranges over all permutations, and $(-1)^{\pi}$ is $-1$ if $\pi$ has an odd number of inversions and $1$ otherwise.
    
    It is easy to see that each permutation can be viewed as a cycle cover of $G$. If this cycle cover has an odd cycle, then its term and the term with that cycle reversed always sum to $0$. So only even cycle covers can make the determinant nonzero. This completes the proof.

**Theorem**: $\operatorname{rank}\tilde{A}$ is always even, and the size of a maximum matching of $G$ equals half of $\operatorname{rank}\tilde{A}$.

??? note "Proof"
    The rank of a skew-symmetric matrix can only be even; the second part is left to the reader.

In practice, we cannot compute with $|E|$ variables. Instead, we can pick a field, such as the residues $\mathcal{Z}_p$ modulo some prime $p$, randomly replace each variable with a number in $\mathcal{Z}_p$, and then compute. For convenience, when there is no ambiguity, $\tilde{A}$ below refers directly to the matrix after this substitution.

**Theorem**: $\operatorname{rank}\tilde{A}$ is at most twice the size of a maximum matching of $G$, and the two are equal with probability at least $1 - \frac n p$.

Since $n$ in general graph maximum matching problems is rarely more than $10^3$, a prime $p$ on the order of $10^9$ is enough in practice.

By the theorem, if you only need the size of the maximum matching and not the matching itself, a single Gaussian elimination to compute $\operatorname{rank}\tilde{A}$ is enough, which is much simpler than the blossom algorithm. If you need to output the matching, it is a bit more complicated and needs the algorithm described below.

### Constructing a perfect matching

By Tutte's theorem and the theorem above, if $G$ has a perfect matching, then $\tilde{A}$ has full rank with high probability. For convenience, we omit "with high probability" in what follows.

Let $v_i$ be the vertex labeled $i$ in $G$. We further have the following theorem:

**Theorem**: $\tilde{A}^{-1}_{j,i} \ne 0 \iff G - \{v_i, v_j\}$ has a perfect matching.

???+ tip "Inverse matrix and adjugate matrix"
    For any $n \times n$ square matrix $A$, its adjugate matrix is defined as $A^*_{i, j} = (-1)^{i + j} M_{j, i}$, where $M_{j, i}$ is the minor obtained by deleting row $j$ and column $i$. In other words, if $M$ is the cofactor matrix of $A$, then $A^* = M^T$.
    
    **Theorem**: if $A$ is invertible, then $A^{-1} = \frac 1 {\det A} A^*$.
    
    So here $A^{-1}_{j, i} \ne 0 \iff M_{i, j} \ne 0$, that is, $A$ with row $i$ and column $j$ deleted has full rank.

In other words, if $(v_i, v_j) \in E$ and $\tilde{A}^{-1}_{j, i} \ne 0$, then there is a perfect matching that contains the edge $(v_i, v_j)$. Below we call such edges **allowed edges**.

From the theorem above, for an undirected graph $G$ with a perfect matching, there is a fairly obvious brute-force algorithm to find a perfect matching: each time, enumerate $i, j$. If $(v_i, v_j)$ is an allowed edge (the edge exists and $\tilde{A}^{-1}_{j, i} \ne 0$), add $(v_i, v_j)$ to the matching, delete both vertices from $G$, and recompute the new $\tilde{A}^{-1}$.

This takes $\frac n 2$ rounds, each costing $O(n^3)$, for a total of $O(n ^ 4)$, which is a bit slow. In fact, when recomputing $\tilde{A}^{-1}$, we do not need to invert the matrix with Gaussian elimination every time. Instead, we can use the following theorem:

**Theorem** (elimination theorem): let

$$
A = \begin{bmatrix}
  a_{1, 1} & v^T \\
  u & B
\end{bmatrix} \quad A^{-1} = \begin{bmatrix}
  \hat a^{1, 1} & \hat v^T \\
  \hat u & \hat B
\end{bmatrix}
$$

and $\hat a_{1, 1} \ne 0$. Then

$$
B^{-1} = \hat B - \frac {\hat u \hat v^T} {\hat a_{1, 1}}
$$

The theorem describes eliminating the first row and first column. It clearly generalizes to eliminating any row and column. So we only need to compute $\tilde{A}^{-1}$ once at the start of the algorithm; after that, each time we delete two vertices, we just run the $O(n^2)$ elimination step twice.

??? note "The description is a bit abstract; see the C++ code"
    ```cpp
    void eliminate(int A[][MAXN], int r, int c) {  // eliminate row r and column c
      row_marked[r] = col_marked[c] = true;        // already eliminated
    
      int inv = quick_power(A[r][c], p - 2);  // modular inverse
    
      for (int i = 1; i <= n; i++)
        if (!row_marked[i] && A[i][c]) {
          int tmp = (long long)A[i][c] * inv % p;
    
          for (int j = 1; j <= n; j++)
            if (!col_marked[j] && A[r][j])
              A[i][j] = (A[i][j] - (long long)tmp * A[r][j]) % p;
        }
    }
    ```

This takes $\frac n 2$ rounds, each costing $O(n^2)$, so the algorithm above finds a perfect matching in $O(n^3)$ time.

### Constructing a maximum matching

We have just solved the problem of constructing a perfect matching, but problems usually ask for a maximum matching.

As mentioned above, the size of a maximum matching of $G$ equals half of $\operatorname{rank}\tilde{A}$. If we can find a maximum full-rank square submatrix of $\tilde{A}$, then finding a perfect matching in the induced subgraph corresponding to that submatrix gives a maximum matching of $G$.

Looking at it another way, if $G$ has a perfect matching, then $\tilde{A}$ has full rank; in other words, the rows of $\tilde{A}$ are linearly independent. So if $\tilde{A}$ is not full rank, we can find a basis of $\tilde{A}$'s rows and keep only the rows and columns corresponding to that basis. This gives a maximum full-rank square submatrix of $\tilde{A}$.

After finding the maximum full-rank square submatrix, use the algorithm above to find a perfect matching of the induced subgraph, which gives a maximum matching of the original graph. Note that Gaussian elimination may swap rows, so be careful to keep track of the vertex labels in the implementation.

??? note "[UOJ #79. Maximum Matching in General Graphs](https://uoj.ac/problem/79)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/general-match/general-match_2.cpp"
    ```

## Exercises

-   [UOJ #79. Maximum Matching in General Graphs](https://uoj.ac/problem/79)
-   [UOJ #171. [WC2016] Challenge NPC](https://uoj.ac/problem/171)

## References

1.  Mucha M, Sankowski P.[Maximum matchings via Gaussian elimination](http://web.eecs.umich.edu/~pettie/matching/Mucha-Sankowski-maximum-matching-matrix-multiplication.pdf)
2.  Zhou Zixin, Yang Jiaqi, *General Graph Matching Based on Linear Algebra*
3.  ZYQN, [*A General Graph Matching Algorithm Based on Linear Algebra*](https://oi.cyo.ng/wp-content/uploads/2017/02/maximum_matchings_via_gaussian_elimination.pdf)
