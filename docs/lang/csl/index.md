## The C++ standard

First, let's talk about the versions of C++ itself. C++ is just a language, and different compilers implement it in different ways, so a standard is needed to constrain how compilers implement it, so that C++ code behaves the same under different compilers. Since C++ was born in 1985, the International Organization for Standardization (ISO) has published 7 official C++ standards: C++98, C++03, C++11 (also called C++0x), C++14 (also called C++1y), C++17 (also called C++1z), C++20 (also called C++2a) and C++23 (also called C++2b). Drafts of the C++ standard are on the [open-std](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/) website, and you can follow the progress of the latest standard at [Current Status : Standard C++](https://isocpp.org/std/status). There are also some supplementary standards, such as C++ TR1.

Each version of the C++ standard specifies not only the syntax and language features of C++, but also the specification of a built-in library: the C++ standard library. The C++ standard library contains implementations of a lot of commonly used code, such as input/output, basic data structures, memory management and multithreading support. Mastering the C++ standard library is a necessary step toward writing more modern C++ code. Detailed documentation for the C++ standard library is on the [cppreference](https://zh.cppreference.com/) website. It covers the usage, efficiency and caveats of the types and functions in the standard library, so make good use of it.

Note that different OJ platforms support different C++ versions. For example, the [latest ICPC contest rules](https://docs.icpc.global/worldfinals-programming-environment/) support the C++20 standard. By a resolution of the NOI Scientific Committee, since September 1, 2021, [NOI Linux 2.0](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml) has been used as the standard environment for NOI-series contests and events such as CSP-J/S. The g++ 9.3.0 specified in NOI Linux 2.0 [supports C++14 by default](https://gcc.gnu.org/projects/cxx-status.html#cxx14) and also supports C++17, which meets the needs of the vast majority of contestants. So when learning C++, pay attention to the standard your contest supports, to avoid compile errors during the contest.

## The Standard Template Library (STL)

The STL (Standard Template Library) is part of the C++ standard library. It contains templated, general-purpose data structures and algorithms. Because it is templated, it works with your own data types and saves you from a lot of reinventing the wheel. Both NOI and ICPC allow the STL, so using it well saves you from writing unnecessary algorithms and lets you benefit from the compiler's optimizations of the template library. For details on the STL, see the corresponding pages: [STL containers](./container.md) and [STL algorithms](./algorithm.md).

??? note "What is reinventing the wheel?"
    Reinventing the wheel ([Reinventing\_the\_wheel](https://en.wikipedia.org/wiki/Reinventing_the_wheel)) means inventing an existing algorithm again, or rewriting code that already exists and is already optimized. Reinventing the wheel usually takes a lot of time and effort, and the result is often worse than what others have made. But for learning or practice, reinventing the wheel is necessary.

## The Boost libraries

[Boost](https://www.boost.org/) is another well-known open-source C++ library collection besides the standard library. Its code is portable, high-quality, high-performance and highly reliable. Boost has a very large number of modules with comprehensive functionality and full cross-platform support, so it is seen as a quasi-standard library for C++. Many features in the C++ standard come from Boost, such as smart pointers, metaprogramming, and dates and times. Although you cannot use Boost in OI, Boost has many "wheels" you can use to verify algorithms or for stress testing: Boost.Geometry has an R-tree implementation, Boost.Graph has graph algorithms, and Boost.Intrusive provides intrusive containers used much like STL containers. Interested readers can search online for tutorials.

## References

1.  [C++ reference](https://en.cppreference.com/)
2.  [C++ reference manual (Chinese)](https://zh.cppreference.com/)
3.  [Wikipedia - C++](https://zh.wikipedia.org/wiki/C%2B%2B)
4.  [Boost official website](https://www.boost.org/)
5.  [Boost tutorial website](https://theboostcpplibraries.com/)
