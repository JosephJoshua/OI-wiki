author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid, Cryflmind

## Arbiter

**Arbiter** is a judging tool developed by Beihang University (Beijing University of Aeronautics and Astronautics) for NOI Linux. It is now used to judge all the major NOI-series programming contests. According to Lü Kaifeng's talk "The Next-Generation Judging System" at the 2016 Winter Camp, Arbiter was developed by a Beihang University team (GAIT) led by Professor Yin Baolin.

After NOI Linux was updated to version 2.0, Arbiter was also recompiled with Qt 5.12.8 and released as Arbiter 2.0. Since all later judging environments use NOI Linux 2.0, everything below refers to Arbiter 2.0, the version bundled with NOI Linux 2.0.

This judging software is only available on NOI Linux. The binary is located at `/usr/local/arbiter/local/arbiter_local`.

### Usage

#### Setting up

Set up the folder of contestants' source code and the contestant list. Create the contestant folders in the NOIP format:

```text
players/
| -- day1
|    | -- <contestant_1's ID>
|    |     | -- <problem_1>
|    |     |   `-- <problem_1>.c/cpp/pas
|    |     | -- <problem_2>
|    |     |   `-- <problem_2>.c/cpp/pas
|    |     | ...
|    |     | -- <problem_x>
|    |        `-- <problem_x>.c/cpp/pas
|    | -- <contestant_2's ID>
|    |     | -- <problem_1>
|    |     ...
|    ...
| -- day2
|    | -- <contestant_1's ID>
|    |     | -- <problem_1>
|    |     |   `-- <problem_1>.c/cpp/pas
|    |     | -- <problem_2>
|    |     |   `-- <problem_2>.c/cpp/pas
|    |     | ...
|    |     | -- <problem_x>
|    |        `-- <problem_x>.c/cpp/pas
|    | -- <contestant_2's ID>
|    |     | -- <problem_1>
|    |     ...
|    ...
...
```

Here, the `<x>` in `day<x>` is the session number, `<contestant_x's ID>` is the contestant ID in the form `<province>-<number>`, such as HL-001 or JL-125, and `<problem_x>` is the problem name. For self-testing, you can use any combination of letters, hyphens (`-`) and digits as the contestant ID.

The contestant list has the following format:

```text
<contestant_1's ID>,<contestant_1's name>
<contestant_2's ID>,<contestant_2's name>
...
```

Here, `<contestant_x's name>` is the contestant's name. Save this file as plain text or CSV; `UTF-8` encoding works.

You can also add contestants manually after starting Arbiter.

Next, set up the test data. Each test case is named like this:

```text
<problem_x><y>.in <problem_x><y>.ans
```

Here, `<y>` is the test case number, starting from 1. By default, the expected output files have the extension `.ans`, and contestants' output files have the extension `.out`. Don't mix them up.

If you need to rename previously generated .out files to .ans, you can rename them in bulk with the `rename` command on NOI Linux 2.0, or with the `ren` command on Windows. How to use these commands is explained later.

You don't need to put each problem's test data in its own folder; just put all of it together.

Then set up the contest folder.

Start Arbiter from the bottom-left corner via "Show Applications" (显示应用程序) - "All" (全部) - "Arbiter\_local".

![Arbiter\_Home](./images/arbiter_home.png)

Click OPEN to open an existing contest; you then need to select the `setup.cfg` file in that contest's folder. Click NEW to create a new contest and set its name and contest directory. Note that you should create a new folder **in your home directory** and choose it as the contest directory; if you create the contest directory on the desktop, judging will not work. This is most likely because the contest folder path must not contain Chinese characters.

![add\_problem](./images/arbiter_addproblem.png)

In the problem overview on the left, right-click and choose "Add Exam" (添加考试), then right-click the exam label and choose "Add Problem" (添加试题) to create a problem.

Click the down arrow to the left of the exam to expand everything. Click a problem label to rename it to the problem's English name, and set the problem's time limit, memory limit and comparison method. Using "full-text exact comparison" (全文完全直接比较) as the comparison method is strongly discouraged, because it handles data made on Windows very badly. You can pick whichever comparator suits the problem, but you must pick one; otherwise the result will be `No Score.`.

![problem\_list](./images/arbiter_problem.png)

Click "File" (文件) - "Save" (保存). Don't skip this step, or the program will not generate the problem configuration files. Remember to save after every change to the problem configuration.

If you now open the exam folder, you will find the following:

```text
<name>/
| -- data
| -- evaldata
| -- filter
| -- final
| -- players
| -- result
| -- tmp
`-- day1.info
`-- player.info
`-- setup.cfg
`-- task1_1.info
`-- task1_2.info
`-- team.info
```

The `filter` folder holds some comparators; the `result` folder stores contestants' judging results; the `tmp` folder is a cache used during judging. `day<x>.info` is the session configuration file, where `<x>` is the session number; `task<x>_<y>.info` is a problem configuration file, where `<x>` is the session number and `<y>` is the problem number.

Put the contestant program folders you prepared under `players/`. Note that the outermost level should have a `day<x>` folder for each exam day. Put all the test data (not inside subfolders) into `evaldata`. If you use a custom checker, put it in `filter`.

#### Judging

Open the "Problem Judging" (试题评测) tab and you will see the following page:

![Pretest](./images/arbiter_pretest.png)

