## Introduction

Sublime Text (ST below; a number after it indicates the version, and without a number the text applies to all versions) is a lightweight text editor that supports syntax highlighting and code completion for many languages. It is highly extensible and has a Vim mode, and its special hot-exit mode greatly reduces the chance of losing files.

The new NOI Linux supports ST3's last version, 3.2.2[^ref1], so this page focuses on ST3. The stable release of ST4 is now out[^ref2], and if you still use ST3 it will prompt you to update.

Important differences between ST4 and ST3 are noted where relevant. Menu items and settings are referred to by their English names.

## Installation

For installing ST4, see the [Sublime Text 4 download page](https://www.sublimetext.com/download).

For installing ST3, see the [Sublime Text 3 download page](https://www.sublimetext.com/3).

???+ note "Purchase reminder"
    ST is paid software, but it has an unlimited trial. The trial has no missing features, but a pop-up asking you to activate will appear from time to time.

## Plugins and customization

### Chinese localization

ST does not support Chinese out of the box. If you want a Chinese interface, you need to install a localization plugin.

#### Installing the package manager

After opening ST, press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> to bring up the command palette, type `Install` and press Enter (the full command is `Install Package Control`, case-insensitive). You should then see a `=` moving back and forth in the bottom-left corner. A pop-up will tell you when Package Control has been installed (or failed to install); how long it takes depends on your network.

If the pop-up says installation failed (a network issue), download [Package Control](https://packagecontrol.io/Package%20Control.sublime-package) manually and put the downloaded file into the `\Installed Packages` folder in ST's data directory. Wait a moment and ST will detect the plugin automatically (sometimes you need to restart ST).

???+ note "Path of the ST data directory"
    On Windows, if there is a `\data` folder in ST's **installation directory**, ST automatically uses (or initializes) that folder as the data directory.
    
    The path is usually `C:\Users\<username>\AppData\Roaming\Sublime Text 3` for ST3 and `C:\Users\<username>\AppData\Roaming\Sublime Text` for ST4. ST first looks for the path of its own version; if that doesn't exist, it looks for the path of an older version; if none exist, it creates and initializes a new one.
    
    On Ubuntu 20.04.1, which NOI Linux is based on, ST3's data directory is `$HOME/.config/sublime-text-3` and ST4's is `$HOME/.config/sublime-text`. The rules are the same as on Windows.
    
    You can use `Preferences->Browse Packages...` to quickly open the `\Packages` folder in the data directory.

#### Installing the localization plugin

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> again, type `Install` and press Enter (the full command is `Package Control: Install Package`). Wait for it to load; you should then see this screen:

![](./images/sublime3-1.png)

Type `Chinese`, select ChineseLocalizations and press Enter. Wait for installation to finish; the interface will then switch to Chinese automatically (in ST4, since the localization plugin hasn't been updated, some newer menu items will be missing, but this usually doesn't affect editing).

### Changing the font

Open `Preferences->Settings` and add a line `"font_face": "font name",` inside the braces of the user settings on the right. ST stores its settings in JSON. Save after editing; if the font is installed on your system, ST switches to it automatically.

Generally, if you only care about how Chinese text is displayed, Microsoft Yahei Consolas and Microsoft YaHei Mono are good choices.

???+ warning "Warning"
    Never change any setting (including plugin settings) in the default settings on the left, even if you can. This is not recommended: when the software (or plugin) updates, the default settings will be reset.

### Installing plugins and themes

Plugins and themes are installed the same way as the localization plugin.

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd>, type `Install` and press Enter, then search for the plugin/theme/color scheme.

Recommended plugins:

-   BracketHighlighter : improves the built-in bracket highlighting. A must-have.
-   C++ Snippets : ST comes with C++ code completion that keeps opening braces on the same line. If you prefer a style with braces on a new line, install this plugin; it also adds some extra completions.
-   C++ 11 : C++ 11 syntax highlighting (not needed in ST4).
-   SublimeAstyleFormatter : Astyle, for formatting code.
-   Diffy : press <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>D</kbd> to quickly compare the files open in the first and second panes, line by line.
-   ConvertToUTF8 : detects file encodings automatically and supports converting between encodings.
-   SideBarEnhancements : improves the sidebar. Fairly recommended.
-   Transparency : makes the window transparent.

If you need something else, try searching for it.

Some themes:[^ref3]

1337 (color scheme only), 3024 (color scheme only), Grandson-of-Obsidian (color scheme only), Seti\_UI (theme only, also adds highlighting for formats such as git; fairly recommended), Material Theme, Predawn, Agila, Materialize.

To edit your own color scheme, visit [tmTheme Editor](http://tmtheme-editor.herokuapp.com/).

In ST4, you can adjust the color scheme in `Preferences->Customize Color Scheme` or the theme in `Preferences->Customize Scheme`.

### Enabling Vi Mode

ST's developers provide an optional plugin, Vintage, for Vi users. It emulates most of Vi's features.

#### How to enable it

The Vintage plugin is disabled by default. Open `Preferences->Settings`, remove Vintage from the `"ignored_packages"` entry in the user settings and save (don't delete the whole entry, only Vintage). `INSERT MODE` will then appear on the left of ST's status bar, which means Vintage is enabled.

Alternatively, press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd>, type `Enable`, select `Package Control: Enable Package`, press Enter and choose Vintage. This method requires Package Control.

#### Related settings

To disable the arrow keys, add the following in `Preferences->Key Bindings`:

```JSON
{ "keys": ["left"], "command": ""},
{ "keys": ["right"], "command": ""},
{ "keys": ["up"], "command": ""},
{ "keys": ["down"], "command": ""},
```

To make ST start in command mode, add the following in `Preferences->Settings`:

```json
"vintage_start_in_command_mode": true,
```

You can also bind entering command mode to any key via key bindings (see [Key bindings](#key-bindings) for details).

#### Differences from Vi

ST's Vintage plugin differs from Vi in some ways. Some of them are listed here:

-   Selecting text in insert mode does not enter visual mode; typing then replaces the text instead of being treated as a command. Visual mode can only be entered from command mode.
-   `r`, `R`, `zA`, `za`, `zi`, `z=`, `@` and commands that use the <kbd>\[</kbd>, <kbd>]</kbd> or <kbd>"</kbd> keys don't exist.
-   Shortcuts using <kbd>Ctrl</kbd>, <kbd>Shift</kbd> and <kbd>Alt</kbd> keep their ST bindings. For example, <kbd>Ctrl</kbd>+<kbd>V</kbd> pastes normally instead of entering visual mode.
-   Command-line mode only keeps `:e`, `:0`, `:$` and `:s`.
-   The `\` and `?` commands open the search box instead of letting you type the word in the command. Also, numeric counts don't work with them.
-   The `q` macro-recording command starts ST's built-in macro recording. After pressing <kbd>Q</kbd>, you press one more key to start recording, but the recorded macro is not bound to that key; you replay it with <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Q</kbd>. To save it, use `Tools->Save Macro...`; you have to set up a shortcut for it yourself.
-   The `number+.` combination doesn't work.

### Settings

#### ST settings

Configure these in `Preferences->Settings`. Here are some of the more useful options:

```JSON
{
  //font size
  "font_size": 11,
  
  //font; optional, defaults to Consolas
  "font_face": "",
  
  //convert tabs to spaces automatically
  "translate_tabs_to_spaces": true,
  
  //indent width
  "tab_size": 4,
  
  //highlight the current line
  "highlight_line": true,
  
  //remove trailing whitespace when saving
  "trim_trailing_white_space_on_save": true,
  
  //when text is selected, search only within the selection
  "auto_find_in_selection": true,
  
  //disables plugins unlikely to be used in OI; adjust as you like
  "ignored_packages": [
    "ActionScript", "AppleScript", "ASP", "Batch File", "C#", 
    "Clojure", "CSS", "D", "Diff", "Erlang", "Git Formats", 
    "Go", "Graphviz", "Groovy", "Haskell", "HTML", "Java", 
    "LaTeX", "Lisp", "Lua", "Makefile", "Matlab", 
    "Objective-C", "OCaml", "Perl", "PHP", "Python", 
    "R","Rails", "RestructuredText", "Ruby", "Rust", 
    "Scala", "ShellScript", "SQL", "TCL", "Textile", "XML", 
  ],
  
  //relative line numbers; useful with Vintage for quick jumps
  "relative_line_numbers": false,
}
```

#### Key bindings

Configure these in `Preferences->Key Bindings`. Find the command you want to change on the left, copy it to the right and change the keys.

For example, to change the build shortcut from <kbd>Ctrl</kbd>+<kbd>B</kbd> to <kbd>F9</kbd> (if you don't disable the original shortcut, this actually adds a second way to trigger it), add the following in `Preferences->Key Bindings`:

```JSON
//bind the build command to f9
{ "keys": ["f9"], "command": "build" },

//move the sort-lines command originally on f9 to shift+f9; you rarely need it, so this line is optional
{ "keys": ["shift+f9"], "command": "sort_lines", "args": {"case_sensitive": false} },
```

#### Plugin settings

Plugin settings are in `Preferences->Package Settings->plugin name`. Be careful not to modify the default settings.

For example, here are some settings for BracketHighlighter, changed in `Preferences->Package Settings->BracketHighlighter->Bracket Settings`:

```JSON
{
  //draw a line at the start of the lines between matching brackets, to quickly see the bracket's range
  "content_highlight_bar": true,
  
  //show matching brackets in the minimap
  "show_in_minimap": true,
  
  //ignore the match search limit
  "ignore_threshold": true,
  
  //style is the highlight style: bold highlights a block, underline is a thick underline, outline draws a box around
  //color is the color; the default settings already list all supported colors
  //icon is the marker shown in the gutter
  "bracket_styles": {
    "default": {"icon": "dot", "color": "region.yellowish", "style": "bold",},
    "unmatched": {"icon": "question", "color": "region.redish", "style": "outline",},
    "curly": {"icon": "curly_bracket", "color": "region.purplish",},
    "round": {"icon": "round_bracket", "color": "region.yellowish",},
    "square": {"icon": "square_bracket", "color": "region.bluish",},
    "angle": {"icon": "angle_bracket", "color": "region.orangish",},
    "tag": {"icon": "tag", "color": "region.orangish",},
    "c_define": {"icon": "hash", "color": "region.yellowish",},
    "single_quote": {"icon": "single_quote", "color": "region.greenish",},
    "double_quote": {"icon": "double_quote", "color": "region.greenish",},
    "regex": {"icon": "star", "color": "region.greenish",}
  }
}
```

### Modifying and adding

Sometimes parts of a plugin are not quite what you want, or you want to localize a plugin. Then you need to modify the plugin.

Plugins are stored in the `\Installed Packages` folder in the data directory.

The files there have the `.sublime-package` extension but are really `.zip` archives, so you can open them with any archive tool.

For example, to change the auto-completions, edit the `\Snippets\*.sublime-snippet` files in the `\Packages\C++` plugin in ST's **installation directory**. To **add** completions, install C++ Snippets and edit or add files there (or create a new plugin; you can't add files directly to the built-in C++ plugin, or they won't be recognized). When saving any change, you **must** close ST, and make a backup first; otherwise you may lose files.

Of course, anything you add can go under `\Packages\User\` in the data directory; that is always supported.

For example, a completion for a file template can be written like this:

```XML
<snippet>
  <description>template_code</description> <!-- this is the preview of the completion -->
  <content><![CDATA[#include <cstdio>
using namespace std;

int main() {
  freopen("${1:file name}.in", "r", stdin);
  freopen("$1.out", "w", stdout);
  ${0:/* code */}
  fclose(stdin);
  fclose(stdout);
  return 0;
}]]></content>
  <tabTrigger>code</tabTrigger> <!-- this is the text that triggers the completion -->
  <scope>source.c++</scope> <!-- this is the language the completion applies to -->
</snippet>
```

Below are some file extensions and what they are for. For a detailed plugin development tutorial, see the [community documentation](https://docs.sublimetext.io/guide/extensibility/plugins/) and the [official documentation](https://www.sublimetext.com/docs/3/):

| Extension            | Purpose                                                                   |
| -------------------- | ------------------------------------------------------------------------- |
| .sublime-build       | Build system file                                                         |
| .sublime-completions | Completion list for file names (usually header files)                     |
| .sublime-syntax      | Syntax highlighting file                                                  |
| .sublime-settings    | Settings file                                                             |
| .tmPreferences       | List file in preferences                                                  |
| .sublime-keymap      | Key binding file                                                          |
| .sublime-snippet     | Code completion (snippet) file                                            |
| .sublime-commands    | Command definition file                                                   |
| .sublime-menu        | ST UI file, including the sidebar and top menu bar (the main target of localization) |

Plugin updates overwrite the original files directly, so back up any files you change.

## Editing

### Setting the syntax

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and type the syntax name, or click `Plain Text` in the bottom-right corner and change it to the language you need. You can also set it in `View->Syntax`.

![](images/sublime3-2.png)

### Shortcuts

ST has chord shortcuts. For example, <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Backspace</kbd> means press <kbd>Ctrl</kbd>+<kbd>K</kbd> first, then <kbd>Ctrl</kbd>+<kbd>Backspace</kbd>.

Some shortcuts:

| Keys                                                                       | Command                                                                                     |
| -------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| <kbd>Ctrl</kbd>+<kbd>X</kbd>                                               | Cut the current line                                                                        |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>K</kbd>                              | Delete line                                                                                 |
| <kbd>Ctrl</kbd>+<kbd>Enter</kbd>                                           | Insert line below                                                                           |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Enter</kbd>                          | Insert line above                                                                           |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Up</kbd>                             | Move line up                                                                                |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Down</kbd>                           | Move line down                                                                              |
| <kbd>Ctrl</kbd>+<kbd>L</kbd>                                               | Select line; repeat to select more lines below                                              |
| <kbd>Ctrl</kbd>+<kbd>D</kbd>                                               | Select word; repeat to select more occurrences and enter multiple selection mode (for quick bulk edits) |
| <kbd>Ctrl</kbd>+<kbd>M</kbd>                                               | Jump to the matching bracket                                                                |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>M</kbd>                              | Select the contents inside the brackets (without the brackets); repeat to include the brackets |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>K</kbd>                  | Delete to end of line (chord shortcut; using Vim mode instead is recommended)               |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Backspace</kbd>          | Delete to start of line (chord shortcut; using Vim mode instead is recommended)             |
| <kbd>Ctrl</kbd>+<kbd>]</kbd>                                               | Indent the current (selected) lines                                                         |
| <kbd>Ctrl</kbd>+<kbd>\[</kbd>                                              | Unindent the current (selected) lines                                                       |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>                              | Duplicate the current line below                                                            |
| <kbd>Ctrl</kbd>+<kbd>J</kbd>                                               | Join the next line onto the current line                                                    |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd>                              | Paste and indent (for pasting whole blocks of code)                                         |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd> | Paste from history (chord shortcut; consider changing it to <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>V</kbd>) |
| <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd>                             | Add a cursor on the line below, keeping the current one (enters multiple selection mode)    |
| <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Up</kbd>                               | Add a cursor on the line above, keeping the current one (enters multiple selection mode)    |
| <kbd>Ctrl</kbd>+<kbd>R</kbd>                                               | Go to any symbol in the file (function or type definition)                                  |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>R</kbd>                              | Go to any symbol in the project (function or type definition)                               |
| <kbd>Ctrl</kbd>+<kbd>P</kbd>                                               | Go to any file (files opened before or existing in the project)                             |
| <kbd>\~</kbd>                                                              | Toggle the case of the selection                                                            |

### Auto-completion

ST has rich completion features. Possible completions are shown below the cursor; press <kbd>Tab</kbd> or <kbd>Enter</kbd> to accept one (in ST4, after accepting a non-snippet completion, pressing <kbd>Tab</kbd> again cycles through completions that contain it as a substring).

Snippet completions usually have some edit fields. After completing, the first field is selected so you can replace it. For complex completions with several fields, such as `for`, press <kbd>Tab</kbd> after editing one field to move to the next. While inside a field, you must use <kbd>Enter</kbd> to accept a completion (in ST4 you can keep using <kbd>Tab</kbd>).

If auto-completion doesn't work, fix it like this:

1.  Check that you have switched the language; by default ST creates new files as Plain Text.

2.  Open `Preferences->Settings` and add these two lines:

```JSON
"auto_complete": true,
"auto_match_enabled": true,
```

### Multiple selection

Hold <kbd>Ctrl</kbd> and click to add cursors on the screen. <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Up</kbd> or <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd> adds a cursor on the adjacent line. Any editing action is applied to all cursors at once.

### Find and replace

<kbd>Ctrl</kbd>+<kbd>F</kbd> is find, <kbd>F3</kbd> is find next, <kbd>Shift</kbd>+<kbd>F3</kbd> is find previous, and <kbd>Ctrl</kbd>+<kbd>H</kbd> is replace.

The five search options are: regular expression, case sensitive, whole word, wrap around, and in selection.

It's recommended to set `"auto_find_in_selection"` to `true` in your settings. Then, when more than one word is selected, find automatically searches only within the selection.

## Demos

### Hot exit

Try typing something in ST and then closing the whole ST window directly. ST closes immediately without any prompt, and when you open it again you won't lose any data, as long as you don't restore your computer from a backup.

### Multiple selection

To change every `bok` in the code below to `book`, just put the cursor in any `bok` and press <kbd>Ctrl</kbd>+<kbd>D</kbd> repeatedly to select them all quickly.

```cpp
int check() {
  book[1] = 1, book[2] = 1, book[3] = 1, bok[1] = 1, bok[2] = 1, bok[3] = 1,
  bok[4] = 1, bok[5] = 1;
}
```

To change everything after the equals signs in the file below to `"good"`, put the cursor before `aaa` on the first line, press <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd> five times, then press <kbd>Ctrl</kbd>+<kbd>D</kbd> and type `good`.

Or select `"a` and press <kbd>Ctrl</kbd>+<kbd>D</kbd> repeatedly, then press <kbd>Right</kbd> and <kbd>Ctrl</kbd>+<kbd>D</kbd>, and then type.

```cpp
s[1] = "aaa";
s[2] = "aab";
s[3] = "aac";
s[4] = "good";
s[5] = "aae";
s[6] = "aaf";
```

To add parentheses around every `a + b` below, select one `a + b`, press <kbd>Ctrl</kbd>+<kbd>D</kbd> repeatedly and type <kbd>(</kbd> (when a region is selected, typing any opening bracket wraps the region in matching brackets).

```plain
a + b*a + b*a + b
```

### Find and replace

To change everything after the equals signs in the file below to `"good"`, you can also use replace with <kbd>Ctrl</kbd>+<kbd>H</kbd>: turn on regex, enter `".*"`, and replace it with `"good"`.

```cpp
s[1] = "aaa";
s[2] = "aab";
s[3] = "aac";
s[4] = "good";
s[5] = "aae";
s[6] = "aaf";
```

To add semicolons to the code below, use replace in selection: turn on regex, enter `\n`, and replace it with `;\n`.

```plain
int main() {  int a, b  cin >> a >> b  cout << a + b  return 0}
```

### Macro recording

To add semicolons to the code below, press <kbd>Ctrl</kbd>+<kbd>q</kbd> to start recording a macro, then press <kbd>End</kbd>, <kbd>;</kbd>, <kbd>Down</kbd> in order, and press <kbd>Ctrl</kbd>+<kbd>q</kbd> to stop recording (the bottom-left corner won't show that recording is in progress the whole time, but it really is recording). Then just press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>q</kbd> repeatedly.

```plain
int main() {
  int a, b
  cin >> a >> b
  cout << a + b
  return 0
}
```

??? note "If the Vintage plugin is enabled"
    After running <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>q</kbd> once, you can press <kbd>Esc</kbd> to enter command mode and type `..` (the `.` command can repeat ST3 commands)

For saving macros and binding them to keys, see the [community documentation](https://docs.sublimetext.io/guide/extensibility/macros.html).

## Compiling and running

ST's build environment is already configured and ready to use.

On Windows, you need to add the directory containing g++ to the PATH environment variable and restart ST.

### Compiling

Just press <kbd>Ctrl</kbd>+<kbd>B</kbd> to build. The first time, you'll need to choose a build system: choose `C++ Single File` (compile) or `C++ Single File - Run` (compile and run).

#### Changing the compile options

ST's default compile command is `g++ "${file}" -o "${file_path}/${file_base_name}"`. To change the compile options, create a new build system.

Open `Tools->Build System->New Build System...` and enter the following between the braces:

```JSON
// adjust the compile options as you like
// compile and run
"shell_cmd": "g++ -Wall \"${file}\" -o \"${file_path}/${file_base_name}.exe\" && \"${file_path}/${file_base_name}.exe\"",

// this line lets ST3 show errors graphically; remove it if you prefer reading g++'s messages
"file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
```

After saving, press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> to switch build systems and use it. This configuration compiles the program and runs it in an external CMD window.

The file is saved as `\Packages\User\<build system name>.sublime-build` in the data directory, and you can edit it again any time.

### Running

If you chose `C++ Single File - Run` (run after compiling) or configured automatic running, the build output panel that pops up at the bottom should show nothing (unless there's a compile error), because ST's build output panel is actually a terminal and you can type input directly.

When the program finishes, ST shows the running time. It measures from when you pressed <kbd>Ctrl</kbd>+<kbd>B</kbd> until all the CMD commands finish, so it includes compile time and the time spent typing input, and, if running in an external CMD, the time to open and close CMD.

???+ warning "Warning"
    You cannot send <kbd>F6</kbd> or <kbd>Ctrl</kbd>+<kbd>Z</kbd> in this panel. For programs that read until end of file, use file input, or configure the program to run in an external CMD.

### Debugging

You can install plugins that let ST do graphical gdb debugging, but relying on plugins for gdb debugging is not recommended.

A better approach is to add commands that start gdb when configuring the build system, and debug on the command line outside ST.

## Miscellaneous

-   Drag a folder into ST and press <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>B</kbd> to open the sidebar for switching files quickly.
-   Make good use of the jump features, especially <kbd>Ctrl</kbd>+<kbd>P</kbd> to jump between files and <kbd>Ctrl</kbd>+<kbd>R</kbd> to jump to functions.
-   ST supports git[^ref4].
-   All of ST's configuration is stored in the data directory, so you can pack it up and take it anywhere, but the license registration can't be used on multiple computers.

## External links

-   [Debugging from the command line](../cmd.md)
-   [Sublime Text 3 official documentation](https://www.sublimetext.com/docs/3/)
-   [Sublime Text community documentation](https://docs.sublimetext.io/)

## References and notes

[^ref1]: [NOI Linux 2.0 released](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)

[^ref2]: [Sublime Text 4 released](https://www.sublimetext.com/blog/articles/sublime-text-4)

[^ref3]: [sublime, a handy and clean text editor](https://www.luogu.com.cn/blog/acking/sublime)

[^ref4]: [Sublime Text Git integration](https://www.sublimetext.com/docs/git_integration.html)
