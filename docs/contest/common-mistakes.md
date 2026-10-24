author: Estrella-Explore, H-J-Granger, orzAtalod, ksyx, Ir1d, Chrogeek, Enter-tainer, yiyangit, shuzhouliu, broken-paint, CarvingAn

This page lists some mistakes that many people often make in contests.

## Mistakes caused by different environments

-   Using the `%I64d` format specifier in `scanf` or `printf` may cause wrong input/output formatting on Linux.

## Mistakes that cause CE

These are mostly lexical, syntax and semantic errors. Their causes are fairly simple, and they are easy to fix.

Examples:

-   Typos such as writing `int main()` as `int mian()`.

-   Forgetting the semicolon after a `struct` or `class`.

-   Making an array too large, using a forbidden function (on an OJ; for example, multithreading), or declaring a function without defining it causes a linker error.

-   Mismatched function argument types.

    -   Example: when using the `max` function from the `<algorithm>` header, passing one argument of type `int` and one of type `long long`.

        ```cpp
        // query is a user-defined function that returns long long
        printf("%lld\n", max(0, query(1, 1, n, l, r));

        // error    no instance of overloaded function "std::max" matches the argument list
        ```

-   Skipping the initialization of some local variables when using `goto` and `switch-case`.

## Mistakes that don't cause CE but do cause warnings

Programs with these mistakes compile, but they will very likely produce wrong results when run. The compiler points out these mistakes when you compile with `-W{warningtype}` options.

-   Mixing up the assignment operator `=` and the comparison operator `==`.

    -   Example:

        ```cpp
        std::srand(std::time(nullptr));
        int n = std::rand();
        if (n = 1)
          printf("Yes");
        else
          printf("No");

        // whatever random value n gets, the output is always Yes
        // warning    incorrect operator: assignment of constant in Boolean context. Consider using "==" instead.
        ```

    -   If you really want to use `=` where `==` would normally go (for example `while (foo = bar)`) and don't want a warning, you can use **double parentheses**: `while ((foo = bar))`.

-   Mistakes caused by operator precedence.

    -   Example:

        ```cpp
        // wrong
        // std::cout << (1 << 1 + 1);
        // correct
        std::cout << ((1 << 1) + 1);

        // warning    "<<": check operator precedence for possible error; use parentheses to clarify precedence
        ```

-   Using the `static` specifier incorrectly.

-   Forgetting the address-of operator `&` when reading with `scanf`.

-   Argument types that don't match the format specifiers in `scanf` or `printf`.

-   Using bitwise operators together with the comparison operator `==` without parentheses.
    -   Example: `(x >> j) & 3 == 2`

-   `int` literal overflow.

    -   Example: `long long x = 0x7f7f7f7f7f7f7f7f`, `1<<62`.

-   Uninitialized local variables.

    ???+ note "What happens with uninitialized variables"
        Original post: <https://loj.ac/d/3679> by @hly1204
        
        For example, if we declare `int a;` in C++ without initializing it, we might think `a` holds a "random" value (which may not really be random), and we might treat it as some fixed value. But in reality that is not the case.
        
        In a simple test program
        
        <https://wandbox.org/permlink/T2uiVe4n9Hg4EyWT>
        
        the code is:
        
        ```cpp
        #include <iostream>
        
        int main() {
          int a;
          std::cout << std::boolalpha << (a < 0 || a == 0 || a > 0);
          return 0;
        }
        ```
        
        With some compilers and environments, when optimization is turned on, the output is false.
        
        If you're interested, see <https://www.ralfj.de/blog/2019/07/14/uninit.html>. Although its experiments use Rust, the underlying issue is the same.

-   A local variable with the same name as a global variable, so the global variable is accidentally shadowed. (Turning on `-Wshadow` catches this kind of mistake.)

-   Output mistakes caused by operator overloading.
    -   Example:

        ```cpp
        // Intended: the first << is the overloaded operator for output; the second << is the shift operator, shifting 1
        // left by 1 bit. But because the parentheses were forgotten, the compiler treats the second <<
        // as an output operator too, so the output differs from what was expected. Wrong: std::cout << 1 << 1; Correct:
        std::cout << (1 << 1);
        ```

## Mistakes that cause neither CE nor warnings

The compiler can't find these mistakes; you have to track them down yourself.

### Mistakes that cause WA

-   Not clearing arrays after finishing one test case and before reading the next.

-   Fast input that doesn't handle negative numbers.

