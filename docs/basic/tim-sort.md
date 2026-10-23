This page introduces Timsort, a hybrid, stable sorting algorithm.

## Introduction

Timsort was designed in 2002 by Tim Peters, a Python core developer, for use in the Python language. It cleverly combines the strengths of insertion sort and merge sort, and is carefully tuned to take advantage of order that already exists in the data. It works especially well on data that contains many partially sorted subsequences. CPython has used Timsort since version 2.3; starting from version 3.11, its merge-order strategy was replaced with Powersort[^powersort]. Timsort is also widely used in other programming environments. For example, Java SE 7 uses it to sort arrays of non-primitive objects.

This page describes classic Timsort, following the merge rules in CPython 3.6.5, which include the fix for the stack-invariant bug[^merge-policy].

## Steps

The core idea of Timsort is to speed up sorting by finding and using the order that already exists in the data. It has these main steps:

1.  **Find runs**: scan the array to be sorted and find contiguous sorted subsequences (runs);
2.  **Extend runs**: if a run found is shorter than `MIN_RUN`, extend it using insertion sort;
3.  **Merge runs**: Timsort keeps a special stack and uses a specific merge strategy to combine the runs on the stack into longer sorted sequences.

### Finding runs

First, Timsort scans the array from left to right and finds contiguous sorted sequences. These sorted sequences are called runs:

-   **Ascending run**: if the next element is greater than or equal to the previous one, keep extending the run.
-   **Descending run**: if the next element is less than the previous one, keep extending the run, then reverse the run so it becomes ascending.

### Extending runs

To sort small pieces of data efficiently, Timsort sets a minimum run length, `MIN_RUN`. Its value is usually computed from the length of the array to be sorted, and is typically between $32$ and $64$.

-   If the run found has length at least `MIN_RUN`, nothing extra is needed; the run is pushed onto the stack directly.
-   If the run found is shorter than `MIN_RUN`, binary insertion sort is used to insert the elements that follow the run into it, until the run reaches length `MIN_RUN`. Then it is pushed onto the stack.

### Merging runs

In Timsort, merging is managed and controlled with a **stack**. The stack holds the sorted runs found so far, and specific merge rules decide when runs on the stack are merged. The goal is to keep merges balanced and the sort stable.

#### Merge rules

Timsort is a stable sorting algorithm: equal elements keep their original relative order after sorting. To guarantee this, Timsort only ever merges runs that are adjacent and contiguous, never runs that are not adjacent. Non-adjacent runs may contain equal elements, and merging them directly could easily mess up their relative order.

At the same time, to keep merges balanced and limit the number of runs waiting to be merged, Timsort requires every three adjacent runs on the stack to satisfy the following invariants. Call the three runs X, Y and Z, going from the top of the stack toward the bottom:

-   **Condition 1**: `len(Z) > len(Y) + len(X)`
-   **Condition 2**: `len(Y) > len(X)`

When there are only two runs on the stack, `len(Y) > len(X)` is still required. Each time a new run is pushed, `mergeCollapse` checks at most the top four runs on the stack. Call them X, Y, Z, W from the top down. It decides whether to merge in this order[^merge-policy]:

1.  If `len(Z) <= len(Y) + len(X)` or `len(W) <= len(Z) + len(Y)`, merge Y with the shorter of X and Z; if X and Z have the same length, choose X;
2.  Otherwise, if `len(Y) <= len(X)`, merge Y and X;
3.  Otherwise, stop merging for this round and go on to find the next run.

A condition is only checked if all the runs it needs exist. After each merge, X, Y, Z, W are determined again and the process repeats. The figure below shows how the stack changes when X and Y are merged.

![Merge Rules](./images/tim-sort-1.svg)

???+ note "Why check a fourth run?"
    If only the top three runs are checked, a merge might leave the invariant broken deeper in the stack without noticing. For example, push runs of lengths $240,160,50,40,60$ in that order (from bottom to top of the stack). The old rule merges $50$ and $40$, giving $240,160,90,60$. Now the top of the stack satisfies $160>90+60$ and $90>60$, but deeper down we have $240\le160+90$.
    
    This bug breaks the fixed stack-size guarantee that is derived from the whole-stack invariant. CPython fixed the check conditions in 2015[^merge-fix].

#### Merge optimization

To merge runs of different lengths more efficiently and use less extra space, Timsort first uses binary search to pin down exactly which range of elements needs to be processed, and only merges the part that actually has to move. Specifically:

1.  **Find the insertion points**: use binary search to find where the first element of the second run would be inserted in the first run, and where the last element of the first run would be inserted in the second run. This narrows down the range to merge, so only the elements that need to move are processed;

2.  **Temporary buffer**: classic in-place merge algorithms are too slow because they move elements around a lot. To cut this cost, Timsort uses a temporary buffer: it copies the shorter run into the buffer, then copies elements from the buffer back into the original array step by step.

For example, suppose there are two runs A and B:

-   Run A:$[1, 2, 3, 6, 10]$
-   Run B:$[4, 5, 7, 9, 12, 14, 17]$

Using binary search, we find that:

-   Element $4$ should be inserted at the fourth position of run A.
-   Element $10$ should be inserted at the fifth position of run B.

So the first $3$ elements of run A and the last $3$ elements of run B are already in the right place and need no work. We only need to merge $[6, 10]$ from run A with $[4, 5, 7, 9]$ from run B. The merge process is shown below:

![Timsort Merge](./images/tim-sort-2.apng)

#### Galloping mode

To make merging even faster, Timsort introduces **galloping mode**. In a normal merge, the algorithm compares elements of the two runs one by one and puts the smaller one into the result. But if one run has a long stretch of consecutive elements that are all smaller than the current element of the other run, comparing them one by one wastes time.

