## Introduction

### What is LaTeX

LaTeX (pronounced /ˈlɑːtɛx/ or /ˈleɪtɛx/) is a typesetting system that makes your documents look more professional; it is not a word processor. It is especially good for long, well-structured documents, and it excels at typesetting mathematical formulas. It is free software and works on most operating systems.

LaTeX is based on TeX, a typesetting system that Donald Knuth designed in 1978 for digital typesetting. TeX is a low-level language that computers can process, but most people find it hard to use. LaTeX was designed to make it easier to use. The current version of LaTeX is LaTeX 2e.

If you are used to writing documents in Microsoft Office Word, LaTeX's way of working will feel unfamiliar. Word is a typical "what you see is what you get" (WYSIWYG) editor: you see the final layout while you edit the document. With LaTeX you cannot easily see the final result while editing, which lets you focus on content rather than appearance.

A LaTeX document is a text file ending in `.tex`. You can edit it with any text editor, such as Notepad, but for most people a proper LaTeX editor makes editing much easier. While editing, you mark up the structure of the document. When you are done, you compile it, which means converting it into a document of another format. Several formats are supported, but the most common one is PDF.

### Before you start

This article uses the following conventions:

-   Actions you should perform are marked with an arrow $\rightarrow$;
-   Text you type is shown in code blocks;
-   Names of menu commands and buttons are shown in **bold**.

### Some concepts

