author: ouuan, akakw1, Ir1d, partychicken, Xeonacid

This page is a beginner's tutorial for Emacs.

> Get started with Emacs in 15 minutes.

## Introduction

Emacs is an editor that is very easy to get started with: it works after just a few short lines of configuration. But it takes some time to become really skilled at using Emacs for all kinds of work.

As a beginner's tutorial, this page only covers the basic features of Emacs and convenient ways to write and debug code with it.

## Getting started

### Commands

Commands play a big role in Emacs.

Press the Application key[^note1] (Emacs on Windows does not bind this key, so you have to set it up yourself) or the shortcut M-x (<kbd>Alt</kbd>+<kbd>x</kbd>) to open the command prompt. Type a command and press Enter to run it.

Usually you use the `es` or `eshell` command to open Eshell (something like a terminal).

Most commands can be replaced by keyboard shortcuts.

### Buffers

A buffer is an open file or process. If you don't save, changes you make in a buffer do not change the file.

You can switch buffers by clicking a buffer's name at the bottom of the buffer area, or with a keyboard shortcut.

### Compiling, debugging and running

Compiling and debugging are found in the Tools drop-down in the top menu bar. You can also use them through commands or custom keyboard shortcuts.

You can run programs in a terminal or in Eshell.

Click Debugger (gud-gdb) in Tools, enter the program name (it is usually filled in automatically, but if you used "save as" in between or opened two programs to debug, **the automatically filled file name may be wrong**), and debugging starts.

### Split windows

This feature lets you see the contents of several buffers at once without switching back and forth, which makes testing and debugging code easier.

Splitting shows several windows at the same time. Drag the edge of a window with the mouse to resize it.

A few shortcuts:

-   Delete window "C-x 0": remove this window
-   Split side by side "C-x 3": split this window into left and right halves
-   Split top and bottom "C-x 2": split this window into top and bottom halves

The recommended layout splits the screen into four parts. First split side by side and make one part about 3/4 of the screen wide, to use as the editing window. Split the other part side by side again: one part shows debugging and compiler messages, and the other is split top and bottom, with one half showing the input file and the other the output file.

![](./images/emacs.png)

### Keyboard shortcuts

Emacs has a huge number of keyboard shortcuts that can greatly speed up your work. You can define your own shortcuts or remap shortcuts in the configuration.

Because there are so many shortcuts, Emacs shortcuts work differently from the operating system's usual ones.

For ease of description, we use these conventions:

| Character | Key             |
| --------- | --------------- |
| C         | <kbd>Ctrl</kbd> |
| M         | <kbd>Alt</kbd>  |
| ?         | any key         |

There are generally three kinds:

-   `F?`, `ESC`: just press the corresponding function key.
-   `M-?`, `C-?`, `C-M-?`: hold <kbd>Alt</kbd> or <kbd>Ctrl</kbd> and press `?`.
-   `? ?`: press the key for the first `?`, release it, then press the key for the second `?`.

Here are some common shortcuts:

