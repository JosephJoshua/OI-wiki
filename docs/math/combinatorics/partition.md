Partition: a way of writing a natural number $n$ as a sum of positive integers in non-increasing order.

$$
n=r_1+r_2+\ldots+r_k \quad r_1 \ge r_2 \ge \ldots \ge r_k \ge 1
$$

Each positive integer in the sum is called a part.

Partition number: $p_n$, the number of partitions of the natural number $n$.

Partition numbers starting from $0$:

| n     | 0 | 1 | 2 | 3 | 4 | 5 | 6  | 7  | 8  |
| ----- | - | - | - | - | - | - | -- | -- | -- |
| $p_n$ | 1 | 1 | 2 | 3 | 5 | 7 | 11 | 15 | 22 |

## Partitions into k parts

The number of partitions of $n$ into exactly $k$ parts is called the number of partitions into $k$ parts, written $p(n,k)$.

Clearly, $p(n,k)$ is also the number of solutions of the following equation:

$$
n-k=y_1+y_2+\ldots+y_k\quad y_1\ge y_2\ge\ldots\ge y_k\ge 0
$$

If exactly $j$ of the parts in this equation are non-zero, there are exactly $p(n-k,j)$ solutions. So we have the sum:

$$
p(n,k)=\sum_{j=0}^k p(n-k,j)
$$

Taking the difference of two adjacent sums gives:

$$
p(n,k)=p(n-1,k-1)+p(n-k,k)
$$

If we write these in a table, each cell equals the number diagonally up-left of it plus the number that lies, in the same column, as many rows above it as its column index.

