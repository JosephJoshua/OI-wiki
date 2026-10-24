This page explains how to install various compilers and interpreters on different systems.

## GCC

### Windows

#### Manual download and install

Visit the [MinGW-w64](https://www.mingw-w64.org/downloads) download page, which lists several builds. For convenience, we use the build provided by WinLibs.

First go to [WinLibs](https://winlibs.com) and download the latest package, choosing a suitable version. This guide uses GCC 12.3.0 + LLVM/Clang/LLD/LLDB 16.0.4 + MinGW-w64 11.0.0 (UCRT):

LLVM Clang is included by default. If you don't want it, you can pick the "without LLVM/Clang/LLD/LLDB" option on the right instead.

![](./images/compiler1.png)

After downloading, extract it somewhere on your computer. This guide extracts it to the root of the C drive. The directory name should preferably contain no non-English characters or spaces; otherwise it may cause problems later.

![](./images/compiler2.png)

Next, add the compiler's executable directory to the system environment variables, so you don't need to give the compiler's path every time you compile. Above we extracted MinGW to `C:\mingw64`, so the executables are in `C:\mingw64\bin`.

Press Windows logo + R, type `rundll32.exe sysdm.cpl,EditEnvironmentVariables` to open the system environment variables window. In the "System variables" section, select the variable named "Path" and click the "Edit" button:

![](./images/compiler3.png)

In the edit window, click the "New" button on the right to add an entry to "Path", and fill in the executable directory noted above (`C:\mingw64\bin` in this guide).

![](./images/compiler4.png)

??? note "Tip for some older versions of Windows"
    Some older versions only let you edit the variable's value as text. In that case, add a **half-width semicolon** at the end of the value, then paste the executable directory after the semicolon, as shown:
    
    ![](./images/compiler5.png)

When done, click "OK" on each window to close them.

Then open a terminal, type `g++ --version` and press Enter. If you see output like the picture below, the installation succeeded.

![](./images/compiler6.png)

#### Installing with MSYS2

MSYS2 provides several independent development environments. If you are not sure which to pick, MSYS2 officially recommends UCRT64.

Open PowerShell and run the following command to install MSYS2:

```powershell
winget install MSYS2.MSYS2
```

After installation, search for and open the MSYS2 UCRT64 terminal from the Start menu. MSYS2 is a rolling release, so first fully update the system:

```bash
pacman -Suy
```

If the update asks you to close all MSYS2 processes, confirm, reopen the MSYS2 UCRT64 terminal, and run `pacman -Suy` again until the update finishes.

Then install the full GNU toolchain for the UCRT64 environment:

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-toolchain
```

In the UCRT64 environment, `MINGW_PACKAGE_PREFIX` is `mingw-w64-ucrt-x86_64`, so the command above installs GCC, GDB, Make and other tools. After installation, you can verify with:

```bash
gcc --version
g++ --version
gdb --version
```

??? note "Why UCRT64"
    UCRT64 uses GCC, UCRT and libstdc++, and it is the environment MSYS2 recommends when you are unsure which to choose. CLANG64 also uses UCRT, but uses LLVM/Clang, LLD and libc++ by default. MINGW64 uses the older MSVCRT and is now listed by MSYS2 as a legacy environment. The MSYS environment is mainly for running Unix tools that depend on the POSIX compatibility layer, and is not suitable for building ordinary native Windows contest programs.
    
    UCRT improves compatibility with MSVC at the C runtime level, but this does not mean that GCC/MinGW and MSVC share a C++ ABI, or that their object files and static libraries can be used interchangeably.

??? warning "Do not modify the global Path"
    We don't recommend adding `C:\msys64\ucrt64\bin` to the global Windows `Path`. The MSYS2 UCRT64 terminal already sets the correct `PATH` for its environment when it starts. Using the matching MSYS2 terminal directly avoids mixing toolchains and runtime libraries from different environments.
    
    Note that if you don't add the UCRT64 `bin` directory to the global Windows `Path`, you also shouldn't call the MSYS2-installed GCC directly from an ordinary PowerShell or CMD. For example, during compilation GCC starts internal programs such as `cc1.exe`, and the DLLs these programs depend on are in the `bin` directory of the UCRT64 environment. Without the environment variables that the MSYS2 UCRT64 terminal sets up, they may fail to start because the DLLs cannot be found. So when using this GCC toolchain, run your compile commands from the MSYS2 UCRT64 terminal, or from a terminal that inherits its environment variables.

#### Installing with Scoop

Open PowerShell and run the following script:

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw-winlibs
```

### Linux

#### Debian/Ubuntu

First update the package list:

```bash
sudo apt update
```

Then install it directly with:

```bash
sudo apt install g++
```

#### Arch Linux

Install it directly with:

```bash
sudo pacman -Syu gcc
```

#### openSUSE

Install it directly with:

```bash
sudo zypper in gcc-c++
```

### macOS

First update the package manager:

```bash
brew upgrade
brew update
```

Then install it directly with:

```bash
brew install gcc
```

## JDK

There are many JDK distributions. Here are two:

-   [Eclipse Temurin](https://adoptium.net/zh-cn/)[^temurin], an OpenJDK build: see [Install Eclipse Temurin™ | Adoptium](https://adoptium.net/zh-CN/installation/).
-   Oracle JDK: see [JDK Installation Guide (JDK 17)](https://docs.oracle.com/en/java/javase/17/install/overview-jdk-installation.html).

## Python 3

There are also many Python implementations[^pythonimpl]. For CPython 3, see [Download Python | Python.org](https://www.python.org/downloads/).

## LLVM

### Windows

??? note "A pitfall of LLVM on Windows"
    LLVM lacks a standard library on Windows, so you still need to install MSVC or GCC.

#### Direct install

Visit the [LLVM](https://github.com/llvm/llvm-project/releases/latest) download page and download LLVM-\*-win64.exe.

If your network connection is poor, you can also download it from the [Tsinghua University open source mirror](https://mirrors.tuna.tsinghua.edu.cn/github-release/llvm/llvm-project/LatestRelease/).

Open the .exe file. During installation, check "Add LLVM to system PATH for current user", then keep clicking "Next" to finish.

Open a terminal, type `clang++ --version` and press Enter. If you see

```text
clang version 15.0.1
Target: x86_64-pc-windows-msvc
Thread model: posix
InstalledDir: <omitted>
```

or something similar, the installation succeeded.

#### Installing with MSYS2

In MSYS2 you can either install Clang as an extra in the UCRT64 environment, or use the CLANG64 environment, whose default toolchain is LLVM.

##### UCRT64 environment

If you mainly use GNU GCC and only need Clang now and then, install it in the MSYS2 UCRT64 terminal:

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-clang ${MINGW_PACKAGE_PREFIX}-llvm
```

If you also need development tools such as `clangd` and `clang-tidy`, install:

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-clang-tools-extra
```

UCRT64 is a GCC-based environment, so the Clang installed here still uses the GNU linker and libstdc++ by default, and you can keep using things provided by libstdc++ such as `bits/stdc++.h`. After installation, you can verify with:

```bash
clang --version
clang++ --version
```

##### CLANG64 environment

If you want a full environment built around LLVM, open the MSYS2 CLANG64 terminal from the Start menu. If you haven't updated MSYS2 yet, first run:

```bash
pacman -Suy
```

If the update asks you to close all MSYS2 processes, reopen the MSYS2 CLANG64 terminal and run the command again. Then install the full toolchain for this environment:

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-toolchain
```

In the CLANG64 environment, `MINGW_PACKAGE_PREFIX` is `mingw-w64-clang-x86_64`. This toolchain includes Clang, LLVM, LLD, LLDB, libc++, Make and other components. The CLANG64 terminal automatically sets the `PATH` this environment needs, so again we don't recommend adding `C:\msys64\clang64\bin` to the global Windows `Path`.

#### Installing with Scoop

Open PowerShell and run the following script:

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install llvm
```

### Linux

#### openSUSE

Install it directly with:

```bash
sudo zypper in llvm clang
```

## MSVC (Visual Studio)

Visit the [Download Visual Studio](https://visualstudio.microsoft.com/zh-hans/downloads/) page, find the "Community" part of the "Downloads" section, and click "Free download". When the download finishes, open the installer and choose to install "Community 2022". In the window that pops up, select only "Desktop development with C++", then click Install.

If you don't want to install the full Visual Studio, scroll down to the "All Downloads" section, find "Build Tools for Visual Studio" under "Tools for Visual Studio", and click "Download" next to it. When the download finishes, open the installer, follow the prompts to select "Desktop development with C++", and install. You can also use the [PortableBuildTools](https://github.com/Data-Oriented-House/PortableBuildTools) tool to install just the MSVC compiler.

[^temurin]: [Eclipse Temurin](https://adoptium.net/) is the former [AdoptOpenJDK](https://adoptopenjdk.net/), which was transferred to the [Eclipse Foundation](https://www.eclipse.org/org/foundation/) in July 2021. See [this announcement](https://blog.adoptopenjdk.net/2021/03/transition-to-eclipse-an-update/) for details.

[^pythonimpl]: [Alternative Python Implementations | Python.org](https://www.python.org/download/alternatives/)