-   `C-x h`: select all
-   `C-x left`, `C-x right`: switch to the previous/next buffer
-   `C-x d`: open a directory
-   `C-x C-f`: open a file (creates it if it doesn't exist)

## Customization

A freshly installed Emacs looks ugly and is not very convenient, so you need to customize it.

The configuration is hard to memorize, so for anything you can set directly through the menus, we suggest not memorizing the configuration for it.

### Setting directly

-   Options: `Highlight Matching Parentheses` highlights matching parentheses
-   Options: `Blink Cursor` makes the cursor blink
-   Options Show/Hide: `Tool Bar` shows/hides the toolbar (shown by default; hiding it is recommended)
-   Options: `Use CUA Keys` when checked, lets you copy and paste with shortcuts like Ctrl + C, Ctrl + V
-   Options Customize-Emacs: `Custom Theme` chooses a color scheme; click save after choosing
-   Options: `Save Options` **saves the configuration**

### Configuration file

Show hidden files in your home directory (on Windows, look in `AppData\Roaming` under your **user directory**). ".emacs" is the configuration file (if it isn't there, you haven't saved options before). Open it and edit it. If Emacs is already open, you need to restart Emacs for the configuration to take effect.

The recommended configuration for contests is below.

```text
;;one-key compile; you can add your own flags. Hard to memorize, so not recommended in contests; don't rely on one-key compile
(defun compile-file ()(interactive)(compile (format "g++ -o %s %s -g -lm -Wall" (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key [f9] 'compile-file)
;;;;set the compile shortcut (if you set up one-key compile, don't let them conflict)
;;(global-set-key [f9] 'compile)

(global-set-key (kbd "C-a") 'mark-whole-buffer) ;;select-all shortcut
(global-set-key (kbd "C-z") 'undo) ;;undo shortcut
(global-set-key [f10] 'gud-gdb) ;;GDB debugging shortcut
(global-set-key (kbd "RET") 'newline-and-indent) ;;auto-indent on newline
(global-set-key (kbd "C-s") 'save-buffer) ;;set the save shortcut
(setq-default kill-ring-max 65535) ;;keep more undo history

;;C++ code style, mainly controls indentation rules
;;;"bsd" every brace goes on a new line
;;;"java" no brace goes on a new line. else follows the closing brace
;;;"awk" only braces for namespaces, class definitions and function definitions go on a new line. else follows the closing brace
;;;"linux" only braces for namespaces, class definitions and function definitions go on a new line. else follows the closing brace. Normally this style uses 8-space indentation
(setq-default c-default-style "awk")
```

??? note "Full configuration"
    ```text
    ;;one-key compile
    (defun compile-file ()(interactive)(compile (format "g++ -o %s %s -g -lm -Wall" (file-name-sans-extension (buffer-name))(buffer-name))))
    (global-set-key [f9] 'compile-file)
    ;;;;set the compile shortcut (if you set up one-key compile, don't let them conflict)
    ;;(global-set-key [f9] 'compile)
    
    ;;contest essentials
    (global-set-key (kbd "C-a") 'mark-whole-buffer) ;;select-all shortcut
    (global-set-key (kbd "C-z") 'undo) ;;undo shortcut
    (global-set-key [f10] 'gud-gdb) ;;GDB debugging shortcut
    (global-set-key (kbd "RET") 'newline-and-indent) ;;auto-indent on newline
    (global-set-key (kbd "C-s") 'save-buffer) ;;set the save shortcut
    (setq-default kill-ring-max 65535) ;;keep more undo history
    ;;(define-key key-translation-map [apps] (kbd "M-x")) ;; set the command shortcut on Windows
    
    ;;indentation
    ;;;C++ indentation width.
    (setq-default c-basic-offset 4)
    ;;;indent with tabs
    (setq-default indent-tabs-mode t)
    ;;;tab width. Must match the indentation width
    (setq-default default-tab-width 4)
    (setq-default tab-width 4)
    
    ;;default encoding
    (set-language-environment "UTF-8")
    (set-default-coding-systems 'utf-8)
    
    ;;don't show the welcome screen
    (setq-default inhibit-startup-screen t)
    
    ;;set the title
    (setq-default frame-title-format "")
    
    ;;show line numbers
    (global-display-line-numbers-mode t)
    
    ;;highlighting
    (global-hl-line-mode 1);;highlight the current line
    (show-paren-mode t);;highlight matching parentheses
    (global-font-lock-mode t);;syntax highlighting
    
    ;;allow pasting between emacs and other programs (seems to be allowed by default)
    (setq-default x-select-enable-clipboard t)
    
    ;;use Ubuntu Mono at size 16; reports an error if the font doesn't exist
    (set-face-attribute 'default nil :font "Ubuntu Mono-16")
    ;(set-face-attribute 'default nil :font "Consolas-16") ;; use this line on Windows
    
    ;;mouse wheel support
    (mouse-wheel-mode t)
    
    ;;make the cursor a vertical bar (default is a block)
    (setq-default cursor-type 'bar)
    
    ;;answer y/n instead of yes/no
    (fset 'yes-or-no-p 'y-or-n-p)
    
    ;;transparency
    (set-frame-parameter (selected-frame) 'alpha (list 85 60))
    (add-to-list 'default-frame-alist (cons 'alpha (list 85 60)))
    
    ;;scroll fewer lines at a time instead of a whole page
    (setq-default scroll-margin 3 scroll-conservatively 10000)
    
    ;;better file navigation
    (ido-mode t)
    
    ;;color scheme
    (setq default-frame-alist
             '((vertical-scroll-bars)
               (top . 25)
               (left . 45)
               (width . 120)
               (height . 40)
               (background-color . "grey15")
               (foreground-color . "grey")
               (cursor-color . "gold1")
               (mouse-color . "gold1")
               (tool-bar-lines . 0)
               (menu-bar-lines . 1)
               (scroll-bar-lines . 0)
               (right-fringe)
               (left-fringe)))
    
    (set-face-background 'highlight "gray5")
    (set-face-foreground 'region "cyan")
    (set-face-background 'region "blue")
    (set-face-foreground 'secondary-selection "skyblue")
    (set-face-background 'secondary-selection "darkblue")
    (set-cursor-color "wheat")
    (set-mouse-color "wheat")
    
    (custom-set-variables
     '(ansi-color-faces-vector
       [default default default italic underline success warning error])
    ;;enable Ctrl-x Ctrl-c Ctrl-v = cut copy paste
     '(cua-mode t nil (cua-base))
     '(show-paren-mode t)
    ;;hide the toolbar
     '(tool-bar-mode nil))
    ;;turn off cursor blinking
     '(blink-cursor-mode nil)
    (custom-set-faces)
    ```

### Further reading

To start Emacs in terminal mode, add the `-nw` flag when launching it. Emacs has several variants, such as [GCC Emacs](http://akrl.sdf.org/gccemacs.html), which uses native-comp to reduce latency, and its pure-GTK variant, as well as Emacs Macport, which is optimized for macOS.

Emacs has a centralized package repository. Once configured, you can install packages with `M-x package-install`. Using a [mirror](https://mirrors.bfsu.edu.cn/help/elpa/) can speed up downloads.

Emacs can use a language server (Language Server Protocol) to improve the editing experience. The currently recommended C++ backend is [Clangd](https://clangd.llvm.org/). For the frontend you can use [Eglot](https://github.com/joaotavora/eglot) or [Emacs LSP](https://emacs-lsp.github.io/lsp-mode/); [this entry](https://github.com/joaotavora/eglot#historical-differences-to-lsp-modeel) may help you choose a frontend.

Org Mode documents with the extension `.org` can be converted to Markdown with [Pandoc](https://pandoc.org/).

## References and notes

[^note1]: This key opens the right-click context menu. It is usually the first key to the left of the right <kbd>Ctrl</kbd>.
