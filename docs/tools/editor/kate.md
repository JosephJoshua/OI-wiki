author: CoelacanthusHex

## About

Kate, short for KDE Advanced Text Editor, is a feature-rich, cross-platform text editor. Kate also comes with many plugins, including an embedded terminal that lets you run console commands directly from Kate, a powerful search and replace plugin, and a preview plugin that can render MD, HTML and even SVG files. It supports recovering data after a system crash via swap files and autocompletion with argument hints, and it supports the [LSP (Language Server Protocol)](https://microsoft.github.io/language-server-protocol/) for more powerful completion.

## Download and installation

Open the [Kate website](https://kate-editor.org/) and go to the [Get It page](https://kate-editor.org/zh-cn/get-it/). Then install it according to your system and preferred installation method.

## Usage and features

### Swap files to prevent data loss

Like Vim, Kate writes unsaved changes to a swap file (usually the original file name with a dot in front and `.kate-swp` at the end). If something unexpected happens, like a power failure or a crash, your unsaved changes will not be lost the next time you start Kate.

### Syntax highlighting

Kate supports syntax highlighting for more than three hundred languages. Usually Kate picks the right language for highlighting automatically, but it is occasionally wrong. In that case, click the button in the bottom-right corner and choose the correct language.

#### Writing your own syntax highlighting files

Although Kate supports syntax highlighting for more than three hundred languages, some languages are inevitably not covered. In that case you can write a syntax highlighting file yourself.

Kate's own built-in files are listed at [Syntax Highlighting Powered By KSyntaxHighlighting Framework](https://kate-editor.org/syntax/). For the syntax, see [Working with Syntax Highlighting](https://docs.kde.org/trunk_kf6/en/kate/katepart/highlight.html). Place your finished file as described in [Syntax definition files](https://github.com/KDE/syntax-highlighting#syntax-definition-files). [CoelacanthusHex/dotfiles@80a913c/pam\_env.xml](https://github.com/CoelacanthusHex/dotfiles/blob/80a913cc5b90d7878eb0ed77b8df2d9b97926272/kate/.local/share/katepart5/syntax/pam_env.xml) is a file written by the author that you can use as a reference.

### Changing the interface language

Click `Settings` on the toolbar at the top, then click `Configure Language`, and choose a language. Note that you can also choose fallback languages.

### Encoding and line endings

Kate can automatically detect which encoding the current file uses. If it guesses wrong, click the second-to-last button in the bottom-right corner and choose the correct encoding.

Kate can also automatically detect the line endings the current file uses. If it guesses wrong, click `Tools`→`End of Line` and choose the correct line ending.

### Find and replace

Click `Edit`→`Find` (shortcut <kbd>Ctrl</kbd>+<kbd>F</kbd>) to open the "Find" bar. Click `Edit`→`Replace` (shortcut <kbd>Ctrl</kbd>+<kbd>R</kbd>) to open the "Find and Replace" bar. You can also open "Find and Replace" by clicking `Search and Replace` in the bottom-left corner.

It works much like in other editors, but it supports some extra features, such as:

1.  Case sensitivity on or off
2.  Regular expressions (including capture groups)
3.  Scopes ranging from the current file to multiple files to the current project
4.  Selectively replacing among the search results

### Language Server Protocol

Kate has supported an LSP client since 19.12. At first it only supported C/C++, D, Fortran, Go, LaTeX/BibTeX, OCaml, Python and Rust; now it supports dozens of languages. The table below lists LSP servers for some common languages:

|        Language        |                                                      LSP Server                                                      |
| :--------------------: | :------------------------------------------------------------------------------------------------------------------: |
|         C, C++         |                                           [clangd](https://clangd.llvm.org)                                          |
|         Python         |                               [pylsp](https://github.com/python-lsp/python-lsp-server)                               |
|          Java          |                               [jdtls](https://github.com/eclipse-jdtls/eclipse.jdt.ls)                               |
| JavaScript, TypeScript |        [typescript-language-server](https://github.com/typescript-language-server/typescript-language-server)        |
|          Rust          |                                   [rust-analyzer](https://rust-analyzer.github.io)                                   |
|           Go           |                                       [gopls](https://golang.org/x/tools/gopls)                                      |
|           Lua          |                         [lua-language-server](https://github.com/sumneko/lua-language-server)                        |
|          Bash          |                       [bash-language-server](https://github.com/bash-lsp/bash-language-server)                       |
|          JSON          | [vscode-json-languageserver](https://github.com/microsoft/vscode/tree/main/extensions/json-language-features/server) |
|          YAML          |                   [yaml-language-server](https://github.com/redhat-developer/yaml-language-server)                   |
|        Markdown        |                                 [marksman](https://github.com/artempyanykh/marksman)                                 |
|          HTML          | [vscode-html-languageserver](https://github.com/Microsoft/vscode/tree/main/extensions/html-language-features/server) |
|           CSS          |  [vscode-css-languageserver](https://github.com/Microsoft/vscode/tree/main/extensions/css-language-features/server)  |
|          LaTeX         |                                     [texlab](https://github.com/latex-lsp/texlab)                                    |

The full list is in [`addons/lspclient/settings.json` in the KDE Kate source code](https://invent.kde.org/utilities/kate/-/raw/master/addons/lspclient/settings.json).

To enable the LSP features, go to `Settings`→`Configure Kate` in the menu bar and enable `LSP Client` under `Plugins`. When you open a file in a supported language, Kate automatically starts the matching LSP server.

#### Adding configuration

You can also write the configuration by hand. The format is:

```json
{
    "servers": {
        "bibtex": {
            "use": "latex",
            "highlightingModeRegex": "^BibTeX$"
        },
        "c": {
            "command": ["clangd", "-log=error", "--background-index"],
            "commandDebug": ["clangd", "-log=verbose", "--background-index"],
            "url": "https://clang.llvm.org/extra/clangd/",
            "highlightingModeRegex": "^(C|ANSI C89|Objective-C)$"
        },
        "cpp": {
            "use": "c",
            "highlightingModeRegex": "^(C\\+\\+|ISO C\\+\\+|Objective-C\\+\\+)$"
        },
        "haskell": {
            "command": ["haskell-language-server-wrapper", "--lsp"],
            "rootIndicationFileNames": ["*.cabal", "stack.yaml", "cabal.project", "package.yaml"],
            "url": "https://github.com/haskell/haskell-language-server",
            "highlightingModeRegex": "^Haskell$"
        },
        "latex": {
            "command": ["texlab"],
            "url": "https://texlab.netlify.com/",
            "highlightingModeRegex": "^LaTeX$"
        },
        "rust": {
            "command": ["rls"],
            "rootIndicationFileNames": ["Cargo.lock", "Cargo.toml"],
            "url": "https://github.com/rust-lang/rls",
            "highlightingModeRegex": "^Rust$"
        }
    }
}
```

Each entry in `server` represents one language. Within a language, `command` is the command used to start the LSP server; `command` is an array holding the command to run, split on spaces. `url` is the LSP server's website. `rootIndicationFileNames` lists files used to find the project root. `highlightingModeRegex` matches the name of a syntax highlighting mode, to decide which LSP server to use. If there is a `use` entry, the configuration of the language named in `use` is used instead.

This setting is under `Settings`→`Configure Kate`→`LSP Client`→`User Server Settings`. The `LSP Client` section only appears after you enable the `LSP Client` plugin under `Plugins`.

### Built-in terminal

???+ note "Note"
    The built-in terminal depends on KDE's Konsole[^ref1], and Konsole is only available on \* nix. In other words, this feature is not available on Windows.

Press <kbd>F4</kbd> to show or hide the built-in terminal, or click the `Terminal` button in the bottom-left corner to open it. The current directory of the built-in terminal automatically follows the current file and changes as you switch files. Otherwise it is not much different from an ordinary terminal.

### External tools

Click `Tools`→`External Tools` to run them.

Click `Tools`→`External Tools`→`Configure` to configure external tools.

#### Adding external tools

##### Adding from the presets

On the configuration page, click `Add`→`Add Tool from Defaults` in the bottom-left corner, then click the tool you want.

##### Adding a hand-written configuration

On the configuration page, click `Add`→`Add Tool` in the bottom-left corner and fill in the fields as prompted. You can follow [this documentation (in English)](https://docs.kde.org/trunk_kf6/en/kate/kate/kate-application-plugin-external-tools.html) to write your own external tool configuration. Note that you can click the icon below to see the variables you can use.

![](images/kate-3-var.png)

#### Common external tools

##### Compiling and running a single C++ file

On \* nix systems, open any C++ source file, find `Compile & Run cpp` in the external tools, and click it.

???+ note "For Windows users"
    By default, this tool's executable is `sh`, so the tool doesn't work on Windows. However, you can modify the tool so it works on Windows.
    
    To do so, first make sure your system has a working C++ compiler. Then add `Compile & Run cpp` from the default tools, change its `Executable` from `sh` to `powershell`, and change the arguments to `-ExecutionPolicy Bypass -Command "g++ %{Document:FilePath} -o %{Document:FileBaseName}.exe;./%{Document:FileBaseName}.exe"` [^note1][^note2].

##### Git Blame

Open any file, find `git blame` in the external tools, and click it. A window opens showing the result of git blame.

##### Formatting

Formatting requires the corresponding package or program to be available. For example, formatting C/C++ requires `clang-format`. For other languages, you can check the default executable in the external tools configuration for reference.

Open any source file, find `Format with xxx` in the external tools, and click it. Also, for C/C++ source files, `clang-format` can format just the selected text.

### Git Blame

To enable this feature, go to `Settings`→`Configure Kate` in the menu bar and select `Git Blame` under `Plugins`.

Once enabled, Kate shows, in a lighter font after each line, when and by whom that line was last changed in Git. Hovering the mouse over this text shows a popup with the details of the commit.

## Related external links

-   [The Kate Handbook](https://docs.kde.org/stable_kf6/en/kate/kate/kate.pdf)
-   [How to write your own LSP client configuration (in English)](https://docs.kde.org/trunk_kf6/en/kate/kate/kate-application-plugin-lspclient.html#Configuration)
-   [How to write your own external tool configuration (in English)](https://docs.kde.org/trunk_kf6/en/kate/kate/kate-application-plugin-external-tools.html)

## References and footnotes

[^ref1]: In the [Arch Linux description of this package](https://archlinux.org/packages/extra/x86_64/kate/), `konsole` is an optional dependency, described as `open a terminal in Kate`.

[^note1]: If `g++` is not in the `PATH` environment variable, replace it with the absolute path of the compiler

[^note2]: Or, if you use Clang, replace `g++` with `clang++`.
