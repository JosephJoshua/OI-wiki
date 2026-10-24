author: StudyingFather, ayalhw, qinyihao, CoderOJ, mcendu, Libaray

Graphical interfaces can do more and more these days, but many advanced tasks still need the command line.

This page gives a short introduction to using the command line.

## Basics

Windows comes with two command-line interfaces. "Command Prompt" (`cmd`) is the older one, and its features are fairly simple. PowerShell is the newer one; it has many built-in features but is rather heavy. You can find both in the Start menu.

Unix-like systems (including macOS and Linux, called Unix below) come in two kinds: with or without a graphical interface. If the system has a graphical interface (for example macOS, or Linux with GNOME, KDE or another desktop installed), you can usually open the command line with a program called "Terminal" (or "Console"). A system without a graphical interface drops you into the command line automatically after booting.

The Windows command line looks like this:

```doscon
C:\Users\chtholly>
```

Commands you type appear after the `>`.

```doscon
C:\Users\chtholly>echo "Hello World!"
```

The Unix command line looks like this (using Debian/Ubuntu as an example; other systems look roughly the same):

```console
chtholly@seniorious:~$
```

Commands you type appear after the `$`.

```console
chtholly@seniorious:~$ echo "Hello World!"
```

If you log in to the Unix command line as `root`, the `$` is replaced by `#`:

```console
root@seniorious:~# apt-get install gcc
```

Before the `>`, `$` or `#`, the command line shows a path. This path is the working directory, also called the current directory. On Unix the current directory is sometimes shown in a form like `~/folder`, where the leading `~` is the home directory of the logged-in user. The home directory of user `chtholly` is in a different place on different systems: on Linux it is `/home/chtholly`, and on macOS it is `/Users/chtholly`.

## Syntax and common commands[^1]

### File system

First, there are two ways to describe a location in the file system: relative paths and absolute paths.

-   Relative path: describes a location relative to the current path. For example, if the current path is `~/folder`, then `./a.cpp` actually means the file `~/folder/a.cpp`. **When the current path changes, the location a relative path refers to may change too.**

-   Absolute path: describes a location with the full path. For example, `~/folder/a.cpp` is an absolute path. **The location an absolute path refers to does not change when the current path changes.**

    On both Windows and Unix, `.` means the current directory and `..` means its parent directory. On Unix, `~` also means the user's home directory (note that `~` is expanded by the shell, so it may not work in other places).

On Unix, the `pwd` command prints the current directory (PowerShell on Windows also has it, but Windows Command Prompt does not; see the tip below). On both Windows and Unix, the `cd <directory>` command changes the current directory. For example, `cd folder` switches to the `folder` subdirectory of the current directory, and `cd ..` switches to the parent directory.

???+ note "Special tips for Windows Command Prompt"
    Windows Command Prompt has no `pwd` command, but running `cd` with no arguments does roughly the same thing.
    
    Also note that in Windows Command Prompt, if you use `cd` to switch to a directory **on a different drive from the current directory**, the current directory does not change. You can either type the drive letter of the target path again, or use `cd /d <directory>` to switch the drive at the same time. The two methods look like this:
    
    ```doscon
    C:\Users\Libaray>cd D:\Codes
    C:\Users\Libaray>D:
    D:\Codes>
    ```
    
    ```doscon
    C:\Users\Libaray>cd /d D:\Codes
    D:\Codes>
    ```

On Windows, the `dir` command lists the files in the current directory. On Unix, the command is `ls`. PowerShell also supports the same `ls` command as Unix.

On Windows, use `md <directory>` or `mkdir <directory>` to create a new directory, and `rd <directory>` or `rmdir <directory>` to delete one. On Unix, these two commands are `mkdir` and `rmdir`. Note that **a directory must be empty before you can delete it with `rd` or `rmdir`**. To delete a non-empty directory (along with all files in it), run `rm -r <directory>` on Unix, or `rd /s <directory>` on Windows.

### Redirection

> I compiled a program that reads from standard input and writes to standard output. But the input and output files are both huge. Is there a way to redirect the input from a given input file and the output to a given output file?

You can do it with the following command.

```console
$ command < input > output
```

For example, `./prog < 1.in > 1.out` makes the program `prog` read data from `1.in` in the current directory and write its output to `1.out`, overwriting it.

???+ warning "Warning"
    The old contents of `1.out` will be overwritten. If you want to append to the end of the output file instead, use `>>`, as in `./prog >> 1.out`

Note that PowerShell only supports output redirection, not input redirection.

In fact, most online judges use this redirection mechanism. Contestants submit programs that use standard input and output. With redirection, the judge can make the program read from a given input file and write to a given output file, and then judge it by comparing files.

### Running programs

To run an executable or a batch script, just type its file name on the command line.

Of course, when running a file, the command line does not search every directory. The environment variable `PATH` describes where the command line searches, and the command line looks for the target file in the paths listed in `PATH`.

On Windows, **the current directory is also searched by default**. For example, typing `hello` runs `hello.exe` in the current directory. PowerShell, however, does not look in the current directory for executables by default (the same as Unix). So in PowerShell you need a relative or absolute path to run an executable in the current directory, such as `.\hello.exe`. Otherwise you will see this error:

```ps1con
PS> hello
hello: The term 'hello' is not recognized as a name of a cmdlet,
function, script file, or executable program.
Check the spelling of the name, or if a path was included, verify that
the path is correct and try again.

Suggestion [3,General]: The command hello was not found, but does exist
in the current location. PowerShell does not load commands from the
current location by default. If you trust this command, instead type:
".\hello". See "get-help about_Command_Precedence" for more details.
```