To solve this, Timsort sets a threshold `Min_Gallop` (default $7$). When elements from one run "win" the comparison `Min_Gallop` times in a row, the algorithm enters galloping mode to locate positions quickly. The steps are:

1.  **Exponential search**: starting from the current position, the algorithm searches in one run with exponentially growing steps $(1, 2, 4, 8, \dots)$ until it finds a range that contains the target element;
2.  **Binary search**: once the range containing the target element is known, the algorithm uses binary search inside that range to find the exact position of the target element.

This way, Timsort can skip many unnecessary comparisons and quickly handle a long stretch of consecutive smaller (or larger) elements in one run, moving them into the merged result in one batch.

However, galloping mode is not faster in every case. For some data distributions, it can lead to more comparisons. So Timsort adjusts dynamically:

-   **Threshold adjustment**: it keeps a variable `Min_Gallop` parameter. When galloping mode works well (that is, elements keep being taken from the same run many times in a row), `Min_Gallop` is decreased by $1$, encouraging further use of galloping mode. When galloping mode works poorly (the algorithm keeps switching between the two runs), `Min_Gallop` is increased by $1$, making galloping mode less frequent.

By adjusting `Min_Gallop` on the fly, the algorithm strikes a balance between normal merging and galloping mode based on the actual data. For partially or highly sorted data, galloping mode can greatly improve efficiency, bringing Timsort's performance close to $O(n)$. For random data, the algorithm gradually leans toward normal merging, which keeps the time complexity at $O(n \log n)$.

## Complexity

The time complexity of Timsort depends on how sorted the data already is:

-   **Best case**: $O(n)$
    -   When the data is already sorted or nearly sorted, the runs found have length close to $n$, there are fewer merges, and the complexity approaches $O(n)$.
-   **Worst case**: $O(n \log n)$
    -   If there are $r$ runs, $r-1$ two-way merges are needed in the end; the number of merges cannot be written as $O(\log n)$.

Finding runs costs $O(n)$, and extending short runs with a bounded `MIN_RUN` also costs $O(n)$ in total. The cost of merging is the sum, over all merges, of the lengths of the two runs being merged. This equals the sum, over all elements, of the number of merges each element takes part in. The upper bound on this sum depends on the exact merge rules. For the Python 3.6.5 TimSort merge rules analyzed in the paper[^complexity], amortized analysis gives $O(n+n\log r)$, so the worst case is $O(n\log n)$.

As for space complexity, Timsort needs roughly $O(n)$ extra space for the stack and the temporary buffer, so the total space complexity is $O(n)$.

## Implementation

???+ note "Pseudocode"
    $$
    \begin{array}{ll}
    1 & \textit{nRemaining} \gets \text{array length} \\
    2 & \textit{minRun} \gets \text{choose a suitable MinRun value}(\textit{nRemaining}) \\
    3 & \textit{startIndex} \gets 0 \\
    4 & \textbf{while } \textit{nRemaining} > 0 \ \textbf{do} \\
    5 & \qquad \textit{runLength} \gets \text{find run }(\textit{array}, \textit{startIndex}, \textit{nRemaining}) \\
    6 & \qquad \textbf{if } \textit{runLength} < \textit{minRun} \ \textbf{then} \\
    7 & \qquad \qquad \textit{extendLength} \gets \min(\textit{minRun}, \textit{nRemaining}) \\
    8 & \qquad \qquad \text{extend the range } [\textit{startIndex}, \textit{startIndex} + \textit{extendLength} - 1] \text{ using insertion sort}\\
    9 & \qquad \qquad \textit{runLength} \gets \textit{extendLength} \\
    10 & \qquad \textbf{end if} \\
    11 & \qquad \text{push run } (\textit{startIndex}, \textit{runLength}) \text{ onto the stack} \\
    12 & \qquad \textbf{call } \text{mergeCollapse(stack)} \ \text{to check and merge runs on the stack} \\
    13 & \qquad \textit{startIndex} \gets \textit{startIndex} + \textit{runLength} \ \text{update the start position} \\
    14 & \qquad \textit{nRemaining} \gets \textit{nRemaining} - \textit{runLength} \ \text{update the remaining length} \\
    15 & \textbf{end while} \\
    16 & \textbf{call } \text{mergeForceCollapse(stack)} \ \text{to do the final merge of all runs on the stack} \\
    \end{array}
    $$

## References and notes

1.  [Timsort](https://en.wikipedia.org/wiki/Timsort)
2.  [Tim Peters's design notes (CPython 3.6.5; for the merge conditions, the code of the matching version is authoritative)](https://github.com/python/cpython/blob/v3.6.5/Objects/listsort.txt)
3.  [Java implementation](https://cs.android.com/android/platform/superproject/main/+/main:libcore/ojluni/src/main/java/java/util/TimSort.java)
4.  [C implementation (CPython 3.6.5)](https://github.com/python/cpython/blob/v3.6.5/Objects/listobject.c)

[^complexity]: [On the Worst-Case Complexity of TimSort](https://drops.dagstuhl.de/opus/volltexte/2018/9467/pdf/LIPIcs-ESA-2018-4.pdf).

[^powersort]: [CPython: commit adopting the Powersort merge-order strategy](https://github.com/python/cpython/commit/5cb4c672d855033592f0e05162f887def236c00a); [CPython 3.11 notes on the merge strategy](https://github.com/python/cpython/blob/v3.11.0/Objects/listsort.txt#L329-L347).

[^merge-policy]: [CPython 3.6.5: `merge_collapse`](https://github.com/python/cpython/blob/v3.6.5/Objects/listobject.c#L1816-L1849).

[^merge-fix]: [CPython Issue 23515: Bad logic in timsort's merge\_collapse](https://bugs.python.org/issue23515).
