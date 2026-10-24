author: Marcythm, YZircon, Chaigidel, Tiger3018, voidge, H-J-Granger, ouuan, Enter-tainer, lcfsih, Xeonacid, Ir1d

This page explains how to speed up stream-based I/O and C-style I/O.

???+ note "Note"
    The actual speed of stream-based I/O and C-style I/O varies with the environment (compiler, operating system and hardware). If you want to analyze it further, trust experimental results. But be careful to control variables in your experiments, so that several factors changing at once don't lead you to the wrong conclusion.

## Stream-based I/O

For stream-based I/O (such as `std::cin` and `std::cout`), the most common optimizations are turning off synchronization with the C streams and untying the input stream from the output stream.

### Turning off synchronization

Use the [`std::ios::sync_with_stdio(false)`](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio) function to turn off synchronization with the C streams. For compatibility with C, that is, to make sure a program that uses both `printf` and `std::cout` doesn't produce jumbled output, C++ keeps these two kinds of streams synchronized. Synchronized C++ streams are guaranteed to be thread-safe.

This is really a conservative choice C++ makes for compatibility. With synchronization on, every I/O operation on a C++ stream is immediately applied to the corresponding C buffer. If your code doesn't use C-style I/O at all, this work is wasted. So you can turn off synchronization with the C streams before doing any I/O. After that, be careful: later code must not mix `std::cin` with `scanf`, or `std::cout` with `printf`. However, you can still mix `std::cin` with `printf`, or `scanf` with `std::cout`.

### Untying the streams

