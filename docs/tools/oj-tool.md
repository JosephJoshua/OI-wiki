This page introduces some tools for online judges (OJs).

## cf-tool

cf-tool is a cross-platform (Windows, Linux, macOS) command-line tool for Codeforces that supports many common operations.

The source code is hosted at [xalanq/cf-tool](https://github.com/xalanq/cf-tool).

![cf-tool screenshot 1](./images/oj-tool-1.jpg)

![cf-tool screenshot 2](./images/oj-tool-2.jpg)

### Features

-   Supports all programming languages on Codeforces.
-   Supports Contests and Gym.
-   Submits code.
-   Live-refreshes the status after submitting.
-   Fetches the sample tests of problems.
-   Compiles locally and tests against the samples.
-   Fetches all of someone's submitted code.
-   Generates code from a given template (including timestamp, author and other info).
-   Lists summary information for all problems in a contest.
-   Opens the problem page, standings, submission page, etc. in your default web browser.
-   Colorful command-line output.

### Download

Go to [cf-tool/releases](https://github.com/xalanq/cf-tool/releases) to download the latest version.

Later updates can be installed directly with the `upgrade` command.

### Usage

Put the downloaded executable `cf` (or `cf.exe`) in a suitable place (see the second FAQ item), then open a terminal and run `cf config` to set your username, password and code template.

### Example usage

Below is a short walkthrough of a contest.

`cf race 1136`

Start contest 1136! You can get 1136 from the contest's link; in this example the contest link is <https://codeforces.com/contest/1136>.

If the contest hasn't started yet, the command shows a countdown. Once the contest has started or the countdown ends, the tool opens all the problem pages of the contest in your default browser and fetches the samples to your computer.

`cd 1136/a`

Enter the folder for problem A. It now contains the samples for this problem.

`cf gen`

Generate code from the default template; let's say it is `a.cpp`.

`vim a.cpp`

Write your code in Vim (or any other editor or IDE).

`cf test`

Compile and test against the samples.

`cf submit`

Submit the code.

`cf list`

Show information about each problem in the current contest.

`cf stand`

Open the standings in the browser to see the rankings.

### FAQ

1.  I double-clicked the program but nothing happened

    cf-tool is a command-line tool; you should run it in a terminal.

2.  I can't use the `cf` command

    You should put the `cf` program in a folder that is already in the system's PATH variable (for example `/usr/bin/` on Linux).

    If this is unclear, search for "how to add a folder to PATH".

3.  How do I add a new test case

    Create two extra test files `inK.txt` and `ansK.txt` (K is a string of digits 0\~9).

4.  How do I enable tab completion in the terminal

    Use the tool [Infinidat/infi.docopt\_completion](https://github.com/Infinidat/infi.docopt_completion).

    Note: if a new version is released (especially one that adds new commands), you should rerun `docopt-completion cf`.

## Codeforces Visualizer

Website: [Codeforces Visualizer](https://cfviz.netlify.app)

The source code is hosted at [sjsakib/cfviz](https://github.com/sjsakib/cfviz/).

This website has three features:

-   Visualizes various information about a user with nice charts (such as the difficulty distribution of solved problems).
-   Compares two users.
-   Computes rating predictions for a contest.

## Competitive Companion

This tool is a browser extension that parses test data from web pages. It supports almost all major OJ platforms (such as Codeforces and AtCoder). With this extension, you never have to copy test data by hand again.

The source code is hosted at [jmerle/competitive-companion](https://github.com/jmerle/competitive-companion).

How to use it:

-   Install the extension in Chrome or Firefox. The tool sends the parsed test data as JSON to a given port.
-   Install any local tool that can listen on that port and read the data; see the [official example](https://github.com/jmerle/competitive-companion-example).

Demo:

![Competitive Companion demo](images/oj-tool-3.apng)

The demo uses [bytetools](https://github.com/zqxyz73/bytetools) by [zqxyz73](https://github.com/zqxyz73).

## ac-predictor

ac-predictor is an extension that shows your rating change for an AtCoder contest before the ratings are updated.

This tool is a Tampermonkey script, so you first need to install [tampermonkey](https://www.tampermonkey.net/).

Then go to [greasyfork](https://greasyfork.org/zh-CN/scripts/369954-ac-predictor) and click install.

After installing, the contest standings page shows the predicted rating change for each user.

There is a Chinese-localized version of this tool by [GoodCoder666](https://github.com/GoodCoder666); click [here](https://greasyfork.org/zh-CN/scripts/458528-ac-predictor-cn) to install it.
