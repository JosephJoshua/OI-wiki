author: marscheng1

## Definition

Topological sorting solves the problem of how to order all the nodes of a directed acyclic graph.

We can describe this process with the example of scheduling university courses each semester. Suppose the university courses include "Programming", "Algorithmic Languages", "Advanced Mathematics", "Discrete Mathematics", "Compiler Techniques", "General Physics", "Data Structures", "Database Systems" and so on. Following the schedule in the example, to study "Data Structures" you must first learn "Discrete Mathematics", and after finishing that course you meet the prerequisite for "Compiler Techniques". Of course, "Compiler Techniques" also has an even earlier prerequisite, "Algorithmic Languages". These courses are like vertices $u$, and a directed edge $(u,v)$ between vertices is like the order in which the courses must be taken. When the academic office arranges these courses into a timetable that respects all these dependencies, it is doing a topological sort.

![topo](images/topo-example-1.svg)

But suppose one day the teacher who makes the schedule dozes off and says that to study Data Structures you must first take Operating Systems, while the prerequisite of Operating Systems is Data Structures. Which one should be taken first (assuming you cannot take both at once)? Here, Data Structures and Operating Systems form a cycle. Clearly the students cannot figure out what to study first, so no topological sort is possible. This is because if a directed graph contains a cycle, it cannot be topologically sorted.

So we can say: in a [DAG (directed acyclic graph)](./dag.md), we order the vertices linearly so that for every directed edge $(u,v)$ from vertex $u$ to $v$, $u$ comes before $v$.

Also, given a DAG, if there is an edge from $i$ to $j$, we say $j$ depends on $i$. If there is a path from $i$ to $j$ ($j$ is reachable from $i$), we say $j$ indirectly depends on $i$.

The goal of topological sorting is to order all nodes so that no node depends on a node that comes after it.

## AOV network

In daily life, a large project can be seen as a collection of smaller subprojects. These subprojects must happen in some order: some of them can only start after certain others are finished.

We use a directed graph to show the order between subprojects, where each ordering relation is a directed edge. Such a directed graph is called an activity-on-vertex network, or **AOV network (Activity On Vertex Network)**. An AOV network must be a directed acyclic graph, that is, it has no cycles. Unlike a general DAG, in an AOV network the activities are placed on the vertices. (The example graph above is an AOV network.)

In an AOV network, vertices represent activities and arcs represent precedence between activities. An AOV network should contain no cycle; then we can find a sequence of vertices in which all predecessor activities of each vertex's activity come before that vertex. Such a sequence is called a topological order (the topological order of an AOV network is not unique), and the process of building a topological order from an AOV network is called topological sorting. So topological sorting can also be described as arranging all activities of an AOV network in a sequence so that every activity's predecessor activities come before it (the topological sort of an AOV network is not unique either).

-   Predecessor activity: the activity at the start of a directed edge is a predecessor activity of the activity at its end (an activity can only start after all its predecessors are finished).

-   Successor activity: the activity at the end of a directed edge is a successor activity of the activity at its start.

To check whether an AOV network has a cycle, build a topological order and see whether it contains all vertices.

### Steps to build a topological order

1.  Pick a vertex with in-degree zero from the graph.
2.  Output this vertex, and delete it and all its outgoing edges from the graph.

Repeat these two steps until all vertices have been output, in which case the topological sort is complete, or until the graph has no vertex with in-degree zero. In the latter case the graph has a cycle, the topological sort cannot be completed, and the process is deadlocked.

## Critical path and AOE network

The counterpart of the AOV network is the **AOE network (Activity On Edge Network)**, a network in which edges represent activities. An AOE network is a weighted directed acyclic graph where vertices represent events and arcs represent how long activities take. AOE networks are commonly used to estimate how long a project will take to finish. An AOE network should be acyclic and have a unique start vertex with in-degree zero (the source) and a unique finish vertex with out-degree zero (the sink).

![topo](images/topo-example-2.svg)

