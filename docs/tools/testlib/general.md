This page covers some common verdicts, objects and functions of Testlib checkers, interactors and validators, along with some usage notes and caveats. Please read this page in full before reading the other pages.

## Common verdicts

| Verdict            | Testlib alias | Meaning                                                                                                                                                                                                                                                       |
| ------------------ | ------------ | ------------------------------------------------------------------------------------------------------------------------------- |
| Ok                 | `_ok`        | The answer is correct.                                                                                                                                                                                                                                        |
| Wrong Answer       | `_wa`        | The answer is wrong.                                                                                                                                                                                                                                          |
| Presentation Error | `_pe`        | The answer has a format error. Note that many OJs, including Codeforces, do not distinguish PE from WA.                                                                                                                                                       |
| Partially Correct  | `_pc(score)` | The answer is partially correct. Only for tests with partial points, where `score` is a positive integer from $0$ (no points) to $100$ (the maximum possible score). (`quitf+_pc` exists only for compatibility with the old pascal-testlib; to give partial points, `quitp` is recommended[^1].) |
| Fail               | `_fail`      | In a validator: the input is invalid and fails validation.<br>In a checker: an internal error, a wrong reference output, or a contestant output better than the reference output; the judge/problem setter needs to look into it. (In other words, the problem is broken.) |

Usually the verdict is reported by the program's exit code, but there are other ways too: writing an xml output file, printing information to stdout or elsewhere... All of these are done by the `quitf` function in the function table below.

## Common objects

| Object | Meaning                   |
| ----- | ----- |
| `inf` | Input file stream         |
| `ouf` | Contestant output stream  |
| `ans` | Reference output stream   |

## Common functions

Non-member functions:

| Call                                                                                            | Meaning                                                                                                                                     |
| ----------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| `void registerTestlibCmd(int argc, char* argv[])`                                               | Registers the program as a checker                                                                                                          |
| `void registerInteraction(int argc, char* argv[])`                                              | Registers the program as an interactor                                                                                                      |
| `void registerValidation()`/`void registerValidation(int argc, char* argv[])`                   | Registers the program as a validator                                                                                                        |
| `void registerGen(int argc, char* argv[], int randomGeneratorVersion)`                          | Registers the program as a generator<br>`randomGeneratorVersion` should preferably be `1`                                                   |
| `void quit(TResult verdict, string message)`/`void quitf(TResult verdict, string message, ...)` | Ends the program, returning `verdict` and printing `message`                                                                                |
| `void quitif(bool condition, TResult verdict, string message, ...)`                             | If `condition` holds, calls `quitf(verdict, message, ...)`                                                                                  |
| `void quitp(F points, string message, ...)`                                                     | Ends the program with partial points. Most OJs (such as Luogu and UOJ) expect `points` to be a real number in $[0,1]$, meaning the fraction of the score; some OJs (such as Lyrio) expect a real number in $[0,100]$ (the OJ drops the fractional part automatically), meaning the test's score out of 100 |

Stream member functions:

| Call                                                                                                                                                              | Meaning                                                                            |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| `char readChar()`                                                                                                                                                 | Reads one character                                                                |
| `char readChar(char c)`                                                                                                                                           | Reads one character, which must be `c`                                             |
| `char readSpace()`                                                                                                                                                | Same as `readChar(' ')`                                                            |
| `string readToken()`/`string readWord()`                                                                                                                          | Reads a string, stopping at whitespace (space, Tab, EOLN, etc.)                    |
| `string readToken(string regex)`/`string readWord(string regex)`                                                                                                  | Reads a string, which must match `regex`                                           |
| `long long readLong()`                                                                                                                                            | Reads a 64-bit integer                                                             |
| `long long readLong(long long L, long long R)`                                                                                                                    | Reads a 64-bit integer, which must be in $[L,R]$                                   |
| `vector<long long> readLongs(int n, long long L, long long R)`                                                                                                    | Reads $N$ 64-bit integers, all of which must be in $[L,R]$                         |
| `int readInt()`/`int readInteger()`                                                                                                                               | Reads a 32-bit integer                                                             |
| `int readInt(int L, int R)`/`int readInteger(L, R)`                                                                                                               | Reads a 32-bit integer, which must be in $[L,R]$                                   |
| `vector<int> readInts(int n, int L, int R)`/`vector<int> readIntegers(int n, int L, int R)`                                                                       | Reads $N$ 32-bit integers, all of which must be in $[L,R]$                         |
| `double readReal()`/`double readDouble()`                                                                                                                         | Reads a double-precision floating-point number                                     |
| `double readReal(double L, double R)`/`double readDouble(double L, double R)`                                                                                     | Reads a double-precision floating-point number, which must be in $[L,R]$           |
| `double readStrictReal(double L, double R, int minPrecision, int maxPrecision)`/`double readStrictDouble(double L, double R, int minPrecision, int maxPrecision)` | Reads a double-precision floating-point number, which must be in $[L,R]$, with the number of digits after the decimal point in $[minPrecision,maxPrecision]$; unusual formats such as scientific notation are not allowed |
| `string readString()`/`string readLine()`                                                                                                                         | Reads a line (including the line break) and moves the stream pointer to the start of the next line |
| `string readString(string regex)`/`string readLine(string regex)`                                                                                                 | Reads a line, which must match `regex`                                             |
| `void readEoln()`                                                                                                                                                 | Reads EOLN (`LF` on Linux, `CR LF` on Windows)                                     |
| `void readEof()`                                                                                                                                                  | Reads EOF                                                                          |
| `void quit(TResult verdict, string message)`/`void quitf(TResult verdict, string message, ...)`                                                                   | Ends the program, returning `verdict` if `Stream` is `ouf` and `_fail` otherwise; prints `message` |
| `void quitif(bool condition, TResult verdict, string message, ...)`                                                                                               | If `condition` holds, calls `quitf(verdict, message, ...)`                         |

