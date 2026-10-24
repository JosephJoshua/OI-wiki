author: AntiLeaf

The Berlekamp–Massey algorithm finds the shortest linear recurrence of a sequence. Given a sequence of length $n$ whose shortest recurrence has order $m$, the Berlekamp–Massey algorithm finds the shortest recurrence of every prefix of the sequence in $O(nm)$ time. In the worst case $m = O(n)$, so the worst-case complexity of the algorithm is $O(n^2)$.

### Definition

A recurrence of a sequence $\{a_0 \dots a_{n - 1} \}$ is a sequence $\{r_0\dots r_m\}$ that satisfies:

$\sum_{j = 0} ^ m r_j a_{i - j} = 0, \forall i \ge m$

where $r_0 = 1$. $m$ is called the **order** of the recurrence.

The shortest recurrence of the sequence $\{a_i\}$ is the recurrence with the smallest order.

### How it works

Slightly differently from the definition above, we define new recurrence coefficients $\{f_0 \dots f_{m - 1}\}$ that satisfy:

$a_i = \sum_{j = 0} ^ {m - 1} f_j a_{i - j - 1}, \forall i \ge m$

Clearly $f_i = -r_{i + 1}$, and the order $m$ is the same as in the earlier definition.

We can build the recurrence incrementally: go through the terms of $\{a_i\}$ in order, and adjust the coefficients $\{f_i\}$ whenever the recurrence predicts a term wrongly. For convenience, let $F_i = \{f_{i, j}\}$ denote the shortest recurrence of the first $i$ terms.

Clearly $F_0 = \{\}$ at the start. Suppose the coefficients $F_{i - 1}$ hold for the first $i - 1$ terms of $\{a_i\}$. Then for the $i$-th term there are two cases:

1.  The coefficients also hold for $a_i$. No adjustment is needed; just set $F_i = F_{i - 1}$.
2.  The coefficients do not hold for $a_i$. We must adjust $F_{i - 1}$ to get a new $F_i$.

Let $\Delta_i = a_i - \sum_{j = 0} ^ m f_{i - 1, j} a_{i - j - 1}$, that is, the difference between $a_i$ and the value predicted by $F_{i - 1}$.

If this is the first time we modify the coefficients, then $a_i$ is the first non-zero term of the sequence. In this case, just let $F_i$ be $i$ zeros; clearly this is a valid shortest recurrence.

