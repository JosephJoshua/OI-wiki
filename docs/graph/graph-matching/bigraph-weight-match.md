author: accelsao, Enter-tainer, guodong2005, StudyingFather, Backl1ght, Chrogeek, H-J-Granger, Henry-ZHR

A maximum weight matching of a bipartite graph is a matching whose total edge weight is as large as possible.

## Hungarian algorithm (Kuhn–Munkres algorithm)

The Hungarian algorithm, also called the **KM** algorithm, finds a **maximum weight perfect matching** of a bipartite graph in $O(n^3)$ time.

The two sides of a bipartite graph do not always have the same number of vertices. To use the KM algorithm for maximum weight matching, first do the following: add dummy vertices to the smaller side so that both sides have the same number of vertices, and set the weight of every missing edge to $0$. The problem then becomes a **maximum weight perfect matching problem**, which the KM algorithm can solve.

???+ note "Feasible labeling"
    Assign each vertex $i$ a value $l(i)$ (its label) such that every edge $(u,v)$ satisfies $w(u,v) \leq l(u) + l(v)$.

???+ note "Equality subgraph"
    For a given feasible labeling, the equality subgraph is the spanning subgraph of the original graph that contains all vertices but only the edges $(u,v)$ with $w(u,v) = l(u) + l(v)$.

