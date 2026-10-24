author: shenyouran, Xeonacid, StudyingFather, CoelacanthusHex

## Introduction

Xcode is an integrated development environment (IDE) for macOS, developed by Apple Inc.

## Installation

### Method 1

Open the App Store that comes with your Mac (or try this [quick link](https://apps.apple.com/cn/app/xcode/id497799835?mt=12)) and download Xcode. Click Get, then enter your Apple ID password to start downloading and installing.

![](images/xcode-1.jpg)

### Method 2

Visit the [Apple Developer downloads page](https://developer.apple.com/download/more/), sign in with your Apple ID, and find the installer for the latest stable version of Xcode (the latest version without "Beta"; here it is 11.6):

![](images/xcode-2.jpg)

Click the blue file name in the pop-up to download it. Once you have the archive, extract it with the system's built-in tool to get Xcode.app. Move this file into the Applications folder and it's ready to use.

## Basic setup

The first time you open Xcode, you may see this pop-up window:

![](images/xcode-3.jpg)

This window guides you through installing Xcode components. Click `Install` and enter your user password.

After installation, the left side of the window shows:

![](images/xcode-4.jpg)

Click `Create a new Xcode project`, choose `Command Line Tool` under `macOS` at the top, and click `Next` in the bottom-right corner.

![](images/xcode-5.jpg)

Next, you can name the project, but the most important thing is to choose the project's language. Pick C or C++ under `Language` at the bottom, depending on what you need:

![](images/xcode-6.jpg)

Choose the project directory as you like. After it's created, Xcode opens the project automatically and creates a `main` file (with the extension `.c` for C and `.cpp` for C++).

Click this file to open the editor area:

![](images/xcode-7.jpg)

After writing code, press ⌘B to build and ⌘R to run. After running, drag the panes apart and you get three areas:

![](images/xcode-8.jpg)

Usually we only use the editor area and the run (console) area. If the program reads input, type it in the run area and you'll get the output. It looks like this:

![](images/xcode-9.jpg)

In the same way, you can run any single C/C++ program.

## Using the all-in-one header

While writing code, we may need many header files. A common solution is to use the all-in-one header.

We include the all-in-one header on the first line of the source, but compiling reports `'bits/stdc++.h' file not found`, meaning the header file can't be found.

![](images/xcode-10.jpg)

This is because macOS uses [libc++](https://libcxx.llvm.org/) as its C++ standard library implementation by default, while the all-in-one header `bits/stdc++.h` exists only in [GNU libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/).

However, we can write an all-in-one header ourselves.

### Step 1

Open Terminal (Terminal.app) and go to the folder where Xcode stores its header files:

```bash
cd /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1
```

If your Xcode version is 12.5 or later, use

```bash
cd /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/
```

### Step 2

Create a `bits` folder and enter it:

```bash
mkdir bits
cd bits
```

Create the stdc++.h file with vim:

```bash
vim stdc++.h
```

You'll see this:

![](images/xcode-11.jpg)

Next, we edit the file with vim. Press the i (insert) key to enter insert/edit mode (`-- INSERT --` appears at the bottom):

![](images/xcode-12.jpg)

Copy the code block below and paste it into the terminal:

??? note "All-in-one header code"
    ```cpp
    // C++ includes used for precompiling -*- C++ -*-
    
    // Copyright (C) 2003-2020 Free Software Foundation, Inc.
    //
    // This file is part of the GNU ISO C++ Library.  This library is free
    // software; you can redistribute it and/or modify it under the
    // terms of the GNU General Public License as published by the
    // Free Software Foundation; either version 3, or (at your option)
    // any later version.
    
    // This library is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.
    
    // Under Section 7 of GPL version 3, you are granted additional
    // permissions described in the GCC Runtime Library Exception, version
    // 3.1, as published by the Free Software Foundation.
    
    // You should have received a copy of the GNU General Public License and
    // a copy of the GCC Runtime Library Exception along with this program;
    // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
    // <http://www.gnu.org/licenses/>.
    
    /** @file stdc++.h
     *  This is an implementation file for a precompiled header.
     */
    
    // 17.4.1.2 Headers
    
    // C
    #ifndef _GLIBCXX_NO_ASSERT
    #include <cassert>
    #endif
    #include <cctype>
    #include <cerrno>
    #include <cfloat>
    #include <ciso646>
    #include <climits>
    #include <clocale>
    #include <cmath>
    #include <csetjmp>
    #include <csignal>
    #include <cstdarg>
    #include <cstddef>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <ctime>
    #include <cwchar>
    #include <cwctype>
    
    #if __cplusplus >= 201103L
    #include <ccomplex>
    #include <cfenv>
    #include <cinttypes>
    #include <cstdbool>
    #include <cstdint>
    #include <ctgmath>
    /* https://stackoverflow.com/a/25892335/15125422 */
    #if defined(__GLIBCXX__) || defined(__GLIBCPP__)
    #include <cstdalign>
    #include <cuchar>
    #endif
    #endif
    
    // C++
    #include <algorithm>
    #include <bitset>
    #include <complex>
    #include <deque>
    #include <exception>
    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <ios>
    #include <iosfwd>
    #include <iostream>
    #include <istream>
    #include <iterator>
    #include <limits>
    #include <list>
    #include <locale>
    #include <map>
    #include <memory>
    #include <new>
    #include <numeric>
    #include <ostream>
    #include <queue>
    #include <set>
    #include <sstream>
    #include <stack>
    #include <stdexcept>
    #include <streambuf>
    #include <string>
    #include <typeinfo>
    #include <utility>
    #include <valarray>
    #include <vector>
    
    #if __cplusplus >= 201103L
    #include <array>
    #include <atomic>
    #include <chrono>
    #include <codecvt>
    #include <condition_variable>
    #include <forward_list>
    #include <future>
    #include <initializer_list>
    #include <mutex>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <thread>
    #include <tuple>
    #include <type_traits>
    #include <typeindex>
    #include <unordered_map>
    #include <unordered_set>
    #endif
    
    #if __cplusplus >= 201402L
    #include <shared_mutex>
    #endif
    
    #if __cplusplus >= 201703L
    #include <any>
    #include <charconv>
    // #include <execution>
    #include <filesystem>
    #include <memory_resource>
    #include <optional>
    #include <string_view>
    #include <variant>
    #endif
    
    #if __cplusplus > 201703L
    #include <bit>
    #include <compare>
    #include <concepts>
    #include <numbers>
    #include <ranges>
    #include <span>
    #include <stop_token>
    // #include <syncstream>
    #include <version>
    #endif
    ```

The file comes from [libstdc++ version 10.2.0](https://github.com/gcc-mirror/gcc/blob/ee5c3db6c5b2c3332912fb4c9cfa2864569ebd9a/libstdc++-v3/include/precompiled/stdc++.h), with small changes to make it work with libc++.

Press <kbd>Esc</kbd> in the top-left corner of the keyboard to leave edit mode, then type `:wq` and press Enter to save the file.

### Step 3

Close the terminal and go back to Xcode. Press ⌘B/⌘R again to build, and this time it succeeds:

![](images/xcode-13.jpg)

## Pros and cons

Pros: developed by Apple, well suited to Mac users, with a complete and good-looking interface.

Cons: Xcode is mainly for developing Apple apps, so for contests most of its features are unnecessary. The installer is large, and it only runs on Mac.
