The STL provides about 100 template functions that implement algorithms. Most of them are in `<algorithm>`, and some are in `<numeric>` and `<functional>`. For the complete list of functions, [see the reference manual](https://zh.cppreference.com/w/cpp/algorithm); for sorting, see [the page on sorting](../../basic/stl-sort.md).

-   `find`: linear search. `find(v.begin(), v.end(), value)`, where `value` is the value to look for.

-   `reverse`: reverses an array or string. `reverse(v.begin(), v.end())` or `reverse(a + begin, a + end)`.

-   `unique`: removes adjacent duplicate elements in a container. `unique(ForwardIterator first, ForwardIterator last)` returns an iterator to the end of the container **after deduplication**; the size of the original container does not change. Combined with `sort`, it removes all duplicates from a container.

-   `random_shuffle`: randomly shuffles an array. `random_shuffle(v.begin(), v.end())` or `random_shuffle(v + begin, v + end)`.

    ???+ warning "The `random_shuffle` function has been removed from the latest C++ standard"
        `random_shuffle` was deprecated in C++14 and removed in C++17.
        
        In C++11 and later standards, you can use the `shuffle` function instead of the old `random_shuffle`. Use it as `shuffle(v.begin(), v.end(), rng)` (the last argument is the random number generator to use; usually this is the Mersenne Twister pseudo-random generator [`mt19937`](https://zh.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine), seeded with the true random number generator [`random_device`](https://zh.cppreference.com/w/cpp/numeric/random/random_device)).
        
        ```cpp
        // #include <random>
        std::mt19937 rng(std::random_device{}());
        std::shuffle(v.begin(), v.end(), rng);
        ```

-   `sort`: sorting. `sort(v.begin(), v.end(), cmp)` or `sort(a + begin, a + end, cmp)`, where `end` is one past the last element of the array to sort and `cmp` is a custom comparison function.

-   `stable_sort`: stable sorting. Used the same way as `sort()`.

-   `nth_element`: partitions by a given position, that is, finds the $n$-th largest element of the sequence so that everything to its left is smaller and everything to its right is larger. `nth_element(v.begin(), v.begin() + n, v.end(), cmp)` or `nth_element(a + begin, a + begin + n, a + end, cmp)`.

-   `binary_search`: binary search. `binary_search(v.begin(), v.end(), value)`, where `value` is the value to look for.

-   `merge`: **merges** two (sorted) sequences **in order** into a third sequence through an **insert iterator**. `merge(v1.begin(), v1.end(), v2.begin(), v2.end() ,back_inserter(v3))`.

-   `inplace_merge`: **merges in place** two ranges (sorted by the less-than operator), `[first,middle), [middle,last)`, **into one sorted sequence**. `inplace_merge(v.begin(), v.begin() + middle, v.end())`.

-   `lower_bound`: binary search in a sorted sequence; returns an iterator to the first element **greater than or equal to**  $x$. If there is no such element, it returns the end iterator. `lower_bound(v.begin(),v.end(),x)`.

-   `upper_bound`: binary search in a sorted sequence; returns an iterator to the first element **greater than**  $x$. If there is no such element, it returns the end iterator. `upper_bound(v.begin(),v.end(),x)`.

    ???+ warning "Time complexity of `lower_bound` and `upper_bound`"
        On an ordinary array, both functions run in $O(\log n)$ time. But on associative containers such as `set`, calling `lower_bound(s.begin(),s.end(),val)` directly takes $O(n)$ time.
        
        Associative containers such as `set` already provide member functions like `lower_bound` (called as `s.lower_bound(val)`), and calling them this way takes $O(\log n)$ time.

-   `next_permutation`: changes the current permutation into **the next permutation among all permutations**. If the current permutation is already **the last of all permutations** (elements in strictly decreasing order), the function returns `false` and changes it into **the first of all permutations** (elements in increasing order); otherwise, it returns `true`. `next_permutation(v.begin(), v.end())` or `next_permutation(v + begin, v + end)`.

-   `prev_permutation`: changes the current permutation into **the previous permutation among all permutations**. Used the same way as `next_permutation`.

-   `partial_sum`: computes prefix sums. With source container $x$ and destination container $y$, it sets $y[i]=x[0]+x[1]+\dots+x[i]$. `partial_sum(src.begin(), src.end(), back_inserter(dst))`.

### Usage examples

-   Use `next_permutation` to generate all permutations of $1$ to $9$. Example problem: [Luogu P1706 Full Permutation Problem](https://www.luogu.com.cn/problem/P1706)

    ???+ note "Implementation"
        ```cpp
        int N = 9, a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        do {
          for (int i = 0; i < N; i++) cout << a[i] << " ";
          cout << endl;
        } while (next_permutation(a, a + N));
        ```
-   Use `lower_bound` and `upper_bound` to find the boundaries between elements less than $x$, equal to $x$ and greater than $x$ in a sorted array $a$.

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 1, 2, 4, 5, 5, 7, 7, 9, 9}, x = 5;
        int i = lower_bound(a, a + N, x) - a, j = upper_bound(a, a + N, x) - a;
        // a[0] ~ a[i - 1] are the elements less than x, a[i] ~ a[j - 1] are the elements equal to x,
        // a[j] ~ a[N - 1] are the elements greater than x
        cout << i << " " << j << endl;
        ```
-   Use `partial_sum` to compute the prefix sums of the elements in $src$ and store them in $dst$.

    ???+ note "Implementation"
        ```cpp
        vector<int> src = {1, 2, 3, 4, 5}, dst;
        // Compute prefix sums of src: dst[i] = src[0] + ... + src[i]
        // back_inserter works on the dst container and provides an iterator
        partial_sum(src.begin(), src.end(), back_inserter(dst));
        for (unsigned int i = 0; i < dst.size(); i++) cout << dst[i] << " ";
        ```
-   Use `lower_bound` to find the element closest to $x$ in a sorted array $a$. Example problem: [UVa10487 Closest Sums](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1428)

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 1, 2, 4, 5, 5, 8, 8, 9, 9}, x = 6;
        // lower_bound returns the address of the first element in a that is >= x; i is its index
        int i = lower_bound(a, a + N, x) - a;
        // a[i] (the first element in a that is >= x) is the answer in these two cases:
        // 1. even the smallest element of a is >= x;
        // 2. a has an element >= x, and the first such element (a[i])
        // is closer to x than the last element less than x (a[i - 1]);
        // otherwise, a[i - 1] (the last element in a that is < x) is the answer
        if (i == 0 || (i < N && a[i] - x < x - a[i - 1]))
          cout << a[i];
        else
          cout << a[i - 1];
        ```
-   Use `sort` and `unique` to find **the $k$-th smallest value** in array $a$ (note: a value that appears several times counts only once, so this is not the $k$-th smallest element). Example problem: [Luogu P1138 The k-th Smallest Integer](https://www.luogu.com.cn/problem/P1138)

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 3, 3, 7, 2, 5, 1, 2, 4, 6}, k = 3;
        sort(a, a + N);
        // unique returns the address just past the last element after deduplication; cnt is the length after deduplication
        int cnt = unique(a, a + N) - a;
        cout << a[k - 1];
        ```
