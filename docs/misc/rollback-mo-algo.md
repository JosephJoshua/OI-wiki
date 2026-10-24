author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, YOYO-UIAT

## Introduction

In some problems, when moving between intervals, either adding or deleting an element may be hard to implement. When only adding is hard, or only deleting is hard, we can use rollback Mo's algorithm to solve the problem in $O(n \sqrt m)$ time. The core idea of rollback Mo's algorithm is: since we can only implement one of the operations, we use only that operation and let rollback handle the rest.

There are two kinds of rollback Mo's algorithm: one that uses only additions and one that uses only deletions. Below we only describe the version that uses only additions. The deletion-only version differs from it only slightly in implementation, so we do not cover it separately.

## Example problem [JOISC 2014 Day1 Historical Research](https://loj.ac/problem/2874)

You are given an array $A$ of length $n$ and $m$ queries $(1 \leq n, m \leq 10^5)$. Each query asks for the number with the largest importance in an interval $[L, R]$, and you must **output that importance**. The importance of a number $i$ is defined as $i$ times the number of times $i$ appears in the interval.

In this problem, updating the answer while adding elements is easy, but updating it while deleting elements is hard. If an addition changes the answer, the new answer must be the importance of the number just added. But if a deletion changes which number has the largest importance in the interval, it is hard to figure out which number is the new maximum. So ordinary Mo's algorithm has trouble with this problem.

## How it works

-   Split the original sequence into blocks. Sort the queries using the block index of the left endpoint (ascending) as the first key and the right endpoint (ascending) as the second key.
-   Process the queries in order:
    -   If the block $B$ containing the query's left endpoint differs from the block containing the previous query's left endpoint, set the left end of the Mo's interval to the right end of $B$ plus $1$, and set the right end of the Mo's interval to the right end of $B$.
    -   If the query's left and right endpoints are in the same block, scan the interval directly to answer the query.
    -   If the query's left and right endpoints are in different blocks:
        -   If the query's right endpoint is greater than the right end of the Mo's interval, keep extending the right end until it equals the query's right endpoint.
        -   Keep extending the left end of the Mo's interval until it equals the query's left endpoint.
        -   Answer the query.
        -   Undo the changes made by moving the left end, so that the left end of the Mo's interval rolls back to the right end of $B$ plus $1$.

## Complexity proof

Suppose the block size of rollback Mo's algorithm is $b$:

-   Queries whose left and right endpoints lie in the same block can each be answered in $O(b)$ time.
-   For the other queries, consider those whose left endpoints are in the same block. Their right endpoints increase monotonically, so moving the right end costs $O(n)$ in total, while the left end moves at most $b$ times per query. Since there are $\frac{n}{b}$ blocks, the total complexity is $O(mb+\frac{n^2}{b})$. Choosing $b=\frac{n}{\sqrt{m}}$ is optimal, giving a time complexity of $O(n\sqrt{m})$.

## Implementation

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/rollback-mo-algo/rollback-mo-algo_1.cpp"
    ```

## References

-   [Rollback Mo's Algorithm and Its Simple Applications | Parsnip's Blog](https://www.cnblogs.com/Parsnip/p/10969989.html)
