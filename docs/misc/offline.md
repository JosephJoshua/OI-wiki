This chapter introduces the idea of offline algorithms, along with common offline algorithms and optimizations.

Offline algorithms are designed under the assumption that "**all the data is known before solving**". They suit problems with many queries. The opposite is an [online algorithm](https://en.wikipedia.org/wiki/Online_algorithm).

For example, [selection sort](../basic/selection-sort.md) needs to know the global minimum of the array before it can run, so it is an offline algorithm. [Insertion sort](../basic/insertion-sort.md), on the other hand, can take in data and sort it as it arrives, without needing all the data in advance, so it is an online algorithm.

For the same problem, offline algorithms are often easier to design than online ones. To stop contestants from using offline algorithms, problems sometimes "force online" processing. A common way is to make the parameters of each query depend on the answer to the previous query ([interactive problems](../contest/problems.md#交互题) and [communication problems](../contest/problems.md#通信题) also belong to this category).

Common ideas in offline algorithms include solving all queries together (such as [CDQ divide and conquer](./cdq-divide.md)), and getting the answer to one query from the answer to a similar query (such as [parallel binary search](./parallel-binsearch.md) and [Mo's algorithm](./mo-algo-intro.md)).

Since offline processing is an idea rather than one specific algorithm, it is combined with many kinds of data structures and algorithms, and the related problems are quite varied.
