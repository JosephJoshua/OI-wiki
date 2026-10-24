author: ouuan, HeRaNO

A heap is a tree in which every node has a key, and every node's key is greater than or equal to (or less than or equal to) its parent's key.

A heap where every node's key is greater than or equal to its parent's key is called a min-heap; otherwise it is called a max-heap. [The STL `priority_queue`](../lang/csl/container-adapter.md#priority-queue) is actually a max-heap.

The main operations supported by a (min-)heap are: insert a number, find the minimum, delete the minimum, merge two heaps, and decrease the value of an element.

Some more powerful heaps (mergeable heaps) can also support operations such as merge (efficiently).

Some even more powerful heaps also support persistence, that is, querying or operating on any past version to produce a new version.

## Types of heaps

| Operation `\` data structure[^ref4] | Pairing heap | Binary heap | Leftist heap | Binomial heap | Fibonacci heap |
| :---------------------: | :--------------------------------------------------------------------------: | :----------: | :----------: | :------------------: | :----------------: |
| insert | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$[^ref1] | $O(1)$ |
| find-min | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$[^ref2][^ref3] | $O(1)$ |
| delete-min | $O(\log n)$[^ref3] | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$[^ref3] |
| merge | $O(1)$ | $O(n)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ |
| decrease-key | $o(\log n)$ (lower bound $\Omega(\log \log n)$, upper bound $O(2^{2\sqrt{\log \log n}})$)[^ref3] | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$[^ref3] |
| Persistent? | $\times$ | $\checkmark$ | $\checkmark$ | $\checkmark$ | $\times$ |

[^ref1]: A single insertion costs $O(\log n)$. But for $k$ consecutive insertions, you can build a binomial heap containing only the new elements and then merge it with the original binomial heap, giving an amortized cost of $O(1)$.

[^ref2]: You can keep a pointer to the minimum element and update it during other operations. Then a query takes $O(1)$.

[^ref3]: Amortized complexity.

[^ref4]: The table comes from [Wikipedia](https://en.wikipedia.org/wiki/Priority_queue#Summary_of_running_times).

By convention, when people say "heap" without any qualifier, they usually mean a binary heap.