If you already have a contestant list, choose "Import List" (导入名单) on the right to import it. If there are only a few contestants, you can choose "Add Contestant" (添加选手) on the right instead.

The page after importing looks like this.

![Test](./images/arbiter_test.png)

The ID in the example is `HL-001`, and the program automatically fills in the "Affiliation" (所属) column. IDs that don't follow the NOIP convention cannot be recognized.

Change "judge session 0" to "judge session 1" (or another session). Then choose Select All on the right (or select specific contestants), choose "Judge Selected Contestants" below, select the problems to judge (or all problems), and wait for judging to finish.

Detailed per-test-case results are in the `result` folder, which contains a result folder for each contestant. The result files have the extension `.result` and can be viewed as plain text. If you get the error `No score file.`, check whether the file `/tmp/_eval.score` was generated during judging.

### Writing a custom checker

By decompiling other checkers, you can find that the command used to run a custom checker is `<problem>_e <in> <out> <ans>`. The last three arguments are the input file, the contestant's output and the answer file. The final score must be written to the file `/tmp/_eval.score`: the first line is the judging message and the second line is the score, with 10 being full marks.

After compiling, the custom checker must be named `<problem>_e`, where `<problem>` is the problem name. When configuring the problem, choose the custom checker option and then select the checker you need.

To judge output-only problems, go to the problem configuration in problem management, change the submission type from source code to answer file, and then select a custom checker.

### Things to watch out for

Confirmed issues:

-   Save the contest often, or Arbiter may crash while you work. To be safe, save the contest several times, or save after every change.
-   Don't click the score statistics button at the top before any judging has been done, or Arbiter will crash immediately.
-   Because of the Linux runtime stack limit, if you want an unlimited stack, first run `ulimit -s unlimited` in a terminal and then run `arbiter_local` to open the judge; otherwise you may get `Exceeding memory limit`.
-   For official judging, give all problems the same memory limit when preparing them. When judging, replace `unlimited` in the command with the problem's memory limit in kibibytes (KiB). For example, if the memory limit is 512 MiB, the command is `ulimit -s $((512 * 1024))`. The main cause of this issue is that when Arbiter is launched directly, its parent process is GNOME, and child processes inherit the parent's stack size limit.
-   The software's working directory should not contain spaces. If it does, all the default checkers will likely fail to be copied into the filter directory when a contest is created (that is, the filter directory will be empty). Every submission will then score 0, and the generated result files will show `Compile Failed.`.
-   When viewing code, the message "Answer file not found" (未找到答案文件) actually means the contestant's source code was not found.

Unconfirmed issues:

-   It freezes easily; for example, moving the mouse during a large judging run can freeze it.
-   It crashes at random times (partly because the contest was not saved in time).
-   After changing the comparison method, the change sometimes fails, that is, the new comparison method is not applied.
-   Watch out for permission problems during setup. However, if the same user creates the contest, copies the data and runs the judging, there will be no permission problems.

### Loopholes

Because it has gone unmaintained for a long time, the system has some loopholes. For example, `#pragma G++ optimize("O2")` and `__attribute__((__optimize__("-O2")))` can be used. You can use [gcc-plugins-for-oi](https://github.com/xdu-icpc/gcc-plugins-for-oi) to detect these directives at compile time.

### Assessment

Arbiter 1.0.2 received no substantial updates after it was finished, so the judging experience is very poor and the UI is far from modern design. In NOI Linux 1.4.1, it became, together with the GUIDE editor bundled with NOI Linux, a favorite target of complaints from contestants and coaches. In NOI Linux 2.0, apart from removing the comparators' source code and recompiling the whole program with Qt 5, not much has changed, and some stability problems remain unsolved.

??? note "Appendix: how to use the ren and rename commands"
    Windows comes with a built-in command for renaming files: `ren`.
    
    Its syntax is:
    
    ```shell
    ren [<drive>:][<path>]<filename1> <filename2>
    ```
    
    To rename all files in the current working directory, for example to change all .out files to .ans files, run:
    
    ```shell
    ren *.out *.ans
    ```
    
    To do this on NOI Linux 2.0, the most convenient option right now seems to be the `rename` command. It is not included in NOI Linux 2.0, so you need to install it first:
    
    ```shell
    sudo apt install rename
    ```
    
    Note: if you see `E: Unable to locate package package_name`, run this command first: `sudo apt-get update`
    
    Once installed, you can use `rename` normally. `rename` works like a plain text substitution. Its syntax on NOI Linux 2.0 is:
    
    ```shell
    rename 's/<text before>/<text after>/' <filename>
    ```
    
    Here `<filename>` can use the wildcard `*`, or name one kind of file (such as `*.out`).
    
    Note that there is one more `/` at the end inside the quotes. If you leave it out, `rename` will report the error `Substitution replacement not terminated at (user-supplied code)`.
    
    So, to rename all files in the current working directory, for example changing all .out files to .ans files, you can write:
    
    ```shell
    rename 's/\.out/\.ans/' *
    ```
    
    Here `\.` escapes the `.`.
    
    (Tip: if you leave out the `\.` and one of your files is named `outtest.out`, this command will rename it to `anstest.out`.)
    
    Similarly, to rename all files named `atmost<x>.ans` (where `<x>` is the test case number) to `test<x>.ans`, you can write:
    
    ```shell
    rename 's/atmost/test/' *.ans
    ```
