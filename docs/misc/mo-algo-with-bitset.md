author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

A bitset is often used for decision and counting problems that ordinary data structures handle poorly, while Mo's algorithm can maintain range information that ordinary data structures handle poorly. Combining the two lets you use the strengths of both.

## Example problem [Ynoi2016 Falling into the Rabbit Hole](https://www.luogu.com.cn/problem/P4688)

This problem fits exactly the pattern of Mo's algorithm with a bitset described above. It is not hard to think of storing, for each interval, all the values that appear in it in a bitset. The answer to a query is then the total length of all the intervals minus the number of elements in the intersection of the three, $\times 3$.

But using a bitset in Mo's algorithm also requires adjusting the algorithm to the properties of bitsets:

1.  A bitset cannot handle the same value appearing several times well. We can insert into the bitset the element's compressed value plus its number of occurrences so far in the current interval.
2.  When we normally use Mo's algorithm, we may not care about the order of the 4 pointer moves. So while the pointers move, the left endpoint of the interval may end up to the right of the right endpoint, giving a negative interval length and thus a negative element count. In other cases this doesn't matter, but in this problem the element inserted into the bitset depends on the element count. So we must order the 4 pointer moves carefully, putting the statements that move the left pointer leftward and the right pointer rightward first, to avoid inserting negative numbers into the bitset.
3.  Although a bitset uses little memory, it still cannot handle a data size of $10 ^ 5 \times 10 ^ 5$. So we split the queries into a constant number of groups and process them separately. This keeps the time complexity unchanged while making the memory just enough.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-with-bitset/mo-algo-with-bitset_1.cpp"
    ```

## Exercises

-   [The Wish of a Refreshing Scumbag](https://www.luogu.com.cn/problem/P3674)
-   [Ynoi2017 Yuno's Cornfield](https://www.luogu.com.cn/problem/P5355)
-   [Ynoi2011 WBLT](https://www.luogu.com.cn/problem/P5313)
