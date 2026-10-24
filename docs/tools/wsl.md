author: GoodCoder666, Ir1d, H-J-Granger, NachtgeistW, StudyingFather, Enter-tainer, abc1763613206, Anti-Li, shenyouran, Chrogeek, SukkaW, Henry-ZHR, Early0v0, andylizf, tootal, Marcythm, CoelacanthusHex, indevn, qinyihao, peasoft

![Header image](./images/wsl-header.png)

This chapter explains how to run a Linux environment on Windows using the Windows Subsystem for Linux.

## Introduction[^ref1]

Most schools' contest practice environments are built on Windows, but the NOI series of contests already uses NOI Linux, a modified version of the Ubuntu operating system.

The environment for NOI contests (since September 1, 2021) is as follows.[^ref2]

| Category                           | Software or module        | Version            | Notes                                                                                      |
| :---------- | :------------------------ | :----------------- | :--------------------------------------------- |
| System                             | Linux kernel              | `5.4.0-42-generic` | 64-bit x86 (AMD64)                                                                         |
| Languages                          | GCC (`gcc` and `g++`)     | `9.3.0`            | C and C++ compilers                                                                        |
|                                    | FPC                       | `3.0.4`            | Pascal compiler (note: since 2022, NOI series contests no longer support Pascal)           |
|                                    | Python 2                  | `2.7`              | Not a contest language                                                                     |
|                                    | Python 3                  | `3.8`              | Not a contest language                                                                     |
| Debugging tools                    | GDB                       | `9.1`              |                                                                                            |
|                                    | DDD                       | `3.3.12`           | GUI front end for GDB                                                                      |
| Integrated development environments (IDE) | Code::Blocks       | `20.03`            | C/C++ IDE                                                                                  |
|                                    | Lazarus                   | `2.0.6`            | Pascal IDE                                                                                 |
|                                    | Geany                     | `1.36`             | C/C++/Pascal (lightweight) IDE                                                             |
| Text editors                       | Visual Studio Code        | `1.54.3`           |                                                                                            |
|                                    | GNU Emacs                 | `26.3`             |                                                                                            |
|                                    | gedit                     | `3.36.2`           |                                                                                            |
|                                    | Vim                       | `8.1`              |                                                                                            |
|                                    | Joe                       | `4.6`              |                                                                                            |
|                                    | nano                      | `4.8`              |                                                                                            |
|                                    | Sublime Text              | `3.2.2`            |                                                                                            |
| Other software                     | Firefox                   | `79.0`             | Web browser                                                                                |
|                                    | Midnight Commander (`mc`) | `4.8.24`           | File manager                                                                               |
|                                    | xterm (uxterm)            | `3.5.3`            | Terminal                                                                                   |
|                                    | Arbiter-local             | `1.02`             | Standalone program judging tool                                                            |

The contest environment differs from an everyday environment in a number of ways:

-   Working on the command line differs from working in a graphical interface.
-   Linux differs from Windows, for example in case sensitivity.
-   Different compilers (MSVC and GCC) and different compiler versions (GCC on Windows vs. on Linux, 32-bit vs. 64-bit Linux GCC, GCC 7 vs. GCC 8, etc.) behave differently, for example in variable initialization and in handling out-of-bounds array indices.
-   Different judging systems (Luogu and Arbiter) check time limits and memory limits differently.

This can lead to a series of awkward situations:

-   You press <kbd>Ctrl</kbd>+<kbd>C</kbd> to copy, and the program exits instead.
-   A program template that always gets AC gets WA on Linux.

To avoid such awkward situations in the contest room, we need to get familiar with Linux beforehand.

Although the official NOI website has released the ISO image of NOI Linux, setting up a virtual machine is rather troublesome. Also, since NOI Linux ships with a graphical interface by default, it may not run smoothly on low-end machines.

Windows 10 introduced the Linux subsystem (WSL) in its Anniversary Update and upgraded it to WSL 2 in the May 2020 Update. As of June 1, 2020, WSL supports installing mainstream Linux distributions such as Ubuntu, openSUSE Leap, Kali and Debian. However, WSL does not support Arbiter, which NOI uses for judging.