On Unix, **the current directory is not searched by default**, so to run the program `hello` in the current directory you type `./hello`:

```console
$ hello
hello: command not found
$ ./hello
Hello World!
```

### Summary

The usage above covers only a small part of the available commands; many others are not mentioned. Type the help command `help` on the command line to see all basic commands and what they do.

Below is a table comparing Windows and Unix commands for reference.

| Task             | Windows | Unix    |
| ---------------- | ------- | ------- |
| List files       | `dir`   | `ls`    |
| Change directory | `cd`    | `cd`    |
| Make directory   | `md`    | `mkdir` |
| Remove directory | `rd`    | `rmdir` |
| Compare files    | `fc`    | `diff`  |
| Copy file        | `copy`  | `cp`    |
| Move file        | `move`  | `mv`    |
| Rename file      | `ren`   | `mv`    |
| Delete file      | `del`   | `rm`    |

## Compiling and debugging on the command line

See: [Compiling and Debugging on the Command Line](compile-debug.md).

## Command-line tips

### Autocompletion

Completion is one of the basic features of a shell. It mainly reduces how much you need to type and the chance of typos.

Usually the completion key is <kbd>Tab</kbd>. When you press it, the shell completes what you have typed based on the characters entered so far.

Different shells offer completion features of different power.

The completion features of common shells are[^autocomplete]:

| Shell                                   | Completion features (what can be completed)                                                                                        |
| --------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| cmd (the traditional Windows console)   | file paths                                                                                                                         |
| PowerShell                              | file paths, command names in PATH, built-in command names, function names, command arguments; fuzzy matching, auto-correction      |
| Bash                                    | file paths, command names in PATH, built-in command names, function names, command arguments                                       |
| Zsh                                     | file paths, command names in PATH, built-in command names, function names, command arguments; fuzzy matching, auto-correction and suggestions |
| Fish                                    | file paths, command names in PATH, built-in command names, function names, command arguments; fuzzy matching, shows what each argument does while completing, auto-correction and suggestions |

???+ note "Note"
    Some PowerShell features require the PSReadline module to be loaded, or running inside PowerShell ISE.  
    For full completion in Bash you usually need a package called `bash-completions`; some software ships its own completion files.  
    Full completion in Zsh needs user-defined completion files (usually installed with the Zsh package or the corresponding software package).  
    Fish provides good, complete completion out of the box, but completion files for some software not covered officially are provided by that software itself.

### Help documentation

In general, command-line programs come with "help". On Windows you usually get it with `command /?` or `command -?`; on Unix-like systems (such as Linux) you usually use `command --help` or `command -h` (though the "help" on BSD is often too brief to be very useful).

In addition, Unix-like systems have the "manual", which you can read with `man command`. It is usually more detailed than the "help".

### Built-in time and GNU time

To measure how long a program runs, we usually use the `time` command.

But there are actually two commands with this name on the system: one is built into some shells (such as Bash), and the other is GNU time (a separate program). They differ in a few ways.

Usually, typing `time` in Bash calls Bash's built-in version. You can control its output format with the `TIMEFORMAT` environment variable. For example, setting it to `%3lR` prints the real (wall-clock) running time with three decimal places, and `%3lU` prints the user-space running time with three decimal places.[^bash-time-format]

To call the GNU version of time, use `\time` or `/usr/bin/time`. Its output format is not easy to read, but you can add the `-p` flag (that is, `\time -p`) to get readable output.

## Pipes

Suppose we have two programs A and B, both using standard input and output. How do we redirect A's output into B's input?

We could use the redirection described above: first redirect A's output to a temporary file, then redirect B's input from that temporary file.

But this is inefficient. It needs a new file, disk IO may become a bottleneck, and the two programs cannot run at the same time: B can only start after A finishes. Is there a better way?

Yes: a **pipe**. It is very easy to use:

```console
$ A | B
```

This creates a pipe in memory and starts both programs at the same time. Everything A outputs is redirected into the pipe, and the pipe itself does not store data (it actually has a small buffer). Until B reads the data, A's output operation blocks; once B has read the data, A can continue writing. This neatly solves the problems above: there is no disk IO, both programs run at the same time, and no extra memory is used to store intermediate results.

### Named pipes

Sometimes we need more than redirecting one program's output into another's input. For example, in interactive problems we often need to redirect A's output into B's input and B's output into A's input. A normal pipe cannot do this. Redirecting to files does not let the two programs run at the same time either. What we need is a pipe that looks like a file: a named pipe.

On Unix, you can create a named pipe with the following command (using the name `my_pipe` as an example):

```console
$ mkfifo my_pipe
```

If you now list the files in the current directory with `ls`, you will see a new file `my_pipe|`. This is the named pipe; the `|` after the file name means it is a pipe file. You can then read from and write to it just like redirecting to a file.

With named pipes, we can make two programs interact like this:

```console
$ mkfifo input output
$ ./checker > input < output # You must write > input first. Otherwise the shell opens the output pipe first, which has nothing in it yet, and checker will block.
$ ./my_code < input > output
```

When you are done, you can delete the named pipes with `rm`, just like ordinary files.

## References and notes

[^1]: Liu Rujia, *Introduction to Algorithm Competitions (2nd edition)*, Appendix A: Development Environment and Methods

[^autocomplete]: [Comparison\_of\_command\_shells#Interactive\_features](https://en.wikipedia.org/wiki/Comparison_of_command_shells#Interactive_features)

[^bash-time-format]: <https://unix.stackexchange.com/a/70655>
