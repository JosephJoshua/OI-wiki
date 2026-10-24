author: ouuan, NachtgeistW

This page gives a short introduction to Polygon, a platform for collaborative problem setting.

## Introduction

### What is Polygon

Website: [Index Page - Polygon](https://polygon.codeforces.com)

Polygon is a problem-setting platform that supports collaboration among several people, and it is very full-featured. The official site describes it as "Polygon mission is to provide platform for creation of programming contest problems."

Problems for Codeforces (CF) must be prepared on Polygon. When setting problems elsewhere, especially as a team, Polygon is also a good choice.

### Advantages

-   It has version control, so collaboration doesn't turn into a mess and nobody has to send files back and forth.

-   The problem-preparation system is complete: validator, generator, checker and solutions all fit together, and outputs are generated automatically.

-   You can tag solutions. It warns you when a wrong solution gets AC or a correct one doesn't, which makes it easy to break wrong solutions one by one.

-   Stress testing is easy, and tests found by stress testing can be added directly to the problem's tests.

-   You can open issues when you find problems, instead of being flooded with messages while nothing gets fixed.

-   It prepares you for setting CF rounds in the future.

-   ...

## Problem list

The problem list shows basic information about each problem, such as the progress of the statement and editorial, the test generation status, and the settings of the main solution (std), validator and checker.

You can double-click the "Name" column of the problem list to write a note, such as things to remind yourself of (need to add more tests/need to write tutorial) or the planned score distribution for the problem. Fill it in however you like, or leave it empty.

In the "x/y" of "Rev.", x is the current version of the problem and y is the version of the package. If they differ, y is shown in red.

In "Edit session", "Start" means your account hasn't opened this problem yet, and "Continue (x) Discard" means your account is at version x of this problem. Click "Start" or "Continue (x)" to enter the problem management page. Clicking "Discard" **irreversibly** throws away all your changes and returns to the state as if you had never opened the problem.

If your account has uncommitted changes to a problem, the whole row in the problem list turns red.

## Problem management

Most of Polygon's features need no learning; if you can read English, you can basically use it.

???+ warning "Warning"
    Statements cannot use Markdown; only TeX is allowed.

-   Invocation is for testing solutions.

-   Stress is for stress testing.

-   Tests are made in Tests with a generator, and generators are uploaded in Files.

### General Info

On this page you can set the problem's time limit, memory limit, problem type, tags and the contest it belongs to.

At the bottom of the page, "statement sketch" and "tutorial sketch" let you edit **drafts** of the statement and editorial. Note that these two do not appear in the final statement or editorial.

### Statement

This page is for writing the statement and the editorial. You can also use the "Review" button to view the statement, validator and checker, usually for reviewing.

Both the statement and the editorial use TeX syntax, not Markdown. For example, you must use `\textbf{text}` instead of `**text**`. However, Polygon actually supports only a very small subset of TeX; try things out yourself to see what works.

Use the "In HTML" link at the top to see the rendered statement, and "Tutorial in HTML" to see the rendered editorial.

To add images to the statement, first upload them in "Statement Resource Files" below, then add `\includegraphics{filename.png}` to the statement.

### Files

"Source Files" holds all code **other than solutions**, such as the validator, checker and generator, plus the interactor for IO-style interactive problems.

If this code needs to include other files, such as [Tree-Generator](https://github.com/ouuan/Tree-Generator), those files go in "Resource Files".

For grader-style interactive problems, see the [official tutorial](https://codeforces.com/blog/entry/66916).

### Checker

testlib.h provides some built-in checkers. They are briefly described in the drop-down box, and you can select one and click "View source" to see its source code.

If you need to write your own checker, see the [checker tutorial](./testlib/checker.md).

In "Checker tests" below, use "Add test" to add some outputs together with the expected verdicts, then click "Run tests" to check whether the checker returns the right verdicts.

### Interactor

Needed only for IO-style interactive problems; see the [interactor tutorial](./testlib/interactor.md).

### Validator

The validator checks that the tests are valid. To write one, see the [validator tutorial](./testlib/validator.md).

"Validator tests" below works like "Checker tests": you provide inputs and whether each is expected to be valid, to test the validator.

### Tests

This page is for managing tests.

On Polygon, the recommended approach is to generate tests with a small number of [generators](./testlib/generator.md) **that take command-line parameters**, rather than writing many generators or editing the generator for every test. Also, you only need to generate the inputs; the outputs are generated automatically.

A "Testset" is a set of tests. If you are setting a problem for CF, you need to add a "pretests" testset by hand, and "pretests" must be a subset of "tests".

"Add Test" adds a test by hand, usually for typing in samples or small tests. You can upload tests from files, but this is **not recommended**: every test should either be typed in by hand or generated by a generator with some parameters.

If you check "Use in statements", the test becomes a sample and is added to the statement automatically. If you want the statement to show something other than the sample's input and output (usually for interactive problems), click "If you want to specify custom content of input or output data for statements click here" and enter the input and output you want to show in the statement.

The bottom of the Tests page is where you enter the script that generates tests, such as `generator-name [params] > test-index`. You can use `generator-name [params] > $` so you don't have to give test numbers by hand.

You can follow [Polygon's tutorial](https://polygon.codeforces.com/docs/freemarker-manual) to generate scripts in bulk with Freemarker.

"Preview Tests" lets you preview the generated tests.

### Stresses

This page is for stress testing.

Click "Add Stress" to add a stress test. "Script pattern" is a script that generates tests, where you can write things like "\[10..100]" to pick a random value in a range.

Then run the stress test. If it finds a failure, it shows "Crashed", and you can add that test to Tests with one click.

### Solution Files

This page holds code that solves the problem, both correct and wrong solutions. Uploading wrong solutions makes it easy to break them, and also reminds you that they need to be broken.

### Invocations

This page is for running solutions.

Pick the code and the tests, and run them. Afterwards you can click into an entry in the list ("View") to see the details.

The verdict "FL" means judging failed, usually because a test didn't pass validation or the validator/checker/interactor got RE. "RJ" happens in two cases: either an "FL" occurred, or the code failed the very first test.

If the running time is between half and twice the time limit, it is highlighted in yellow.

If some variable in the tests never reaches its minimum or maximum value, you get a reminder at the bottom.

### Issues

The place to open issues.

### Packages

A package contains all the information about a problem. When setting a CF round, CF judges based on the package (for example, if you fix a mistake during the contest, it only affects CF after you update the package). At other times, it can be used for exporting.

"Verify" checks that all solutions match their tags (AC, WA, TLE), that the checker passes the checker tests, and that the validator passes the validator tests.

### Manage access

Manages access rights to the problem.

### Sidebar

The first panel shows some basic information. If something breaks the rules (for example, tests don't contain pretests, or there are duplicate tests), it is shown in yellow; hover over it to see details.

"View changes" shows the history of changes. Note that "switch" cannot be used to roll back to a given version; it only allows non-conflicting changes on top of some version, which is actually pointless, so switch is effectively read-only.

"Update Working Copy" fetches updates (from others).

"Commit Changes" commits your updates.

When you commit, anything that breaks the rules or needs a warning is listed.

## Contest management

If you are setting a whole contest, you can create one with "New Contest", which makes managing the problems easier.

"Add problems?" in the top right of the problem list on the contest management page adds an existing problem to the contest.

"New problem" in the sidebar creates a new problem and adds it to the contest.

"Manage problem access" above shows the access rights of each problem, and "Manage developers list" below manages who has access to the contest. Access is granted automatically when you create a problem with "New problem" or add a new developer, but problems added with "Add problems?" do not grant access to existing developers.

The sidebar also lets you preview all statements, all editorials and all validators & checkers, download the package of the whole contest, and renumber the problems.

## Resolving conflicts

When several people prepare problems together on Polygon, a conflict ("Conflicted") happens if your version of a problem differs from the remote version and the changed files cannot be merged automatically when you fetch the latest version or commit your updates.

After a conflict, Polygon offers a "Resolve conflicts" option among the options of the conflicted problem, where you can resolve conflicts in the conflicting files.