???+ note "[What is the Linux subsystem (WSL)](https://zh.wikipedia.org/zh-cn/%E9%80%82%E7%94%A8%E4%BA%8ELinux%E7%9A%84Windows%E5%AD%90%E7%B3%BB%E7%BB%9F)"
    Windows Subsystem for Linux (WSL) is a compatibility layer for running Linux binary executables (in ELF format) natively on Windows 10, Windows 11 and Windows Server 2019.
    
    WSL lets developers run a GNU/Linux environment as is - including most command-line tools, utilities and applications - without the overhead of a virtual machine.
    
    WSL is only available on 64-bit Windows 10 version 1607 and later, Windows 11 and Windows Server 2019/2022.

## Enabling WSL[^ref3]

### Automatic installation

???+ warning "Warning"
    This section applies to Windows 10 version 2004 and later (build 19041 and later) or Windows 11.
    
    If you are using a version before 2004 or your computer doesn't support virtualization, read the manual installation section below.
    
    If you are using Windows 10 before version 1607, your system doesn't support WSL.

1.  Open Windows PowerShell as administrator (right-click the "Start" button and choose Windows PowerShell (Admin) or Windows Terminal (Admin))

2.  Type `wsl --install` and wait for all components to install automatically. You may need to restart your computer during this to enable the required Windows features.

3.  After installation, you can find your installed distribution in the "Start" menu or in a Windows Terminal tab.

4.  Next, go to the "Configuring the distribution" section below to finish the remaining setup.