Use the [`tie()`](https://en.cppreference.com/w/cpp/io/basic_ios/tie) function to untie the input stream from the output stream.

By default, `std::cin` is tied to `&std::cout`, so every formatted input operation first calls `std::cout.flush()` to flush the output buffer, which adds I/O overhead. You can untie them with `std::cin.tie(nullptr)` to make things faster.

???+ warning "Note"
    You can't leave out the argument and write `std::cin.tie()`. That doesn't untie anything; it just returns the output stream tied to `std::cin`. You also don't need `std::cout.tie(nullptr)`, because by default no other output stream is tied to `std::cout`.

### Implementation

```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
```

???+ note "Note"
    After doing both of the operations above, you must `flush` manually to make sure that whatever you print with `std::cout` appears before `std::cin` reads input. This is because in this case `std::cout` doesn't flush its buffer automatically when you use `std::cin`. For example:
    
    ```cpp
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << "Please input your name: "
              << std::flush;  // or: std::endl;
                              // because every std::endl flushes the output
                              // buffer, while \n does not.
    // Without std::flush, the prompt would not appear before the name is read
    std::cin >> name;
    ```

## C-style I/O

`scanf` and `printf` can still be made faster. All the methods below work by speeding up the conversion between integers and strings.

???+ note "Note"
    The input and output optimizations on this page only cover integers. Optimizing input and output of floating-point numbers is very complicated. For input, see the [Bellerophon algorithm](https://dl.acm.org/doi/10.1145/93542.93557); for output, see the [Ryū algorithm](https://dl.acm.org/doi/10.1145/3192366.3192369).

### Design

???+ note "Note"
    The methods here focus on faster I/O, while the data conversion itself uses the naive approach and doesn't take full advantage of the hardware. Today almost all x86 CPUs support the AVX2 instruction set, which can use SIMD to speed up conversion between integers and strings. The standard library functions don't use SIMD; for example, the libstdc++ [implementation](https://github.com/gcc-mirror/gcc/blob/releases/gcc-14.3.0/libstdc%2B%2B-v3/include/bits/charconv.h#L81) converts two digits at a time and turns them into characters with a lookup table. So optimizing the conversion step could also bring gains. But for competitive programming, the methods on this page are enough for almost every situation.

#### Faster input

Each integer consists of a sign and digits, and the sign always comes before the digits, so we read the sign first. For the sign, the `+` of a positive integer is usually omitted and doesn't affect the value of the digits after it, but `-` can't be omitted, so we have to check for it. If the input contains no negative integers, this check can be skipped. The digit part only contains the digits 0 to 9, so as soon as we read a character that can't be part of an integer (usually a space), we know the integer has been fully read.

Since digits are read from left to right, we can use Horner's method to build the integer. So the whole conversion can be done while reading the input.

While reading the digits, we need to check whether each character is a decimal digit. You can simply use the condition `ch >= '0' && ch <= '9'`, or use the [`isdigit()`](https://en.cppreference.com/w/cpp/string/byte/isdigit) function.

#### Faster output

For output, we need to convert the integer into a string. The usual naive method computes the digits from the lowest to the highest, converts them to characters, and prints them in reverse order.

### Implementation details

#### Integer overflow

Watch out for integer overflow in the implementation. For example, in output optimization, negating carelessly turns the minimum value of the integer type into a number larger than the maximum value the type can hold, which may cause wrong output. Similar overflow can also happen when reading the minimum value, but in that case the value read may still be correct, because the value obtained after overflow may happen to equal the actual input.

Signed integer overflow is undefined behavior. In the implementation, you can avoid the problem above by relying on the fact that in C, division of negative integers rounds toward zero. But if you never need to read or print negative numbers, or the minimum value of the type can never appear, this problem won't occur.

#### Making the implementation more general

If a program uses integer variables of several types, you may need several input/output functions that have different types but the same logic. In that case you can use C++ [`template`](https://en.cppreference.com/w/cpp/language/templates.html)s to write input/output optimizations for all integer types at once. For example, in C++11 you can use

```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value &&
                        std::is_signed<T>::value>::type
read(T &x);
```

or in C++20 you can use

```cpp
template <std::signed_integral T>
void read(T &x);
```

to define the function.

To keep things readable, the implementations below assume you only need to read integers of type `int`. These implementations are enough for most problems.

### Implementation

The common implementations only differ in which functions they use to read and write characters; the integer conversion logic is the same. They are introduced below by the functions they use.

#### Using `getchar` and `putchar`

The core code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_1.cpp:core"
```

#### Using `fread` and `fwrite`

`fread` and `fwrite` let you read and write even faster. Their signatures are as follows.

```cpp
std::size_t fread(void* buffer, std::size_t size, std::size_t count,
                  std::FILE* stream);
std::size_t fwrite(const void* buffer, std::size_t size, std::size_t count,
                   std::FILE* stream);
```

For example, `fread(Buf, 1, SIZE, stdin)` reads `SIZE` data blocks of 1 byte each from standard input into `Buf`. The return value is how many bytes were read successfully.

Because `fread` and `fwrite` read and write whole chunks at once, they are faster than `getchar()` and `putchar()`. If the buffer is large enough, you can read the whole file in one go. If the buffer isn't large enough, you need to read several times to make sure you get all of the input. To do this, you only need to redefine `getchar`.

```cpp
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
```

Output works similarly: first put the output into a buffer, then write the whole buffer at the end with a single `fwrite`.

The core code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_2.cpp:core"
```

When using this method, note that:

-   When the debug switch is off, `fread()` and `fwrite()` are used, and `fwrite()` runs automatically in the destructor when the program exits. When the debug switch is on, `getchar()` and `putchar()` are used, which makes debugging easier.
-   If you need to read from or write to files, call `freopen()` before any reading or writing.

#### Using `mmap`

`mmap` is a Linux system call that maps a whole file into memory at once, so you can access it like a memory region through a pointer. In some situations it is faster. Its signature is as follows:

```c
void *mmap(void addr[.length], size_t length, int prot, int flags, int fd,
           off_t offset);
```

???+ warning "Note"
    `mmap` can't be used on Windows (for example, the judges of Codeforces and HDU), and it isn't recommended in official contests either. In practice `fread` is already fast enough, and if you use `mmap` to repeatedly read a small file, the cost of setting up the memory mapping and of the kernel handling page faults is far larger than the cost of `fread`.

First get the file descriptor `fd`, then get the file size with `fstat`, and then use `mmap` to get a pointer `*pc` to the file mapped into memory. After that you can read the file with `*pc++` instead of `getchar()`.

If you need to read from standard input, you can set `fd` to `0`. **However, using mmap on standard input is extremely dangerous, and you can't type input in a terminal. You can redirect a file to standard input instead.**

???+ note "Example problem: [Luogu P10815 [Template] Fast Input](https://www.luogu.com.cn/problem/P10815)"
    Read $n$ integers in the range $[-n, n]$, and output their sum, where $n \leq 10^8$. It is guaranteed that the sum of every prefix of the sequence fits in a $32$-bit signed integer.

The reference code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_3.cpp"
```

## References

[Speeding up input and output with cin.tie and sync\_with\_stdio - hankcs.com](https://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.html)

[Speeding up C++ - Heavy Watal](https://heavywatal.github.io/cxx/speed.html)

['Re: mmap/mlock performance versus read' - MARC](https://marc.info/?l=linux-kernel&m=95496636207616&w=2)