???+ note "Theorem 1: For a feasible labeling, if its equality subgraph has a perfect matching, then that matching is a maximum weight perfect matching of the original bipartite graph."
    Proof 1.
    
    Take any perfect matching $M$ of the original bipartite graph. Its total edge weight is
    
    $val(M) = \sum_{(u,v)\in M} {w(u,v)} \leq \sum_{(u,v)\in M} {l(u) + l(v)} \leq \sum_{i=1}^{n} l(i)$
    
    For a perfect matching $M'$ of the equality subgraph of any feasible labeling, the total edge weight is
    
    $val(M') = \sum_{(u,v)\in M} {l(u) + l(v)} = \sum_{i=1}^{n} l(i)$
    
    So no perfect matching has total weight larger than $val(M')$, which means $M'$ is a maximum weight matching.

With Theorem 1, our goal is to keep adjusting the feasible labeling until the equality subgraph has a perfect matching.

Since both sides have the same number of vertices, let that number be $n$. Let $lx(i)$ be the label of the $i$-th left vertex, $ly(i)$ the label of the $i$-th right vertex, and $w(u,v)$ the weight between the $u$-th left vertex and the $v$-th right vertex.

First, initialize a feasible labeling, for example

$lx(i) = \max_{1\leq j\leq n} \{ w(i, j)\},\, ly(i) = 0$

Then pick an unmatched vertex and search for an augmenting path, as in maximum matching. If an augmenting path is found, augment; otherwise, we get an alternating tree.

Let $S$ and $T$ be the left and right vertices in the alternating tree, and $S'$ and $T'$ the vertices not in the alternating tree.

![bigraph-weight-match-1](./images/bigraph-weight-match-1.png)

In the equality subgraph:

-   There are no $S-T'$ edges; otherwise the alternating tree would grow.
-   $S'-T$ edges must be unmatched; otherwise that left vertex would belong to $S$.

Suppose we subtract $a$ from the labels in $S$ and add $a$ to the labels in $T$. We can see that

-   $S-T$ edges stay in the equality subgraph.
-   $S'-T'$ edges do not change.
-   For $S-T'$ edges, $lx + ly$ decreases, so they may join the equality subgraph.
-   For $S'-T$ edges, $lx + ly$ increases, so they cannot join the equality subgraph.

So the value $a$ should clearly be the smallest slack among the $S-T'$ edges:

$a = \min \{ lx(u) + ly(v) - w(u,v) | u\in{S} , v\in{T'} \}$.

When a new edge $(u,v)$ joins the equality subgraph, there are two cases:

-   $v$ is unmatched, so we have found an augmenting path;
-   $v$ is already matched to a vertex in $S'$.

So after changing the labels at most $n$ times, we can find an augmenting path.

Each time the labels change, the edges in the alternating tree do not leave the equality subgraph, so we can maintain this tree directly.

For each vertex $v$ in $T$, we maintain

$slack(v) = \min \{ lx(u) + ly(v) - w(u,v) | u\in{S} \}$.

So the label change $a$ can be computed in $O(n)$:

$a = \min \{ slack(v) | v\in{T'} \}$

When a new vertex enters $S$ in the alternating tree, updating $slack(v)$ takes $O(n)$. Changing the labels takes $O(n)$ to subtract $a$ from every $slack(v)$. As soon as the alternating tree reaches an unmatched vertex, we have found an augmenting path.

We go through $n$ vertices to find augmenting paths. Finding each augmenting path extends the alternating tree up to $n$ times, and each extension takes $O(n)$ maintenance work, for $O(n^3)$ in total.

??? note "Reference code"
    ```cpp
    template <typename T>
    struct hungarian {  // km
      int n;
      vector<int> matchx;  // matched vertex of each left vertex
      vector<int> matchy;  // matched vertex of each right vertex
      vector<int> pre;     // left vertex connected to each right vertex
      vector<bool> visx;   // visited array, left side
      vector<bool> visy;   // visited array, right side
      vector<T> lx;
      vector<T> ly;
      vector<vector<T>> g;
      vector<T> slack;
      T inf;
      T res;
      queue<int> q;
      int org_n;
      int org_m;
    
      hungarian(int _n, int _m) {
        org_n = _n;
        org_m = _m;
        n = max(_n, _m);
        inf = numeric_limits<T>::max();
        res = 0;
        g = vector<vector<T>>(n, vector<T>(n));
        matchx = vector<int>(n, -1);
        matchy = vector<int>(n, -1);
        pre = vector<int>(n);
        visx = vector<bool>(n);
        visy = vector<bool>(n);
        lx = vector<T>(n, -inf);
        ly = vector<T>(n);
        slack = vector<T>(n);
      }
    
      void addEdge(int u, int v, int w) {
        g[u][v] = max(w, 0);  // a negative weight is worse than not matching, so setting it to 0 changes nothing
      }
    
      bool check(int v) {
        visy[v] = true;
        if (matchy[v] != -1) {
          q.push(matchy[v]);
          visx[matchy[v]] = true;  // in S
          return false;
        }
        // found a new unmatched vertex; update matches. pre[] stores the vertex joined to it by an "unmatched edge"
        while (v != -1) {
          matchy[v] = pre[v];
          swap(v, matchx[pre[v]]);
        }
        return true;
      }
    
      void bfs(int i) {
        while (!q.empty()) {
          q.pop();
        }
        q.push(i);
        visx[i] = true;
        while (true) {
          while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
              if (!visy[v]) {
                T delta = lx[u] + ly[v] - g[u][v];
                if (slack[v] >= delta) {
                  pre[v] = u;
                  if (delta) {
                    slack[v] = delta;
                  } else if (check(v)) {  // delta=0 means it may join the equality subgraph; look for an augmenting path
                                          // if found, return and rebuild the alternating tree
                    return;
                  }
                }
              }
            }
          }
          // no augmenting path; change the labels
          T a = inf;
          for (int j = 0; j < n; j++) {
            if (!visy[j]) {
              a = min(a, slack[j]);
            }
          }
          for (int j = 0; j < n; j++) {
            if (visx[j]) {  // S
              lx[j] -= a;
            }
            if (visy[j]) {  // T
              ly[j] += a;
            } else {  // T'
              slack[j] -= a;
            }
          }
          for (int j = 0; j < n; j++) {
            if (!visy[j] && slack[j] == 0 && check(j)) {
              return;
            }
          }
        }
      }
    
      void solve() {
        // initial labels
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            lx[i] = max(lx[i], g[i][j]);
          }
        }
    
        for (int i = 0; i < n; i++) {
          fill(slack.begin(), slack.end(), inf);
          fill(visx.begin(), visx.end(), false);
          fill(visy.begin(), visy.end(), false);
          bfs(i);
        }
    
        // custom
        for (int i = 0; i < n; i++) {
          if (g[i][matchx[i]] > 0) {
            res += g[i][matchx[i]];
          } else {
            matchx[i] = -1;
          }
        }
        cout << res << "\n";
        for (int i = 0; i < org_n; i++) {
          cout << matchx[i] + 1 << " ";
        }
        cout << "\n";
      }
    };
    ```

## Dynamic Hungarian Algorithm

Original paper: [The Dynamic Hungarian Algorithm for the Assignment Problem with Changing Costs](https://www.ri.cmu.edu/publications/the-dynamic-hungarian-algorithm-for-the-assignment-problem-with-changing-costs/)

A paper with clearer pseudocode: [A Fast Dynamic Assignment Algorithm for Solving Resource Allocation Problems](https://www.researchgate.net/publication/352490780_A_Fast_Dynamic_Assignment_Algorithm_for_Solving_Resource_Allocation_Problems)

Related OJ problem: [DAP](https://www.spoj.com/problems/DAP/)

???+ note "Idea of the algorithm"
    1.  Change the weights between a single vertex $u_i$ and all $v_j$, that is, one row of the weight matrix:
        -   Update the label $lx(u_i) = max(w_{ij} - v_{j}), \forall j$
        -   Remove the matching edge involving $u_i$
    2.  Change the weights between all $u_i$ and a single vertex $v_j$, that is, one column of the weight matrix:
        -   Update the label $ly(v_j) = max(w_{ij} - u_{i}), \forall i$
        -   Remove the matching edge involving $v_j$
    3.  Change the weight between a single vertex $u_i$ and a single vertex $v_j$, that is, one element of the weight matrix:
        -   Just do either operation 1 or operation 2
    4.  Add a single vertex $u_i$ or a single vertex $v_j$, that is, add or remove a row or column of the weight matrix:
        -   Do 1 or 2 accordingly. Note that adding a vertex here only adds the vertex and sets no extra weights; the weights between the new vertex and other vertices are 0.

???+ note "Proof of the algorithm"
    -   Let the original graph be G, the labels of the left and right sides be $\alpha^{i}$ and $\beta^{j}$, and the feasible labeling be l. Then $G_l$ is the subgraph of G containing the vertices and edges of G that satisfy $w_{ij} = alpha_{i}+beta_{j}$.
    -   In the Hungarian algorithm section above, Theorem 1 proved: for a feasible labeling, if its equality subgraph has a perfect matching, then that matching is a maximum weight perfect matching of the original bipartite graph.
    -   Suppose the original optimal matching is $M^*$. When a change happens, we update the feasible labeling according to the rules, and call the updated labels $\alpha^{i^*}$ or $\beta^{j^*}$. The following cases can occur:
        1.  A whole row of the weight matrix is changed. Let it be row $i^*$, so all edges of $v_{i^*}$ are changed. The old label of $v_{i^*}$ may no longer satisfy the condition, since we need $w_{i^{*}j} \leq alpha_{i^*}+beta_{j}$. But for the other $u_j$, apart from edges involving $i^*$, their edge weights do not change, so their labels are all still valid. So the algorithm changes the label of $v_{i^*}$, which makes the labeling feasible again.
        2.  A whole column of the weight matrix is changed. By the same argument, the algorithm's label change makes the labeling feasible.
        3.  One element of the weight matrix is changed. Changing either one of the two labels is enough to satisfy the labeling condition.
    -   Each change to the weight matrix concerns one specific vertex, which may be on the left or the right; call it $x$. In the old optimal matching, this vertex is matched to some vertex $y$. Each change unpairs at most this one pair of vertices, so we only need to run one round of the Hungarian algorithm's search to get a new matching, and by Theorem 1, the new matching is optimal.

The code below should be the code submitted by the author of paper 2 (it is the version that maximizes weight; the original paper minimizes cost).

??? note "Reference code for the dynamic Hungarian algorithm"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-weight-match/bigraph-weight-match_1.cpp"
    ```

## Reduction to a min-cost flow model

As with [bipartite maximum matching](./bigraph-match.md), maximum weight bipartite matching can also be solved as a network flow problem.

First, add a source and a sink to the graph.

From the source, add an edge with capacity $1$ and cost $0$ to each left vertex of the bipartite graph. From each right vertex, add an edge with capacity $1$ and cost $0$ to the sink.

Next, for each edge of the bipartite graph between a left vertex $u$ and a right vertex $v$ with weight $w$, add an edge from $u$ to $v$ with capacity $1$ and cost $w$.

Also, in a maximum weight matching, the number of matched edges is not necessarily the same as in a maximum matching. So for each left vertex, also add an edge with capacity $1$ and cost $0$ to the sink.

Find the [maximum-cost maximum flow](../flow/min-cost.md) of this network to get the answer. The maximum flow of this network is always the number of left vertices, and the maximum cost under maximum flow corresponds to a maximum weight matching.

## Exercises

??? note "[UOJ #80. Maximum Weight Bipartite Matching](https://uoj.ac/problem/80)"
    Template problem
    
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-weight-match/bigraph-weight-match_2.cpp"
    ```
