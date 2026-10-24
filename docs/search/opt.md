author: CBW2007, ChungZH, Marcythm, abc1763613206, Ir1d

## Preface

DFS (depth-first search) is a common algorithm, and most problems can be solved with DFS. But in most cases it is only a partial-credit trick; very few problems have brute-force search as the intended solution, because DFS has a very high time complexity. (If you have not learned DFS yet, please study it first.)

Since it can't be the intended solution, let's at least earn more partial points with it. This article introduces some practical optimizations (commonly called "pruning").

First, here is a DFS template. The later templates are modified from it.

```cpp
int ans = worst_case, now;  // now is the current answer

void dfs(parameters) {
  if (reached the goal) ans = best of current solution and existing solution;
  for (every possibility)
    if (feasible) {
      apply the operation;
      dfs(smaller problem);
      undo the operation;
    }
}
```

Here ans can be a record of the solution; then "best of current solution and existing solution" becomes outputting the solution.

## Pruning methods

The three most common kinds of pruning are memoized search, optimality pruning, and feasibility pruning.

### Memoized search

In a search, the same input values often lead to the same result, so we can remember results in an array. See [memoized search](../dp/memo.md) for details.

**Template:**

```cpp
int g[MAXN];  // define the memoization array
int ans = worst_case, now;

void dfs f(parameters) {
  if (g[size] != invalid_value) return;  // or record the solution, depending on the case
  if (reached the goal) ans = best of current solution and existing solution;  // output the solution, depending on the case
  for (every possibility)
    if (feasible) {
      apply the operation;
      dfs(smaller problem);
      undo the operation;
    }
}

int main() {
  // ...
  memset(g, invalid_value, sizeof(g));  // initialize the memoization array
  // ...
}
```

### Optimality pruning

Another reason a search runs slowly is that it keeps searching even when the current solution is already worse than an existing one. So we just need to check whether the current solution is already worse than the existing one.

**Template:**

```cpp
int ans = worst_case, now;

void dfs(parameters) {
  if (now is already worse than ans) return;
  if (reached the goal) ans = best of current solution and existing solution;
  for (every possibility)
    if (feasible) {
      apply the operation;
      dfs(smaller problem);
      undo the operation;
    }
}
```

### Feasibility pruning

Continuing to search after the current solution has already become invalid is another reason a search runs slowly.

**Template:**

```cpp
int ans = worst_case, now;

void dfs(parameters) {
  if (current solution is already invalid) return;
  if (reached the goal) ans = best of current solution and existing solution;
  for (every possibility)
    if (feasible) {
      apply the operation;
      dfs(smaller problem);
      undo the operation;
    }
}
```

## Pruning ideas

There are many pruning ideas, and most of them require analyzing the specific problem. Here we briefly introduce a few common ones.

-   Extreme-case method: consider the extreme case. If even the most extreme (most ideal) case cannot satisfy the requirement, then the actual search cannot produce a better result.

-   Adjustment method: by comparing subtrees, cut off duplicate subtrees and subtrees that are clearly not the most "promising".

-   Mathematical methods: for example, using connected components in graph theory, analyzing modular equations in number theory, or bounding with inequalities to estimate a lower bound.

## Example problem

???+ note "Job assignment problem"
    There are $n$ ($1 \leq n \leq  15$) jobs to be assigned to $n$ people, one job per person. Person $i$ takes a positive integer time $t_{i,k}$ ($1 \leq t_{i,k} \leq 10^4$) to finish job $k$, where $1 \leq i, k \leq n$. Find an assignment that minimizes the total time to finish all $n$ jobs.

Since every person must be given a job, we can create a 2D array `time[i][j]` for the time person $i$ spends on job $j$. Use a loop that assigns jobs starting from person 1 until everyone has a job. When assigning a job to person $i$, loop over the jobs and check whether each one is already assigned; if not, give it to person $i$, otherwise check the next job. A 1D array `is_working[j]` records whether job $j$ is assigned: `is_working[j]=0` if not, otherwise `is_working[j]=1`. Using backtracking, after the loop for a worker ends, we go back to the previous worker, cancel that worker's current job, and try the next job until one can be assigned. By backtracking all the way to worker 1 in this way, we get all feasible solutions.

Checking an assignment really means checking that, in a feasible solution, the first indices of the 2D array are all different and the second indices are all different. We want the minimum total time to finish the $n$ jobs, that is, the feasible solution with the smallest total time. So we define a global variable `cost_time_total_min` for the smallest total time among the solutions found so far. Initially `cost_time_total_min` is the sum of `time[i][i]`, that is, the sum of the job times on the diagonal. When everyone has been assigned a job, compare `count` with `cost_time_total_min`. If `count` is smaller than `cost_time_total_min`, we have found a better solution, so we assign `count` to `cost_time_total_min`.

But for efficiency, there is one more pruning optimization we can do. Every time we compute the partial cost variable `count`, if `count` is already greater than `cost_time_total_min`, there is no need to keep assigning, because the resulting solution cannot be optimal.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/opt/opt_1.cpp"
    ```
