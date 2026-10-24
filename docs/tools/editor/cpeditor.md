author: zarttic, xk2013

## Introduction

[CP Editor](https://github.com/cpeditor/cpeditor) is designed specifically for competitive programming, unlike other IDEs, which are mainly designed for software development. It automates compiling, running and testing, so you can focus on designing algorithms. It can even fetch sample tests from various competitive programming websites and submit your code to [Codeforces](https://codeforces.com/)!

## Download and installation

See [Installation | CP Editor](https://cpeditor.org/zh/docs/installation/).

## Basic configuration

> CP Editor does not bundle a compiler, so you need to install and configure one yourself. If needed, see this site's article on installing compilers[^compiler]. Of course, if you downloaded an installer with the suffix `with-gcc-<GCC version>-llvm-<LLVM version>`, you can use CP Editor's bundled compiler, located at `{install directory}/mingw64/bin/`.

-   Set the default language

    The editor's default language is `C++`.

    ![cp-setting-lang-1](images/cp-setting-lang-1.png)

    ![cp-setting-lang-2](images/cp-setting-lang-2.png)

-   Set the `C++` commands

    You need to set some necessary compile commands, depending on your compiler.

    ![cp-setting-lang-3](images/cp-setting-lang-3.png)

-   Set a template

    The template is filled in automatically when you create a new file. Note that CP Editor needs a `xxx.cpp` file as the template file.

    ![cp-setting-lang-4](images/cp-setting-lang-4.png)

> After finishing the basic steps above, you can use the most basic features.

## Basic features

-   Keyboard shortcuts

    |                    Shortcut                   |        Action        |
    | :-------------------------------------------: | :------------------: |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>C</kbd> |       Compile.       |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>R</kbd> |   Compile and run.   |
    |          <kbd>Ctrl</kbd>+<kbd>R</kbd>         |         Run.         |
    |  <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>D</kbd>  |   Run in terminal.   |
    |          <kbd>Ctrl</kbd>+<kbd>K</kbd>         | Kill all processes.  |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>I</kbd> |     Format code.     |

    See the [official documentation](https://cpeditor.org/zh/docs/preferences/key-bindings/) for details.

-   Sample testing

    You can copy the samples from the problem statement and let CP Editor judge your program automatically. You can even set a time limit!

    ![cp-setting-limits](images/cp-setting-limits.png)

    ![cp-judge-1](images/cp-judge-1.png)

    ![cp-judge-2](images/cp-judge-2.png)

    ![cp-judge-3](images/cp-judge-3.png)

    ![cp-judge-4](images/cp-judge-4.png)

## References

[^compiler]: [Compilers - OI Wiki](../compiler.md)
