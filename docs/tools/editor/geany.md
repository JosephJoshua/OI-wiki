author: xingjiapeng, MingqiHuang

Geany is a lightweight, convenient editor that is fairly friendly to beginners on Linux.

Like Dev-C++, it can compile and run a single file.

Unlike Dev-C++, though, it runs on Linux, Windows and macOS.

Its official website is: <https://geany.org/>

## Pros and cons

### Pros

1.  Lightweight;
2.  Can compile and run a single file;
3.  Needs little configuration;
4.  Cross-platform.

### Cons

1.  Not many people use it;
2.  It has some permission issues on macOS Catalina[^1];
3.  New files have no syntax highlighting by default; you have to switch the file type manually.

## Installation

See [Download | Geany](https://geany.org/download/)

## Tips

### Switching the file type

Switch it in *Document -> Set Filetype*.

For example, for C++, click *Document -> Set Filetype -> Programming Languages -> C++ source file*, and the file now has C++ syntax highlighting.

### Setting up file templates

Create a templates/files folder in the configuration directory. Files you create in it become template files. Reopen Geany, and you will find them under *File -> New (with Template)*.

You can find the configuration directory in the second and third lines of *Help -> Debug Messages*.

Here are the default template directories on macOS and Linux:

-   System directory: `/usr/share/geany/templates/files/`
-   User directory: `~/.config/geany/templates/files/`[^2]

## Common problems

### Working with Deepin Terminal

In *Preferences -> Tools -> Terminal*, change the terminal command to:

```bash
deepin-terminal -x "/bin/sh" %c
```

Then click the "Apply" button.[^3]

## References and notes

[^1]: See: <https://github.com/geany/geany/issues/2344>

[^2]: Source: <https://wiki.geany.org/config/templates>

[^3]: Source: Deepin Wiki <https://wiki.deepin.org/>
