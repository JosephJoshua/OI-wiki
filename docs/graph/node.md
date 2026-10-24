author: Anguei, sshwy, Xeonacid, Ir1d, MonkeyOliver, hsfzLZH1

Vertex splitting is a graph-modeling idea. It is often used in [network flow](./flow.md) to handle **vertex weights or flow limits on vertices**, and it is also often used for **layered graphs**.

## Maximum flow with capacity limits on vertices

If we turn each vertex into an edge, we can solve this problem with the standard template.

We turn each vertex with a flow limit into the following structure: two vertices $u,v$ joined by one edge $\left\langle u,v \right\rangle$. Vertex $u$ receives all edges that, in the original graph, go from other vertices into this vertex. Vertex $v$ sends out all edges that, in the original graph, go from this vertex to other vertices. The capacity of edge $\left\langle u,v \right\rangle$ is the flow limit of the vertex in the original graph. Then the standard template solves the problem. This is the basic idea of vertex splitting.

Suppose the original graph looks like this:

![](./images/node.svg)

After splitting the vertices, the graph looks like this:

![](./images/node-split.svg)

## Shortest paths on a layered graph

A typical layered-graph shortest path problem: you may traverse an edge at zero cost $k$ times; find the minimum total cost. For this kind of problem we can use a DP-style idea. Let $\text{dis}_{i, j}$ be the shortest distance from the start to vertex $i$ after using $j$ free passes. Clearly, the $\text{dis}$ array can be updated like this:

$\text{dis}_{i, j} = \min\{\min\{\text{dis}_{from, j - 1}\}, \min\{\text{dis}_{from,j} + w\}\}$

Here $from$ is a predecessor of $i$, and $w$ is the weight of the edge being used. When $j - 1 \geq k$, $\text{dis}_{from, j}$=$\infty$.

In fact, this DP is the same as splitting each vertex into $k+1$ vertices. Each new vertex stands for reaching the original vertex after using a different number of free passes. In other words, vertex $u_i$ means reaching vertex $u$ after using $i$ free passes.

??? note "[JLOI2011 Flight Routes](https://www.luogu.com.cn/problem/P4568)"
    Problem: given an undirected graph with $n$ vertices and $m$ edges, you may choose $k$ roads to travel at zero cost. Find the minimum cost from $s$ to $t$.
    
    Core reference code:
    
    ```cpp
    struct State {    // node struct for the priority queue
      int v, w, cnt;  // cnt is how many free passes have been used
    
      State() {}
    
      State(int v, int w, int cnt) : v(v), w(w), cnt(cnt) {}
    
      bool operator<(const State &rhs) const { return w > rhs.w; }
    };
    
    void dijkstra() {
      memset(dis, 0x3f, sizeof dis);
      dis[s][0] = 0;
      pq.push(State(s, 0, 0));  // reaching the start uses no free pass; distance is zero
      while (!pq.empty()) {
        const State top = pq.top();
        pq.pop();
        int u = top.v, nowCnt = top.cnt;
        if (done[u][nowCnt]) continue;
        done[u][nowCnt] = true;
        for (int i = head[u]; i; i = edge[i].next) {
          int v = edge[i].v, w = edge[i].w;
          if (nowCnt < k && dis[v][nowCnt + 1] > dis[u][nowCnt]) {  // can pass for free
            dis[v][nowCnt + 1] = dis[u][nowCnt];
            pq.push(State(v, dis[v][nowCnt + 1], nowCnt + 1));
          }
          if (dis[v][nowCnt] > dis[u][nowCnt] + w) {  // cannot pass for free
            dis[v][nowCnt] = dis[u][nowCnt] + w;
            pq.push(State(v, dis[v][nowCnt], nowCnt));
          }
        }
      }
    }
    
    int main() {
      n = read(), m = read(), k = read();
      // The author prefers numbering from 1 to n, but this problem uses 0 to n - 1, so shift it
      s = read() + 1, t = read() + 1;
      while (m--) {
        int u = read() + 1, v = read() + 1, w = read();
        add(u, v, w), add(v, u, w);  // edges in this problem are bidirectional
      }
      dijkstra();
      int ans = std::numeric_limits<int>::max();  // initialize ans to the max int value
      for (int i = 0; i <= k; ++i)
        ans = std::min(ans, dis[t][i]);  // take the best over all ways to reach the end
      println(ans);
    }
    ```