To be continued...

## Minimal regular expressions

Some of the input functions above accept "minimal regular expressions", as follows:

-   Character sets. For example, `[a-z]` means any lowercase English letter, and `[^a-z]` means any character except lowercase English letters.
-   Ranges. For example, `[a-z]{1,5}` means a string of length in $[1,5]$ containing only lowercase English letters.
-   The "or" operator. For example, `mike|john` means either `mike` or `john`.
-   The "optional" operator. For example, `-?[1-9][0-9]{0,3}` means a nonzero integer in $[-9999,9999]$ (note the optional minus sign).
-   The "repeat" operators. For example, `[0-9]*` means zero or more digits, and `[0-9]+` means one or more digits.
-   Note that these regular expressions are "greedy" ("repeat" matches as much as possible). For example, `[0-9]?1` does not match `1` (because `[0-9]?` matches the `1`, leaving the remaining `1` in the pattern unmatched).

## Include testlib.h first

Make sure testlib.h is the **first** header you include. Testlib redefines/disables (through name clashes) some random-related functions (such as `random()`) so that random results don't depend on the environment. This is very important for generators; the [generator page](./generator.md) explains this in detail.

## Use item names

For the range-checked calls such as `readInt/readInteger/readLong/readDouble/readWord/readToken/readString/readLine`, it is recommended to pass one more `string` argument at the end: a name for the item being read, which makes error messages readable. For example, if you use `inf.readInt(1, 100, "n")` instead of `inf.readInt(1, 100)`, the error message becomes `FAIL Integer parameter [name=n] equals to 0, violates the range [1, 100]`.

## Use `ensuref/ensure()`

These two functions check whether a condition holds (similar to `assert()`). For example, to check $x_i \neq y_i$, we can use

```cpp
ensuref(x[i] != y[i], "Graph can't contain loops");
```

You can also use C-style placeholders, such as

```cpp
ensuref(s.length() % 2 == 0,
        "String 's' should have even length, but s.length()=%d",
        int(s.length()));
```

It has a simplified version, `ensure()`: we can write `ensure(x> y)` directly without a description (adding a description is not supported). If the condition fails, the error is `FAIL Condition failed: "x > y"`. Without an extra description, this kind of error is often unhelpful, so we usually use `ensuref()` with a description instead of `ensure()`.

???+ warning "Warning"
    Note the difference between the global and member `ensuref/ensure()`
    
    The global functions `::ensuref/ensure()` are mostly used in generators and validators; if a check fails, they always return `_fail`.
    
    The member functions `InStream::ensuref/ensure()` are generally used to check whether the output of the contestant or the reference solution is valid. When the `InStream` is `ouf`, they return `_wa`; when it is `inf` (input data is generally not checked in a checker; that should be done in the validator) or `ans`, they return `_fail`. See [Checker - Writing a readAns function](./checker.md#好的实现) for details.

**This article is mainly translated and compiled from the [Testlib - Codeforces](https://codeforces.com/testlib) series. The GitHub repository of `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**

[^1]: [Link to the issue](https://github.com/MikeMirzayanov/testlib/issues/115#issuecomment-863414940)