Some activities in an AOE network can be done in parallel, so the shortest time to finish the whole project is the length of the longest activity path from the start to the finish (here the length of a path is the sum of the durations of the activities on it, that is, the sum of the arc weights, not the number of arcs). Since a project must complete all its activities, the longest activity path is also the critical path, which determines the total time to finish the project.

### Basic concepts of AOE networks

-   Activity: in an AOE network, arcs represent activities. The weight of an arc is the duration of the activity. An activity starts once its preceding event (the start of the arc) has been triggered.

-   Event: in an AOE network, vertices represent events. An event is triggered once all its preceding activities (the arcs pointing to it) have finished.

-   Earliest time of event (vertex) $v_i$: the earliest possible time the event can happen, written $ve(i)$. It determines the earliest start time of the activities that begin at this vertex. Clearly the earliest time of the source is 0. Since an event happens only after all its preceding activities finish, it equals the maximum length of a path from the start vertex to this vertex. As a recurrence: $ve(i) = \max\{ve(j) + val^j_i ~\vert~ j \in pre_i\}$, where $val^j_i$ is the weight of the edge from j to i (the duration of the activity from j to i) and $pre_i$ is the set of all preceding events of i.

-   Latest time of event (vertex) $v_i$: the latest time the event can happen without delaying the whole project, written $vl(i)$. It determines the latest time of all activities that end at this event. It equals the minimum of the latest start times of all succeeding activities of the event, that is, $vl(i) = \min\{vl(j) - val^i_j ~\vert~ j \in nxt_i\}$, where $val^i_j$ is the weight of the edge from i to j (the duration of the activity from i to j) and $nxt_i$ is the set of all succeeding events of i.

-   Earliest start time of activity (arc) $(u, v)$: the earliest possible time the activity can start, written $e(u,v)$. Clearly it equals the earliest time of its preceding event, that is, $e(u,v)=ve(u)$.

-   Latest start time of activity (arc) $(u, v)$: the latest time the activity can start without delaying the whole project, written $l(u,v)$. It equals the latest time of its succeeding event minus the duration (weight) of the activity, that is, $l(u,v)=vl(v)-val^u_v$, where $val^u_v$ is the weight of the edge from u to v (the duration of the activity from u to v).

-   Critical path: the length of the longest path from the source to the sink in the AOE network.

-   Critical activity: an activity on the critical path. Its earliest start time equals its latest start time.

### Computing earliest and latest times by recurrence

Compute them in topological order: earliest times are computed from front to back, and latest times from back to front, using the recurrences given in **Basic concepts of AOE networks** above.

## Kahn's algorithm

### Process

At the start, the set $S$ holds all vertices with in-degree $0$, and $L$ is an empty list.

Each time, take a vertex $u$ out of $S$ (any one will do) and put it into $L$, then delete all edges $(u, v_1), (u, v_2), (u, v_3) \cdots$ of $u$. For an edge $(u, v)$, if the in-degree of $v$ becomes $0$ after the edge is deleted, put $v$ into $S$.

Repeat this until $S$ is empty. Then check whether the graph still has any edges. If it does, the graph must have a cycle; otherwise return $L$, and the order of the vertices in $L$ is the resulting topological order.

First, look at the pseudocode from [Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm):

???+ note "Implementation"
    ```text
    L ← Empty list that will contain the sorted elements
    S ← Set of all nodes with no incoming edges
    while S is not empty do
        remove a node n from S
        insert n into L
        for each node m with an edge e from n to m do
            remove edge e from the graph
            if m has no other incoming edges then
                insert m into S
    if graph has edges then
        return error (graph has at least one cycle)
    else
        return L (a topologically sorted order)
    ```

The core of the code is keeping a set of vertices with in-degree 0.

You can refer to this graph:

![topo](images/topo-example.svg)

The result of sorting it is: 2 -> 8 -> 0 -> 3 -> 7 -> 1 -> 5 -> 6 -> 9 -> 4 -> 11 -> 10 -> 12

### Time complexity

For a graph $G = (V, E)$, initializing the set $S$ of vertices with in-degree $0$ requires going over the whole graph and checking every edge, which takes $O(E+V)$ time. Then processing the set also clearly takes $O(E+V)$ time.

So the total time complexity is $O(E+V)$.

