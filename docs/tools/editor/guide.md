GUIDE (GAIT Universal IDE) is a small integrated development environment developed by the GAIT research group at Beihang University, designed specifically for NOI contestants. It supports three programming languages: C, C++ and Pascal.

???+ note "Note"
    NOI Linux 2.0, in use since September 1, 2021, no longer includes GUIDE.[^ref1]

## Installation

### Windows

See <https://www.noi.cn/xw/2009-03-23/714714.shtml>.

### Linux

See <https://www.noi.cn/xw/2009-03-23/714714.shtml>, or install it with the steps below.

#### Required shared libraries and package names

| Shared library      | Arch package     | Debian package | Fedora package | openSUSE x86 package | openSUSE x86\_64 package |
| ------------------- | ---------------- | -------------- | ---------- | ----------------- | ----------------------- |
| libpng12.so.0       | lib32-libpng12   | libpng12       | libpng12   | libpng12-0        | libpng12-0-32bit        |
| libSM.so.6          | lib32-libsm      | libsm6         | libSM      | libSM6            | libSM6-32bit            |
| libICE.so.6         | lib32-libice     | libice6        | libICE     | libICE6           | libICE6-32bit           |
| libXi.so.6          | lib32-libxi      | libxi6         | libXi      | libXi6            | libXi6-32bit            |
| libXrender.so.1     | lib32-libxrender | libxrender1    | libXrender | libXrender1       | libXrender1-32bit       |
| libXrandr.so.2      | lib32-libxrandr  | libxrandr      | libXrandr  | libXrandr2        | libXrandr2-32bit        |
| libfreetype.so.6    | lib32-freetype2  | libfreetype6   | freetype   | libfreetype6      | libfreetype6-32bit      |
| libfontconfig.so.1  | lib32-fontconfig | libfontconfig1 | fontconfig | libfontconfig1    | libfontconfig1-32bit    |
| libXext.so.6        | lib32-libxext    | libxext6       | libXext    | libXext6          | libXext6-32bit          |
| libX11.so.6         | lib32-libx11     | libx11-6       | libX11     | libX11-6          | libX11-6-32bit          |
| libz.so.1           | lib32-zlib       | zlib1g         | zlib       | libz1             | libz1-32bit             |
| libgthread-2.0.so.0 | lib32-glib2      | libglib2.0-0   | glib2      | libgthread-2\_0-0 | libgthread-2\_0-0-32bit |
| libglib-2.0.so.0    | lib32-glib2      | libglib2.0-0   | glib2      | libglib2\_0-0     | libglib2\_0-0-32bit     |
| libstdc++.so.6      | lib32-gcc-libs   | libstdc++6     | libstdc++  | libstdc++6        | libstdc++6-32bit        |
| libgcc\_s.so.1      | lib32-gcc-libs   | lib32gcc1      | libgcc     | libgcc\_s1        | libgcc\_s1              |
| librt.so.1          | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libpthread.so.0     | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libdl.so.2          | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libm.so.6           | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libc.so.6           | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |

#### Installing on Debian or Ubuntu

```bash
sudo apt install -y libpng12 libsm6 libice6 libxi6 libxrender1 libxrandr libfreetype6 libfontconfig1 libxext6 libx11-6 zlib1g libglib2.0-0 libglib2.0-0 libstdc++6 lib32gcc1 libc6
wget -c http://download.noi.cn/T/noi/GUIDE-1.0.2-ubuntu.tar
tar -xvf GUIDE-1.0.2-ubuntu.tar
cd GUIDE-1.0.2-ubuntu
echo "install:\n\tinstall -Dm755 -t /usr/bin GUIDE\n\tinstall -Dm644 -t /usr/share/ lang_en.qm\n\tmkdir -p /usr/share/apis/ && cp -r apis/* /usr/share/apis/\n\tmkdir -p /usr/share/doc/GUIDE/ && mkdir -p /usr/share/doc/GUIDE/html/ && cp -r doc/*  /usr/share/doc/GUIDE/html/" > Makefile
sudo apt install -y checkinstall
sudo checkinstall --pkgname "GUIDE" --pkgversion "1.0.2" -y
```

#### Installing on openSUSE

Install opi following the instructions at [openSUSE/opi](https://github.com/openSUSE/opi#install).

Then run the following (32-bit users should remove `-32bit`):

```bash
sudo opi checkinstall
sudo zypper install -n {libpng12-0,libSM6,libICE6,libXi6,libXrender1,libXrandr2,libfreetype6,libfontconfig1,libXext6,libX11-6,libz1,libgthread-2_0-0,libglib2_0-0,libstdc++6,libgcc_s1,glibc}-32bit
wget -c http://download.noi.cn/T/noi/GUIDE-1.0.2-ubuntu.tar
tar -xvf GUIDE-1.0.2-ubuntu.tar
cd GUIDE-1.0.2-ubuntu
echo "install:\n\tinstall -Dm755 -t /usr/bin GUIDE\n\tinstall -Dm644 -t /usr/share/ lang_en.qm\n\tmkdir -p /usr/share/apis/ && cp -r apis/* /usr/share/apis/\n\tmkdir -p /usr/share/doc/GUIDE/ && mkdir -p /usr/share/doc/GUIDE/html/ && cp -r doc/*  /usr/share/doc/GUIDE/html/" > Makefile
sudo checkinstall --pkgname "GUIDE" --pkgversion "1.0.2" -y -rpmi
```

## Editing files

Click the "New File" button on the toolbar at the top (or press <kbd>Ctrl</kbd>+<kbd>N</kbd>) to create a new file.

By default, GUIDE's code font is not monospaced, which looks quite ugly, so you should change the font in the settings.

In Edit -> Options -> Syntax Highlighting Settings, click the "All Fonts" button to change the editor font.

Note that unsaved new files still use the default font. So we suggest saving the file first (click the "Save" button on the toolbar, or press <kbd>Ctrl</kbd>+<kbd>S</kbd>) before you start editing.

## Compiling and running

After editing the source code, click the "Compile" button on the toolbar (or press <kbd>F7</kbd>) to compile.

???+ note "Changing compiler options"
    GUIDE has no way to set default compiler options; you can only change the compiler options for one file at a time.
    
    Right-click the tab of the file whose compiler options you want to change and choose **Set Compile Command** to change that file's compiler options.

If the source code compiles successfully, click the "Run" button on the toolbar (or press <kbd>Ctrl</kbd>+<kbd>F5</kbd>) to run the program.

## Debugging

GUIDE's built-in debugger has many bugs (for example, it may crash in the middle of a session), so we don't recommend using it directly.

We recommend debugging with gdb directly in the [terminal](../cmd.md) instead.

[^ref1]: [NOI Linux 2.0 released, officially in use from September 1!](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)