???+ tip "Tip"
    If the `wsl --install` progress bar is very slow or fails repeatedly, download the offline installer with the `.msi` extension from the [release page on GitHub](https://github.com/microsoft/wsl/releases).

### Manual installation[^ref4]

???+ warning "Warning"
    Below are the steps for installing WSL manually. If you have already done the automatic installation, skip this part.

#### Enable the Windows Subsystem for Linux

Before installing any Linux distribution for WSL, you must use one of the two methods below to make sure the "Windows Subsystem for Linux" optional feature is enabled:

Using the command line:

1.  Open PowerShell as administrator and run:

    ```powershell
    Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
    # Skip this step if you only want to use WSL 1
    Enable-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform
    ```

2.  Restart your computer when prompted.

Using the graphical interface:

![Windows features](./images/wsl-windows-features.png)

1.  Open "Control Panel"

2.  Go to "Turn Windows features on or off" under "Programs and Features"

3.  Select "Windows Subsystem for Linux" and "Virtual Machine Platform"

4.  Click OK

5.  Restart

#### Install the kernel update package

If you want to use WSL 1, skip this step.

Download and install the [WSL2 Linux kernel update package for x64 machines](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi).

#### Set the default WSL version

In most cases, WSL 2 is recommended.
For the differences between WSL 1 and WSL 2, see [Comparing WSL 2 and WSL 1](https://docs.microsoft.com/zh-cn/windows/wsl/compare-versions)

??? note "About systemd"
    WSL 1 does not support systemd at all (which means some features that need systemd won't work or need workarounds). WSL 2 has built-in support for systemd. If you need systemd and the distribution you are running isn't configured to enable it, see [Advanced settings configuration in WSL](https://learn.microsoft.com/zh-cn/windows/wsl/wsl-config#systemd-support).

```powershell
# Set the default WSL version to WSL 2
wsl --set-default-version 2
```

#### Install a WSL distribution

![Search page](./images/wsl-search-page.png)

Open the Microsoft Store, search for "Ubuntu", select "Ubuntu", and click "Install". You can also open [Ubuntu's store page](https://www.microsoft.com/zh-cn/p/ubuntu/9nblggh4msv6).

???+ warning "Warning"
    The Ubuntu in the Microsoft Store is updated along with Ubuntu, so its contents may change. If you want a stable Ubuntu long-term support release, install an LTS version of Ubuntu from the Microsoft Store.

Because Microsoft Store downloads are unstable in mainland China, it is recommended to get the latest LTS release from the [official Ubuntu website](https://ubuntu.com/download/wsl), or earlier versions from [Ubuntu Release](https://releases.ubuntu.com/). Download the file with the `.wsl` extension and double-click it. For other versions, you can also find the URLs in [WSL/Distribution.json](https://github.com/microsoft/WSL/blob/master/distributions/DistributionInfo.json).

## Configuring the distribution[^ref5]

This chapter uses Ubuntu installed automatically by Windows as an example.

### Running Ubuntu

Find Ubuntu in the "Start" menu and launch it, or start it from the Windows command line with the `wsl` command.

You can create an app tile for Ubuntu or pin it to the taskbar so it's easy to open next time.

### Initialization

The first time you run Ubuntu, you need to finish initialization.

```console
    Installing, this may take a few minutes...
```

After a minute or two, the system asks you to create a new user account.

```console
    Please create a default UNIX user account. The username does not need to match your Windows username.
    For more information visit: https://aka.ms/wslusers
    Enter new UNIX username: chtholly
```

After you enter the username, it asks for a password. On Linux, it is normal that nothing is shown on screen while you type a password.

```console
    Enter new UNIX password:
```

Once the username and password are set, WSL is installed.

```console
    Installation successful!
    To run a command as administrator (user "root"), use "sudo <command>".
    See "man sudo_root" for details.
    
    chtholly@SENIORIOUS:~$
```

## Basic configuration

A freshly installed system has no C/C++ compiler, so you need to set up the environment by hand.

```console
$ gcc
The program 'gcc' is currently not installed. You can install it by typing:
sudo apt install gcc
$ g++
The program 'g++' is currently not installed. You can install it by typing:
sudo apt install g++
```

### Switching to a mirror in China

Ubuntu's default package sources are outside China; you can switch to a mirror in China to speed things up. See [MirrorZ's Ubuntu help page](https://help.mirrorz.org/ubuntu/), choose the configuration that matches your system version (use `lsb_release -a` to check your Ubuntu version), and follow the commands given on the page.

???+ warning "Use package sources that match your system version"
    Unless you know what you are doing, don't use sources that don't match your system version!

After switching sources, run the following commands to update your software:

```console
$ sudo su # After this command, the prompt changes from $ to #; watch the prompt before running the commands below
[sudo] password for xxx:
# apt update
# apt upgrade -y
```

### Installing the Chinese language environment

```console
# apt install language-pack-zh-hans -y
# apt install fontconfig -y
# apt install fonts-noto-cjk fonts-wqy-microhei fonts-wqy-zenhei -y # Chinese fonts
# dpkg-reconfigure locales
```

A settings menu now appears. Ignore it and just press Enter.

In the next menu, select `zh_CN.UTF-8` and press Enter.

<!-- scripts.linter.preprocess.fix_details off -->

```text
    Default locale for the system environment:

                 None
                 C.UTF-8
                 en_US.UTF-8
                [zh_CN.UTF-8]

            <Ok>            <Cancel>
```

<!-- scripts.linter.preprocess.fix_details on -->

Then close WSL and restart it, and the system will be in Chinese.

Next, enter the following commands one by one to switch the `man` help pages to Chinese.[^ref6]

```console
# apt install manpages-zh
# sed -i 's|/usr/share/man|/usr/share/man/zh_CN|g' /etc/manpath.config
```

You can test it with `man help`.

### Installing the build environment[^ref7]

```console
# apt install -y build-essential vim ddd gdb fpc emacs gedit anjuta lazarus
```

To install GUIDE, see [Installing GUIDE on Debian or Ubuntu](./editor/guide.md#installing-on-debian-or-ubuntu).

This installs the basics plus the environment officially required by NOI. If needed, you can install other packages with `sudo apt install <package-name>`.
To install other versions, see Debian's official [package management manual](https://www.debian.org/doc/manuals/debian-reference/ch02.zh-cn.html).

Here is an example program:

```console
$ vim cpuid.cpp
...
$ g++ -Wall cpuid.cpp -o cpuid
$ ./cpuid
AMD Ryzen 5 1400 Quad-Core Processor
```

???+ note "Note"
    On Linux, executables don't need an extension. See the commands above for how to run them.

## Advanced usage

### Running GUI programs with WSLg

If you use Windows 10 build 19044 or later, or Windows 11, you can use the integrated desktop experience provided by WSL 2. It lets you install and launch Linux desktop programs directly without any other configuration.

See [Run Linux GUI apps on the Windows Subsystem for Linux](https://docs.microsoft.com/zh-cn/windows/wsl/tutorials/gui-apps)

### Installing a graphical environment and connecting with Remote Desktop

If your version doesn't support WSLg yet, you can try the guide below to enable a graphical interface.

We use Xfce as an example.

If you only want to install Xfce, run:

```console
$ sudo apt install xfce4 tightvncserver -y
```

If you want more software besides Xfce, run:

```console
$ sudo apt install xubuntu-desktop -y
```

The graphical environment files are large, so downloading and unpacking takes some time.

Configure xrdp:

```console
$ sudo apt install xrdp -y
$ echo "xfce4-session" >~/.xsession
$ sudo service xrdp restart
```

To avoid conflicting with the computer's existing Remote Desktop, you need to change the default port.

![What happens if you don't change the port](./images/wsl-result-of-not-changing-ports.png)

Run `sudo sed -i 's/port=[0-9]\{1,5\}/port=otherport/' /etc/xrdp/xrdp.ini`, where `otherport` is another port (such as `3390`).

    [globals]
    ...
    port=3390

Run `sudo service xrdp restart`, then go to the Start menu and connect to `localhost:otherport` (with Remote Desktop Connection).

![](./images/wsl-login-using-non-root.png)

![](./images/wsl-first-login.png)

### Connecting with Xming

Enter the Ubuntu environment and install xterm:

```console
# apt install xterm -y
```

Exit Ubuntu.

Download the latest Xming Server from the [Xming X Server download page](https://sourceforge.net/projects/xming/), then install it:

![](./images/wsl-xming-setup-wizard.png)

If you forgot to check Launch Xming after installing, open Xming from the Start menu:

![Don't forget!](./images/wsl-xming.png)

Then go back to Ubuntu and type the following command:

```console
$ DISPLAY=:0 xterm
```

![](./images/wsl-open-xterm.png)

If you installed xfce4, you can start xfce4 in the window that pops up with the following command:

```console
$ xfce4-session
```

![](./images/wsl-open-xfce4-session.png)

The result is shown below. (Press <kbd>Ctrl</kbd>+<kbd>C</kbd> in Xming to exit this screen.)

![](./images/wsl-xfce.png)

### Accessing files between WSL and Windows

Windows drives are mounted automatically under the `/mnt` folder in the Linux environment.
For example, the C drive is at `/mnt/c` in WSL.

```console
PS C:\Users\chtholly> bash
/mnt/c/Users/chtholly$ echo "Hello world!" > hello
/mnt/c/Users/chtholly$ exit
PS C:\Users\chtholly> cat hello
Hello world!
PS C:\Users\chtholly> echo "Welcome!" > welcome
PS C:\Users\chtholly> bash
/mnt/c/Users/chtholly$ cat welcome
Welcome!
```

You can also access WSL folders from the file manager. After installing WSL, a Linux entry appears in the File Explorer sidebar, where you can access the files of all installed distributions.

Similarly, you can type `\\wsl$` directly in the File Explorer address bar or in Run (Win+R) to go to the WSL folders.

You can also access subfolders directly with paths such as `\\wsl$\Ubuntu\home\`.

### Editing with Visual Studio Code

If you like editing code with [Visual Studio Code](./editor/vscode.md) on Windows, you can install the `Remote - WSL` extension in VS Code to edit files in WSL more easily.

With `Remote - WSL`, you can work with the WSL subsystem directly from the VS Code interface on Windows, making it easier to edit files in the subsystem's folders and to debug in the terminal.

Type `code .` in WSL to open Visual Studio Code in the current folder and edit the files there.

You can also edit a specific file with a command like `code filename`.

The Getting Started page of the `Remote - WSL` extension gives a detailed introduction to editing.

You can also refer to the WSL section of the official Visual Studio Code documentation ([Remote development in WSL](https://code.visualstudio.com/docs/remote/wsl-tutorial)), which gives a more detailed walkthrough of the whole process, from installing WSL to using the extension.

## Upgrading WSL1 to WSL2

???+ warning "Warning"
    Make sure you have finished the WSL1 installation steps above.

Run `wsl -l -v` and you will see that the WSL version is 1. You need to upgrade it to get to 2.

1.  Enable the "Virtual Machine Platform" feature

    Run the following in PowerShell as administrator:

    ```shell
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
    ```

    Then **restart your computer**.

2.  Download the Linux kernel update package

    -   Kernel update package for [x64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi).
    -   Kernel update package for [ARM64/AArch64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_arm64.msi).

3.  Set the distribution's version

    Run: `wsl --set-version <distro-name> <version>`

    For example, the command to set Ubuntu 18.04 to WSL 2 is `wsl --set-version Ubuntu-18.04 2`

    This step takes a while. When it finishes, run `wsl -l -v` to check whether the upgrade succeeded.

## FAQ

See also: [FAQ](https://docs.microsoft.com/zh-cn/windows/wsl/faq), [WSL 2 FAQ](https://docs.microsoft.com/zh-cn/windows/wsl/wsl2-faq)

-   How do I do xxx in the subsystem?

    You can use the built-in command line or a graphical interface.
    For example, for vim, type `man vim` on the command line to get detailed usage instructions.
    You can also use `vim --help`.

    For the command line, read [Command line](./cmd.md)

-   How much system resources does it use?

    This system shares the Host with Windows 10, so in theory it uses less than a virtual machine.

## External links

-   [About the Windows Subsystem for Linux](https://docs.microsoft.com/zh-cn/windows/wsl/about)
-   [Ubuntu software repository - MirrorZ Help](https://help.mirrorz.org/ubuntu/)
-   [Dev on Windows with WSL (developing elegantly on Windows with WSL)](https://dowww.spencerwoo.com)
-   [Awesome-WSL on GitHub](https://github.com/sirredbeard/Awesome-WSL)
-   [Troubleshooting the Windows Subsystem for Linux](https://docs.microsoft.com/zh-cn/windows/wsl/troubleshooting)
-   [Upgrading WSL1 to WSL2 (in Chinese)](https://www.cnblogs.com/stulzq/p/13926936.html)

## References and notes

[^ref1]: [Luogu Daily #6 (in Chinese)](https://www.luogu.com.cn/blog/asfr/Run-Ubuntu-On-Windows10)

[^ref2]: [NOI Linux 2.0 released, officially in use from September 1! (in Chinese)](https://noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)

[^ref3]: [Install WSL, Microsoft Docs](https://docs.microsoft.com/zh-cn/windows/wsl/install)

[^ref4]: [Manual installation steps for older versions of WSL](https://docs.microsoft.com/zh-cn/windows/wsl/install-manual)

[^ref5]: [WSL-Ubuntu wiki, ubuntu wiki](https://wiki.ubuntu.com/WSL)

[^ref6]: [How to set up Chinese man pages on Ubuntu (in Chinese), Frank Kan Lushan, 2017-06-09](https://blog.csdn.net/qq_14989227/article/details/72954523)

[^ref7]: [Run Bash on Ubuntu on Windows, Mike Harsh, 2016-05-30, Windows Blog](https://blogs.windows.com/buildingapps/2016/03/30/run-bash-on-ubuntu-on-windows/#cie8WdR3uSjgR5Ru.97)