### Implementation

=== "C++"
    ```cpp
    int n, m;
    vector<int> G[MAXN];
    int in[MAXN];  // in-degree of each node
    
    bool toposort() {
      vector<int> L;
      queue<int> S;
      for (int i = 1; i <= n; i++)
        if (in[i] == 0) S.push(i);
      while (!S.empty()) {
        int u = S.front();
        S.pop();
        L.push_back(u);
        for (auto v : G[u]) {
          if (--in[v] == 0) {
            S.push(v);
          }
        }
      }
      if (L.size() == n) {
        for (auto i : L) cout << i << ' ';
        return true;
      }
      return false;
    }
    ```

=== "Python"
    ```python
    from collections import defaultdict, deque
    
    
    def topo_sort(graph):
        lst = []
        in_degree = defaultdict(int)
        for u in graph:
            for v in graph[u]:
                in_degree[v] += 1
    
        s = deque([u for u in graph if in_degree[u] == 0])
        while s:
            u = s.popleft()
            lst.append(u)
            for v in graph.get(u, []):
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    s.append(v)
    
        return None if any(in_degree.values()) else lst
    ```

## DFS algorithm

### Implementation

=== "C++"
    ```cpp
    using Graph = vector<vector<int>>;  // adjacency list
    
    struct TopoSort {
      enum class Status : uint8_t { to_visit, visiting, visited };
    
      const Graph& graph;
      const int n;
      vector<Status> status;
      vector<int> order;
      vector<int>::reverse_iterator it;
    
      TopoSort(const Graph& graph)
          : graph(graph),
            n(graph.size()),
            status(n, Status::to_visit),
            order(n),
            it(order.rbegin()) {}
    
      bool sort() {
        for (int i = 0; i < n; ++i) {
          if (status[i] == Status::to_visit && !dfs(i)) return false;
        }
        return true;
      }
    
      bool dfs(const int u) {
        status[u] = Status::visiting;
        for (const int v : graph[u]) {
          if (status[v] == Status::visiting) return false;
          if (status[v] == Status::to_visit && !dfs(v)) return false;
        }
        status[u] = Status::visited;
        *it++ = u;
        return true;
      }
    };
    ```

=== "Python"
    ```python
    from enum import Enum, auto
    
    
    class Status(Enum):
        to_visit = auto()
        visiting = auto()
        visited = auto()
    
    
    def topo_sort(graph: list[list[int]]) -> list[int] | None:
        n = len(graph)
        status = [Status.to_visit] * n
        order = []
    
        def dfs(u: int) -> bool:
            status[u] = Status.visiting
            for v in graph[u]:
                if status[v] == Status.visiting:
                    return False
                if status[v] == Status.to_visit and not dfs(v):
                    return False
            status[u] = Status.visited
            order.append(u)
            return True
    
        for i in range(n):
            if status[i] == Status.to_visit and not dfs(i):
                return None
    
        return order[::-1]
    ```

Time complexity: $O(E+V)$. Space complexity: $O(V)$.

### Why it works

Consider a graph. After deleting a node with in-degree $0$, if the new graph can be topologically sorted, so can the original graph. Conversely, if the original graph can be topologically sorted, so can the graph after the deletion.

### Applications

Topological sorting can check whether a graph has a cycle, and whether a graph is a single chain. It can also be used to find the critical path in an AOE network and estimate the shortest time to finish a project.

### Lexicographically largest/smallest topological order

Just replace the queue in Kahn's algorithm with a priority queue implemented as a max-heap/min-heap. The total time complexity is then $O(E+V \log{V})$.

## Exercises

[CF 1385E](https://codeforces.com/problemset/problem/1385/E): requires a construction using topological sorting.

[Luogu P1347](https://www.luogu.com.cn/problem/P1347): topological sorting template.

## References

1.  Discrete Mathematics and Its Applications. ISBN:9787111555391
2.  [Topological sorting - Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting)
3.  [Data Structures Lecture 9 (Graphs: Topological Sorting, Critical Path, Shortest Paths) - Zhihu Column](https://zhuanlan.zhihu.com/p/164751109)
