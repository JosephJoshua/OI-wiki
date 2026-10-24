author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid

## Lemon

???+ warning "Warning"
    On macOS, Lemon may measure memory usage inaccurately, because macOS lacks some of the monitoring tools Linux has, and Lemon-Linux is not optimized for macOS.

**Lemon** is an open-source judging tool written by zhipeng-jia. Its source code is hosted at [zhipeng-jia/project-lemon](https://github.com/zhipeng-jia/project-lemon).

### Ready-to-run versions

-   Ir1d provides a prebuilt version for Linux. Its source code is hosted at [FreestyleOJ/Project\_lemon](https://github.com/FreestyleOJ/Project_lemon/tree/Built).
-   (No longer maintained) Menci provides an updated version. Its source code is hosted at [Menci/Lemon](https://github.com/Menci/Lemon/).
-   (No longer maintained) Dust1404 maintains a version that supports subfolders, testing a single problem, and more. Its source code is hosted at [Dust1404/Project\_LemonPlus](https://github.com/Dust1404/Project_LemonPlus).
-   iotang and Coelacanthus maintain a version that supports subfolders, testing a single problem, and more. Its source code is hosted at [Project-LemonLime/Project\_LemonLime](https://github.com/Project-LemonLime/Project_LemonLime).

### Building it yourself

Ubuntu:

```bash
sudo apt update
sudo apt install qt5-default build-essential git -y
git clone --depth=1 https://github.com/Menci/Lemon.git
cd lemon
# Change the number after -j to set the number of parallel make jobs
./make -j2
sudo install -Dm755 -t /usr/bin/ Lemon
```

To build LemonLime, see LemonLime's [build guide](https://github.com/Project-LemonLime/Project_LemonLime/blob/master/BUILD.md).

### Data format

First open lemon and choose "New Problem", then open the folder of the new problem.

Problems and data should be laid out as follows:

```text
├── data
│   ├── gendata.py
│   ├── product
│   │   ├── product100.in
│   │   ├── product100.out
│   │   ├── product10.in
│   │   ├── product10.out
│   │   ├── product11.in
...
```

After all problems are added, go back to lemon and choose "Add Problems Automatically". The problems and test cases will then show up in lemon.