| k        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| -------- | - | - | - | - | - | - | - | - | - |
| $p(0,k)$ | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(1,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(2,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(3,k)$ | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 |
| $p(4,k)$ | 0 | 1 | 2 | 1 | 1 | 0 | 0 | 0 | 0 |
| $p(5,k)$ | 0 | 1 | 2 | 2 | 1 | 1 | 0 | 0 | 0 |
| $p(6,k)$ | 0 | 1 | 3 | 3 | 2 | 1 | 1 | 0 | 0 |
| $p(7,k)$ | 0 | 1 | 3 | 4 | 3 | 2 | 1 | 1 | 0 |
| $p(8,k)$ | 0 | 1 | 4 | 5 | 5 | 3 | 2 | 1 | 1 |

### Example problem

???+ note "Computing the number of partitions into k parts"
    Compute the number of partitions into $k$ parts, $p(n,k)$. There are multiple test cases, with $n$ up to $10000$ and $k$ up to $1000$. Output the answer modulo $1000007$.
    
    Looking at the table and the recurrence, updating column by column is better for storage. The program is easy to write:
    
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    int p[10005][1005]; /*number of ways to partition n into k parts*/
    
    int main() {
      int n, k;
      while (~scanf("%d%d", &n, &k)) {
        memset(p, 0, sizeof(p));
        p[0][0] = 1;
        int i;
        for (i = 1; i <= n; ++i) {
          int j;
          for (j = 1; j <= k; ++j) {
            if (i - j >= 0) /*p[i-j][j]: all parts greater than 1*/
            {
              p[i][j] = (p[i - j][j] + p[i - 1][j - 1]) %
                        1000007; /*p[i-1][j-1]: at least one part equals 1.*/
            }
          }
        }
        printf("%d\n", p[n][k]);
      }
    }
    ```

### Generating function

By the formula for the sum of a geometric series:

$$
\frac{1}{1-x^k}=1+x^k+x^{2k}+x^{3k}+\ldots
$$

$$
1+p_1 x+p_2 x^2+p_3 x^3+\ldots=\frac{1}{1-x}  \frac{1}{1-x^2}  \frac{1}{1-x^3}\ldots
$$

For partitions into $k$ parts, the generating function is a bit more complicated. It is:

$$
\sum_{n,k=0}^\infty {p(n,k) x^n y^k }=\frac{1}{1-xy}  \frac{1}{1-x^2 y}  \frac{1}{1-x^3 y}\ldots
$$

### Ferrers diagram

Ferrers diagram: each part of a partition is drawn as a row of dots. The number of dots in a row is the size of that part.

By the definition of a partition, the rows of a Ferrers diagram are arranged in decreasing order, with the longest row on top.

For example, the Ferrers diagram of the partition $12=5+4+2+1$:

![](./images/ferrers.jpg)

Flipping a Ferrers diagram along its diagonal gives a new Ferrers diagram, called the conjugate of the original diagram. The new partition is called the conjugate of the original partition. Clearly, conjugation is a symmetric relation.

For example, the conjugate of the partition $12=5+4+2+1$ above is $12=4+3+2+2+1$.

Number of partitions with largest part $k$: the number of partitions of the natural number $n$ whose largest part is $k$.

From the definition of conjugate, we get an obvious result:

The number of partitions with largest part $k$ equals the number of partitions into $k$ parts; both are $p(n,k)$.

## Partitions into distinct parts

Number of partitions into distinct parts: $pd_n$, the number of partitions of the natural number $n$ in which all parts are different. (d for Different)

| n      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------ | - | - | - | - | - | - | - | - | - |
| $pd_n$ | 1 | 1 | 1 | 2 | 2 | 3 | 4 | 5 | 6 |

Similarly, define $pd(n,k)$ as the number of partitions into $k$ distinct parts. It is the number of solutions of this equation:

$$
n=r_1+r_2+\ldots+r_k\quad r_1>r_2>\ldots>r_k\ge 1
$$

Exactly as before, it is also the number of solutions of this equation:

$$
n-k=y_1+y_2+\ldots+y_k\quad y_1>y_2>\ldots>y_k\ge 0
$$

The difference from before is that, since the parts are distinct, at most one part in the new equation can be zero. The same conclusion holds: if exactly $j$ parts are non-zero, there are exactly $pd(n-k,j)$ solutions, but here $j$ can only be $k$ or $k-1$. This directly gives the recurrence:

$$
pd(n,k)=pd(n-k,k-1)+pd(n-k,k)
$$

Again we can list a table, as for binomial coefficients. Each cell equals the number in the previous column that lies as many rows above it as its column index, plus the number in the same column that lies as many rows above it as its column index.

| k         | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --------- | - | - | - | - | - | - | - | - | - |
| $pd(0,k)$ | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(1,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(2,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(3,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(4,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(5,k)$ | 0 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(6,k)$ | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 |
| $pd(7,k)$ | 0 | 1 | 3 | 1 | 0 | 0 | 0 | 0 | 0 |
| $pd(8,k)$ | 0 | 1 | 3 | 2 | 0 | 0 | 0 | 0 | 0 |

### Example problem

???+ note "Computing the number of partitions into distinct parts"
    Compute the number of partitions into distinct parts $pd_n$. There are multiple test cases, with $n$ up to $50000$. Output the answer modulo $1000007$.
    
    Looking at the table and the recurrence, updating column by column is better for storage. The code saves space in the second dimension by keeping only two adjacent columns.
    
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    int pd[50005][2]; /*number of ways to partition n into k distinct parts*/
    
    int main() {
      int n;
      while (~scanf("%d", &n)) {
        memset(pd, 0, sizeof(pd));
        pd[0][0] = 1;
        int ans = 0;
        int j;
        for (j = 1; j < 350; ++j) {
          int i;
          for (i = 0; i < 350; ++i) {
            pd[i][j & 1] = 0; /*pd[i][j] depends only on pd[][j] and pd[][j-1]*/
          }
          for (i = 0; i <= n; ++i) {
            if (i - j >= 0) /*pd[i-j][j]: all parts greater than 1*/
            {
              pd[i][j & 1] = (pd[i - j][j & 1] + pd[i - j][(j - 1) & 1]) %
                             1000007; /*pd[i-j][j-1]: at least one part equals 1.*/
            }
          }
          ans = (ans + pd[n][j & 1]) % 1000007;
        }
        printf("%d\n", ans);
      }
    }
    ```

### Partitions into odd parts

Number of partitions into odd parts: $po_n$, the number of partitions of the natural number $n$ in which every part is odd. (o for Odd)

There is an obvious identity:

$$
\prod_{i=1}^\infty (1+x^i ) =\frac{\prod_{i=1}^\infty (1-x^{2i} ) }{\prod_{i=1}^\infty (1-x^i ) }=\prod_{i=1}^\infty \frac{1}{1-x^{2i-1} }
$$

The far left is the generating function for partitions into distinct parts, and the far right is the generating function for partitions into odd parts. Their coefficients are equal, so the number of partitions into odd parts equals the number of partitions into distinct parts:

$$
po_n=pd_n
$$

But clearly partitions into $k$ odd parts and partitions into $k$ distinct parts are different concepts, so we do not list them here.

We introduce two more concepts:

Number of even distinct partitions: $pde_n$, the number of partitions of the natural number $n$ into an even number of distinct parts. (e for Even)

Number of odd distinct partitions: $pdo_n$, the number of partitions of the natural number $n$ into an odd number of distinct parts. (o for Odd)

So we have:

$$
pd_n=pde_n+pdo_n
$$

There are also corresponding $k$-part versions. They are too complicated, so we do not list them.

## Pentagonal number theorem

Look at the denominator of the generating function for partition numbers on its own:

$$
\prod_{i=1}^\infty (1-x^i ) 
$$

When we expand it, partitions into distinct parts come to mind, and the sign depends on whether the number of parts is odd or even.

Specifically, partitions into an even number of distinct parts are counted positively in the expansion, and partitions into an odd number of distinct parts are counted negatively. So each coefficient of the expansion is the difference of the two counts. That is:

$$
\sum_{i=0}^\infty ({pde}_n-{pdo}_n ) x^n =\prod_{i=1}^\infty (1-x^i ) 
$$

Next we show that in most cases the two counts are equal, so the coefficient in the expansion is $0$. Only at a few positions do the two counts differ by $1$ or $-1$.

We can do this by constructing a correspondence.

Draw the Ferrers diagram of each partition into distinct parts. The last row is called the bottom of the diagram, and the number of dots on it is $b$ (Bottom). The longest $45$-degree line segment starting from the last dot of the top row and going through dots of the diagram is called the slope of the diagram, and the number of dots on it is $s$ (Slide).

![](./images/bottom_slide.jpg)

To build a correspondence between partitions into an even number of distinct parts and partitions into an odd number of distinct parts, we define transformations that change the number of rows by $1$ while keeping the parts distinct:

Transformation A: when $b$ is at most $s$, move the bottom to the right side, where it becomes a new slope.

Transformation B: when $b$ is greater than $s$, move the slope to the bottom, where it becomes a new bottom.

For most $n$, exactly one of these two transformations can be applied to any partition of $n$ into distinct parts. This gives a one-to-one correspondence between partitions into an even number and an odd number of distinct parts. Two sets in one-to-one correspondence have the same size, so in this case the $n$-th coefficient of the expansion is $0$.

But for some $n$, there is exactly one partition into distinct parts to which neither transformation can be applied.

-   Case 1: when $b=s$ and the bottom and the slope share a dot, transformation A cannot be applied. In this case

$$
n=s+(s+1)+\ldots+(s+s-1)=\frac{s(3s-1)}{2}
$$

The $n$-th term of the expansion depends on whether the number of parts is odd or even, and equals $(-1)^s x^n$.

-   Case 2: when $b=s+1$ and the bottom and the slope share a dot, transformation B cannot be applied. In this case

$$
n=(s+1)+(s+2)+\ldots+(s+s)=\frac{s(3s+1)}{2}
$$

The $n$-th term of the expansion is $(-1)^s x^n$.

Replacing $s$ with $-s$ in the formula above gives $n=\frac{s(3s-1)}{2}$, where $s$ is a negative integer, and the $n$-th term of the expansion is still $(-1)^s x^n$.

Since the two cases never happen for the same $n$, we can combine the two conditions. The condition on $n$ is

$$
\exists k\in\mathbb{Z},n=\frac{k(3k-1)}{2}
$$

So we have proved:

$$
(1-x)(1-x^2 )(1-x^3 )\ldots=\sum_{k=-\infty}^{+\infty} (-1)^k x^{\frac{k(3k-1)}{2}} =\ldots+x^{26}-x^{15}+x^7-x^2+1-x+x^5-x^{12}+x^{22}-\ldots
$$

Recall that this is the reciprocal of the generating function for partition numbers, so its product with that generating function is $1$. Rearranging and comparing coefficients on both sides gives a recurrence for the partition numbers.

$$
(1+p_1 x+p_2 x^2+p_3 x^3+\ldots)(1-x-x^2+x^5+x^7-x^{12}-x^{15}+x^{22}+x^{26}-\ldots)=1
$$

$$
p_n=p_{n-1}+p_{n-2}-p_{n-5}-p_{n-7}+\ldots
$$

This recurrence has infinitely many terms. But if we define the partition number of a negative number to be $0$ (the partition number of $0$ is already defined as $1$), it reduces to finitely many terms.

### Example problem

???+ note "Computing partition numbers"
    Compute the partition number $p_n$. There are multiple test cases, with $n$ up to $50000$. Output the answer modulo $1000007$.
    
    We use the pentagonal number theorem. The code:
    
    ```cpp
    #include <cstdio>
    
    long long a[100010];
    long long p[50005];
    
    int main() {
      p[0] = 1;
      p[1] = 1;
      p[2] = 2;
      int i;
      for (i = 1; i < 50005;
           i++) /*coefficients of the recurrence: 1,2,5,7,12,15,22,26...i*(3*i-1)/2,i*(3*i+1)/2*/
      {
        a[2 * i] = i * (i * 3 - 1) / 2; /*pentagonal numbers are 1,5,12,22...i*(3*i-1)/2*/
        a[2 * i + 1] = i * (i * 3 + 1) / 2;
      }
      for (
          i = 3; i < 50005;
          i++) /*p[n]=p[n-1]+p[n-2]-p[n-5]-p[n-7]+p[12]+p[15]-...+p[n-i*[3i-1]/2]+p[n-i*[3i+1]/2]*/
      {
        p[i] = 0;
        int j;
        for (j = 2; a[j] <= i; j++) /*the value may be negative, so add 1000007*/
        {
          if (j & 2) {
            p[i] = (p[i] + p[i - a[j]] + 1000007) % 1000007;
          } else {
            p[i] = (p[i] - p[i - a[j]] + 1000007) % 1000007;
          }
        }
      }
      int n;
      while (~scanf("%d", &n)) {
        printf("%lld\n", p[n]);
      }
    }
    ```
