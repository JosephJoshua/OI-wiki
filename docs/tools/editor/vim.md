author: Enter-tainer, ouuan, Xeonacid, Ir1d, partychicken, ChungZH, LuoshuiTianyi, Kewth, s0cks5, Doveqise, StudyingFather, SukkaW, SodaCris, SkyeYoung, 383494, danielqfmai, yui-ng

Vim - the ubiquitous text editor.

## Introduction

Vim is a text editor that grew out of vi. It has a very rich set of programming-friendly features, such as code completion, compiling and jumping to errors, and is widely used among programmers.

## Installation

Linux systems usually come with Vim. Open a terminal and type `vim` to start it, or `vim filename` to open a file directly. You can also open a file from inside Vim with `:e filename`.

If you need to install it manually, Vim's [official website](https://www.vim.org/) has [download instructions](https://www.vim.org/download.php); compile and install it as needed.

## Vim's modes and common keys

Vim's basic operations are covered in its built-in tutorial. Open a terminal and type `vimtutor` to start it.

It usually takes twenty or thirty minutes to get a rough feel for these operations.

### Command Mode

This is the default mode after you start Vim.

In this mode, Vim treats your keystrokes as commands, not as text to insert. For example, if you press <kbd>i</kbd> now, no character is typed; <kbd>i</kbd> is treated as a command.

Vim's direction keys are <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd>, or <kbd>h</kbd>, <kbd>j</kbd>, <kbd>k</kbd>, <kbd>l</kbd>.

```text
        ↑(k)
        ^
(h)← <     > →(l)
        v
        ↓(j)
```

Common commands in command mode:

-   `i` switches to insert mode and starts inserting text **at the cursor**. Press <kbd>Esc</kbd> to return to normal mode.
-   `r` replaces the character under the cursor: press it, then press another key to replace with. Press <kbd>Esc</kbd> to cancel.
-   `R` switches to replace mode and starts overwriting text from the cursor. Press <kbd>Esc</kbd> to return to normal mode.
-   `x` deletes the character under the cursor.
-   `:` switches to command-line mode, where you type a command on the bottom line.
-   `a` switches to insert mode and starts inserting text **after the cursor**.
-   `o` switches to insert mode and opens a new line below the cursor
-   `O` switches to insert mode and opens a new line above the cursor.
-   `p` pastes the clipboard below the cursor; `P` pastes it above the cursor.
-   `dd` deletes the whole line the cursor is on.
-   `d` also deletes. It is usually combined with a motion command, or used in visual mode.
-   `c` changes text: `cX` is roughly `dX` followed by `i` to enter insert mode. But `cw`/`cW` are special cases equivalent to `ce`/`cE`: they only change up to the end of the word, and don't also delete the whitespace after it as `dw` does.
-   `u` undoes the last change to the text.
-   `y` copies (yanks) the selected region. You need to press `v` to enter visual mode first.
-   `yy` copies the current line.
-   `Ctrl + r` redoes the last undone change.
-   `:w` saves the file; often combined with q to save and quit.
-   `:q` quits Vim.
-   `:q!` force-quits Vim without saving changes.

??? info "About the clipboard"
    Vim's built-in clipboard is isolated from the outside world. To paste external content, press <kbd>Ctrl</kbd>+<kbd>V</kbd> in insert/replace mode (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd> on Unix-like systems).

Motion commands (pressed alone they move the cursor; they can be combined with `c`, `d` and `y`):

-   `w` start of the next word
-   `e` end of the current or next word
-   `b` start of the current or previous word
-   `0` start of the line
-   `$` end of the line
-   `gg` first line of the file
-   `G` last line

For example, consider this situation:

```cpp
int a = 1 << 32;
```

Go to this line, press `0` to jump to the start, press `cw` to change the word, type `long long`, and press <kbd>Esc</kbd> to finish.

Some other commands:

-   `=` auto-indents the selected lines using the default format.
-   `==` auto-indents the current line.
-   `.` repeats the last command. (See "Advanced topics".)

