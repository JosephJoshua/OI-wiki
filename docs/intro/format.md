Before we begin: everyone on the **OI Wiki** team warmly welcomes you to contribute pages to this project. **OI Wiki** is what it is today thanks to hundreds of people like you!

This page lists the recommended format conventions and editing policies for writing **OI Wiki**. Before you write or fix a Wiki page, please read the following carefully. It will help you produce higher-quality content.

If you can't wait to get started, we suggest reading the [TL;DR](#tldr) and [Illustrated examples](#illustrated-examples) sections first.

??? abstract "Changelog"
    **Note**: only changes related to writing, reviewing and so on are recorded here; changes such as formatting fixes are not.
    
    | Date | Main changes | Related Issue/Pull Request links |
    | ---------- | --------------------------------------------------- | ----------------------------------------------------------------------------------------------------------- |
    | 2026-02-22 | Refined the rules on using quotation marks | [#6793](https://github.com/OI-wiki/OI-wiki/pull/6793) |
    | 2026-01-07 | Require the full-width period instead of the Chinese full stop | [#6746](https://github.com/OI-wiki/OI-wiki/pull/6746) |
    | 2025-08-10 | Added format requirements for the format guide itself;<br>Code: added requirements for snippet code | [#6412](https://github.com/OI-wiki/OI-wiki/pull/6412) |
    | 2025-08-10 | Added Changelog and TL;DR | [#6409](https://github.com/OI-wiki/OI-wiki/pull/6409) |
    | 2024-10-08 | Code: refined format requirements for testing on all platforms | [#5912](https://github.com/OI-wiki/OI-wiki/pull/5912), [#5924](https://github.com/OI-wiki/OI-wiki/pull/5924) |
    | 2024-03-26 | When linking to an OJ problem, use the original link rather than a mirror | [#5482](https://github.com/OI-wiki/OI-wiki/pull/5482) |
    | 2023-10-09 | Theme plugins: added format requirements for content tabs[^note6] | [#5152](https://github.com/OI-wiki/OI-wiki/pull/5152) |
    | 2023-07-23 | For tool pages, require citing the official documentation for downloading, installation, etc. | [#5023](https://github.com/OI-wiki/OI-wiki/pull/5023) |
    | 2023-04-15 | Added rules for using quotation marks | [#4792](https://github.com/OI-wiki/OI-wiki/pull/4792) |
    | 2023-03-28 | LaTeX: table of mathematical symbols | [#4587](https://github.com/OI-wiki/OI-wiki/pull/4587) |
    | 2023-03-02 | Added rules for full-width/half-width punctuation and dashes | [#4726](https://github.com/OI-wiki/OI-wiki/pull/4726) |
    | 2022-12-13 | Theme plugins: removed the shadow-style requirement for nested collapsible blocks | [#4500](https://github.com/OI-wiki/OI-wiki/pull/4500) |
    | 2022-08-09 | When linking to a section of an internal page, use the Chinese heading | [#4057](https://github.com/OI-wiki/OI-wiki/pull/4057) |
    | 2022-06-12 | Refined the requirements for changes to the table of contents[^note4] | [#4043](https://github.com/OI-wiki/OI-wiki/pull/4043) |
    | 2021-09-09 | Theme plugins: added requirements for collapsible blocks | [#3517](https://github.com/OI-wiki/OI-wiki/pull/3517) |
    | 2021-09-03 | LaTeX: `\Leftrightarrow` $\to$ `\iff` | [#3499](https://github.com/OI-wiki/OI-wiki/pull/3499) |
    | 2021-08-18 | Code: added format requirements for example problem code | [#3447](https://github.com/OI-wiki/OI-wiki/pull/3447) |
    | 2021-08-12 | Images: prefer APNG for animations | [#3422](https://github.com/OI-wiki/OI-wiki/pull/3422) |
    | 2021-06-29 | Images: recommend also submitting source files | [#3255](https://github.com/OI-wiki/OI-wiki/pull/3255) |
    | 2021-05-29 | Code: removed the requirement to keep opening braces on the same line; added readability requirements | [#3197](https://github.com/OI-wiki/OI-wiki/pull/3197) |
    | 2021-03-15 | Site maintenance: standardized how Pull Requests are merged[^note5] | [#3061](https://github.com/OI-wiki/OI-wiki/pull/3061) |
    | 2021-02-01 | LaTeX: `\lt` $\to$ `<`, `\gt` $\to$ `>` | [#2950](https://github.com/OI-wiki/OI-wiki/pull/2950) |
    | 2021-01-27 | Recommend saving backups of external links in the [Internet Archive](https://web.archive.org/) | [#2918](https://github.com/OI-wiki/OI-wiki/pull/2918) |
    | 2020-09-19 | Site maintenance: requirements for writing commit messages and Pull Request titles[^note4] | [#2744](https://github.com/OI-wiki/OI-wiki/pull/2744) |
    | 2020-10-18 | Images: prefer SVG | [#2215](https://github.com/OI-wiki/OI-wiki/pull/2215) |
    | 2020-08-05 | LaTeX: added format requirements for multi-letter variables | [#2502](https://github.com/OI-wiki/OI-wiki/pull/2502) |
    | 2020-07-28 | LaTeX: the `cases` environment may not have more than two columns | [#2466](https://github.com/OI-wiki/OI-wiki/pull/2466) |
    | 2020-07-24 | LaTeX: `{n \choose m}`$\to$ `\dbinom{n}{m}` | [#2442](https://github.com/OI-wiki/OI-wiki/pull/2442) |
    | 2020-07-20 | Markdown: strikethrough syntax disabled | [#2422](https://github.com/OI-wiki/OI-wiki/pull/2422) |
    | 2020-07-19 | Theme plugins: require keeping the indentation spaces on blank lines inside collapsible blocks[^note3];<br>LaTeX: added format requirements for math formulas | [#2412](https://github.com/OI-wiki/OI-wiki/pull/2412) |
    | 2020-07-11 | First version | [#2350](https://github.com/OI-wiki/OI-wiki/pull/2350) |

## TL;DR

For readers new to this document, this section lists the key points of the guide:

-   File storage:

    -   Use lowercase file names, with `-` instead of spaces. See [SAVE-1](#SAVE-1).

    -   Don't embed images from external links. See [SAVE-2](#SAVE-2).

    -   Use SVG for images whenever possible, and only the SVG 1.1 standard. See [SAVE-3](#SAVE-3).

    -   Animations should use SVG or APNG. See [SAVE-4](#SAVE-4).

    -   For images that have source files, we recommend submitting the source files too. See [SAVE-5](#SAVE-5).

    -   When adding an external link, we recommend also adding a snapshot link. See [SAVE-6](#SAVE-6).

    -   Don't write internal links as external links. See [SAVE-7](#SAVE-7).

-   Punctuation:

    -   Use punctuation properly. End every sentence with a **full stop**. See [PUNC-1](#PUNC-1) to [PUNC-7](#PUNC-7).

    -   Distinguish between the different dashes (hyphen, en dash, em dash). See [PUNC-8](#PUNC-8).

-   Markdown syntax and theme extension syntax:

    -   Only use level-2, level-3 and level-4 headings. Don't use headings instead of bold. Don't put LaTeX formulas in headings. See [LINT-1](#LINT-1), [MDFM-1](#MDFM-1), [CONT-4](#CONT-4), [CONT-9](#CONT-9).

    -   When using collapsible block[^note3] syntax and content tab[^note6] syntax, keep the inner indentation consistent, **including on blank lines**. **Don't leave out** the indentation spaces on blank lines. See [LINT-6](#LINT-6), [MDFM-6](#MDFM-6).

    -   Don't use the strikethrough syntax `~~foo~~`. See [LINT-3](#LINT-3).

    -   A display formula should be written as

        ```text
        $$
        a^{2}=b^{2}+c^{2}
        $$
        ```

        and not as `$$a^{2}=b^{2}+c^{2}$$`. See [LINT-5](#LINT-5).

    -   Use collapsible blocks instead of blockquotes. See [MDFM-5](#MDFM-5).

    -   Code blocks should only use the ` ``` ` syntax and must specify a language. See [LINT-7](#LINT-7), [MDFM-3](#MDFM-3).

-   LaTeX formulas:
    -   Must not conflict with the [table of mathematical symbols](./symbol.md). See [MATH-1.1](#MATH-1.1).

    -   Pay attention to the fonts used. See [MATH-1.2](#MATH-1.2), [MATH-1.15](#MATH-1.15), [MATH-2.6](#MATH-2.6), [MATH-2.7](#MATH-2.7).

    -   Don't overuse LaTeX formulas. See [MATH-1.14](#MATH-1.14).

    -   Don't use programming-language notation in LaTeX formulas. (For example, don't write $a==b$, $a<<1$ or $a\%b$.) Don't chain square brackets ($a[i][j]$). See [MATH-1.9](#MATH-1.9), [MATH-1.10](#MATH-1.10).

-   Code:

    -   Keep it as short and easy to understand as possible, and avoid bad habits such as cramming many statements onto one line. Keep it readable and make the idea of the algorithm stand out. See [CONT-10](#CONT-10).

    -   We don't recommend putting code directly into the Markdown document. See [CODE-1.1](#CODE-1.1), [CODE-1.2](#CODE-1.2).

## Format requirements for this document

-   <span id="FREQ-1">FREQ-1</span>: When revising an entry of the format guide, also update the Changelog. If you are only fixing formatting, you don't need to update the Changelog.
-   <span id="FREQ-2">FREQ-2</span>: Except for the [TL;DR](#tldr) section, every entry of the format guide needs a unique number. The number must match the regular expression `(?<category>[A-Z]{4})-(?<id>[1-9][0-9]*(?:\.[1-9][0-9]*)*)`, where `category` should have an intuitive meaning. Explanatory text does not need a number.
-   <span id="FREQ-3">FREQ-3</span>: Entries in the [TL;DR](#tldr) must come from other sections of the format guide, and must cite the corresponding entry number at the end.
-   <span id="FREQ-4">FREQ-4</span>: Once an entry's number is set, it should not change. If a change is really necessary (for example, when deleting or merging entries), mark it with text such as "Deprecated" or "Moved to XXXX-id".

## Requirements for contributed documents

When you plan to contribute to some part of the content, you should get as familiar as you can with the following three things:

-   The format for storing documents
-   How reasonable the document is
-   The format requirements of remark-lint and of $\rm{\LaTeX}$ formulas

### Format for references and storage

-   <span id="SAVE-1">SAVE-1</span>: **File names must be all lowercase, separated by `-`.** For example: `file-name.md`.

-   <span id="SAVE-2">SAVE-2</span>: Make sure that all images from **external links** used in the document have been copied into the matching `images` folder **in this repository** (to avoid triggering hotlink protection on some sites). We recommend naming them as `MD document name + number` (see how images are handled in existing documents). For example, this document's file name is format, so the first image used in it is named `format1.png`.

-   <span id="SAVE-3">SAVE-3</span>: We recommend SVG images[^ref4] for better sharpness and scaling. Because the various components of **OI Wiki** support the SVG standard to different degrees, your images should follow the [SVG 1.1](http://www.w3.org/TR/SVG11/) standard.

-   <span id="SAVE-4">SAVE-4</span>: If an animation can't be made as SVG, or you don't know how, we recommend an APNG[^apng] file. Windows users can record with [ScreenToGif](https://www.screentogif.com), and Linux users can record with [Peek](https://github.com/phw/peek); remember to switch the setting to record APNG. Otherwise, we recommend making a video file such as MP4 first and then converting it to APNG. With ffmpeg, you can convert it with `ffmpeg -i filename.mp4 -f apng filename.apng -plays 0`.[^intro-apng]

-   <span id="SAVE-5">SAVE-5</span>: For images that have both a source file and an exported image (for example, a JPG file and a PSD file, or an SVG image and TikZ TeX source code), we recommend saving the source file in the same folder with the same file name as the image.

-   <span id="SAVE-6">SAVE-6</span>: Make sure the links cited in your document are stable. We **don't recommend** citing resources from **self-hosted** services (such as problems on a self-hosted OJ). When adding an external link, we recommend also saving it to the Internet Archive[^webarchive], in case an irreplaceable link stops working.

-   <span id="SAVE-7">SAVE-7</span>: For links within the site, drop the site's domain and link to the corresponding `.md` file with a relative path. For example, to link to the miscellaneous introduction (`misc`) from this page (`intro/format`), use `[Miscellaneous introduction](../misc/index.md)`. You can add a hash to the link to point to a section, for example [`[Pull Request message format](./htc.md#pull-request-message-format)`](./htc.md#pull-request-message-format). You can get the hash value from the button to the right of each heading or from the links in the table of contents on the right side of the page.

### How reasonable the document is

**Reasonable** means the **content** you write must have the following properties:

-   <span id="STRC-1">STRC-1</span>: Go from easy to hard; the difficulty of the content should increase gradually.
-   <span id="STRC-2">STRC-2</span>: Logical.

    -   <span id="STRC-2.1">STRC-2.1</span>: Content about an algorithm or a mathematical concept should, where possible, include the following:

        1.  Principle: explain the principle behind the content;
        2.  Examples: give 1 \~ 2 typical examples;
        3.  Problems: under this heading, **only give the problem names and links**. For algorithm problems, the preferred OJ for problem links is: the original OJ (OJs outside China must be smoothly accessible from mainland China) > UOJ > LOJ > Luogu.

        Example page: [IDA\*](../search/idastar.md)

    -   <span id="STRC-2.2">STRC-2.2</span>: Content about a tool should, where possible, include the following:

        1.  Introduction: explain the background and purpose of the tool.
        2.  Setup: describe in detail how to set up the environment and how to use it. For downloading and installation, we recommend citing the official documentation whenever possible.

        Example page: [WSL (Windows 10)](../tools/wsl.md)

Unless the existing content is of low quality, we suggest contributing by **adding to** it rather than overwriting it. If you are unsure, see the [ways to get in touch on the About page](./about.md#how-to-get-in-touch) section and contact the **OI Wiki** team.

### Basic format requirements for documents

#### Remark-lint format requirements

[remark-lint](https://github.com/remarkjs/remark-lint) can automatically give the files in the project a consistent style. The configuration **OI Wiki** currently uses is hosted at [.remarkrc](https://github.com/OI-wiki/OI-wiki/blob/master/.remarkrc).

While setting it up, the **OI Wiki** team ran into some problems that remark-lint does not handle well, so please follow these requirements strictly when editing documents:

-   <span id="LINT-1">LINT-1</span>: Don't use level-1 headings such as `<h1>` or `# Heading`.

-   <span id="LINT-2">LINT-2</span>: Put one half-width space after the heading marker, for example: `## Introduction`.

-   <span id="LINT-3">LINT-3</span>: Because remark-lint does not handle strikethrough well, please don't use strikethrough syntax. (Another reason not to use it: struck-through content is usually a "clever joke" that does little to help readers understand, which does not meet the [requirements on how content is expressed](#CONT-5) in "Format requirements for text content" below.)

-   <span id="LINT-4">LINT-4</span>: Lists:
    -   <span id="LINT-4.1">LINT-4.1</span>: Put a blank line before a list, starting a new paragraph.
    -   <span id="LINT-4.2">LINT-4.2</span>: In an ordered list (such as `1. Example`), put a space after the period.

-   <span id="LINT-5">LINT-5</span>: Put one blank line before and after a display formula; otherwise it is treated as an inline formula.

-   <span id="LINT-6">LINT-6</span>: When using the Details syntax that starts with `???` or `!!!`, every line of text inside the Details box must start with at least 4 spaces.

    **Even blank lines must keep the same indentation as the other lines. Please don't use your editor's feature that automatically trims trailing spaces.**

    ???+ success "Example"
        In the code below, `␣` stands for a space ` `.
        
        ```text
        ???+ warning
        ␣␣␣␣Remember to add 4 spaces before the text. The rest of the syntax is the same as Markdown.
        ␣␣␣␣
        ␣␣␣␣Without the 4 spaces, the text won't appear inside the Details box.
        ␣␣␣␣
        ␣␣␣␣What this `???` is will be explained [below](#MDFM-5).
        ```
        
        ???+ warning "Warning"
            Remember to add 4 spaces before the text. The rest of the syntax is the same as Markdown.
            
            Without the 4 spaces, the text won't appear inside the Details box.
            
            What this `???` is will be explained [below](#MDFM-5).

-   <span id="LINT-7">LINT-7</span>: For plain-text blocks styled as code, use ` ```text`. Using plain ` ``` ` without specifying the language of the plain-text block may cause the content to be indented incorrectly.

#### Use of punctuation

-   <span id="PUNC-1">PUNC-1</span>: End every sentence with a **full stop**.

<!-- scripts.linter.postprocess.fix_full_stop off -->

-   <span id="PUNC-2">PUNC-2</span>: Use **full-width** and **half-width** punctuation correctly. Use full-width punctuation for Chinese and half-width punctuation for English. When English is mixed into Chinese text, follow the [Editorial Standard for Using English in Chinese Publications](https://www.nppa.gov.cn/xxgk/fdzdgknr/hybz/202210/t20221004_445147.html). In particular, in Chinese text use the full-width period (U+FF0E) instead of the Chinese full stop (U+3002).

<!-- scripts.linter.postprocess.fix_full_stop on -->

<!-- scripts.linter.postprocess.fix_quotation off -->

-   <span id="PUNC-3">PUNC-3</span>: Because `“……”` and `‘……’` don't distinguish full-width from half-width, use corner brackets (U+300C and U+300D) as full-width double quotes, `"..."` as half-width double quotes, white corner brackets (U+300E and U+300F) as full-width single quotes, and `'...'` as half-width single quotes.

<!-- scripts.linter.postprocess.fix_quotation on -->

-   <span id="PUNC-4">PUNC-4</span>: Distinguish between the use of the **enumeration comma** (U+3001) and the **comma**.
-   <span id="PUNC-5">PUNC-5</span>: Pay attention to where **parentheses** go. Parentheses inside a sentence and parentheses outside a sentence are placed differently.
-   <span id="PUNC-6">PUNC-6</span>: Usually use a **semicolon** to show the relation between the clauses of the items in a list.
-   <span id="PUNC-7">PUNC-7</span>: For ordered lists, we recommend ending each item with a **semicolon** and the last item with a **full stop**; for unordered lists, we recommend ending each item with a **full stop**.
-   <span id="PUNC-8">PUNC-8</span>: Distinguish between the different dashes, such as the hyphen (usually typed as U+002D hyphen-minus (-), the "minus" key on the keyboard), U+2013 en dash (–) and U+2014 em dash (—). (In English, an en dash must be used to join several people's names, but it is very often wrongly written as a hyphen. Other misuses are fairly rare, so this is basically the only point to remember.) See [Dash - Wikipedia (Chinese)](https://zh.wikipedia.org/wiki/%E8%BF%9E%E6%8E%A5%E5%8F%B7).

    ???+ success "Example"
        -   Academic olympiads for secondary school students mainly include the Olympiad in Informatics, the Olympiad in Informatics, the Olympiad in Informatics, the Olympiad in Informatics and the Olympiad in Informatics (whoever wrote this example should be carried off).
        -   "Have you eaten yet?" Li Si asked Zhang San.
        -   I want to tell you: "I really like you so much."
        -   "If it serves my country, I will give my life for it; how could I seek fortune or flee misfortune for my own sake!"
        -   Zhang Hua got into university; Li Ping went to a technical school; I became a worker: we all have a bright future.[^note1]
        -   Here are the basic steps of this algorithm:
            1.  Initialize the distance to every vertex as infinity, mark all vertices as not visited, and initialize a queue;
            2.  Push the start vertex into the queue, mark it as visited, and set its distance to $0$;
            3.  Pop the front element of the queue and mark it as not visited;
            4.  Go through all edges connected to this element; if there is a shorter distance to the other end, relax it;
            5.  If that vertex has not been visited, push it into the queue and mark it as visited;
            6.  Go back to step 3 until the queue is empty.
        -   The KMP algorithm (Knuth–Morris–Pratt algorithm, KMP algorithm) was published jointly by Knuth, Pratt and Morris in 1977.[^note2]

#### Format requirements for Markdown and theme extensions

-   <span id="MDFM-1">MDFM-1</span>: For emphasis, use `**SOMETHING**` and corner-bracket quotes (U+300C and U+300D) rather than a heading, because using headings breaks the article's structure and/or causes problems in the table of contents.

-   <span id="MDFM-2">MDFM-2</span>: When citing a problem link, use the link to the original OJ's problem set whenever possible, rather than a mirror link.

-   <span id="MDFM-3">MDFM-3</span>: Use Markdown's block features correctly. Wrap inline code in a pair of backticks; wrap block code in a pair of ` ``` `. The backtick is the key under the tilde in the top-left corner of the keyboard. For block code, add the language name after the first ` ``` ` (for example, ` ```cpp`).

    ???+ success "Example"
        ````text
        ```cpp
        // #include<stdio.h>    //bad style
        #include <cstdio>  //good style
        ```
        ````
        
        ```cpp
        // #include<stdio.h>    //bad style
        #include <cstdio>  //good style
        ```

-   <span id="MDFM-4">MDFM-4</span>: Write "References and notes" using Markdown's footnote feature. The format is:

    ```markdown
    Text content.[^footnote-name]
    [^footnote-name]: Reference content. Note: the colon is an English (half-width) colon, followed by a space.
    ```

    A footnote name can be a number or text. Footnote markers are placed in the same way as parentheses. For a neat look, we recommend that footnote names within one page follow a consistent naming pattern, such as ref1, ref2, note1...

    Put all footnote content under the level-2 heading `## References and notes`.

    ???+ success "Example"
        ```markdown
        When `#include <cxxxx>` can replace `#include <xxxx.h>`, use the former.[^ref1]
        
        On January 21, 2020, CCF announced that NOIP would resume.[^ref2]
        
        ## References and notes
        
        [^ref1]: [cstdio stdio.h namespace](https://stackoverflow.com/questions/10460250/cstdio-stdio-h-namespace)
        
        [^ref2]: [Announcement by CCF on Resuming the NOIP Competition - China Computer Federation](https://www.ccf.org.cn/c/2020-01-21/694716.shtml)
        ```
        
        When `#include <cxxxx>` can replace `#include <xxxx.h>`, use the former.[^ref1]
        
        On January 21, 2020, CCF announced that NOIP would resume.[^ref2]

-   <span id="MDFM-5">MDFM-5</span>: We recommend using the theme extension's `???+note` format (i.e. [Collapsible Blocks](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#collapsible-blocks)) for problem statements and reference code. You can also use it to show other content that needs extra explanation.

    Example code (in the code below, `␣` stands for a space ` `):

    ```text
    ??? note "Title"
    ␣␣␣␣This box is collapsed by default.
    ␣␣␣␣
    ␣␣␣␣We recommend putting **solution code** in a collapsible box.

    ???+note "[HDOJ: A + B Problem](https://acm.hdu.edu.cn/showproblem.php?pid=1000)"
    ␣␣␣␣The title can also use a Markdown hyperlink. The hyperlink here is HDOJ's "A + B Problem".
    ␣␣␣␣
    ␣␣␣␣We also recommend **marking the original problem link** this way.
    ␣␣␣␣
    ␣␣␣␣Note where the double quotes go.
    ```

    Result:

    ??? note "Title"
        This box is collapsed by default.
        
        We recommend putting **solution code** in a collapsible box.

    ???+ note "[HDOJ: A + B Problem](https://acm.hdu.edu.cn/showproblem.php?pid=1000)"
        The title can also use a Markdown hyperlink. The hyperlink here is HDOJ's "A + B Problem".
        
        We also recommend **marking the original problem link** this way.
        
        Note where the double quotes go.

    The difference between the two formats is that the one with `+` is expanded by default, and the one without `+` is collapsed by default.

    The title of a collapsible block, i.e. the content after `note` in `???+note`, should be wrapped in `"`. Markdown syntax is supported inside it. See [Admonition - Changing the title](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#changing-the-title). (Blocks that can't be collapsed are ordinary admonitions; see [Admonitions - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/reference/admonitions).)

-   <span id="MDFM-6">MDFM-6</span>: When you need to add code in different languages, we recommend Content tabs, which let readers switch between the code in each language. Content tabs have other uses too; see [Content tabs](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/#usage). Usage and result are shown below.

    ???+ success "Example"
        Note that you need to add 4 spaces before the text (shown as `␣` below). The rest of the syntax is the same as Markdown.
        
        ````text
        === "C"
        ␣␣␣␣```c
        ␣␣␣␣#include <stdio.h>
        ␣␣␣␣
        ␣␣␣␣int main(void) {
        ␣␣␣␣  printf("Hello world!\n");
        ␣␣␣␣  return 0;
        ␣␣␣␣}
        ␣␣␣␣```
        
        === "C++"
        ␣␣␣␣```cpp
        ␣␣␣␣#include <iostream>
        ␣␣␣␣
        ␣␣␣␣int main(void) {
        ␣␣␣␣  std::cout << "Hello world!" << std::endl;
        ␣␣␣␣  return 0;
        ␣␣␣␣}
        ␣␣␣␣```
        ````
        
        === "C"
            ```c
            #include <stdio.h>
            
            int main(void) {
              printf("Hello world!\n");
              return 0;
            }
            ```
        
        === "C++"
            ```cpp
            #include <iostream>
            
            int main(void) {
              std::cout << "Hello world!" << std::endl;
              return 0;
            }
            ```

If you have other questions about mkdocs-material (the theme we use), you can also read the [MkDocs usage guide](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) (in Chinese), which explains how to use the plugins of the mkdocs-material theme.

#### Format requirements for text content

-   <span id="CONT-1">CONT-1</span>: Every occurrence of the text **OI Wiki** should be marked in bold.

-   <span id="CONT-2">CONT-2</span>: A page should start with a short paragraph (such as "This page introduces...") that summarizes the page.

    ???+ success "Example"
        This page lists the recommended format conventions and editing policies for writing **OI Wiki**.

-   <span id="CONT-3">CONT-3</span>: For pages that require "prerequisites", add a line **Prerequisites: ...** at the beginning, before the page summary. The format is:

    `Prerequisites: [Internal page 1](url1), [Internal page 2](url2) and [Internal page 3](url3)`

    ???+ success "Example"
        Prerequisites: [Time complexity](../basic/complexity.md)
        
        This page introduces the basics of the theory of computation.

-   <span id="CONT-4">CONT-4</span>: Pay attention to document structure. It should be well organized, with clear levels. Please never let something like a "level-5 heading" happen again; a normal article does not need such a complex structure.

-   <span id="CONT-5">CONT-5</span>: Pay attention to how content is expressed. As an encyclopedia site, **OI Wiki** should use written, objective language. Content such as "clever jokes" that does little to help readers understand should not appear in **OI Wiki**.

-   <span id="CONT-6">CONT-6</span>: Try to give each link a full title or a recognizable hint, and avoid bare URLs and vague descriptions such as "this" or "here". Every hyperlink should have a clear and specific description, so readers know where it leads.

    We recommend using the title of the source article or the tab.

    ???+ failure "Not recommended"
        ```markdown
        Please see [this page](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        
        Please see <https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork>
        ```
        
        Please see [this page](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        
        Please see <https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork>

    ???+ success "Recommended"
        ```markdown
        Please see GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        ```
        
        Please see GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)

-   <span id="CONT-7">CONT-7</span>: Because of Markdown's limitations, the level-2 heading `## References and notes` must be at the end of the page.

-   <span id="CONT-8">CONT-8</span>: We recommend writing all numbers used as ordinals in words. Examples:
    -   The first term of the sequence.
    -   The first line of the input file.

-   <span id="CONT-9">CONT-9</span>: Try to avoid MathJax formulas in headings of any level. Formulas in headings can cause the table of contents to display incorrectly.[^ref3]

-   <span id="CONT-10">CONT-10</span>: Pay attention to code readability.

    -   <span id="CONT-10.1.1">CONT-10.1.1</span>: Code should have clear logic and be as short and easy to understand as possible. Don't cram too much onto one line, and don't add too much unrelated code. Try to avoid anything unrelated to the idea of the algorithm.
    -   <span id="CONT-10.1.2">CONT-10.1.2</span>: We recommend adding suitable comments to reference code to help readers understand it.

    For C/C++-like languages:

    -   <span id="CONT-10.2.1">CONT-10.2.1</span>: Try to avoid preprocessor directives and macros that make the code harder to read.

    -   <span id="CONT-10.2.2">CONT-10.2.2</span>: Don't use `0` instead of `false`/`NULL`/`nullptr` and the like, and don't use `1` instead of `true` and the like.

    -   <span id="CONT-10.2.3">CONT-10.2.3</span>: When declaring a [type alias](https://en.cppreference.com/w/cpp/language/type_alias), we recommend `using` rather than `typedef`.

    -   <span id="CONT-10.2.4">CONT-10.2.4</span>: We don't recommend defining constants with macros; define them directly with keywords such as `constexpr`/`const`.

    -   <span id="CONT-10.2.5">CONT-10.2.5</span>: We don't recommend using the `inline` keyword on functions; see [Compiler optimizations](../lang/optimizations.md#inline).

    -   <span id="CONT-10.2.6">CONT-10.2.6</span>: Try to avoid complex template metaprogramming techniques such as type traits and partial specialization. If you really need them, add comments explaining what they mean.

        ???+ failure "Not recommended"
            ```cpp
            --8<-- "docs/intro/code/format/format_1.cpp:not-recommended"
            ```
            
            This code gives a complicated implementation of the [greatest common divisor](../math/number-theory/gcd.md), where:
            
            -   The first `gcd` takes two unsigned integers `x`, `y` and returns their greatest common divisor; the return type is guaranteed to be wide enough to hold both `x` and `y`.
            -   The second `gcd` takes two integers `x`, `y`, at least one of which is signed, and returns their greatest common divisor.
            -   The third `gcd` takes more than two integers and returns their greatest common divisor.
            -   The fourth `gcd` takes a container and returns the greatest common divisor of all numbers in it.
            
            For **OI Wiki**, we only care about the idea of the greatest common divisor algorithm. This code includes too many unrelated and complex technical details, and should be avoided.

        ???+ success "Recommended"
            ```cpp
            --8<-- "docs/intro/code/format/format_1.cpp:recommended"
            ```
            
            Topics such as "adding type checks", "handling negative input" and "letting the function take many arguments" are mostly engineering concerns; our focus should always be the idea of the algorithm.

#### Format requirements for LaTeX formulas

LaTeX is the first choice for typesetting formulas, and we should use it correctly. So we have strict requirements on how LaTeX is used. If you want to get started quickly, read the table at the end of this section.

-   <span id="MATH-1.1">MATH-1.1</span>: The symbols you use must not conflict with those defined in the [table of mathematical symbols](./symbol.md).

-   <span id="MATH-1.2">MATH-1.2</span>: Use Roman (upright) type for numbers, constants, operators and functions. Use Italic type for variables and subscripts. LaTeX already predefines some common constants, functions, operators and so on, which we can use directly, including but not limited to:

    ```latex
    \log, \ln, \lg, \sin, \cos, \tan, \sec, \csc, \cot, \gcd, \min, \max, \exp, \inf, \mod, \bmod, \pmod
    ```

    So when typing constants, function names, operators and so on, first check whether you should use Roman type or another font. For how to write LaTeX symbols, see the [Supported Functions page of KaTeX](https://katex.org/docs/supported.html) (not complete), or search for it.

    Because writing lowercase Greek letters in Roman type is awkward in LaTeX, lowercase Greek constants, operators and functions may use Italic type, such as $\pi$, and the $\delta$ in $\delta x$.

    If you need a **function name** in Roman type that isn't predefined, you can produce it with `$\operatorname{something}$`; for example, `$\operatorname{lcm}$` produces an upright least common multiple (function) symbol. Similarly, use `$\mathrm{}$` for Roman **constants**; use `$\mathbf{}$` for Roman bold symbols; use `$\boldsymbol{}$` for Italic bold symbols (such as the vector $\boldsymbol{a}$). For multi-letter variables, use `$\textit{}$`. All other non-math content, including English words, special symbols and so on, goes in `$\text{}$`. As for Chinese text, we recommend not putting it in LaTeX formulas at all.

-   <span id="MATH-1.3">MATH-1.3</span>: If an expression must be broken across lines (common in long display formulas), follow these line-breaking rules:

    -   <span id="MATH-1.3.1">MATH-1.3.1</span>: Put the line break before $=$, $+$, $-$, $\pm$, $\mp$; if necessary, it can also go before $\times$, $\cdot$, $/$. For example:

        $$
        \begin{aligned}
            \mathrm{e}^x &= \sum\limits_{n=0}^{\infty} \frac{x^n}{n!} \\
            &= \phantom{+} 1 + x + \frac{x^2}{2} \\
            & \phantom{=} + \frac{x^3}{6} + \frac{x^4}{24} + \dots \\
        \end{aligned}
        $$

    -   <span id="MATH-1.3.2">MATH-1.3.2</span>: The same operator should not appear both before and after a line break;

    -   <span id="MATH-1.3.3">MATH-1.3.3</span>: Try not to break lines inside an expression in parentheses.

-   <span id="MATH-1.4">MATH-1.4</span>: For inline fractions, use `$\dfrac{}{}$`. For example, `$\dfrac{1}{2}$` gives $\dfrac{1}{2}$, rather than `$\frac{1}{2}$`, which gives $\frac{1}{2}$.

-   <span id="MATH-1.5">MATH-1.5</span>: For binomial coefficients, use `\dbinom{n}{m}`, which gives $\dbinom{n}{m}$, rather than `{n \choose m}` (this form is no longer recommended in LaTeX). As with the previous rule about fractions, don't use `\binom{n}{m}`, which gives $\binom{n}{m}$.

-   <span id="MATH-1.6">MATH-1.6</span>: Avoid large operators (such as $\sum$, $\prod$, $\int$) inline whenever possible.

-   <span id="MATH-1.7">MATH-1.7</span>: When it causes no ambiguity, use `$\times$` instead of an asterisk. Use `$\times$` for the cross product and `$\cdot$` for the dot product. For example, write $a\times b$ or $a\cdot b$, not $a\ast b$.

-   <span id="MATH-1.8">MATH-1.8</span>: Use `$\cdots$` (centered between the baseline and the top line), `$\ldots$` (on the baseline) and `$\vdots$` (vertical ellipsis) instead of `$...$`. For example, write $a_1,a_2,\cdots a_n$, not $a_1,a_2,... a_n$.

-   <span id="MATH-1.9">MATH-1.9</span>: Don't use any programming-language notation outside code areas; use LaTeX formulas instead. For example, use `$=$` instead of `$==$` (write $a=b$, not $a==b$), use `` `a<<1` `` or `$a\times 2$` instead of `$a<<1$`, use `$a\bmod b$` instead of `$a\%b$` (write $a\bmod b$, not $a\%b$), and so on.

-   <span id="MATH-1.10">MATH-1.10</span>: In formulas, don't chain square brackets (the C++ notation for multidimensional arrays); use subscripts instead. That is, write $a_{i,j,k}$ rather than $a[i][j][k]$. When the subscripts in a formula get complicated, we suggest using a multivariable function ($f(i,j,k)$) or inline code format instead. For a simple function of one variable, `$f_i$`, `$f(i)$` and `$f[i]$` are all fine.

-   <span id="MATH-1.11">MATH-1.11</span>: For consistency and ease of writing, write big $O$ notation in complexity analysis directly as `$O()$`, not `$\mathcal O()$`.

-   <span id="MATH-1.12">MATH-1.12</span>: For equivalence, use `$\iff$`, which gives $\iff$, rather than `$\Leftrightarrow$`, which gives $\Leftrightarrow$.

-   <span id="MATH-1.13">MATH-1.13</span>: The piecewise function environment `cases` **may only have two columns** (that is, one `&` separator).

-   <span id="MATH-1.14">MATH-1.14</span>: Please don't overuse LaTeX formulas. Overuse not only makes pages load slowly (MathJax is notoriously slow), but also makes the page layout messy. We usually use the LaTeX formula font for variable names. Our advice is: unless necessary, avoid **heavily** mixing formulas with normal body text, and unless necessary, don't use formulas at all. For example:

    ```LaTeX
    We are going to learn the $SPFA$ min-cost flow in $Network-flow$, which uses the $Edmonds–Karp$ algorithm for augmentation.
    ```

    is a typical example of **abusing the formula font**. (To use italics on a page, write `*text*`.)

-   <span id="MATH-1.15">MATH-1.15</span>: Use the correct LaTeX symbols, especially for special symbols such as Greek letters in formulas. For example, use `$\varphi$` for Euler's totient function, `$\Phi$` for the diameter of a circle, and `$\phi$` for the golden ratio. These symbols all represent the Greek letter Phi, but they mean different things in different contexts. Remember: **never insert such symbols with your input method's special-symbol feature**.

    Also, for historical reasons in LaTeX, the empty set symbol should be `$\varnothing$`, not `$\emptyset$`; other symbols should follow the [table of mathematical symbols](./symbol.md).

We can summarize the above in a table. Note that the table does not show how to use every symbol; it only lists common mistakes. Handle similar cases by analogy.

| Non-compliant usage | Rendered | Compliant usage | Rendered |
| ---------------------------- | ----------------- | ---------------------------------------- | ----------------------------------- |
| `$log, ln, lg$` | $log, ln, lg$ | `$\log$, $\ln$, $\lg$` | $\log$, $\ln$, $\lg$ |
| `$sin, cos, tan$` | $sin, cos, tan$ | `$\sin$, $\cos$, $\tan$` | $\sin$, $\cos$, $\tan$ |
| `$gcd, lcm$` | $gcd, lcm$ | `$\gcd$, $\operatorname{lcm}$` | $\gcd$, $\operatorname{lcm}$ |
| `$e$, $\text{e}$, e` (base of the natural logarithm) | $e$, $\text{e}$, e | `$\mathrm{e}$` | $\mathrm{e}$ |
| `$i$, $\text{i}$, i` (imaginary unit) | $i$, $\text{i}$, i | `$\mathrm{i}$` | $\mathrm{i}$ |
| `$ primes less than a $` | $primes less than a$ | `primes less than $a$` | primes less than $a$ |
| `$...$` | $...$ | `$\cdots$, $\ldots$, $\vdots$, $\ddots$` | $\cdots$, $\ldots$, $\vdots$, $\ddots$ |
| `$a*b$` (product of two numbers) | $a*b$ | `$a\times b$, $a\cdot b$` | $a\times b$, $a\cdot b$ |
| `$SPFA$` (English name) | $SPFA$ | `SPFA` | SPFA |
| `$a==b$`                     | $a==b$            | `$a=b$`                                  | $a=b$                               |
| `$f[i][j][k]$` | $f[i][j][k]$ | `$f_{i,j,k}$, $f(i,j,k)$` | $f_{i,j,k}$, $f(i,j,k)$ |
| `$R,N^*$` (sets) | $R,N^*$ | `$\mathbf{R}$, $\mathbf{N}^*$` | $\mathbf{R}$, $\mathbf{N}^*$ |
| `$\emptyset$`                | $\emptyset$       | `$\varnothing$`                          | $\varnothing$                       |
| `$size$`                     | $size$            | `$\textit{size}$`                        | $\textit{size}$                     |

#### Additional format requirements for math formulas

Note that although the syntax for typing formulas above is very similar to the real LaTeX typesetting system, **MathJax and LaTeX are two completely unrelated things**. MathJax only uses a subset of syntax that looks very much like LaTeX. In fact, there are quite a few small differences between them, and these often make a formula work in one but not in the other.

Because **OI Wiki** has built a PDF export tool on the LaTeX typesetting engine, compatibility of formulas between MathJax and LaTeX matters. **Please keep the following points in mind when writing math formulas in the Wiki.**

These rules already make as many compromises toward MathJax as possible. The export tool supports some forms that originally only worked in MathJax.

-   <span id="MATH-2.1">MATH-2.1</span>: Use `\begin{aligned} ... \end{aligned}` for multi-line aligned formulas;

-   <span id="MATH-2.2">MATH-2.2</span>: If these multi-line aligned formulas need **numbering**, use the `align` or `equation` environment;

-   <span id="MATH-2.3">MATH-2.3</span>: Don't use the `split` or `eqnarray` environments;

-   <span id="MATH-2.4">MATH-2.4</span>: Don't use `\lt`, `\gt` for the less-than and greater-than signs; use `<`, `>` directly;

-   <span id="MATH-2.5">MATH-2.5</span>: Don't break lines with a bare `\\` (wrap formulas that need line breaks in `aligned` or another multi-line environment);

-   <span id="MATH-2.6">MATH-2.6</span>: To output the LaTeX logo $\rm{\LaTeX}$, use `$\rm{\LaTeX}$`, not `mathrm`; (in the TeX typesetting system, `\LaTeX` is a command that can't be used in math mode, while `\mathrm` can't be used outside math mode; also, although the `\text` command works normally in TeX, in MathJax the argument of `\text` is printed literally instead of being interpreted as commands);

-   <span id="MATH-2.7">MATH-2.7</span>: Chinese text in a math formula **must be placed inside the `\text{}` command**, while variables, numbers, operators and function names must be outside `\text{}`. **Don't nest math formulas inside the `\text{}` command**;

-   <span id="MATH-2.8">MATH-2.8</span>: When using the `array` environment, make sure **the number of alignment specifiers matches the actual number of columns**. For example, in the formula below the data actually has 3 columns (`&` is the column separator), so 3 alignment specifiers are needed (`l`/`r`/`c` mean left, right and center alignment).

    ```latex
    $$
    \begin{array}{lll}
    F_1=\{\frac{0}{1},&&\frac{1}{1}\}\\
    F_2=\{\frac{0}{1},&\frac{1}{2},&\frac{1}{1}\}\\
    \end{array}
    $$
    ```

#### Pseudocode format

There are no strict rules for the exact format of pseudocode; refer to Introduction to Algorithms or academic papers. Be careful not to write it as Python.

<span id="PCOD-1">PCOD-1</span>: In the Wiki, pseudocode is written in LaTeX, inside an array environment as a whole. Use `$\qquad$` for indentation, `$\text$` for text descriptions, `$\textbf$` for keywords, `$\textit$` for multi-letter variables, and `$\gets$` for assignment.

Reference example:

$$
\begin{array}{l}
\textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
\text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
\textbf{Output. } \text{The edges of the MST of the input graph}. \\
\textbf{Method. } \\
\begin{array}{ll} 
1 &  \textit{result} \gets \varnothing \\
2 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
3 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
4 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
5 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
6 &  \qquad\qquad \textit{result} \gets \textit{result}\;\bigcup\ \{(u, v, w)\} \\
7 &  \textbf{return } \textit{result}
\end{array}
\end{array}
$$

```latex
$$
\begin{array}{l}
\textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
\text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
\textbf{Output. } \text{The edges of the MST of the input graph}. \\
\textbf{Method. } \\
\begin{array}{ll} 
1 &  \textit{result} \gets \varnothing \\
2 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
3 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
4 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
5 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
6 &  \qquad\qquad \textit{result} \gets \textit{result}\;\bigcup\ \{(u, v, w)\} \\
7 &  \textbf{return } \textit{result}
\end{array}
\end{array}
$$
```

#### Format requirements for code blocks

There are currently two kinds of code blocks: snippets and example problem code.

About snippet code:

-   <span id="CODE-1.1">CODE-1.1</span>: If a code snippet is short enough and doesn't need testing, you can edit it directly in the Markdown document.
-   <span id="CODE-1.2">CODE-1.2</span>: Because code embedded in Markdown documents is hard to test automatically, we recommend inserting snippet code in the same format as example problem code. You can choose the [multi-file compilation approach](https://github.com/OI-wiki/OI-wiki/pull/5729) or the [Snippet Sections](https://facelessuser.github.io/pymdown-extensions/extensions/snippets/#snippet-sections) syntax:

    Example of the multi-file compilation approach: [Bubble sort](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/bubble-sort.md?plain=1#L48). The text includes [bubble-sort\_1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/code/bubble-sort/bubble-sort_1.cpp), and the test code is in [bubble-sort\_1.aux1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/code/bubble-sort/bubble-sort_1.aux1.cpp).

    Example of Snippet Sections: [Prefix sums](https://github.com/OI-wiki/OI-wiki/blob/c7cf6d6de13b44757f1d0528e952349beb921f8a/docs/basic/prefix-sum.md?plain=1#L37). The text doesn't need to include the testing part of [prefix-sum\_1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c7cf6d6de13b44757f1d0528e952349beb921f8a/docs/basic/code/prefix-sum/prefix-sum_1.cpp), so only the main code snippet is inserted.

    **Note**: Don't use the [Snippet Lines](https://facelessuser.github.io/pymdown-extensions/extensions/snippets/#snippet-lines) syntax.

    To reuse code more, you can also split code into header files and include them from different test files. If the text needs to show the complete test code as the reference implementation of an example problem, the text should use Snippet Sections syntax to stitch it together into single-file code, so it is easy for readers to read. Example: [Red-black tree](https://github.com/OI-wiki/OI-wiki/blob/3b721e22ea60d59a2687a9b10555263de7bdc2f0/docs/ds/rbtree.md?plain=1#L218-L231).

About example problem code:

-   <span id="CODE-2.1">CODE-2.1</span>: Example problem code is written as `--8<-- "path"`, and the code is stored at `path`. The path is usually `docs/topic/code/content/content_number.cpp`.

-   <span id="CODE-2.2">CODE-2.2</span>: When you change example problem code, make sure your code is correct. Each example problem code has a set of test data, stored in `/docs/topic/examples/content/content_number.in/ans`.

If you need to add an example problem:

-   Add your example code to `docs/topic/code/content` and give it a number. Usually, this `content` folder already has one or more code files. Example: if you need to change the code of `dag.md`, the path is `docs/dp/code/dag`, where `dp` is the topic and `dag` is the content.

-   If you need to add an example code after all existing example problems, continue the current numbering. For example, if `code/prefix-sum/prefix-sum_3.cpp` already exists and you need to add another example after the last one, name your code `prefix-sum_4.cpp` and add it to `docs/basic/code/prefix-sum`.

-   If you need to add an example code in the middle of the article, insert it and renumber the existing ones. For example, if `prefix-sum_2.cpp` and `prefix-sum_3.cpp` already exist and you need to add an example between the second and third examples, name your code `prefix-sum_3.cpp` and rename the old `prefix-sum_3.cpp` to `prefix-sum_4.cpp`, and **update the numbers in the Markdown document and in the test data folder at the same time**.

-   **Don't forget: you also need to add a set of test data for your code, to make sure it runs correctly.** Add the test data to the `docs/topic/examples/content` folder, storing the input as `content_number.in` and the expected answer as `content_number.ans`.

-   Finally, you can add the code to the document. Just add a code block in the document and write `--8<-- "your code path"` inside it.

**OI Wiki** tests example problem code on all platforms. To make sure your code passes the tests, follow these rules:

-   <span id="CODE-3.1">CODE-3.1</span>: Your code must compile and run under the C++14, C++17 and C++20 standards.
-   <span id="CODE-3.2">CODE-3.2</span>: Don't use non-standard headers such as `<bits/stdc++.h>` and `<bits/extc++.h>`.
-   <span id="CODE-3.3">CODE-3.3</span>: The expected answer file must not contain extra spaces.
-   <span id="CODE-3.4">CODE-3.4</span>: Don't use [alternative tokens](https://en.cppreference.com/w/cpp/language/operator_alternative#Alternative_tokens).
-   <span id="CODE-3.5">CODE-3.5</span>: When using [aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization), don't write `object{args}` as `(object){args}`.
-   <span id="CODE-3.6">CODE-3.6</span>: Pay attention to the form when using [operator overloading](https://en.cppreference.com/w/cpp/language/operators). For example, when overloading a comparison operator as a member function, you can't omit the `const` qualifier.
-   <span id="CODE-3.7">CODE-3.7</span>: Don't use macros like `#define int long long`.
-   <span id="CODE-3.8">CODE-3.8</span>: If you need C-style [formatted input/output](https://en.cppreference.com/w/cpp/io/c#Formatted_input.2Foutput), pay special attention to the format specifiers: for example, `size_t` uses `%zu` and `ptrdiff_t` uses `%td`. For instance, to print the size of an STL container, the code should look like `printf("%zu", container.size());`.
-   <span id="CODE-3.9">CODE-3.9</span>: Because the `<chrono>` library of libstdc++ in the current test environment has a [BUG](https://github.com/actions/runner-images/issues/8659), please avoid the `<chrono>` library.
-   <span id="CODE-3.10">CODE-3.10</span>: Because `long` and `unsigned long` are 32 bits in some test environments and 64 bits in others, we don't recommend these two types, to keep the code's behavior the same on all platforms. We recommend [fixed-width integer types](../lang/var.md#fixed-width-integer-types).
-   <span id="CODE-3.11">CODE-3.11</span>: We don't recommend non-standard features such as `__gcd`, `__int128` and the `__builtin_` family of functions. If you need them, make sure your code passes the tests on all platforms. For example, [this code](https://github.com/OI-wiki/OI-wiki/blob/4af83d6db6017f4c36db6d4a7583bbc3f6257484/docs/ds/code/tree-decompose/tree-decompose_1.cpp#L24-L47) provides an all-platform implementation of `_Find_first()`, a member function specific to libstdc++'s [std::bitset](../lang/csl/bitset.md).

Also, to make code more readable, we recommend following [CONT-10](#CONT-10).

## Illustrated examples

The requirements above may be a bit hard to grasp, so next we give some images to show concretely which formats should be used and which should not:

### Example 1

![](./images/format-1.png)

Putting complex LaTeX formulas in display format makes the page well laid out. But since **OI Wiki** is a site mainly in Chinese, we want most of the key structural information (such as headings) to be in Chinese where possible (except for English proper nouns).

### Example 2

![](./images/format-2.png)

For more complex LaTeX formulas, align the equals signs. You can also add suitable **links** to Wiki pages to enrich the content.

### Example 3

![](./images/format-3.png)

In general, we recommend listing cited sources in the `## References and notes` section at the end of the page and adding a footnote after the original sentence, rather than giving the link directly. Also, be sure to avoid using LaTeX formulas to express code; the two square brackets in the image above are non-standard. We recommend `dp(i,j)` or `dp_{i,j}`.

### Example 4

![](./images/format-4.png)

Note that for **multiplication** we usually use `\times` or `\cdot`; in special cases (such as convolution) we use `*` (which can also be written `\ast`). A heading is a short phrase, but we don't want the body text to be pieced together from phrases. In the image above, "two elements" should be changed to "The principle of dynamic programming has the following two elements", so that the text flows. A good point is that using an **ordered** list where appropriate makes the content better organized. A reminder again: when using a list, if each item is a sentence, end it with **punctuation**. Ordered list items usually end with a semicolon, with a full stop after the last item; unordered list items all end with a full stop.

### Example 5

![](./images/format-5.png)

Using **images** where appropriate makes an article easier to read. Expressing an algorithm in **pseudocode** describes the process conveniently and concisely, and is easier to understand than just pasting template code.

### Example 6

![](./images/format-6.png)

Same problem as before: the heading is in English. Also, there is no full stop after the parentheses. In addition, although the display formula in the image above uses no parentheses, it has too many nested subscripts, so the innermost subscript is very small and the whole formula doesn't look good. We suggest changing `son_{now,i}` to `son(now,i)`, or replacing `f_{now}` with `f(now)`. We want to keep nesting of superscripts and subscripts within two levels where possible (when you need to nest superscripts many times, we suggest Knuth's up-arrow notation, e.g. use $2 \uparrow (2 \uparrow (2 \uparrow (2 \uparrow \cdots)))$ instead of $2^{2^{2^{2^{\cdots}}}}$, as in the problem "Seven Minutes of God Creating Problems").

### Example 7

![](./images/format-7.png)

Use the MkDocs extension syntax to separate the problem statement from the description of the algorithm. Collapsing the code makes the article more compact. (After all, most people reading the Wiki want to understand the idea; apart from template code, which needs to be read, the code for exercises can mostly be collapsed.) When describing what a function does, both inline code and LaTeX formulas are good choices.

### Example 8

![](./images/format-8.png)

Listing references at the end of the page makes its content more rigorous and trustworthy.

## External links

-   [Use of Punctuation Marks (GB/T 15834-2011)](http://www.moe.gov.cn/jyb_sjzl/ziliao/A19/201001/W020190128580990138234.pdf) (in Chinese)
-   [Wikipedia: Manual of Style/Punctuation (Chinese Wikipedia)](https://zh.wikipedia.org/wiki/Wikipedia:%E6%A0%BC%E5%BC%8F%E6%89%8B%E5%86%8C/%E6%A0%87%E7%82%B9%E7%AC%A6%E5%8F%B7)
-   [Chinese Copywriting Guidelines (Simplified Chinese edition)](https://mazhuang.org/wiki/chinese-copywriting-guidelines/)
-   [Chinese Copywriting Style Guide - PDFE GUIDELINE](https://pdfe.github.io/GUIDELINE/#/others/copywriter) (in Chinese)
-   [A (Not So) Short Introduction to LATEX2ε, or LATEX2ε in 106 Minutes](https://github.com/CTeX-org/lshort-zh-cn/releases) (Chinese edition)
-   [Editorial Standard for Using English in Chinese Publications](https://www.nppa.gov.cn/xxgk/fdzdgknr/hybz/202210/t20221004_445147.html) (in Chinese)

## References and notes

[^note1]: (The colon) introduces a summary of what comes before it.

[^note2]: Between the full English name of a scientific or technical term and its abbreviation, use an English comma. When an English sentence or passage that annotates, adds to or explains something is embedded in a Chinese sentence, enclose it in Chinese (full-width) parentheses.

[^note3]: Collapsible block: see [Collapsible Blocks](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#collapsible-blocks). We sometimes also call this the "Details syntax", because it works the same way as the [`<details>` element](https://developer.mozilla.org/en-US/docs/Web/HTML/Reference/Elements/details) in HTML.

[^note4]: Moved to [How to contribute](./htc.md).

[^note5]: This rule was added to [Before you edit](../edit-landing.md) and announced, but was not added to this document.

[^note6]: Content tabs: see [Content tabs](https://squidfunk.github.io/mkdocs-material/reference/content-tabs).

[^ref1]: [cstdio stdio.h namespace](https://stackoverflow.com/questions/10460250/cstdio-stdio-h-namespace)

[^ref2]: [Announcement by CCF on Resuming the NOIP Competition - China Computer Federation](https://www.ccf.org.cn/c/2020-01-21/694716.shtml)

[^ref3]: [Why doesn't my formula show up properly in the table of contents? It seems to appear twice](faq.md)

[^ref4]: [SVG|MDN](https://developer.mozilla.org/zh-CN/docs/Web/SVG)

[^webarchive]: [Save Page in Internet Archive](https://web.archive.org/save/)

[^apng]: [APNG](https://en.wikipedia.org/wiki/APNG)

[^intro-apng]: [OI-wiki/OI-wiki#3422](https://github.com/OI-wiki/OI-wiki/issues/3422)
