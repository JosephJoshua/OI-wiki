author: ouuan, CBW2007, partychicken, StudyingFather, Xeonacid, Henry-ZHR

## About

Notepad++ is a text editor for Windows. It supports many interface languages, many encodings, and highlighting and completion for many programming languages. Its logo is also very cute: a chameleon (![npp-logo](./images/npp-logo.webp))

It is much more powerful than many other editors, more stable when opening large files, and undoing over and over won't break anything. You don't even need to save when closing it: it automatically keeps your work in a buffer for you (this may need configuring). It is also very small, just 10MB+, so you can even carry it around on a USB drive.

## Download and installation

See [Getting started | Notepad++ User Manual](https://npp-user-manual.org/docs/getting-started/).

## Changing the interface language

![npp-lang](./images/npp-lang.gif)

Once the language is set, you can tweak the editor however you like!

## Basic usage

This part covers some basic and distinctive features.

### Find and replace

Click "(menu bar) Search" -> "Find" (shortcut `CTRL`+`F`) to open the "Find" page (shown below).

![npp-search](./images/npp-search.png)

Click "(menu bar) Search" -> "Replace" (shortcut `CTRL`+`H`) to open the "Replace" page (shown below).

![npp-replace](./images/npp-replace.png)

Find and Replace are actually one window; click the tabs at the top to switch between them.

It works much like in ordinary editors, but supports more, such as:

1.  Whole-word or case-sensitive matching, etc.
2.  Matching across documents
3.  Escape characters, such as '\r', '\n'.
4.  Regular expressions
5.  Counting

### Periodic backup

![npp-settings-1](./images/npp-settings-1.png)

With this feature, you no longer need to worry about losing code in an accident!

However, this feature only takes a snapshot of your file; it doesn't really save it. So good saving habits are still recommended. Alternatively, you can install the "Auto Save" plugin from the built-in plugin store (see [Advanced usage -> Plugins](#plugins); the same applies below)

### Bookmarks

Press `Ctrl`+`F2` on a line to set/remove a bookmark. Lines with a bookmark have a blue dot at the front.

Press `F2` to jump to the next bookmark.

If you find this inconvenient, you can install the "Bookmarks" plugin from the built-in plugin store

### Syntax highlighting

Right-click "XXX file" in the bottom-left corner to choose highlighting for many languages: C, C++, PASCAL, Markdown and more. You can even define your own highlighting!

If changing the highlighting every time you open a file is annoying, you can change the default in "Settings -> Preferences -> New Document -> Default language".

If you need to render Markdown, install "Markdown Viewer" from the plugin store. Many more plugins like it are waiting for you!

### Show all characters

![npp-settings-2](./images/npp-settings-2.png)

Click the button circled in red to show normally invisible characters such as spaces, TABs and line breaks very clearly (or, depending on your taste, very messily).

### Automatic detection of file encoding and line endings

Notepad++ can automatically detect whether the current file is encoded in `UTF-8`, `GB2312` or something else. No more being haunted by mojibake like `锟斤拷` or `烫烫烫`.

To view the text in a different encoding, click "(top menu) Encoding" -> "Encode in XXX". To convert the file to a different character encoding, click "(top menu) Encoding" -> "Convert to XXX".

It can also automatically detect whether line endings are `CR`, `LF` or `CRLF`, so you don't have to worry about downloaded data losing its line breaks.

In the status bar at the bottom you can see text like "Windows(CR LF)"; this is the line ending of the current file. Right-click it to change the current file's line endings. This is even clearer together with "Show all characters"!

## Advanced usage

This part is for users with more demanding needs.

### Macros

Macros can do a lot of repetitive work for you. For example, changing "abcde" on odd-numbered lines to "afce" takes two steps.

#### Recording a macro

![npp-macro-rec](./images/npp-macro-rec.gif)

#### Using a macro

![npp-macro-use](./images/npp-macro-use.gif)

#### Bulk processing and reuse

What if there are many more lines? The procedure needs a small change.

First, recording: you must first press `HOME` or `END` on the keyboard to move the cursor to the start or end of the line, then use the arrow keys to adjust the horizontal position, and then make your changes. At the end, you must use the arrow keys to move the cursor to the next line to process.

For the example above, first press `END`, then press `←`, `Backspace`, `←`, `Backspace`, `F` in order, then press `↓` twice, and finally stop recording.

Next, playback: move to the first line to process (line 3), then click "Macro" -> "Run a Macro Multiple Times". In the pop-up window, choose the macro to run (the one just recorded is usually the first), set how many times to run it (or run it until the end of the file), and click OK.

#### Saving a macro

Click "Macro" -> "Save Current Recorded Macro" and set a name and shortcut to save it for later use.

### Plugins

#### Managing plugins

Open the "Plugins" menu, and the list shows all plugins you have installed.

Then choose "Plugins Admin" to manage your plugins.

#### Installing plugins (store)

1.  Open the "Available" tab and check the plugins you want in the list
2.  Click the "Install" button in the top-right corner and restart the program as prompted.

#### Installing plugins (manually)

1.  Download the plugin (the official location, hosted by a third party: <https://sourceforge.net/projects/npp-plugins/>). Be sure to choose a plugin with **the same processor architecture as your Notepad++ installation**.
2.  Find a file named "XXX.dll" (usually named after the plugin).
3.  In Notepad++, click Plugins in the menu bar, and click "Open Plugins Folder" in the list.
4.  Put the DLL file you just found into that folder and restart Notepad++.
5.  [Optional] Delete the file you just copied, **but do not delete the generated folder!**

Tips: if it keeps failing, try creating a folder with the same name as the plugin and putting the ".dll" file into that folder

#### Updating plugins

In Plugins Admin, choose the "Updates" tab, check the plugins to update, then click the "Update" button in the top-right corner.

#### Removing plugins

Also in Plugins Admin, choose the "Installed" tab, check the plugins to remove, then click the "Remove" button in the top-right corner.

### Setting up a development environment

It's more than an editor! Notepad++ is practically magical: it can compile code with a few simple clicks and can even replace an IDE! Here we use C++ as an example

1.  Install a compiler and add its required directories to the PATH environment variable. (For C++, add %APPPATH%\bin.) You are done when typing g++ in cmd no longer says "'g++' is not recognized as an internal or external command..." (you may need to restart your computer). We recommend [downloading ConsolePauser](https://sourceforge.net/projects/orwelldevcpp/files/Tools/ConsolePauser.exe/download), putting it anywhere you like, and adding its directory to the environment variable (it is a Dev-C++ helper, also found in the Dev-C++ root directory).

2.  In the menu bar, choose "Run" -> "Run..." to open the "Run" window.

3.  Enter the following commands one at a time

    ```shell
    #compile command:
    cmd /c g++.exe -o $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH)
    #run command:
    cmd /c $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH) & pause
    #debug command:
    cmd /c gdb $(CURRENT_DIRECTORY)\$(NAME_PART).exe

    #If you downloaded ConsolePauser, you can use the following for a better experience running programs! (Remember to add it to the environment variable!)

    #compile command:
    cmd /c (start ConsolePauser "g++.exe -o $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH)")
    #run command:
    cmd /c (start ConsolePauser "$(CURRENT_DIRECTORY)\$(NAME_PART).exe")
    #debug command:
    cmd /c (start ConsolePauser "gdb $(CURRENT_DIRECTORY)\$(NAME_PART).exe")
    ```

4.  Click "Save", give it any name you like, such as "Compile" or "Run", then set the shortcut you want (pick something easy to remember; for example, Dev-C++ uses `F9` and `F10`).

5.  Enjoy it!

## Easter eggs

1.  When you run the installer, you will see this sentence at the bottom:

    > "The best things in life are free. Notepad++ is free. So Notepad++ is the best(.)"
    >
    > (In other words: the best things in life are free; Notepad++ is free; so Notepad++ is the best.)

    Quite the boast, but you have to admit it's confident.

2.  Type "random" in a new tab, select it, and press `F1` to get an amusing quote.