-   Overflow because the data type is not wide enough.
    -   As the Chinese saying goes, "three years of OI all wasted: forget `long long` and you're done for". The contestant loses points because they didn't use `long long` in the right places (that is, define the integers as `long long`), and got a wrong answer.

-   When storing a graph, node numbers start from 0, but the endpoints of the edges in the problem are numbered from 1, and you forget to subtract 1 when reading.

-   Typing the wrong greater-than/less-than sign, or getting it backwards.

-   Mixing the two kinds of IO, `scanf/printf` and `std::cin/std::cout`, after calling `ios::sync_with_stdio(false);`, which scrambles input/output.

    -   Example:

        ```cpp
        // This example shows what happens if you mix the two kinds of IO after turning off sync with stdio
        // Try stepping through it to see the effect
        #include <cstdio>
        #include <iostream>

        int main() {
          // With sync turned off, cin/cout use their own buffer instead of syncing output to the scanf/printf
          // buffer, which reduces IO time
          std::ios::sync_with_stdio(false);
          // with cout, when '\n' is used for a newline, the content is buffered and not printed immediately
          std::cout << "a\n";
          // printf's '\n' flushes printf's buffer, so the output comes out in the wrong order
          printf("b\n");
          std::cout << "c\n";
          // cout's buffer is only printed when the program ends
          return 0;
        }
        ```

-   Mistakes caused by macro expansion without parentheses.

    -   Example: the value this macro returns is not $4^2 = 16$ but $2+2\times 2+2 = 8$.

        ```cpp
        #define square(x) x* x
        printf("%d", square(2 + 2));
        ```

