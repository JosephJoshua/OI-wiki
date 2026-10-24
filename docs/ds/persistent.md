author: morris821028

## Overview

A persistent data structure always keeps every historical version, and its operations are immutable (they do not change existing versions).

## Kinds of persistence

### Partially persistent

Every version can be accessed, but only the newest version can be modified.

### Fully persistent

Every version can be both accessed and modified.

If it also supports merging two historical versions, it is called confluently persistent

## Applications

### Computational geometry

Computational geometry has many offline algorithms. For example, a sweep line algorithm answers all queries in a single sweep, which gives an excellent time complexity. But if the problem forces online queries and we sweep once per query, each query goes from logarithmic time to linear time. Persistence offers another way of thinking about this case: we treat the sweep line's time axis as the thing that changes and make the related structures persistent. As long as a query can jump to any point on this time axis in logarithmic time, we can answer the earlier problem online.

### String processing

Persistence allows very efficient concatenation and avoids the slowdown caused by creating lots of duplicate strings, so all kinds of operations can run far faster than linear time. For example, the C++ rope is a persistent data structure. Beyond strings, persistence is useful whenever the data contains a lot of repetition.

### Version rollback

This is essentially the redo/undo found in most software. If a database or set of operations uses a complex structure for efficiency (unlike a hash table or set, where undoing an operation takes only constant or logarithmic time), then a persistent structure reduces the cost of redo/undo by making it fast to roll back changes.

A database itself can roll back in constant time by just recording what changed. But for computations at the application layer, most implementations throw away the cache and recompute a new structure from scratch. Sometimes the change being rolled back has size m, yet recomputing the structure costs n+m. If n is much larger than m, repeated rollbacks feel very slow.

### Functional programming

Functional programming needs special data structures that fit the language's features. Immutability is especially important, since it helps with parallel environments and debugging. For example, Java, an object-oriented language, introduced streams in Java 8 to support writing functional-style code, which offers special features such as lazy evaluation and infinite ranges.

## References

-   <https://en.wikipedia.org/wiki/Persistent_data_structure>
-   MIT course <https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-854j-advanced-algorithms-fall-2005/lecture-notes/persistent.pdf>