Otherwise, let $k$ be the number of terms of $\{a_i\}$ that had been considered at the previous modification. If there is a sequence $G = \{g_0 \dots g_{m' - 1}\}$ such that:

$\sum_{j = 0} ^ {m' - 1} g_j a_{i' - j - 1} = 0, \forall i' \in [m', i)$

and $\sum_{j = 0} ^ {m' - 1} g_j a_{i - j - 1} = \Delta_i$, then it is easy to see that adding $F_k$ and $G$ term by term gives valid coefficients $F_i$.

How do we construct $G$? One construction that works is

$G = \{0, 0, \dots, 0, \frac{\Delta_i}{\Delta_k}, -\frac{\Delta_i}{\Delta_k}F_{k-1}\}$

where there are $i - k - 1$ zeros at the front, and the final $-\frac{\Delta_i}{\Delta_k} F_{k-1}$ means multiplying every term of $F_{k-1}$ by $-\frac{\Delta_i}{\Delta_k}$ and appending the result to the sequence.

It is easy to check that now $\sum_{j = 0} ^ {m' - 1} g_j a_{i - j - 1} = \Delta_k \frac{\Delta_i}{\Delta_k} = \Delta_i$, so this $G$ is valid. Set $F_i$ to the term-by-term sum of $F_k$ and $G$.

If you need the recurrence $\{r_i\}$ in the original definition, negate all of $\{f_j\}$ and insert $r_0 = 1$ at the front.

From the process above, if the shortest recurrence of the sequence has order $m$, the algorithm runs in $O(nm)$ time. In the worst case $m = O(n)$, so the worst-case complexity is $O(n^2)$.

In an implementation, each adjustment only needs the coefficients $F_k$ from the previous adjustment. So if you only need the shortest recurrence of the whole sequence, you can store just the current coefficients and those from the previous adjustment, and the space complexity is $O(n)$.

??? note "Reference implementation"
    ```cpp
    vector<int> berlekamp_massey(const vector<int> &a) {
      vector<int> v, last;  // v is the answer, 0-based, p is the module
      int k = -1, delta = 0;
    
      for (int i = 0; i < (int)a.size(); i++) {
        int tmp = 0;
        for (int j = 0; j < (int)v.size(); j++)
          tmp = (tmp + (long long)a[i - j - 1] * v[j]) % p;
    
        if (a[i] == tmp) continue;
    
        if (k < 0) {
          k = i;
          delta = (a[i] - tmp + p) % p;
          v = vector<int>(i + 1);
    
          continue;
        }
    
        vector<int> u = v;
        int val = (long long)(a[i] - tmp + p) * power(delta, p - 2) % p;
    
        if (v.size() < last.size() + i - k) v.resize(last.size() + i - k);
    
        (v[i - k - 1] += val) %= p;
    
        for (int j = 0; j < (int)last.size(); j++) {
          v[i - k + j] = (v[i - k + j] - (long long)val * last[j]) % p;
          if (v[i - k + j] < 0) v[i - k + j] += p;
        }
    
        if ((int)u.size() - i < (int)last.size() - k) {
          last = u;
          k = i;
          delta = a[i] - tmp;
          if (delta < 0) delta += p;
        }
      }
    
      for (auto &x : v) x = (p - x) % p;
      v.insert(v.begin(), 1);
    
      return v;  // $\forall i, \sum_{j = 0} ^ m a_{i - j} v_j = 0$
    }
    ```

The basic Berlekamp–Massey algorithm finds the shortest recurrence of a finite sequence. If the sequence is infinite but an upper bound $m$ on the order of its shortest recurrence is known, the first $2m$ terms are enough to find the shortest recurrence of the whole sequence. (Proof omitted.)

### Applications

The Berlekamp–Massey algorithm has poor numerical stability, so it is rarely used for problems over the real numbers. For convenience, all computations below are assumed to be modulo some prime $p$.

#### Shortest recurrence of a sequence of vectors or matrices

To find the shortest recurrence of a sequence of vectors $\boldsymbol{v}_i$ of dimension $n$, we can pick a random $n$-dimensional row vector $\mathbf u^T$ and compute the shortest recurrence of the scalar sequence $\{\boldsymbol{u}^T\boldsymbol{v}_i\}$. By the Schwartz–Zippel lemma, the two shortest recurrences are the same with probability at least $1 - \frac n p$.

The same works for a sequence of matrices $\{A_i\}$. If the matrices are $n \times m$, pick a random $1 \times n$ row vector $\mathbf u^T$ and a random $m \times 1$ column vector $\boldsymbol{v}$, and compute the shortest recurrence of the scalar sequence $\{\boldsymbol{u}^T A_i \boldsymbol{v}\}$. In a similar way, the Schwartz–Zippel lemma shows that the two are the same with probability at least $1 - \frac{n + m} p$.

#### Speeding up fast matrix exponentiation

Let $\boldsymbol{f}_i$ be an $n$-dimensional column vector with the transition $\boldsymbol{f}_i = A \boldsymbol{f}_{i - 1}$. Then $\{\boldsymbol{f}_i\}$ is a sequence of vectors satisfying a linear recurrence of order at most $n$. (Proof omitted.)

We can compute $\boldsymbol{f}_0 \dots \boldsymbol{f}_{2n - 1}$ by brute force, use the method above to find the shortest recurrence of $\{\boldsymbol{f}_i\}$, and then apply [linear recurrences with constant coefficients](./poly/linear-recurrence.md).

If we want the vector $\boldsymbol{f}_m$, the algorithm runs in $O(n^3 + n\log n \log m)$ time. If $A$ is a sparse matrix with only $k$ non-zero entries, this drops to $O(nk + n\log n \log m)$. But since the algorithm needs at least $O(nk)$ time for preprocessing anyway, when the limits are not tight you can also use the $O(n^2 \log m)$ linear recurrence algorithm, which is also fast enough.

#### Minimal polynomial of a matrix

The minimal polynomial of a square matrix $A$ is the polynomial $f$ of smallest degree with $f(A) = 0$.

In fact, the minimal polynomial is exactly the shortest recurrence of $\{A^i\}$, so we can just run the Berlekamp–Massey algorithm. If $A$ is an $n \times n$ matrix, the minimal polynomial clearly has degree at most $n$.

The bottleneck is computing $A^i$, since doing a matrix multiplication each time costs $O(n^4)$. But when finding the shortest recurrence of a matrix sequence we actually find the shortest recurrence of $\{\boldsymbol{u}^T A^i \boldsymbol{v}\}$, so we only need to compute $A^i \boldsymbol{v}$.

If $A$ has $k$ non-zero entries, the complexity is $O(kn + n^2)$.

#### Determinant of a sparse matrix

If we can find the characteristic polynomial of a square matrix $A$, its constant term times $(-1)^n$ is the determinant. But the minimal polynomial is not always the characteristic polynomial.

In fact, if we multiply $A$ by a random diagonal matrix $B$, the minimal polynomial of $AB$ equals its characteristic polynomial with probability at least $1 - \frac {2n^2 - n} p$. At the end, divide by $\text{det}\;B$.

If $A$ is an $n \times n$ matrix with $k$ non-zero entries, the complexity is $O(kn + n ^ 2)$.

#### Rank of a sparse matrix

Let $A$ be an $n\times m$ matrix. First pick a random $n\times n$ diagonal matrix $P$ and a random $m\times m$ diagonal matrix $Q$, then compute the minimal polynomial of $Q A P A^T Q$.

We do not actually need matrix multiplication. Computing the minimal polynomial only requires multiplying $Q A P A^T Q$ by a vector, so we multiply the vector by these matrices one at a time. The answer is the degree of the minimal polynomial after removing all factors of $x$.

If $A$ has $k$ non-zero entries and $n \le m$, the complexity is $O(kn + n ^ 2)$.

#### Solving sparse systems of equations

**Problem**: We have $A \mathbf x = \mathbf b$, where $A$ is an $n \times n$ **full-rank** sparse matrix, and $\mathbf b$ and $\mathbf x$ are $1\times n$ column vectors. Given $A$ and $\mathbf b$, solve for $x$ in less than $n^\omega$ time.

**Solution**: Clearly $\mathbf x = A^{-1} \mathbf b$. If we can find the shortest recurrence $\{r_0 \dots r_{m - 1}\}$ ($m \le n$) of $\{A^i \mathbf b\}$ ($i \ge 0$), then

$A^{-1} \mathbf b = -\frac 1 {r_{m - 1}} \sum_{i = 0} ^ {m - 2} A^i \mathbf b r_{m - 2 - i}$

(Proof omitted.)

Since $A$ is sparse, we can compute $\mathbf b \dots A^{2n - 1} \mathbf b$ directly from the definition.

Again, if $A$ has $k$ non-zero entries, the complexity is $O(kn + n^2)$.

??? note "Reference implementation"
    ```cpp
    vector<int> solve_sparse_equations(const vector<tuple<int, int, int>> &A,
                                       const vector<int> &b) {
      int n = (int)b.size();  // 0-based
    
      vector<vector<int>> f({b});
    
      for (int i = 1; i < 2 * n; i++) {
        vector<int> v(n);
        auto &u = f.back();
    
        for (auto [x, y, z] : A)  // [x, y, value]
          v[x] = (v[x] + (long long)u[y] * z) % p;
    
        f.push_back(v);
      }
    
      vector<int> w(n);
      mt19937 gen;
      for (auto &x : w) x = uniform_int_distribution<int>(1, p - 1)(gen);
    
      vector<int> a(2 * n);
      for (int i = 0; i < 2 * n; i++)
        for (int j = 0; j < n; j++) a[i] = (a[i] + (long long)f[i][j] * w[j]) % p;
    
      auto c = berlekamp_massey(a);
      int m = (int)c.size();
    
      vector<int> ans(n);
    
      for (int i = 0; i < m - 1; i++)
        for (int j = 0; j < n; j++)
          ans[j] = (ans[j] + (long long)c[m - 2 - i] * f[i][j]) % p;
    
      int inv = power(p - c[m - 1], p - 2);
    
      for (int i = 0; i < n; i++) ans[i] = (long long)ans[i] * inv % p;
    
      return ans;
    }
    ```

### Example problems

1.  [LibreOJ #163. Gaussian Elimination 2](https://loj.ac/p/163)
2.  [ICPC 2021 Taipei Gym103443E. Composition with Large Red Plane, Yellow, Black, Gray, and Blue](https://codeforces.com/gym/103443/problem/E)