-   Arithmetic mistakes caused by not using `unsigned` when hashing.
    -   Right-shifting a negative number fills the highest bit with 1. See: [Bitwise operators](../lang/op.md#bitwise-operators).

-   Not deleting or commenting out debug output statements.

-   Adding a stray `;`.

    -   Example:

        ```cpp
        /* clang-format off */
        while (1);
            printf("OI Wiki!\n");
        ```

-   Wrong sentinel values. For example, node `0` in a balanced binary search tree.

-   When initializing variables with `:` in the constructor of a class or struct, the declaration order of the variables doesn't match the dependencies between their initializations.

    -   Member variables are initialized in the order they are declared in the class, not in the order they appear in the initializer list. See: "Initialization order" in [Constructors and member initializer lists](https://zh.cppreference.com/w/cpp/language/constructor)
    -   Example:

        ```cpp
        #include <iostream>

        class Foo {
         public:
          int a, b;

          // a is initialized before b, so its value is indeterminate
          Foo(int x) : b(x), a(b + 1) {}
        };

        int main() {
          Foo bar(1, 2);
          std::cout << bar.a << ' ' << bar.b;
        }

        // possible output: -858993459 1
        ```

-   When merging sets in a disjoint set union, not merging the roots of the two elements.

    -   Example:

        ```cpp
        f[a] = b;              // wrong
        f[find(a)] = find(b);  // correct
        ```

-   Using `a` (append mode) with `freopen`
    -   The CCF judging environment doesn't clear the output files, so using `a` makes the judge also read the previous contestant's output, which causes WA

#### Different newline characters

???+ warning "Warning"
    In official contests, the environment where contestants solve problems is kept as close as possible to the final judging environment.
    
    This section only applies to cases like mock contests, and we also recommend that problem setters make their data follow the [data format](problemsetting.md#data-format) as much as possible.

Different operating systems use different characters to mark a newline. Here are the newline characters of some common systems:

-   LF (written as `\n`): `Unix` or `Unix`-compatible systems

-   CR+LF (written as `\r\n`): `Windows`

-   CR (written as `\r`): `Mac OS` version 9 and earlier

C/C++ uses the escape sequence `\n` for a newline. This may make us assume that newlines in the input are always `\n` too, so we read only one character for the newline, and as a result we don't read the whole input file correctly.

Here are some solutions:

-   Call `getchar()` repeatedly until you read the character you want.

-   Read with `cin`. **This may increase the constant factor of your code**.

-   Read a string with `scanf("%s",str)`, then take `str[0]` as the character read.

-   Use `scanf(" %c",&c)` to skip all whitespace characters.

### Mistakes with unpredictable results

Undefined behavior leads to unpredictable results, such as WA or RE. Compilers usually assume your program has no undefined behavior, which is why code can behave differently with and without O2.

-   Dividing by 0 (computing the inverse of 0)

    ???+ warning "Example"
        ```cpp
        cout << x / 0 << endl;
        ```

-   Array (index) out of bounds

    For example:

    -   Setting the initial value of a loop wrong, so that index -1 is accessed.

    -   Not making the edge list of an undirected graph twice as large.

    -   Not giving a segment tree 4 times the space.

    -   Misreading the constraints and typing one zero too few.

    -   Misestimating the space complexity of the algorithm.

    -   When writing a segment tree, calling `pushup` or `pushdown` on a leaf node.

        The right approach: don't go out of bounds. Remember to check your code so that every index `x` you access is within the declared range.

-   A function other than main that returns a value reaches its end without executing any return statement

    Even if one branch returns a value, if other branches don't, the result is still undefined.

    You can add `-Wall` to the compiler options and see whether the compiler warns about functions that don't return.

-   Trying to modify a string literal

    ???+ warning "Example"
        ```cpp
        char *p = "OI-wiki";
        p[0] = 'o';
        p[1] = 'i';
        ```

    Trying to modify a string literal like this causes **undefined behavior**. Use another **suitable** data type instead, such as `std::string` or `char[]`.

-   Freeing the same memory several times / dereferencing invalid memory

    For example:

    -   Dereferencing a pointer before initializing it.

    -   The memory the pointer points to has already been freed.

        When using `erase`, `delete` or `free`, be careful not to use them on the same address/object more than once.

-   Trying to free part of a whole block of memory allocated by `new []`

    For example:

    ```cpp
    object *pool = new object[POOL_SIZE];

    object *pointer = pool + 10;

    // error!
    delete pointer;
    ```

    This often happens when you allocate a whole block of memory in advance as a memory pool and then try to free a single object taken from the pool with `delete` or `free()`.

-   Dereferencing a null pointer/dangling pointer

    For null pointers: check for null first, using `p == nullptr` or `!p`.

    For dangling pointers: you can avoid them by setting the pointer to `nullptr` when you free it.

-   Signed integer overflow

    For example, suppose we have the expression `x+1 > x`.

    Normally it should be `true`, but when `x` is `INT_MAX` it gives `false`. This is called `signed integer overflow`.

    You can use a larger data type (such as `long long` or `__int128`), or check for overflow. If there are guaranteed to be no negative numbers, you can also use an unsigned integer type.

    Signed integer overflow can affect compiler optimizations. For example, the code:

    ```cpp
    int foo(int x) {
      if (x > x + 1) return 1;
      return 0;
    }
    ```

    may be optimized by the compiler directly into:

    ```cpp
    int foo(int x) { return 0; }
    ```

    because the compiler may assume signed integers never overflow, so `x > x + 1` can never be true.

-   Using uninitialized variables

    ???+ warning "Example"
        ```cpp
        int foo(int a) {
          int t; /* not initialized */
          if (/* used */ t > 3) return a;
          return 0;
        }
        ```

### Mistakes that cause RE

-   Not removing file operations (on some OJs).

-   Mistakes in the comparison function when sorting. `std::sort` requires the comparison function to be a strict weak ordering: `a<a` is `false`; if `a<b` is `true`, then `b<a` is `false`; if `a<b` is `true` and `b<c` is `true`, then `a<c` is `true`. Pay special attention to the second point.
    If these requirements are not met, sorting is very likely to cause RE.
    For example, when writing the odd-even ordering for Mo's algorithm, writing it like this is wrong:

    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        return (block[a.l] & 1) ^ (a.r < b.r);
      else
        return block[a.l] < block[b.l];
    }
    ```

    In the code above, `(block[a.l]&1)^(a.r<b.r)` does not meet the second requirement.
    Changing it like this makes it correct:

    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        // wrong: doesn't satisfy strict weak ordering
        // return (block[a.l] & 1) ^ (a.r < b.r);
        // correct
        return (block[a.l] & 1) ? (a.r < b.r) : (a.r > b.r);
      else
        return block[a.l] < block[b.l];
    }
    ```

-   Not enough stack space on Windows causes a stack overflow. Windows sends the program a SIGSEGV signal, and the program terminates with return value 3221225725 (that is, 0xC00000FD, defined in NTSTATUS as `STATUS_STACK_OVERFLOW`).  
    If you use the gcc compiler, you can add `-Wl,--stack=SIZE` when compiling to set the stack size limit, where `SIZE` is the stack size in bytes.

    Not enough stack space on Linux causes a stack overflow. Linux then scribbles over `head_info` in the stack/heap, which in most cases makes the program exit immediately with a message like `Segmentation fault (core dumped)`.  
    You can change the stack size limit of the current terminal with `ulimit -s SIZE`, where `SIZE` is the stack size in kilobytes (KB).  
    **Note: if you set the stack size limit too large, infinite recursion may make the recursion stack so large that the system crashes.**

### Mistakes that cause TLE

-   Divide and conquer without checking the boundary, causing infinite recursion.

-   Infinite loops.

    -   Loop variables with the same name.

    -   Loop direction reversed.

-   Not marking whether a state has already been visited in BFS.

-   Writing min/max as macros

    This mistake can greatly increase the running time of a program, and can even change the time complexity of the code. It is especially common when beginners write segment trees.

    A common wrong way to write it is:

    ```cpp
    #define Min(x, y) ((x) < (y) ? (x) : (y))
    #define Max(x, y) ((x) > (y) ? (x) : (y))
    ```

    This is correct, but if you take the max of function return values directly, as in `a = Max(func1(), func2())`, and the function takes a long time to run, performance suffers a lot. After macro expansion it becomes `a = func1() > func2() ? func1() : func2()`, which calls the functions three times, one more call than a normal max function. Note that if `func1()` returns a different value each time, this way of writing `max` also gives wrong results. For example, when `func1()` is `return ++a;` and `a` is a global variable.

    Example: the following code can be forced to take $\Theta(n)$ per query, causing TLE.

    ```cpp
    #define max(x, y) ((x) > (y) ? (x) : (y))

    int query(int t, int l, int r, int ql, int qr) {
      if (ql <= l && qr >= r) {
        ++ti[t];  // count node visits to help debugging
        return vi[t];
      }

      int mid = (l + r) >> 1;
      if (mid >= qr) return query(lt(t), l, mid, ql, qr);
      if (mid < ql) return query(rt(t), mid + 1, r, ql, qr);
      return max(query(lt(t), l, mid, ql, qr), query(rt(t), mid + 1, r, ql, qr));
    }
    ```

-   Appending characters to a `std::string` with the + operator

    This mistake creates a temporary `string` variable, modifies it, and then assigns it back to the original variable. The compiler can't optimize this away, and with large data it may make the time complexity worse.

    A common wrong way to write it:

    ```cpp
    std::string a;
    char b = 'c';
    a = a + b;
    ```

    When this code runs, the program first creates a temporary `string` variable, stores the value of `a` in it, appends the value of `b` to the end, and finally stores it back in `a`.

    The [assembly output](https://godbolt.org/z/Eo9vn7or5) shows that `a = a + b` calls three functions in `std::__cxx11::basic_string`: `operator+`, `operator=`, and variable creation.

    The correct way is:

    ```cpp
    std::string a;
    char b = 'c';
    a += b;
    ```

    [This way](https://godbolt.org/z/eGh33Grf3) appends the character `b` directly to the string `a`, calling `operator+=` only once. For a more detailed performance comparison, see [Benchmark](https://quick-bench.com/q/JNDGl7HgOszNG-bo7AgVc42owv4).

-   Not removing file operations (on some OJs).

-   Repeatedly calling a function whose complexity is not $O(1)$ inside a `for/while` loop. Strictly speaking, this may change the time complexity.

-   Wrong midpoint formula or stopping condition in binary search.

### Mistakes that cause MLE

-   Arrays that are too large.

    ??? note "Memory usage metrics on Linux explained"
        > TL;DR: be especially careful if you declare a very large global static array in CCF-series exams. All declared arrays count toward memory usage (unlike most online judges, which only count the part actually used), and in some cases this can even make every test case of the problem get MLE.
        
        -   About RSS and VSZ[^ref1][^ref2]
        
            1.  VSZ (Virtual Memory Size)[^ref3]
        
                VSZ is the **virtual memory size** of a process: the total size of the virtual address space the process can access, usually shown in KB.
        
                Virtual memory is a logical concept and is usually much larger than the memory actually used.
        
                On Linux you can use the `top` command to see the memory usage of a process; the `VIRT` column shows the virtual memory it uses.
        
                Virtual memory generally includes address space the process has allocated but not actually used. In short, virtual memory is roughly however much you requested.
        
                Note in particular that common online judges usually only count physical memory usage. But **the CCF judging environment counts virtual memory**. This means that if you declare a large global static array, it takes up a lot of space even if you only use a small part of it.
            2.  RSS (Resident Set Size)[^ref4]
        
                RSS is the **physical memory size** the process actually uses, that is, the size of the page frames resident in RAM, usually shown in KB.
        
                Similarly, you can use `top` and look at the `RES` column to see the physical memory of a process.
        
                RSS generally only includes the part actually loaded into physical memory; in other words, it's however much you actually use.
        -   Analyzing memory usage behavior
        
            Suppose we declare the following array:
        
            ```cpp
            const int SIZE = 1e8;
            int arr[SIZE];  // space: 4 bytes * 100 million = 400 MB
            ```
        
            This is a static array allocated in the global data segment. Since it isn't explicitly initialized, it is usually placed in the BSS segment (if it were explicitly initialized, e.g. to all 0 or some other values, it would be placed in the DATA segment).
        
            -   When the array is not used at all (assuming the compiler doesn't optimize it away)
        
                -   Physical memory: if the array is never accessed, demand paging means its memory pages are not loaded into physical memory yet. Physical memory doesn't increase, or increases only slightly (some metadata pages may be loaded).
                -   Virtual memory: the size of the array counts toward virtual memory (an increase of `400MB`), because the virtual address space for the whole array has already been allocated.
            -   When part of the array is used
        
                Suppose only a few elements of the array are used, for example:
        
                ```cpp
                arr[0] = 1;
                arr[999999] = 2;
                ```
        
                -   Virtual memory: virtual memory doesn't change; it is still `400MB`.
                -   Physical memory: each time an element of the array is accessed, the corresponding virtual page is loaded into physical memory. Assuming the system page size is `4KB`, each page holds $4 \text{KB} ÷ 4 \text{B} = 1024$ `int` elements. Accessing the array twice may load 2 pages, adding about $2 \times 4 \text{KB} = 8 \text{KB}$ of physical memory.
            -   When most of the array is used
        
                Suppose we assign values to the first $50,000,000$ elements of the array:
        
                ```cpp
                for (int i = 0; i < 50000000; ++i) {
                  arr[i] = i;
                }
                ```
        
                -   Virtual memory (VSZ): VSZ is still `400MB` and doesn't change.
                -   Physical memory (RSS): the access is sequential (the $50,000,000$ elements accessed are adjacent in memory), so the number of pages to load is $\left\lceil \dfrac{50,000,000}{1024} \right\rceil = 48,828$.
        
                    Assuming each page is `4KB`, the total is $48,828 \times 4 \text{KB} \approx 190 \text{MB}$, so physical memory grows to about `190MB`.
        
                    Note: if the indices are random when assigning to the array, physical memory usage can differ a lot from this prediction (because pages are loaded by address, random assignments load many pages).
        
                Quick summary: as the fraction of the array that is accessed grows, physical memory approaches virtual memory (assuming no pages are reclaimed).
-   Inserting too many elements into an STL container.

    -   Often caused by an infinite loop that inserts elements into an STL container.

    -   It may also be that the test data was designed to break your approach.

### Mistakes that cause a large constant factor

-   Not declaring the modulus as a constant.

    -   Example:

        ```cpp
        // int mod = 998244353;      // wrong
        const int mod = 998244353;  // correct; lets the compiler treat it as a constant
        ```

-   Using unnecessary recursion (tail recursion excluded).

-   Adding lots of extra operations when converting recursion to iteration.

### Mistakes that only matter when running the program locally

-   Possible mistakes with file operations:

    -   During stress testing, setting `fp = fopen()` again without first closing the file pointer with `fclose(fp)`. This makes the process leak lots of file handles.

    -   Leaving out `.in`/`.out` from the file names in `freopen()`.

-   Forgetting to `delete` or `free` heap memory after use.

## References and notes

[^ref1]: [What is RSS and VSZ in Linux memory management - Stack Overflow](https://stackoverflow.com/questions/7880784/what-is-rss-and-vsz-in-linux-memory-management)

[^ref2]: [Need explanation on Resident Set Size/Virtual Size - Stack Overflow](https://unix.stackexchange.com/questions/35129/need-explanation-on-resident-set-size-virtual-size)

[^ref3]: [Virtual memory](https://zh.wikipedia.org/wiki/%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98)

[^ref4]: [Resident set size](https://zh.wikipedia.org/wiki/%E5%B8%B8%E9%A9%BB%E9%9B%86%E5%A4%A7%E5%B0%8F)
