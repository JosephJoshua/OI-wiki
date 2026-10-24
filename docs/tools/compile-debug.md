author: CoelacanthusHex, qinyihao, StudyingFather, ksyx, NachtgeistW, CoderOJ, Enter-tainer, mcendu, Tiphereth-A, ayalhw, CCXXXI, Early0v0, HeRaNO, ouuan, swiftqwq, Xeonacid, xiaofu-15191

Before reading this section, install GCC and gdb first. See [Compilers](compiler.md) for how.

## Compiling C++ files with g++ on the command line

### Compiling manually

Type `g++ a.cpp` on the command line to compile the file `a.cpp` (on Windows, you need to add the compiler's directory to `PATH` first).

You can add some compiler options when compiling:

-   `-o <file name>`: set the file name of the executable the compiler outputs.
-   `-g`: add debugging information when compiling (needed for debugging with gdb).
-   `-Wall`: show all compiler warnings.
-   `-O1`, `-O2`, `-O3`, `-Ofast`: optimize the compiled program. Later levels apply more optimizations (turning on optimization affects debugging with gdb).
-   `-DDEBUG`: define the symbol `DEBUG` at compile time (you can use any symbol; for example, `-DONLINE_JUDGE` defines the symbol `ONLINE_JUDGE`).
-   `-UDEBUG`: undefine the symbol `DEBUG` at compile time.
-   `-lm`, `-lgmp`: link a library (here math and gmp; check the library's documentation for the exact name, but it is usually the same as the library name).

???+ note "Note"
    On Unix, if you use the math library from the standard C library (`math.h`), you need to add the `-lm` flag when compiling.[^have-to-link-libm-in-gcc]

???+ note "How to increase the stack size?"
    On Windows, the compiler option `-Wl,--stack=536870912` increases the stack size to 512 MB. The number after the equals sign is the **number of bytes**.
    
    On Unix, use `ulimit -s [num]` to set the stack size of **the current terminal** to `[num]` **KiB**.

### Using GNU Make's built-in rules[^gnu-make-built-in-rules]

For a C/C++ source file named `qwq.c/cpp`, you can run `make qwq` to automatically compile it into a program named `qwq`.

To add extra compiler options, use `export CFLAGS="xxx"` (for C programs) or `export CXXFLAGS="xxx"` (for C++ programs). To add extra preprocessor options, use `export CPPFLAGS="xxx"`. You can also write something like `CFLAGS="xxx" CPPFLAGS="xxx" make qwq` to set the environment variables for a single command only.

### Sanitizers

#### Introduction

Sanitizers are tools built into the compiler for debugging C/C++ code. They insert checking code during compilation to catch errors at run time, such as out-of-bounds memory access and undefined behavior.

There are several kinds:

-   AddressSanitizer[^address-sanitizer]: detects out-of-bounds access to the heap, stack and global variables, invalid frees, and memory leaks (experimental).
-   ThreadSanitizer[^thread-sanitizer]: detects data races in multithreaded code.
-   MemorySanitizer[^memory-sanitizer]: detects reads of uninitialized memory.
-   UndefinedBehaviorSanitizer[^ub-san]: detects undefined behavior.

#### Usage

Recent versions of clang++, g++ and MSVC (partially) all have built-in sanitizers, but their features and usage differ. Using clang++ as an example, you use them like this:

```console
$ clang++ -fsanitize=<name> test.cc
```

Here `<name>` is the feature to enable (a sanitizer can be thought of as a collection of features). For example:

```console
$ clang++ -fsanitize=memory test.cc # enable MemorySanitizer
$ clang++ -fsanitize=signed-integer-overflow test.cc # enable signed integer overflow detection
```

Then just run the executable as usual. If a sanitizer detects an error, it prints it to the `stderr` stream, for example:

```console
$ ./a.out
test.cc:3:5: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

???+ warning "Warning"
    g++ on Windows does not support sanitizers. Use a [modified MinGW64](https://github.com/ssbssa/gcc/releases) or another compiler.
    
    MSVC, from version 16.0 up to version 17.14, only supports AddressSanitizer.

#### Time/memory cost

Obviously, these debugging tools slow your code down a lot and increase its memory use. Here is their time/memory cost:

| Name                       | Memory multiplier | Time multiplier |
| :------------------------- | :---------------- | :-------------- |
| AddressSanitizer           | N/A               | 2               |
| ThreadSanitizer            | 5\~15             | 5\~10           |
| MemorySanitizer            | N/A               | 3               |
| UndefinedBehaviorSanitizer | N/A               | N/A             |

## Debugging with gdb on the command line

```console
$ g++ a.cpp -o a -g
$ gdb ./a
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
--Type <RET> for more, q to quit, c to continue without paging--
```

Press `c` to continue. Next you will see `Reading symbols from [filename]...`. Once `(gdb)` appears, you can type commands to debug.

Below are common commands, grouped by category:

### Basic gdb commands

| Command           | Description                          |
| ----------------- | ------------------------------------ |
| `help`            | Show help information                |
| `quit`            | Exit gdb                             |
| `file [filename]` | Load the program `[filename]` to debug |

### Execution control commands

| Command              | Description                                                                         |
| -------------------- | ----------------------------------------------------------------------------------- |
| `run`                | Run the program until a breakpoint is hit or the program ends                       |
| `continue`           | Continue running until a breakpoint is hit or the program ends                      |
| `next`               | Execute one line; function calls are stepped over, not entered                      |
| `step`               | Execute one line; function calls are entered                                        |
| `finish`             | Run until the current function returns, then stop and wait for a command            |
| `until [num]`        | Run until line `[num]`, then stop and wait for a command                            |
| `break [num]`        | Set a breakpoint at line `[num]`; the program stops there and waits for a command   |
| `condition [id] [p]` | Set a condition on breakpoint `[id]`; it only triggers when expression `[p]` holds  |
| `ignore [id] [num]`  | Ignore the first `[num]` times the breakpoint is hit                                |
| `delete [id]`        | Delete the breakpoint with the given number                                         |
| `disable [id]`       | Disable the breakpoint with the given number                                        |
| `enable [id]`        | Enable the breakpoint with the given number                                         |
| `list`               | List source code, continuing from where the last listing stopped, 10 lines at a time |
| `list [num]`         | List source code centered on line `[num]`                                           |
| `list [func-name]`   | List source code centered on a function                                             |
| `call [function]`    | Call a function and print its return value                                          |

`break [num]` prints the number of the new breakpoint. You can also use `break [func-name]` to set a breakpoint on a function.

You can also use `break [num] [p]` to get roughly the same effect as `condition [id] [p]` when setting the breakpoint.

### Stack frame commands

| Command     | Description                               |
| ----------- | ----------------------------------------- |
| `info args` | Show the arguments of the function        |
| `backtrace` | Show the chain of function calls and their arguments |
| `frame`     | Select a stack frame                      |
| `up`        | Move up one stack frame                   |
| `down`      | Move down one stack frame                 |

### Variable commands

| Command            | Description                                                                                     |
| ------------------ | ----------------------------------------------------------------------------------------------- |
| `print [p]`        | Print the value of expression `[p]`; you can also change variables through the expression       |
| `display [p]`      | Print the value of expression `[p]` every time the program pauses, but not inside called functions |
| `watch [var]`      | Watch variable `[var]`; when it is written, its value is printed and the program pauses          |
| `rwatch [var]`     | Watch variable `[var]`; when it is read, its value is printed                                   |
| `awatch [var]`     | When variable `[var]` is read or written, its value is printed and the program pauses            |
| `set [assignment]` | Execute an assignment statement                                                                 |

Both `display` and `print` let you control the output format: put `/` and a format letter right after the command, for example `print/display [var]` (print the value of `[var]` in decimal). The supported format letters are:

| Letter | Format                              |
| ------ | ----------------------------------- |
| `d`    | Show the variable in decimal        |
| `x`    | Show the variable in hexadecimal    |
| `a`    | Show the variable in hexadecimal    |
| `t`    | Show the variable in binary         |
| `c`    | Show the variable as a character    |
| `f`    | Show the variable as a floating-point number |
| `u`    | Show as an unsigned integer in decimal |
| `o`    | Show the variable in octal          |

### Information commands

| Command            | Description                                  |
| ------------------ | -------------------------------------------- |
| `info breakpoints` | List all breakpoints                         |
| `info locals`      | List the local variables of the current stack frame |
| `info args`        | List the function arguments of the current stack frame |
| `info threads`     | List all threads                             |
| `info program`     | Show the current state of the program        |
| `info registers`   | Show the current register values             |
| `info frame`       | Show information about the current stack frame |

### Other commands

| Command                       | Description                                                          |
| ----------------------------- | -------------------------------------------------------------------- |
| `enable pretty-printer`       | Enable the pretty-printer, which prints STL containers in a human-readable way |
| `checkpoint`[^checkpoint]     | Create a checkpoint you can roll back to                             |
| `restart [num]`[^checkpoint]  | Roll back to checkpoint `[num]`                                      |
| `save breakpoints [filename]` | Save breakpoints to a file                                           |
| `source [filename]`           | Load a breakpoint file                                               |

???+ tip "Tip"
    Most gdb commands can be shortened to any abbreviation that uniquely identifies them. For example, `breakpoint` can be written as `b`, `step` as `s`, and `info args` as `i ar`. See the `help` command for details.

## References and notes

[^have-to-link-libm-in-gcc]: [Why do you have to link the math library in C?](https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c)

[^address-sanitizer]: <https://clang.llvm.org/docs/AddressSanitizer.html>

[^thread-sanitizer]: <https://clang.llvm.org/docs/ThreadSanitizer.html>

[^memory-sanitizer]: <https://clang.llvm.org/docs/MemorySanitizer.html>

[^ub-san]: <https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html>

[^gnu-make-built-in-rules]: [Catalogue of Built-In Rules](https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html)

[^checkpoint]: Checkpoint-related commands only work on GNU/Linux. See the [official GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb#Checkpoint_002fRestart).
