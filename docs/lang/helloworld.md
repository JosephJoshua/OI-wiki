disqus:

## Setting up the environment

A craftsman who wants to do good work must first sharpen his tools.

### Integrated development environments (IDEs)

An IDE is fairly easy to use, so beginners usually write code in one. In contests the most common one is [Dev-C++](../tools/editor/devcpp.md) (if the contest machines run Windows, this IDE is usually provided).

### Compilers

#### Windows

We recommend the GNU compiler. Download and install MinGW from [MinGW Distro](https://nuwen.net/mingw.html). On Windows you can also choose the [Microsoft Visual C++ compiler](https://docs.microsoft.com/en-us/cpp/build/projects-and-build-systems-cpp); download and install it from the [Visual Studio page](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019).

#### macOS

Run this in the terminal:

```bash
xcode-select --install
```

#### Linux

Use `g++ -v` to check whether `g++` is installed.

You can install it with this command:

```bash
sudo apt update && sudo apt install g++
```

#### Compiling code on the command line

Once they are comfortable, some people compile code with the more flexible command line. Then they no longer depend on an IDE and can write code in whatever text editor they like.

```bash
g++ test.cpp -o test -lm
```

`g++` is the compiler for C++ (the compiler for C is `gcc`). `-o` sets the file name of the executable. The option `-lm` links the math library `libm`, so that code using `math.h` compiles and runs correctly.

Note: C++ programs compile and run fine without `-lm`. The C++ compile options for past NOI/NOIP contests have always included `-lm`, so we add it here too.

## Your first program

Let's start our C++ journey with this example program!

Note: make sure your keyboard is in English input mode before you start typing.

C++

```cpp
#include <iostream>  // include a header file

int main() {                     // define the main function
  std::cout << "Hello, world!";  // use cout from the standard namespace
  return 0;  // return 0 and end main. The compiler usually adds this line automatically, so it can usually be left out
}
```

C

```c
#include <stdio.h>  // include a header file

int main() {                // define the main function
  printf("Hello, world!");  // print Hello, world!
  return 0;                 // return 0 and end main
}
```

Note: C is shown here only for reference. C++ is mostly compatible with C and has many new features that can make a contestant's work much easier in a contest. See [Differences between C++ and other common languages](./cpp-other-langs.md) for details.
