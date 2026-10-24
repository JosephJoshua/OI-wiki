author: HeRaNO, Xeonacid, saffahyjp

The full name of the pb\_ds library is Policy-Based Data Structures.

The pb\_ds library wraps many data structures, such as hash tables, balanced binary search trees, tries and heaps (priority queues).

Just like `vector`, `set` and `map`, its components follow the STL interface conventions. Some of them (such as the priority queue) include all the features of the corresponding STL component and add more.

pb\_ds can only be used with compilers whose standard library is libstdc++.

You can use `begin()` and `end()` to get an `iterator` and iterate over the elements

You can `increase_key`, `decrease_key` and delete individual elements

Since the main content of pb\_ds lives in the `__gnu_pbds` namespace, which starts with an underscore, whether it was allowed in NOI-series contests was long unclear. On September 1, 2021, the [Supplementary Notes on Restrictions on Programming Language Use in NOI-Series Contests](https://www.noi.cn/xw/2021-09-01/735729.shtml) allowed library functions and macros that start with an underscore (except those that perform explicitly forbidden operations). This gave an official written basis for using pb\_ds in NOI-series contests.

**Reference: [Applications of the C++ pb\_ds Library in OI](https://github.com/OI-Wiki/libs/blob/master/lang/pb-ds/C%2B%2B的pb_ds库在OI中的应用.pdf)**