To write LaTeX documents, you need to install a "distribution". Common distributions are [TeX Live](http://tug.org/texlive/), [MikTeX](https://miktex.org/), and MacTeX for macOS users (which is really the macOS version of TeX Live). [CTeX](http://www.ctex.org/) is no longer recommended. TeX Live and MacTeX come with almost all LaTeX packages, while MikTeX ships with only a few essential packages and installs others when they are needed.

Both TeX Live and MikTeX include the TeXworks editor. You can also install the more feature-rich TeXstudio editor, or set up an editor such as Visual Studio Code or Notepad++ yourself. The editor used below is TeXworks running on Windows 7.

Most distributions come with several engines, such as pdfTeX and XeTeX. For Chinese users, XeTeX is recommended because it supports Unicode.

TeX comes in several formats, such as Plain TeX and LaTeX. Today LaTeX is the format generally used. So you need the engine bundled with the format you use: for pdfTeX that is pdfLaTeX, and for XeTeX it is XeLaTeX.

Further reading: [An introduction to TeX engines, formats and distributions (in Chinese)](https://liam.page/2018/11/26/introduction-to-TeX-engine-format-and-distribution/).

### Setting up the environment

Windows users need to download TeX Live or MikTeX. Users in mainland China can use the [Tsinghua University TUNA mirror](https://mirrors.tuna.tsinghua.edu.cn/): click the "Get download links" button on the right side of the page (the site is in Chinese), then choose "TeX typesetting system" under the "Applications" tab to download the TeX Live or MikTeX installer. The TeX Live installer is an ISO file; mount it and run `install-tl-advanced.bat` with administrator privileges.

For macOS users, the Tsinghua TUNA mirror also provides downloads of MacTeX and the macOS version of MikTeX.

For Linux users: if you use TeX Live, download the ISO file as well and run the `install-tl` script; if you use MikTeX, install it following the [official documentation](https://miktex.org/download#unx).

## Document structure

### The basics

$\rightarrow$ Open TeXworks.

A new document opens automatically.

$\rightarrow$ Go to the **Format** menu and choose **Line Numbers**.

Line numbers are not essential, but they help you compare your code with messages on the screen and find errors.

$\rightarrow$ Go to the **Format** menu, choose **Syntax Coloring**, then choose **LaTeX**.

Syntax coloring highlights the code and makes it easier to read.

$\rightarrow$ Type the following text:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  A sentence of text.
\end{document}
```

The `\documentclass` command must appear at the start of every LaTeX document. The text in curly braces specifies the document class. The **article** class suits shorter documents such as journal articles and short reports. Other classes include **report** (for longer documents with several chapters, such as PhD theses), **proc** (conference proceedings), **book** and **beamer**. The text in square brackets sets some options; in the example it sets the paper size to A4 and the main font size to 12pt.

The `\begin{document}` and `\end{document}` commands wrap the content of your document. Anything before `\begin{document}` is treated as the preamble and affects the whole document. Anything after `\end{document}` is ignored.

Blank lines are not required, but they make long documents easier to read.

$\rightarrow$ Click the **Save** button; $\rightarrow$ create a new folder called **LaTeX course** in **Libraries>Documents**; $\rightarrow$ name your document **Doc1** and save it as a **TeX document** in this folder.

It is a good idea to keep different LaTeX documents in different folders, since several files may be combined when compiling.

$\rightarrow$ Make sure the typeset menu is set to **xeLaTeX**. $\rightarrow$ Click the **Typeset** button.

Your source file is now converted into a PDF document, which takes some time. When compilation finishes, the TeXworks PDF viewer opens and shows the generated file. The PDF file is saved automatically in the same folder as the TeX document.

### Dealing with problems

If your document contains an error and TeXworks cannot create the PDF, the **Typeset** button turns into a red cross, and the console output at the bottom stays open. In that case:

$\rightarrow$ Click the **Abort typesetting** button. $\rightarrow$ Read the console output; the last line may give a line number showing where the error is. $\rightarrow$ Find that line in your document and fix the error. $\rightarrow$ Click the **Typeset** button again to try compiling the source file.

### Adding a title

The `\maketitle` command creates a title for the document. You need to specify the title. If you don't specify a date, the current date is used. The author is optional.

$\rightarrow$ Type the following text right after the `\begin{document}` command:

```tex
\title{My First Document}
\author{My Name}
\date{\today}
\maketitle
```

Your document now looks like this:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitle

  A sentence of text.
\end{document}
```

$\rightarrow$ Click the **Typeset** button and check the generated PDF.

Key notes:

-   `\today` is a command that inserts the current date. You can also type a different date, such as `\date{November 2013}`.
-   In an **article** document, the body text starts right after the title on the same page. A **report** puts the title on a page of its own.

### Sections

If needed, you may want to divide your document into chapters, sections and subsections. The following sectioning commands work in **article** documents:

-   `\section{...}`
-   `\subsection{...}`
-   `\subsubsection{...}`
-   `\paragraph{...}`
-   `\subparagraph{...}`

The text in curly braces is the section title. **report** and **book** documents also support the `\chapter{...}` command.

$\rightarrow$ Replace "A sentence of text." with the following text:

```tex
\section{Introduction}
This is the introduction.

\section{Methods}

\subsection{Stage 1}
The first part of the methods.

\subsection{Stage 2}
The second part of the methods.

\section{Results}
Here are my results.
```

Your document becomes

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitle

  \section{Introduction}
  This is the introduction.

  \section{Methods}

  \subsection{Stage 1}
  The first part of the methods.

  \subsection{Stage 2}
  The second part of the methods.

  \section{Results}
  Here are my results.
\end{document}
```

$\rightarrow$ Click the **Typeset** button and check the PDF. It should look like this:

![p1](images/latex-for-beginners-1.png)

### Creating labels

You can create a label for any sectioning command so that it can be referred to elsewhere in the document. Use `\label{labelname}` to label a section. Then type `\ref{labelname}` or `\pageref{labelname}` to refer to that section.

$\rightarrow$ On a new line below `\subsection{Stage 1}`, type `\label{sec1}`. $\rightarrow$ In the **Results** section, type `Referring to section \ref{sec1} on page \pageref{sec1}`.

Your document becomes:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitle

  \section{Introduction}
  This is the introduction.

  \section{Methods}

  \subsection{Stage 1}
  \label{sec1} The first part of the methods.

  \subsection{Stage 2}
  The second part of the methods.

  \section{Results}
  Here are my results. Referring to section \ref{sec1} on page \pageref{sec1}
\end{document}
```

$\rightarrow$ Compile and check the PDF (you may need to compile twice in a row):

![p2](images/latex-for-beginners-2.png)

### Table of contents (TOC)

If you use sectioning commands, you can easily generate a table of contents. Use `\tableofcontents` to create it in the document. Usually the table of contents goes right after the title.

You may also want to switch the page numbers to Roman numerals (i, ii, iii). This makes sure the main text starts on page 1. Use `\pagenumbering{...}` to switch page numbering between Arabic and Roman numerals.

$\rightarrow$ Type the following after `\maketitle`:

```tex
\pagenumbering{roman}
\tableofcontents
\newpage
\pagenumbering{arabic}
```

The `\newpage` command starts a new page, so we can see the effect of the `\pagenumbering` command. The first 14 lines of your document look like this:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}

\title{My First Document}
\author{My Name}
\date{\today}
\maketitle

\pagenumbering{roman}
\tableofcontents
\newpage
\pagenumbering{arabic}
```

$\rightarrow$ Compile and check the document (you may need to compile several times; we won't repeat this below).

The first page of the document looks like this:

![p3](images/latex-for-beginners-3.png)

The second page:

![p4](images/latex-for-beginners-4.png)

## Text formatting

### Chinese font support

For readers learning LaTeX from this article, the first thing to learn is naturally how to make LaTeX support Chinese fonts. There are actually many ways to do this. Here we give only the **simplest** solution: use the CTeX package. Just add the following to the preamble of your document:

```tex
\usepackage[UTF8]{ctex}
```

and you are done. Compile the document with the `xelatex` command, since it supports Chinese fonts.

### Font effects

LaTeX has many different font effects. Here are some of them:

```tex
\textit{words in italics} \textsl{words slanted} \textsc{words in smallcaps} \textbf{words
in bold} \texttt{words in teletype} \textsf{sans serif words} \textrm{roman
words} \underline{underlined words}
```

The result:

![p5](images/latex-for-beginners-5.png)

$\rightarrow$ Add more text to your document and try out the different font effects.

### Colored text

To use colored text in your document, you need a package. You can load many packages to extend what LaTeX can typeset. Package commands go in the preamble of the document (that is, before the `\begin{document}` command). Use `\usepackage[options]{package}` to load a package, where **package** is the package name and **options** are parameters that set features of the package.

After `\usepackage{color}`, we can use the common colors:

![p6](images/latex-for-beginners-6.png)

The code for colored text is

```tex
{\color{colorname}text}
```

where **colorname** is the name of the color you want and **text** is your colored text. Notice that yellow and white in the example have a background color behind the text. We can get this with the `\colorbox` command from the color package as well. Usage:

```tex
\colorbox{colorname}{text}
```

$\rightarrow$ Type `\usepackage{color}` before `\begin{document}`. $\rightarrow$ Type `{\color{red}fire}` in the document content. $\rightarrow$ Compile and check the PDF.

The word fire should be red.

You can also add some options to use more colors, or even define your own colors. But that is beyond the scope of this book. For more on colored text, read the [Colors chapter](http://en.wikibooks.org/wiki/LaTeX/Colors) of the LaTeX Wikibook.

### Font size

Next we list some LaTeX commands for setting the font size:

```tex
normal size words {\tiny tiny words} {\scriptsize scriptsize words}
{\footnotesize footnotesize words} {\small small words} {\large large words}
{\Large Large words} {\LARGE LARGE words} {\huge huge words}
```

The result:

![p7](images/latex-for-beginners-7.png)

$\rightarrow$ Try changing the font size of your text.

### Paragraph indentation

By default, LaTeX does not indent the first line of the first paragraph in each section, but indents the first line of later paragraphs. To stop a paragraph from being indented, put the `\noindent` command before it. If you want no paragraph indented anywhere, use the `\setlength{\parindent}{0pt}` command somewhere in the document, and all paragraphs after it will not be indented.

### Lists

LaTeX supports two kinds of lists: numbered lists (enumerate) and bulleted lists (itemize). List items are defined with `\item`. Lists can contain sublists.

$\rightarrow$ Type the following to create a numbered list containing a bulleted list:

```tex
\begin{enumerate}
  \item First thing

  \item Second thing
    \begin{itemize}
      \item A sub-thing

      \item Another sub-thing
    \end{itemize}

  \item Third thing
\end{enumerate}
```

$\rightarrow$ Compile and check the PDF.

The list looks like this:

![p8](images/latex-for-beginners-8.png)

You can change the bullet of a bulleted list with an argument in square brackets. For example, `\item[-]` uses a dash as the bullet, and you can even use a word, such as `\item[One]`.

The following code:

```tex
\begin{itemize}
  \item[-] First thing

  \item[+] Second thing
    \begin{itemize}
      \item[Fish] A sub-thing

      \item[Plants] Another sub-thing
    \end{itemize}

  \item[Q] Third thing
\end{itemize}
```

produces

![p9](images/latex-for-beginners-9.png)

### Comments and spacing

Use % to create a single-line comment. Everything after this character on that line is ignored, up to the start of the next line.

The following code:

```tex
It is a truth universally acknowledged% Note comic irony
in the very first sentence , that a single man in possession of a good fortune,
must be in want of a wife.
```

produces

![p10](images/latex-for-beginners-10.png)

In LaTeX, several consecutive spaces count as one space, and several consecutive blank lines count as one blank line. The main job of a blank line is to start a new paragraph. In general, LaTeX ignores blank lines and other whitespace; two backslashes (`\\`) can be used to break a line.

$\rightarrow$ Try adding comments and blank lines to your document.

If you want to add space to your document, you can use the `\vspace{...}` command. It adds vertical space of a given height. For example, `\vspace{12pt}` adds a space as tall as 12pt text.

### Special characters

The following characters are special in LaTeX:

```text
# $ % ^ & _ { } ~ \
```

To use these characters, escape them by putting a backslash in front:

```tex
\# \$ \% \^{} \& \_ \{ \} \~{}
```

Note that `^` and `~` must be followed by a pair of empty curly braces; otherwise they are interpreted as accents on a letter, for example `\^ e` becomes $\mathrm {\hat{e}}$. The code above produces:

![p11](images/latex-for-beginners-11.png)

Note that a backslash cannot be escaped with a backslash (that would give a line break); use the `\textbackslash` command instead.

$\rightarrow$ Write code that produces the following in your document:

![p12](images/latex-for-beginners-12.png)

Ask an expert or look at the [source code](https://github.com/OI-wiki/OI-wiki/blob/master/docs/tools/latex.md?plain=1) of this page for help.

## Tables

The tabular command is used to typeset tables. By default, LaTeX tables have no horizontal or vertical rules; if you want them, you have to add them yourself. LaTeX sets the width of the table automatically based on its content. The following code starts a table:

```tex
\begin{tabular}{...}
```

The dots are replaced by code that defines the table's columns:

-   `l` means a left-aligned column;
-   `r` means a right-aligned column;
-   `c` means a centered column;
-   `|` means a vertical rule between columns;

For example, `{lll}` creates a table with three left-aligned columns and no vertical rules; `{|l|l|r|}` creates a three-column table where the first two columns are left-aligned, the last is right-aligned, and there are vertical rules between adjacent columns.

The table data is entered after `\begin{tabular}`:

-   `&` separates columns;
-   `\\` starts a new row;
-   `\hline` inserts a horizontal rule across all columns;
-   `\cline{1-2}` inserts a horizontal rule across columns one and two.

Finally, end the table with `\end{tabular}`. Some examples:

```tex
\begin{tabular}{|l|l|}
  Apples       & Green  \\
  Strawberries & Red    \\
  Orange       & Orange \\
\end{tabular}

\begin{tabular}{rc}
  Apples              & Green  \\
  \hline
  Strawberries        & Red    \\
  \cline{1-1} Oranges & Orange \\
\end{tabular}

\begin{tabular}{|r|l|}
  \hline
  8              & here's \\
  \cline{2-2} 86 & stuff  \\
  \hline
  \hline
  2008           & now    \\
  \hline
\end{tabular}
```

The result:

![p13](images/latex-for-beginners-13.png)

### Practice

Try to reproduce the following tables:

![p14](images/latex-for-beginners-14.png)

## Figures

This chapter shows how to insert figures in a LaTeX document. We need the **graphicx** package. Images should be PDF, PNG, JPEG or GIF files. The following code inserts an image named myimage:

```tex
\begin{figure}[h]
  \centering
  \includegraphics[width=1\textwidth]{myimage}
  \caption{Here is my image}
  \label{image-myimage}
\end{figure}
```

`[h]` is the placement option; **h** means put the figure approximately here (if it fits). Other options: **t** puts it at the top of the page; **b** at the bottom of the page; **p** on a separate page. You can also add a **!** option to force the figure into the position given (though the layout may not look as good).

`\centering` puts the image in the center of the page. Without it, the image is left-aligned by default. Using it looks good, because figure captions are centered too.

The `\includegraphics{...}` command places the image into your document automatically. The image file should be in the same folder as the TeX file.

`[width=1\textwidth]` is an optional argument that sets the width of the image, here equal to the width of the text. The width can also be given in centimeters. You can also use `[scale=0.5]` to scale the image down (the example halves it).

`\caption{...}` sets the figure caption. If you use it, LaTeX numbers the figure with a label starting with "Figure". You can use `\listoffigures` to generate a list of figures.

`\label{...}` creates a label that you can refer to.

### Practice

$\rightarrow$ Add `\usepackage{graphicx}` to the preamble of your document. $\rightarrow$ Find an image and put it in your **LaTeX course** folder. $\rightarrow$ Type the following where you want the image to appear:

```tex
\begin{figure}[h!]
  \centering
  \includegraphics[width=1\textwidth]{ImageFilename}
  \caption{My test image}
\end{figure}
```

Replace **ImageFilename** with the name of your file (without the extension). If the file name contains spaces, wrap it in double quotes, such as `"screen 20"`.

$\rightarrow$ Compile and check the document.

## Equations

One of the main reasons to use LaTeX is that it makes typesetting equations easy. We use math mode to typeset equations.

### Inserting equations

A pair of `$` signs turns on math mode, which is used for inline math. For example, `$1+2=3$` produces $1+2=3$.

If you want a displayed equation, use `$$...$$` (nowadays `\[...\]` is recommended, because the former can produce bad spacing). For example, `$$1+2=3$$` produces

$$
1+2=3
$$

To produce a numbered equation, use `\begin{equation}...\end{equation}`. For example:

```tex
\begin{equation}
  1+2=3
\end{equation}
```

produces:

![equation](images/latex-equation.svg)

The number 6 is the section number. It appears only when your document has chapters, as in a **report** document.

Use `\begin{eqnarray}...\end{eqnarray}` to write a group of numbered equations. For example:

```tex
\begin{eqnarray}
  a & = & b + c \\
  & = & y - z
\end{eqnarray}
```

produces

![eqnarray](images/latex-eqnarray.svg)

To write unnumbered equations, add a `*` after the environment name, such as `{equation*}` or `{eqnarray*}`.

??? warning "Warning"
    You may notice that `eqnarray` has problems such as too much space around the equals sign.
    
    You can use the `align` environment from the `amsmath` package instead:
    
    ```tex
    \usepackage{amsmath}
    ...
    \begin{align}
      a & = b + c \\
        & = y - z
    \end{align}
    ```
    
    Or use the `aligned` environment inside a displayed equation. Adding an asterisk after their names gives unnumbered equations.
    
    See section "4.4 Multi-line formulas" in the first resource listed under [Further reading](#further-reading).

### Math symbols

Although some basic symbols can be typed directly, most special symbols need commands to display them.

This book is only an introduction to math symbols. The math chapters of the LaTeX Wikibook are a better and more complete tutorial; go there to learn more. If you are looking for a specific symbol, try [Detexfiy](http://detexify.kirelabs.org), which recognizes hand-drawn symbols.

#### Superscripts and subscripts

Superscripts (powers) use `^`. For example, `$n^2$` produces $n^2$.

Subscripts (indices) use `_`. For example, `$2_a$` produces $2_a$.

If a superscript or subscript has more than one character, wrap it in curly braces. For example, `$b_{a-2}$` produces $b_{a-2}$.

#### Fractions

Fractions are inserted with the `\frac{numerator}{denominator}` command. For example, `$$\frac{a}{3}$$` produces

$$
\frac{a}{3}
$$

Fractions can be nested. For example, `$$\frac{y}{\frac{3}{x}+b}$$` produces

$$
\frac{y}{\frac{3}{x}+b}
$$

#### Roots

We use the `\sqrt{...}` command to insert a root. Replace the dots with the expression under the root. To set the degree of the root, put it in square brackets.

For example, `$$\sqrt{y^2}$$` produces

$$
\sqrt{y^2}
$$

and `$$\sqrt[x]{y^2}$$` produces

$$
\sqrt[x]{y^2}
$$

#### Sums and integrals

Use `\sum` and `\int` to insert sums and integrals. For both symbols, the upper limit uses `^` and the lower limit uses `_`.

`$$\sum_{x=1}^5 y^z$$` produces

$$
\sum_{x=1}^5y^z
$$

and `$$\int_a^b f(x)$$` produces

$$
\int_a^b f(x)
$$

#### Greek letters

A Greek letter is written as a backslash followed by the letter's name. Whether the first letter of the name is uppercase or lowercase decides the form of the Greek letter. For example

-   `$\alpha$`=$\alpha$
-   `$\beta$`=$\beta$
-   `$\delta, \Delta$`=$\delta, \Delta$
-   `$\pi, \Pi$`=$\pi, \Pi$
-   `$\sigma, \Sigma$`=$\sigma, \Sigma$
-   `$\phi, \Phi, \varphi$`=$\phi, \Phi, \varphi$
-   `$\psi, \Psi$`=$\psi, \Psi$
-   `$\omega, \Omega$`=$\omega, \Omega$

### Practice

$\rightarrow$ Write code that produces the following equations:

![p15](images/latex-for-beginners-15.png)

If you need help, look at the [source code](https://github.com/OI-wiki/OI-wiki/blob/master/docs/tools/latex.md?plain=1) of this page.

## Bibliography

### Introduction

LaTeX makes it easy to insert references and a reference list. This article shows how to store references in a separate BibTeX file.

### BibTeX files

A BibTeX file contains all the references you want to cite in your document. Its file extension is `.bib`. It should have the same name as your TeX document. A `.bib` file is a text file. Enter your references in the following format:

```text
@article{
    Birdetal2001,
    Author = {Bird, R. B. and Smith, E. A. and Bird, D. W.},
    Title = {The hunting handicap: costly signaling in human foraging strategies},
    Journal = {Behavioral Ecology and Sociobiology},
    Volume = {50},
    Pages = {9-19},
    Year = {2001} 
}
```

Each reference starts by declaring its reference type. The example uses @article; other types include @book, @incollection for a chapter in a book, and @inproceedings for conference papers. You can see more supported types [here](http://en.wikibooks.org/wiki/LaTeX/Bibliography_Management).

Inside the curly braces, first comes a citation key. Every reference you cite must have a different citation key. You can choose any key, but the first author's name plus the year is a clear choice.

The following lines contain information about the reference, in this format:

```text
Field name = {field contents},
```

You can use LaTeX commands for special text effects. For example, italics can be written as `\emph{Rattus norvegicus}`.

Wrap letters that must stay uppercase in curly braces. BibTeX automatically turns every uppercase letter in a title except the first into lowercase. For example, `Dispersal in the contemporary United States` produces $\text{Dispersal in the contemporary united states}$, while `Dispersal in the contemporary {U}nited {S}tates` produces $\text{Dispersal in the contemporary United States}$.

You can write a BibTeX file by hand or generate it with software.

### Inserting the reference list

Use the following commands to insert the reference list at the current position in the document:

```tex
\bibliographystyle{plain}
\bibliography{references}
```

The references are stored in `references.bib`.

### Citations

Use `\cite{citationkey}` to insert a citation where you want to cite a reference. If you don't want a citation mark in the text but still want the reference to appear in the reference list, use the `\nocite{citationkey}` command.

To include page numbers in a citation, use square brackets: `\cite[p. 215]{citationkay}`.

To cite several references, separate them with commas: `\cite{citation01,citation02,citation03}`.

### Citation styles

#### Numbered citations

LaTeX includes several styles of inline numbered citations:

**Plain** puts numbers in square brackets, such as $[1]$. The reference list is sorted alphabetically by the first author. Each author's name is written in full.

**Abbrv** is the same as **plain**, but authors' names are abbreviated.

**Unsrt** is the same as **plain**, but the reference list is sorted in the order the references are cited in the text.

**Alpha** is like **plain**, but the citation mark combines the author's name and the year instead of a number, such as $[Kop10]$.

#### Author–date citations

If you want author–date citations, use the **natbib** package. It uses the `\citep{...}` command to produce a citation in brackets, such as $[Koppe,2010]$, and `\citet{...}` to produce a citation with only the year in brackets, such as $Koppe [2010]$. See more of its usage [here](http://mirror.ctan.org/macros/latex/contrib/natbib/natnotes.pdf).

The natbib package also has three styles: **plainnat**, **abbrvnat** and **unsrtnat**, which work the same as **plain**, **abbrv** and **unsrt**.

#### Other citation styles

If you need a different style, create a style file (a `.bst` file) in the same folder, and use it by passing its file name to the `\bibliographystyle{...}` command.

### Practice

$\rightarrow$ Create a BibTeX file with the same name in the same folder, and enter your reference information in the correct format. $\rightarrow$ Switch to the TeX document and use the `\cite`, `\bibliographystyle` and `\bibliograph` commands to cite references. $\rightarrow$ Compile the TeX file. $\rightarrow$ Switch to the BibTeX file and compile it (click the **Typeset** button). $\rightarrow$ Switch to the TeX file and compile it **twice**, then check the PDF.

## Further reading

-   The Not So Short Introduction to LATEX 2ε (Chinese edition) <https://github.com/CTeX-org/lshort-zh-cn/releases/download/v6.02/lshort-zh-cn.pdf>, or LaTeX 2ε in 112 minutes.

-   LaTeX Project <http://www.latex-project.org/> Official website - has links to documentation, information about installing LATEX on your own computer, and information about where to look for help.

-   LaTeX Wikibook <http://en.wikibooks.org/wiki/LaTeX/> Comprehensive and clearly written, although still a work in progress. A downloadable PDF is also available.

-   Comparison of TeX Editors on Wikipedia <http://en.wikipedia.org/wiki/Comparison_of_TeX_editors> Information to help you to choose which L A TEX editor to install on your own computer.

-   TeX Live <http://www.tug.org/texlive/>"An easy way to get up and running with the TeX document production system". Available for Unix and Windows (links to MacTeX for MacOSX users). Includes the TeXworks editor.

-   Workbook Source Files <http://edin.ac/17EQPM1> Download the .tex file and other files needed to compile this workbook.

**Translated from [http://www.docs.is.ed.ac.uk/skills/documents/3722/3722-2014.pdf](https://web.archive.org/web/20220309055041/http://www.docs.is.ed.ac.uk/skills/documents/3722/3722-2014.pdf)**, with minor changes based on other sources.
