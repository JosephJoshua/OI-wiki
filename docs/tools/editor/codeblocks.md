## Introduction

Code::Blocks is an open-source integrated development environment (IDE) written in C++, using wxWidgets as its GUI library. The project started in 2001 and is now maintained by the official community. It is mainly used for developing in C, C++ and Fortran.[^ref1]

Pros:

-   **Lightweight and efficient**: Code::Blocks uses few resources and starts quickly. It suits environments with limited resources and developers who prefer a lightweight IDE, and it is also good for beginners to learn with.

-   **Cross-platform**: it supports Windows, Linux, macOS and other operating systems with a consistent user experience, so developers can move between platforms seamlessly.

-   **Wide compiler support**: it supports many compilers, including GCC, MSVC (Microsoft Visual C++), Digital Mars and Borland C++ 5.5, so developers can pick the compiler that best fits their project.

Cons:

-   **Limited features**: compared with IDEs like CLion or Eclipse, its built-in features and tools are fairly basic and may not be enough for complex projects.

-   **Weak plugin ecosystem**: although it supports plugins, the number and quality of third-party plugins is limited, so the plugin ecosystem is relatively weak.

## Installation

Go to the [official Code::Blocks website](https://www.codeblocks.org/downloads/) and choose either the binary installer (Binary Release) or the source code to build yourself (Source Code). Then pick the installer that fits your needs and operating system, and follow the installation wizard.

???+ note "Download the installer that includes MinGW"
    On Windows, if you don't want to configure a compiler by hand, we recommend the installer that includes MinGW, such as `codeblocks-xxxxmingw-setup.exe`. This version already includes the GCC compiler, so you can start developing C and C++ projects without installing or configuring anything else.

![CodeBlocks DownLoad](./images/codeblocks-1.png)

## Configuration

If you chose an installer without MinGW, or you need a different compiler, you have to install and configure the compiler yourself and then set up Code::Blocks to use it.

### Installing the toolchain

Follow this site's [Compilers](../compiler.md) installation guide to download and install the compiler you need.

### Toolchain settings

When Code::Blocks starts for the first time, it automatically scans the system for installed compilers. If it finds none, you can add one manually with these steps:

1.  Open Code::Blocks and click `Settings -> Compiler` in the menu bar to open the compiler settings dialog (shown below). ![CodeBlocks Compiler Settings](./images/codeblocks-2.png)
2.  In the `Selected compiler` drop-down, choose the compiler to configure, for example `GNU GCC Compiler`.
3.  On the `Toolchain executables` tab, click the `Auto-detect` button, and Code::Blocks will scan the system for installed compilers.
4.  If auto-detection fails, you can set the compiler path manually. Enter the compiler's installation path in `Compiler's installation directory`, for example `C:\MinGW\bin`.
5.  When done, click `OK` to save the settings. Now you can use this compiler to build and run projects.

## Usage

Code::Blocks has a built-in project manager and lets you customize how projects are built. In `Project -> Build options` you can set build options, such as the compiler, compiler flags and linker flags. In `Project -> Properties` you can set project properties, such as the project name, path and file list.

??? note "Configuring a Makefile"
    Code::Blocks does not need a Makefile by default. If you want to use a custom Makefile, check the `This is a custom Makefile` option in `Project -> Properties`, then set the Makefile's path in `Project -> Build options`.

### Creating a project

Code::Blocks supports C, C++, Fortran and other languages. After starting Code::Blocks, create a new project with `File -> New -> Project`, choose a project type and template, then follow the wizard to set the project name, path, compiler and so on. Finally, click `Finish` to create the project.

Code::Blocks also supports compiling and running a single file. Create a new file with `File -> New -> File`, write and save your code, then click the `Build and run` button on the toolbar or press `F9` to compile and run the current file.

### Building and running

Using a simple Console Application project as an example, here is how to build and run a project:

1.  After the project is created, you will see a default `main.cpp` file. Write your code in it and save the file.
2.  When the code is ready, click the `Build and run` button on the toolbar or press `F9`. Code::Blocks will compile and run the project.
3.  After compiling and running, the program's output appears in the output window. Check the output there and adjust your code as needed.
4.  If you only want to compile the project without running it, click the `Build` button on the toolbar or press `Ctrl + F9`. Code::Blocks will only compile the project and not run the program.

### Debugging

Code::Blocks has a built-in debugger. You can configure and start it from the `Debug` menu to help you find and fix errors in your program.

Again using a simple Console Application project as an example, here is how to debug a project:

1.  **Set breakpoints**: left-click to the left of the line you want to debug to set a breakpoint. The program will stop at the breakpoint.
2.  **Start the debugger**: click the `Debug` button on the toolbar or press `F8`. Code::Blocks will compile the project and start the debugger.
3.  **Debug the program**: in the debugger you can step through the program and inspect variable values, the call stack and so on, to help you find and fix errors.
4.  **Stop debugging**: when you are done, click the `Stop` button on the toolbar or press `Shift + F8` to stop the debugger.

## Customization

Code::Blocks has many settings for adjusting how the editor behaves. Here are some common ones:

### Interface settings

1.  In `Settings -> Editor`, you can set the editor's font, colors, indentation, autocompletion and other options.
2.  In `Settings -> Environment`, you can set Code::Blocks' global behavior, such as autosave, automatic backups and auto hints.
3.  In the `View` menu, you can adjust the editor layout, for example showing or hiding the file browser, toolbars, status bar and output window.

### Plugin settings

Code::Blocks supports plugins for extra features. You can view and install available plugins via `Settings -> Plugins`, such as DoxyBlocks and wxSmith. Here are some common plugins:

-   **DoxyBlocks**: an integration of the well-known documentation generator Doxygen, which lets you generate project documentation directly in Code::Blocks.
-   **wxSmith**: a plugin for developing wxWidgets applications. It provides a visual interface designer for quickly creating and laying out GUIs, which simplifies development.
-   **Thread Search**: a plugin for multithreaded search that quickly finds and replaces symbols and text in a project, useful for large projects.

For how to install and use plugins, see the [Code::Blocks plugin documentation](https://wiki.codeblocks.org/index.php/Code::Blocks_Plugins), and choose plugins based on what you need.

???+ warning "Note"
    Code::Blocks plugins are fairly simple and basic, and most of them are already built into the software. Third-party plugins are limited in number and quality, so choose plugins based on your actual needs.

### Keyboard shortcut settings

You can view and change keyboard shortcuts on the `Settings -> Editor -> Keyboard shortcuts` tab, and adjust them to suit your habits.

Here are some common shortcuts:

| Action                        | Shortcut            |
| ----------------------------- | ------------------- |
| New file                      | `Ctrl + Shift + N`  |
| Open file                     | `Ctrl + O`          |
| Save current file             | `Ctrl + S`          |
| Save all                      | `Ctrl + Shift + S`  |
| Close current file            | `Ctrl + W`          |
| Close all files               | `Ctrl + Shift + W`  |
| Build and run current project | `F9`                |
| Build current project only    | `Ctrl + F9`         |
| Compile current project only  | `Ctrl + Shift + F9` |
| Run current project           | `Ctrl + F10`        |
| Debug: start/continue         | `F8`                |
| Debug: stop                   | `Shift + F8`        |
| Debug: next line              | `F7`                |
| Debug: step into              | `Shift + F7`        |
| Debug: step out               | `Ctrl + F7`         |
| Debug: toggle breakpoint      | `F5`                |
| Find                          | `Ctrl + F`          |
| Find and replace              | `Ctrl + R`          |
| Go to line                    | `Ctrl + G`          |
| Go to matching brace          | `Ctrl + B`          |
| Toggle full screen            | `F11`               |
| Toggle all folds              | `Ctrl + Shift + -`  |
| Unfold all folds              | `Ctrl + Shift + +`  |
| Select next occurrence        | `Ctrl + E`          |
| Skip to next occurrence       | `Ctrl + Shift + E`  |

## References and notes

[^ref1]: [Code::Blocks - Wikipedia](https://zh.wikipedia.org/wiki/Code::Blocks)