Press <kbd>/</kbd> in command mode and a search box appears at the bottom. Type what you want to find and press Enter to see the results. If there are several matches, press <kbd>n</kbd> to jump to the next one and <kbd>N</kbd> to jump to the previous one.

Press <kbd>\*</kbd> in command mode to search for the word under the cursor.

If you type a number n before a command, the command is repeated n times.

### Insert Mode

Press <kbd>i</kbd> in command mode to enter insert mode, and press <kbd>Esc</kbd> to return to command mode.

In insert mode, you can use these keys:

-   Character keys, with or without <kbd>Shift</kbd>: type characters
-   <kbd>ENTER</kbd>, the Enter key: new line
-   <kbd>BACK SPACE</kbd>, the Backspace key: delete the character before the cursor
-   <kbd>DEL</kbd>, the Delete key: delete the character after the cursor
-   Arrow keys: move the cursor through the text
-   <kbd>HOME/END</kbd>: move the cursor to the start/end of the line
-   <kbd>Page Up/Page Down</kbd>: scroll up/down a page
-   <kbd>Insert</kbd>: toggle between insert and replace mode; the cursor becomes a vertical bar/underline
-   <kbd>ESC</kbd>: leave insert mode and switch to command mode

In insert mode, press <kbd>Ctrl</kbd>+<kbd>o</kbd> to enter "insert-command mode": after running one command, you automatically return to insert mode.

### Command-line mode

Press <kbd>:</kbd> in command mode to enter command-line mode.

In command-line mode you can type commands of one or more characters, and there are a great many of them.

The basic commands in command-line mode are:

-   `:help`/`:h` view Vim's online help (in English).
-   `:e` open a file; type a file name that doesn't exist to create a new file
-   `:split` open a file in a new split below
-   `:vsplit` open a file in a new split on the left
-   `:w` save the file.
-   `:q` quit Vim.
-   `:wq` save the file and quit Vim.
-   `:q!` force-quit Vim without saving changes.
-   `:read src` read the given content below the cursor; it can be a file or the output of a `!command`.
-   `:s` is the substitute command.

```vim
" replace the first str1 on the current line with str2
:s/str1/str2/
" replace every str1 on the current line with str2
:s/str1/str2/g
" replace every str1 on the current line with str2, asking before each replacement
:s/str1/str2/gc
" on lines x1 to x2, replace the first str1 on each line with str2
:x1,x2 s/str1/str2/
" on lines x1 to x2, replace every str1 with str2
:x1,x2 s/str1/str2/g
" on lines x1 to x2, replace every str1 with str2, asking before each replacement
:x1,x2 s/str1/str2/gc
" on every line, replace the first str1 with str2
:%s/str1/str2/
" replace every str1 in the whole file with str2
:%s/str1/str2/g
" replace every str1 in the whole file with str2, asking before each replacement
:%s/str1/str2/gc
```

If the command has the form `:!command`, it is run in a bash terminal.

Press <kbd>Esc</kbd> to leave command-line mode.

### Visual mode

Press `v` to enter visual mode, mostly used for selecting a region. Press `V` (`Shift+v`) to enter visual line mode, for selecting whole lines.

Press <kbd>Ctrl</kbd>+<kbd>v</kbd> or <kbd>Ctrl</kbd>+<kbd>q</kbd> to enter visual block mode.

In visual block mode, press <kbd>I</kbd> or <kbd>A</kbd> to enter insert mode (like `i` and `a`). When you leave insert mode, the change you made to this line is applied at the same position on every selected line. This is often used to comment out many lines at once.

After selecting, you can also type `y` or `d` to run those commands.

You can switch between the three visual modes with keystrokes.

## Vim shortcuts

