## Introduction

CLion is a powerful, feature-rich, cross-platform C/C++ integrated development environment (IDE) developed by JetBrains.

![Clion](./images/clion.png)

## Official tutorials

The official website provides a [Learn CLion](https://www.jetbrains.com/clion/learn/) tutorial.

## Installation

See [Download CLion](https://www.jetbrains.com/clion/download/).

## Configuration

### Installing the toolchain

CLion does not come with a compiler, build tools or debugger by default, so you need to install them yourself.

#### Windows

See [Tutorial: Configure CLion on Windows | CLion Documentation](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html).

Note that the Windows version of CLion bundles MinGW, so you don't need to install a MinGW toolchain separately.

#### Linux

##### Debian/Ubuntu and derivatives

```bash
sudo apt install make cmake # build tools
sudo apt install gcc g++ gdb # compiler and debugger
sudo apt install clang clang++ llvm lldb # you can also choose to use clang toolchain
```

##### Arch Linux and derivatives

```bash
sudo pacman -S make cmake # build tools
sudo pacman -S gcc g++ gdb # compiler and debugger
sudo pacman -S clang clang++ llvm lldb # you can also choose to use clang toolchain
```

##### Fedora/RHEL/CentOS/Rocky Linux

```bash
sudo dnf install make cmake # build tools
sudo dnf install gcc g++ gdb # compiler and debugger
sudo dnf install clang clang++ llvm lldb # you can also choose to use clang toolchain
```

#### macOS

See [Tutorial: Configure CLion on macOS | CLion Documentation](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-macos.html).

### Toolchain settings

#### Setting the toolchain manually

A freshly installed CLion automatically detects the C/C++ toolchains on your system. If an installed toolchain is not detected, you can configure it manually under `Settings` > `Build, Execution, Deployment`>`Toolchains`.

![Config Toolchains](./images/clion-toolchain.png)

### Compiling, running and debugging

CLion was originally designed for complex multi-file C/C++ projects, and early versions used [CMake](https://cmake.org/) as the build tool by default. But since CLion 2022.3, CLion supports [running a single C or C++ file](https://www.jetbrains.com/help/clion/run-single-file.html).

There are several ways to run a C++ program. A simple workflow is:

1.  Create a C/C++ project: `New -> Project -> C++ Executable`, choose a suitable location and language standard, and click `Create`.
2.  Open the project. The project directory should now contain a `cmake-build-debug` directory, a `CMakeLists.txt` file and a `main.cpp` file. Since we don't need CMake to manage the project, we can delete `CMakeLists.txt` and the `cmake-build-debug` directory with everything in it.
3.  Open `main.cpp` and right-click in the editor area. You will see a `Run 'main.cpp'` option. Choose it, and CLion automatically creates a run configuration and runs the program.

![C++ Single File Execution](./images/clion-single-file-execution.png)

To debug the program, set breakpoints in the editor area, right-click in the editor area, and choose `Debug 'main.cpp'`.

### Compiling, running and debugging with CMake

#### Settings

CLion can also use [CMake](https://cmake.org/) as the build tool. CMake settings can be changed in `Build, Execution, Deployment -> Toolchains -> CMake`.

![CMake Settings](./images/clion-cmake.png)

#### Compiler options

By default, CMake uses `CMakeList.txt` in the project root as the configuration file for building the project. You can use the `add_compile_options` command to add compiler options, for example:

```cmake
add_compile_options(-std=c++17 -DDEBUG)
```

For other CMake features, see the [official CMake documentation](https://cmake.org/documentation/).

## Getting a free CLion license

CLion is a paid product, but you can apply for a special license with an educational email address or an open-source project. Once approved, you can use the genuine CLion IDE for free, as well as other paid JetBrains products.

???+ note "Note"
    [Since May 2025, CLion is free for non-commercial use.](https://blog.jetbrains.com/clion/2025/05/clion-is-now-free-for-non-commercial-use)
    
    According to the definition in the Toolbox Subscription Agreement for Non-Commercial Use, a commercial product is one that is distributed or made available for a fee, or used as part of your commercial activity. However, some categories are explicitly excluded from this definition. Common non-commercial use cases include learning and self-education, content creation of any kind, open-source code, and hobby development.

### Getting it with an educational email

Go to the [Free Educational Licenses page](https://www.jetbrains.com/community/education/#students) on the official website, click the `Apply` button, and fill in the required information to apply.

![Educational Licenses](./images/clion-edu.png)

Note: when registering, enter an educational email address ending in @edu.cn in the email field. You get the special license only after verifying your email.

You can apply for an educational email address on your university's academic affairs website. If you can't get one, you need to verify your status through [CHSI](https://www.chsi.com.cn) (mainland China only).

### Getting it with an open-source project

If you are a core developer or maintainer of an open-source project, you can try applying for an Open Source Development License. The process is similar to the educational license, but you need to provide the repository URL of the open-source project.

![Open Source Development License](./images/clion-oss.png)
