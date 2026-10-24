Prerequisites: [sqrt decomposition](../ds/decompose.md).

Plain table lookup ("hard-coding the answers") means computing the answers for all possible inputs during the contest and saving them, then putting the answers into an array in your code and simply printing the right one.

Note that this trick only works when the range of the input is small (for example, the input is a single number with a small range). Otherwise the code may become too long, you may get MLE, or computing the table may take too long.

???+ note "Example problem"
    Let $f(x)$ be the number of $1$s in the binary representation of the integer $x$. Given a positive integer $n$ ($n\leq 10^9$), output $\sum_{i=1}^n f^2(i)$.

If we put the value $f(n)$ into the table for every single $n$, then besides possibly getting MLE, the code might also exceed the maximum code length limit and fail to compile.

Let's shrink this answer table. Using the idea of [sqrt decomposition](../ds/decompose.md), we choose a reasonable step size $m$ (usually chosen based on the code length limit). For the $i$-th block, we compute the value of:

$$
\sum_{k=\frac{n}{m}(i-1)+1}^{\frac{ni}{m}} f^2(k)
$$

and store it.

Then, when answering, we use the same block idea: for whole blocks, use the precomputed values; for the leftover part that is not a whole block, compute the answer by brute force.

In general, this kind of problem is one where computing a single value $f(x)$ is fast, but you need to sum (or multiply, or combine with some other quickly mergeable operation) a huge number of values, so plain enumeration exceeds the time limit. If you can't find the intended solution, a segmented lookup table is a good option.

???+ note "Notes"
    If the exponent in the problem above were not fixed but had a small range, you could still consider a lookup table.

### Example problems

["BZOJ 3798" Special Primes](https://hydro.ac/p/bzoj-P3798): count how many primes in the interval $[l,r]$ can be written as the sum of squares of two positive integers.

["Luogu P1822" Magic Fingerprint](https://www.luogu.com.cn/problem/P1822)