See [The most complete Vim keyboard cheat sheet ever: from beginner to advanced](https://cenalulu.github.io/linux/all-vim-cheatsheat/)

## Advanced topics

### The `.` command

Vim users naturally dislike repetitive text edits, because Vim always needs two more keystrokes than other editors: <kbd>Esc</kbd> and <kbd>i</kbd>. However, Vim provides the repeat command `.`, which works for repeated insertions, changes and deletions.

The `.` command repeats the last command. But this "command" isn't limited to a single command: it can be a `number + command` combination, and `enter insert mode + type text + Esc` also counts as one command. So using `.` well is the key to working efficiently.

For example, every line in the following code is missing a semicolon at the end:

```text
int a, b
cin >> a >> b
cout << a + b
return 0
```

Using `.` together with `A`, the command that moves to the end of the line and starts inserting, you can add the missing semicolons efficiently.

```vim
A;<Esc>
" repeat the command below
j.
```

As another example, in the code below the array name in the last five assignments is misspelled:

```cpp
int check() {
  book[1] = 1, book[2] = 1, book[3] = 1, bok[1] = 1, bok[2] = 1, bok[3] = 1,
  bok[4] = 1, bok[5] = 1;
  return 0;
}
```

Fixing them one by one is tedious, but the `s` command in command-line mode would change all of them.

The first way is to use the `s` command in normal mode (delete the character under the cursor and enter insert mode). Go to the first letter of the first wrong array name, press `3s`/`cw`, type the correct name and leave insert mode. Then move the cursor to each remaining one and use the `.` command.

The second, faster way is to use search. Type `/bok`, press Enter, use `n` to get to the first letter of the first wrong array name, type `3s new_name <Esc>`, and finally repeat `n.`.

The third way uses the simple find command `f`. In normal mode on a line, `f + a single character` finds that character on the line and moves the cursor to it; press `;` to find the next one and `,` to find the previous one. So for the code above, type `fb;;;`, enter insert mode to make the change, and then repeat `;.`. This works when you only need to move within one line.

### Macros

Vim's macro feature can repeat commands of any length.

Before using a macro, you "record" it: you record a sequence of keystrokes and play it back, which gives you repetition. Recording is simple: type `q` in normal mode to start recording. Next, choose a register for the macro by pressing any of the 26 letters. The bottom-left will then show `recording @<the letter you chose>`. Now you can start recording commands. Likewise, press `q` in normal mode to stop recording.

To use it, press `:` to enter command-line mode and type `@<the letter you chose>`; the commands you recorded are then run.

Combining `.` and macros, that is, record a macro → run the macro → repeat with `.` → number + `.`, makes you very efficient.

### The normal command

This command is related to normal mode. It repeats a command on the given lines.

Press `:` to enter command-line mode and type the following command:

```vim
:a,b normal command
```

or:

```vim
:a,b norm command
```

This runs `command` in normal mode on lines a\~b.

Because the `normal` command can be repeated with `.` and is easy to understand, it is used even more often than macros.

### Number + `.` + macros + normal

The three commands above can be combined. For example:

> I downloaded a book and want every chapter to become a "heading", so that I can convert it to formats like mobi or generate a clickable table of contents. How do I do that?

Here is how to do it with Vim:

1.  Press <kbd>/</kbd> to open the search box and search with a regular expression;
2.  Start recording a macro with the `q` command;
3.  Type the `I#` command, then press <kbd>ESC</kbd>;
4.  Stop recording with the `q` command;
5.  Type `normal n@<letter>` to go to the next match and repeat the previous step;
6.  Type `number + .` to repeat it many times.

## External links

-   [Vim official website](https://www.vim.org/)
-   [The original author's configuration](https://github.com/LuoshuiTianyi/Vim-for-OIWiki)
-   [Vim debugging: getting started with termdebug](https://fzheng.me/2018/05/28/termdebug/)
-   [Vim scripting cheatsheet](https://devhints.io/vimscript)
-   [Learn Vimscript the Hard Way](https://learnvimscriptthehardway.stevelosh.com)
-   [Linux vi/vim | Runoob Tutorial](https://www.runoob.com/linux/linux-vim.html)
