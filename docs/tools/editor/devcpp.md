author: topdevst, ksyx, ouuan, Doveqise, hsfzLZH1, wangqingshiyu, sshwy, NanoApe, DawnMagnet, CamberLoid, royqh1979

## Introduction

Dev-C++ is a free integrated development environment (IDE) for developing C/C++ programs, distributed under the GPL. It uses MinGW and GDB as its compiler and debugger. Dev-C++ runs on Microsoft Windows.

Dev-C++ has a simple, friendly interface, is easy to install, and supports compiling single files. This makes it the first choice of many beginner OI contestants and C++ learners. In NOIP, provinces that use Windows as the contest system usually have Dev-C++ preinstalled.

Dev-C++ grew out of Bloodshed Dev-C++, written by Colin Laplace. That version stopped being updated on February 22, 2005. In 2006, Colin Laplace, the main developer of Dev-C++, explained: "I am busy with real-life matters and have no time to continue developing Dev-C++."

Orwell Dev-C++ is a fork of Dev-C++ developed and maintained by the independent programmer Orwell (Johan Mes). It fixed bugs in the original Dev-C++ and updated the compiler. In general, every Dev-C++ 5.x is Orwell Dev-C++. Its last update was in 2015, version 5.11.

Embarcadero Dev-C++[^ref1] is the successor of Bloodshed Dev-C++ and Orwell Dev-C++. In 2020, Embarcadero sponsored and took over the original Dev-C++ project and continued its development. Embarcadero Dev-C++ added high-DPI support, an updated compiler with support for newer C++ standards, and a dark mode.

All of the Dev-C++ distributions above are considered "official". In addition, after Orwell Dev-C++ stopped being updated in 2015, a Chinese individual developer, [royqh1979](https://github.com/royqh1979), decided to continue developing his own fork of Dev-C++ for teaching purposes, named Red Panda Dev-C++[^ref2]. It integrates smart code completion and a recent MinGW64, which makes it very convenient for personal use and learning in China.

After releasing Red Panda Dev-C++ 6.7.5, the author used Qt5 to develop a brand-new Red Panda C++[^ref3], which runs natively on Windows, Linux, macOS and other systems. Red Panda C++ looks similar to Dev-C++. Besides single-file compiling, debugging, syntax highlighting, search/replace and other features similar to Dev-C++ but more polished, it also offers basic features common in modern IDEs, such as **a dark theme**, **smart code completion**, **variable/function renaming** and **switching/auto-detecting file encoding**. Red Panda C++ also has a problem set feature similar to CP Editor: you can write test cases yourself or **download sample tests from common OJ and contest websites**, and **run and test your program automatically**.

## Tutorial

### Common shortcuts

#### Files

-   `Ctrl + N`: new source file
-   `Ctrl + O`: open file
-   `Ctrl + W`: close file
-   `Ctrl + Shift + W`: close all files
-   `Ctrl + P`: print file

#### Formatting

-   `Ctrl + /`: comment/uncomment
-   `Tab`: indent
-   `Shift + Tab`: unindent

#### Line operations

-   `Ctrl + E`: duplicate line
-   `Ctrl + D`: delete line
-   `Ctrl + Shift + Up`: move up
-   `Ctrl + Shift + Down`: move down

#### Navigation

-   `Ctrl + F`: find
-   `Ctrl + R`: replace
-   `F3`: find next
-   `Shift + F3`: find previous
-   `Ctrl + G`: go to line number
-   `Shift + Ctrl + G`: go to function
-   `Ctrl + [1 ~ 9]`: set bookmark
-   `Alt + [1 ~ 9]`: jump to bookmark

#### Display

-   `Ctrl + mouse wheel`: increase or decrease font size
-   `Ctrl + F11`: toggle full screen

#### Running

-   `F9`: compile only
-   `F10`: run only
-   `F11`: compile and run
-   `F12`: rebuild all

#### Debugging

-   `F2`: go to breakpoint
-   `F4`: set or remove breakpoint
-   `F5`: start debugging
-   `F6`: stop
-   `F7`: step

### Debugging workflow

1.  Set the compiler configuration to `TDM-GCC 4.9.2 64-bit Debug`
2.  Press `F4` to set or remove a breakpoint
3.  Put the cursor on a variable and press `Alt + A` to add it to the watch list in the debug window
4.  Press `F5` to start debugging
5.  Press `F7` or `Alt + N` to step
6.  Press `Alt + S` to jump to the next breakpoint
7.  Press `F6` to stop debugging

## Extras

### Adding compiler options

Click Tools -> Compiler Options, then choose the "Code Generation/Optimization" tab. Below are a few compiler options the author often uses.

#### Turning on optimization

Optimizes the code's running time or memory usage.

Choose the "Optimization level (-Ox)" option on the "Code Generation" sub-tab.

![](./images/Dev-C++-11.png)

#### Changing the language standard

Use this to get new language features, or to try compiling your code under an older standard.

Choose the "Language standard (-std)" option on the "Code Generation" sub-tab.

![](./images/Dev-C++-12.png)

#### Showing the most warnings

A little helper for finding bugs.

Choose the "Show most warnings (-Wall)" option on the "Code Warnings" sub-tab.

![](./images/Dev-C++-13.png)

#### Generating debugging information

Turn this on if you see "Project does not have debug information, do you want to enable debugging and rebuild your project?" and clicking it makes the program crash, or whenever you want to use the debugger.

Choose the "Generate debugging information" option on the "Linker" sub-tab.

![](./images/Dev-C++-14.png)

### Compiler tricks

Click Tools -> Compiler Options, then choose the "Compiler" tab. Here are a few common tricks.

#### Increasing the stack size

Prevents things like a DFS overflowing the system stack.

Add the command `-Wl,--stack=128000000` to "Add the following commands when calling the linker".

This sets the stack to about 128MB. You can make it larger if needed.

![](./images/Dev-C++-15.png)

#### Defining macros

Handy for using file input/output when testing locally, or for other purposes.

Add the command `-D[String]` to "Add the following commands when calling the linker".

Replace `[String]` with the macro name you need.

As shown in the picture, once this compiler option is on, the code below reads input from `test.in` and writes output to `test.out`.

![](./images/Dev-C++-16.png)

```cpp
#ifdef LOCAL
freopen("test.in", "r", stdin);
freopen("test.out", "w", stdout);
#endif
```

#### Code formatting

Click AStyle -> Format Current File, or press Ctrl+Shift+A, to format your code.

![](./images/Dev-C++-17.png)

### Appearance

#### Font

Click Tools -> Editor Options, then choose the "Display" tab.

![](./images/Dev-C++-9.png)

#### Theme

Click Tools -> Editor Options, then choose the "Syntax" tab. You can use a preset theme or adjust it yourself.

![](./images/Dev-C++-10.png)

## References

[^ref1]: The project's source code is hosted on [GitHub](https://github.com/Embarcadero/Dev-Cpp) and [SourceForge](https://sourceforge.net/projects/embarcadero-devcpp/).

[^ref2]: The source code is hosted on [GitHub](https://github.com/royqh1979/Dev-Cpp)

[^ref3]: The project's official website is [Red Panda C++](https://royqh1979.gitee.io/redpandacpp), and the source code is hosted on [GitHub](https://github.com/royqh1979/RedPanda-CPP/)
