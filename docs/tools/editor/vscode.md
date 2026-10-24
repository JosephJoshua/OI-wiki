author: NachtgeistW, Ir1d, ouuan, Enter-tainer, Xeonacid, ChungZH, keepthethink, abc1763613206, partychicken, Chrogeek, xkww3n, HeliumOI, Pinghigh, xiaofu-15191, Sekakou, fuxianhu

## Introduction

Visual Studio Code (VS Code below) is an open-source code editor developed by Microsoft that runs on Windows, Linux, macOS and other operating systems. It is written in TypeScript and built on Electron. It has built-in support for JavaScript, TypeScript and Node.js, and a rich ecosystem of extensions for other languages (such as C, C++, Java, Python, PHP and Go).

Official website: [Visual Studio Code - The open source AI code editor](https://code.visualstudio.com/)

Before reading on, it's a good idea to get familiar with the basics of VS Code: [Get started](https://code.visualstudio.com/docs/getstarted/getting-started).

## Running code with the C/C++ Compile Run extension

C/C++ Compile Run is an extension focused on compiling and running single C/C++ files. It skips the tedious setup of the usual C/C++ extension, which makes it a great fit for programming contests: it's quick to learn and simple to use.

Open VS Code, click the "Extensions" icon in the left sidebar (or press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd>), type `C++` in the search box, find C/C++ Compile Run and click "Install".

![](./images/vscode-14.png)

After installing, no extra setup is needed: the extension automatically picks up an already configured MinGW compiler from the environment variables.

Open the file you want to run and click the triangle icon in the top-right corner to run it.

Shortcuts:

-   <kbd>F6</kbd>- compile and run in VS Code's integrated terminal
-   <kbd>F7</kbd>- compile with custom arguments and run with custom arguments in VS Code's integrated terminal
-   <kbd>F8</kbd>- compile and run in an external terminal

## Running code with the Code Runner extension

VS Code can support C/C++ once you install and configure extensions, but the setup is fairly complicated. A simple way to compile and run C++ programs is to install the Code Runner extension.

Code Runner is an extension that runs code with one click. In industry it's usually used to try out code snippets. It supports more than 40 languages, including Node.js, Python, C, C++, Java, PHP, Perl, Ruby and Go.

To install it, search for Code Runner in the extension marketplace and click Install; or go to the [Marketplace](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) and click Install, and your browser will open VS Code and install it.

![](./images/vscode-1.jpg)

After installing, open the file you want to run and click the small triangle icon in the top-right corner to run it; pressing <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>N</kbd> (<kbd>Control</kbd>+<kbd>Option</kbd>+<kbd>N</kbd> on macOS) does the same.

???+ warning "Warning"
    If your code still won't run after installing VS Code and Code Runner, it's most likely because a C/C++ environment isn't installed on your system yet. See the [Hello, World! page](../../lang/helloworld.md) to install one.
    
    Remember to check the Run In Terminal option in the settings, as shown: ![](./images/vscode-7.png)

## Compiling, debugging and code completion with the C/C++ extension

### Installing the extension

Open the extension marketplace in VS Code, type `C++` or `@category:"programming languages"` in the search bar, find C/C++ and click Install.

![](./images/vscode-2.png)

???+ warning "Warning"
    Before configuring, make sure G++ or Clang is installed on your system and added to the `PATH` environment variable. Use CMD or PowerShell, not Git Bash, as the integrated terminal.

### Configuring the GDB/LLDB debugger

#### GDB

Create a new C++ source file in VS Code, write something valid in C++ (such as `int main(){}`), save it and press <kbd>F5</kbd> to enter debug mode.
If you are asked to "Select debugger", choose `C++ (GDB/LLDB)`. Under "Select a configuration", G++ users choose `g++.exe - Build and debug active file`; Clang users choose `clang++ - Build and debug active file`.

???+ warning "Warning"
    Configuration names are not fixed; they can be customized. Different operating systems may show different configuration names.

VS Code will then finish initializing automatically and start debugging in the integrated terminal at the bottom. That completes the GDB setup.

#### LLDB

To use LLDB, you need to install another extension[^ref1]: [CodeLLDB](https://github.com/vadimcn/vscode-lldb/). Download the .vsix file from the project's Releases page[^ref2], then install it from VS Code's Extensions view.

![](images/vscode-9.png)

First go through the GDB setup above, then delete `.vscode/launch.json`, press <kbd>F5</kbd>, choose `LLDB`, and change `${workspaceFolder}/<executable file>` in `launch.json` to `${fileDirname}/${fileBasenameNoExtension}`.

That completes the LLDB setup. Press <kbd>F5</kbd> again and you will see debugging output at the bottom of the window.

To compile and debug code with VS Code later, all your source files need to be saved in this folder. To compile and debug code in another folder, repeat the steps above (or copy the `.vscode` subfolder from the old folder into the new one).

### Debugging your code

Open a source file in VS Code, hover the mouse over the blank area to the left of the line numbers, and click the red dot that appears to set a breakpoint on that line. Click again to remove the breakpoint.

![](images/vscode-5.apng)

Press <kbd>F5</kbd> to enter debug mode. A debug toolbar appears at the top of the editor; its four blue buttons, from left to right, correspond to GDB's `continue`, `next`, `step` and `until`:

![](images/vscode-6.png)

If the editor doesn't switch automatically, click the "Run and Debug" icon in the left toolbar to open the debug view, where you can see the values of variables on the left.

In "Watch", you can enter expressions; they are re-evaluated and displayed after every `next`, `step` and so on.

In "Call Stack", you can see the stack frames of the functions currently executing.

???+ note "Tip"
    You can follow the [official GDB documentation](https://sourceware.org/gdb/current/onlinedocs/gdb.html/Arrays.html) to view a range of elements in an array.

In debug mode, the editor highlights the line that will run next with a yellow background.

### Configuring IntelliSense

This adjusts VS Code's smart code completion.

If you use the Clang compiler, choose `clang-x64` instead of the default `msvc-x64` under "IntelliSense mode"; if you use G++, choose `gcc-x64` to get auto-completion and other features. Otherwise you'll get the error "IntelliSense mode msvc-x64 is incompatible with compiler path."

![](images/vscode-4.png)

## Configuring clangd

???+ warning "Warning"
    Because their features conflict, installing the clangd extension disables the IntelliSense features of the C/C++ extension (debugging and other features still use the C/C++ extension). If the clangd extension isn't working properly, check whether the C/C++ extension's IntelliSense has been disabled.

### About clangd

The LLVM website describes clangd like this:

> Clangd is an implementation of the Language Server Protocol leveraging Clang. Clangd’s goal is to provide language "smartness" features like code completion, find references, etc. for clients such as C/C++ Editors.

Simply put, clangd is Clang's implementation of the Language Server Protocol. It provides smart features such as project-wide indexing, go to definition, renaming variables, faster code completion, hints and diagnostics, and code formatting, and it uses LSP to work with editors such as Vim, Emacs and VSCode. Although the official definition calls it an implementation of LSP, clangd is really a language server rather than just the protocol itself.

VS Code's C/C++ extension also offers auto-completion and similar features, but its messages are somewhat less readable and accurate than clangd's, so we sometimes use clangd instead of the C/C++ extension for auto-completion and similar features.

### Installation

See [Getting started](https://clangd.llvm.org/installation).

### The VS Code extension

Open VS Code's extension marketplace, type `clangd` in the search bar, find the clangd extension and install it

![](images/vscode-8.png)

If a dialog pops up at the bottom asking you to disable IntelliSense for clangd, click "Disable Intellisense" and reload the workspace. You can then enjoy clangd's auto-completion and other features.

## Editing

### Setting the language

In a newly opened editor, click "Select a language" to turn on the corresponding syntax highlighting, as shown:

![](images/vscode-11.apng)

### Shortcuts

The official shortcut PDFs are below. You can also press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> in VS Code to open the command palette and run the command `> Help: Keyboard Shortcuts Reference`.[^ref3]

-   [Windows shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)
-   [Linux shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-linux.pdf)
-   [Mac OS shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-macos.pdf)

Some shortcuts:

| Keys                                                          | Action                                                                     |
| ------------------------------------------------------------- | -------------------------------------------------------------------------- |
| <kbd>Ctrl</kbd>+<kbd>C</kbd>/<kbd>X</kbd>                     | Copy/cut the current line (when nothing is selected)                       |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>K</kbd>                 | Delete the current line                                                    |
| <kbd>Alt</kbd>+<kbd>Up</kbd>/<kbd>Down</kbd>                  | Move line up/down                                                          |
| <kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>Up</kbd>/<kbd>Down</kbd> | Copy line up/down                                                          |
| <kbd>Ctrl</kbd>+<kbd>/</kbd>                                  | Toggle line comment                                                        |
| <kbd>Ctrl</kbd>+<kbd>\[</kbd>/<kbd>]</kbd>                    | Outdent/indent line                                                        |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>\[</kbd>/<kbd>]</kbd>   | Fold/unfold region                                                         |
| <kbd>Ctrl</kbd>+<kbd>P</kbd>                                  | Open a recently opened file                                                |
| <kbd>Alt</kbd>+<kbd>Z</kbd>                                   | Toggle word wrap                                                           |
| <kbd>Alt</kbd>+<kbd>F12</kbd>                                 | Peek definition (e.g. of a function)                                       |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>\\</kbd>                | Jump to matching bracket                                                   |
| <kbd>Ctrl</kbd>+<kbd>T</kbd>                                  | Find a symbol in the workspace (e.g. find a function by name in the folder) |

### Multiple cursors

Hold <kbd>Alt</kbd> and click to add a cursor in the editor; most editing actions then apply to all cursors at once. You can also hold the middle mouse button and drag in the editor to add cursors on several lines, as shown:

![](images/vscode-12.gif)

Press <kbd>Ctrl</kbd>+<kbd>F2</kbd> to change all matching occurrences in the editor at once. You can also find Change All Occurrences in the right-click menu, as shown:

![](images/vscode-13.gif)

Note that a toolbar appears in the top-right corner, where you can turn on options such as match case and match whole word when finding matches.

## References and notes

[^ref1]: If you choose lldb as the debugger in VS Code's C/C++ extension, it uses the lldb-mi program by default. But lldb-mi has been split out of the project by the LLVM developers, so you'd have to compile it yourself. It also has some bugs of its own, and it is less pleasant and convenient to use than the CodeLLDB extension.

[^ref2]: After you install CodeLLDB from the extension marketplace, it downloads its main package from GitHub, which can be extremely slow and sometimes fails, so it's best to download the package directly and install it. To update, just download and install it with the same steps.

[^ref3]: [VS Code official documentation](https://code.visualstudio.com/docs/).
