???+ note "Note"
    This page focuses on the Git version control system. For GitHub-related topics, see [GitHub Docs](https://docs.github.com/cn) and [How to contribute - OI Wiki](../intro/htc.md).

Git is one of the most widely used version control systems today. **OI Wiki** also uses Git for version control.

## Installation

See [Git - Downloads](https://git-scm.com/downloads).

## Configuration

Git splits configuration files into levels according to their scope. The two most commonly used levels are[^note1]:

1.  The global configuration file for the current user. Git reads it whenever this user works with any repository on the system.
2.  The configuration file for the current repository.

When several configuration files set the same option, the more local setting automatically overrides the global one. So if you need a particular setting in one repository, just change that repository's setting; the global settings are not affected.

You change configuration files with the `git config` command.

### Setting your user information

The first thing to do after installing Git is to set your user name and email. Git uses them in every commit.

```console
$ git config --global user.name "OI Wiki"
$ git config --global user.email oi-wiki@example.com
```

???+ note "Note"
    The user name and email here are only for demonstration. When you follow this page, remember to replace them with your own information.

Here `--global` means you're changing the global configuration, so the setting applies to all repositories of the current user. Without the `--global` option, Git changes the current repository's configuration file by default.

To change a setting for one particular repository, just run the command without `--global` inside that repository.

### Configuring the editor

```console
$ git config --global core.editor emacs
```

Running the command above changes the editor to [Emacs](./editor/emacs.md).

On Windows, you can choose Git's default editor when installing Git (see above). To change it later, run the command above in Git Bash with the editor name replaced by the editor's absolute path.

### Viewing the configuration

`git config -l` lists all configuration options that are currently set. `git config --global -l` lists all global options.

## Repository basics

### Creating a Git repository

Creating a Git repository is very easy. Just run this command in the folder where you want the repository:

```console
$ git init
```

Git creates a `.git` folder in the current folder, and the repository is ready.

To clone a repository to your computer (for example, to copy **OI Wiki**'s code locally to edit it), use the `git clone` command.

```console
$ git clone https://github.com/OI-wiki/OI-wiki
```

???+ note "Remote repository URLs"
    The repository URL here is an HTTP(S) URL, meaning we connect to the remote repository over HTTP(S).
    
    In fact, there are several ways to connect to a remote repository. Connecting over ssh is more convenient and secure; we briefly explain how to do it in the section on managing remote repositories.

The contents of the cloned repository are then stored in a new folder, with the same name as the repository, inside the current folder. In this example, a new folder named `OI-wiki` appears in the current folder.

### Tracking files

After you make changes to files in a repository, those changes need to be brought under version control.

The `git status` command shows the state of the files in the current repository.

For example, after adding a `README.md` file to an empty repository, `git status` shows this:

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        README.md

nothing added to commit but untracked files present (use "git add" to track)
```

<!-- scripts.linter.preprocess.fix_details on -->

Untracked files are files that Git hasn't been tracking. If a file isn't tracked, Git doesn't record changes to it.

Running `git add <file>` starts tracking the given file.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git add README.md # start tracking this file
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md
```

<!-- scripts.linter.preprocess.fix_details on -->

Now `README.md` is tracked and has been put in the staging area. Next, you just need to run `git commit` to commit this change.

But before doing that, let's make a small change to `README.md`.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ vim README.md # change something
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore -- <file>..." to discard changes in working directory)

        modified:   README.md
```

<!-- scripts.linter.preprocess.fix_details on -->

You'll notice that `README.md` is both staged and unstaged. In fact, being staged applies to changes, not to files: the earlier change to `README.md` is staged, while the later one isn't yet. If you run `git commit` now, only the staged changes are committed; the unstaged changes are not.

As Git suggests, running `git add README.md` moves the unstaged changes into the staging area.

???+ note "Staging all changes at once"
    The `git add` command stages the changes to the given files.
    
    Most of the time, you'll want to stage all changes at once. For that, use `git add -A`. It stages all changes (including untracked files, but not ignored files).
    
    If you only want to update tracked files without adding untracked files to the staging area, use `git add -u`.

???+ note "Ignoring files"
    Sometimes we don't want to track certain files (such as executables). In that case, create a `.gitignore` file in the repository's root directory and list the files you want to ignore. Git will then not track them.
    
    For example, `*.exe` automatically ignores all files with the `.exe` extension in the repository.

Now stage the unstaged changes and commit all the changes together.

```console
$ git add README.md
$ git commit # an editor will open; write your commit message there
[master (root-commit) f992763] initial commit
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
```

Let's look closely at the output of this commit.

`master` means we're on the `master` branch (branches are covered in detail below), `f992763` is the first few characters of this commit's SHA-1 checksum, and what follows is the commit message.

Pay special attention to the SHA-1 checksum: each checksum corresponds to a snapshot of the repository at some moment. Using it, we can go back to a snapshot of the repository at some point in history and make changes on top of it.

The next two lines describe the file changes in this commit.

You can also use a few options to make committing simpler:

-   `-a`: stage the changes to all tracked files before committing. Note that untracked files (newly created files) are not staged automatically; you have to add them by hand with `git add`.
-   `-m`: followed by a commit message, commits the changes with that message. For example, `git commit -m "fix: typo"` creates a commit titled `fix: typo`.

### Viewing the commit history

The `git log` command shows the repository's commit history.

As you can see, the history records each commit's SHA-1 checksum, author, time and commit message.

```console
$ git log
commit ae9dd3768a405b348bc6170c7acb8b6cb5fe333e (HEAD -> master)
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:30:18 2020 +0800

    feat: update README.md

commit f99276362a3c260d439364c505a7a06859f34bf9
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:06:07 2020 +0800

    initial commit
```

## Branches

Why does version control need branches? There are two main reasons:

1.  Changing the main branch directly not only messes up the history but can also have dangerous consequences.
2.  Branches let us focus on the current task. If we have two different tasks, we just create two branches, and the work on them doesn't interfere.

Simply put, in Git a branch is a pointer to a snapshot. On every commit, Git creates a snapshot for that commit and moves the current branch's pointer to it.

There is also a HEAD pointer, which points to the branch you're currently on.

Switching branches simply means changing HEAD from pointing to the current branch to pointing to another branch. During this, Git updates the files automatically, so after the switch the repository matches the snapshot the target branch points to.

### Creating branches

`git branch` creates a branch, `git switch` switches branches, and `git switch -c` creates a branch and switches to it.

```console
$ git switch -c dev # create a new branch called dev and switch to it
Switched to branch 'dev'
$ git branch # list the branches
  master
* dev
```

The asterisk before `dev` means the repository's current branch is `dev`; from now on, changes to the repository are recorded on this branch.

Try creating a new file `aplusb.cpp`.

```console
$ vim aplusb.cpp
$ git add aplusb.cpp
$ git commit -m "feat: add A+B Problem code"
[dev 5da093b] feat: add A+B Problem code
 1 file changed, 7 insertions(+)
 create mode 100644 aplusb.cpp
```

Now switch back to the `master` branch. `aplusb.cpp` is gone from the folder, and everything is back to how it was when the `dev` branch was created. You can now continue other work on the `master` branch.

```console
$ git switch master
Switched to branch 'master'
$ vim README.md # make a small change to README
$ git commit -a -m "feat: update README.md"
[master 5ca15f0] feat: update README.md
 1 file changed, 1 insertion(+), 1 deletion(-)
```

The picture below explains what we just did.

![](./images/git1.svg)

The `master` branch is shown in red, meaning that after these operations it is the current branch (where HEAD points).

-   At first, `master` points to the snapshot `ae9dd37`.
-   Next, a new dev branch is created where `master` is; at first it points to the same place as master.
-   Some changes are made on the `dev` branch (creating `aplusb.cpp`) and committed. After this commit, `dev` points to the snapshot `5da093b`.
-   After switching back to `master`, since `master` still points to `ae9dd37`, where `aplusb.cpp` hadn't been created yet, the file is not in the repository.
-   Next, changes are made on the `master` branch (updating `README.md`) and committed, and `master` now points to the snapshot `5ca15f0`.

### Merging branches

Once the work on a branch is finished, you can merge it into another branch.

Continuing the example above, the work on `dev` is done. The `git merge` command merges that branch into the current branch (`master`):

```console
$ git merge dev
Merge made by the 'recursive' strategy.
 aplusb.cpp | 7 +++++++
 1 file changed, 7 insertions(+)
 create mode 100644 aplusb.cpp
```

![](./images/git2.svg)

How exactly does this merge work?

Before the merge, `master` points to `5ca15f0` and `dev` points to `5da093b`; these two states are not on the same chain.

Git finds the lowest common ancestor of the two states (`ae9dd37` in the picture above) and does a merge of these three snapshots. The result of merging the three snapshots becomes a new snapshot, and the current branch is moved to point to it.

The merge itself is also a commit, but unlike a normal commit, a merge commit has more than one parent: it is the result of merging several commit states.

After the merge, the `dev` branch has done its job, and you can delete it with this command:

```console
$ git branch -d dev # for an unmerged branch, use -D to force deletion
```

But merging doesn't always go this smoothly. Sometimes a merge produces conflicts, which we cover next.

### Resolving merge conflicts

If two branches make different changes to the same part of the same file, Git can't merge them automatically. This is a merge conflict.

Continuing the example above, suppose you create a new `readme-refactor` branch from the merged `master` to rewrite the README. But by mistake, you change the README on both `readme-refactor` and `master`.

At first the README looks like this:

```markdown
# This is a test repo.

This repo includes some c++ codes.
```

On the `readme-refactor` branch, the README looks like this:

```markdown
# Code Library

This repo includes some c++ codes.
```

On the `master` branch, the README looks like this:

```markdown
# This is a code library.

This repo includes some c++ codes.
```

Now run `git merge readme-refactor`, and Git reports a merge conflict.

Run `git status` to see which files caused the conflict.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git status
On branch master
You have unmerged paths.
  (fix conflicts and run "git commit")

Unmerged paths:
  (use "git add <file>..." to mark resolution)

    both modified:      README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

<!-- scripts.linter.preprocess.fix_details on -->

How do you resolve a conflict? In every file with a merge conflict, Git adds standard conflict markers. For example, the `README.md` file in this example looks like this when you open it:

```markdown
<<<<<< HEAD
# This is a code library.
======
# Code Library
>>>>>> readme-refactor

This repo includes some c++ codes.
```

`======` is the divider between the two branches' contents. The part between the `<<<<<< HEAD` marker and `======` is the content of HEAD (the `master` branch), and the part between `======` and the `>>>>>> readme-refactor` marker is the content of the `readme-refactor` branch.

To resolve the merge conflict, edit the text to settle the conflict, remove the conflict markers, save the file, stage it, and commit.

```console
$ git add README.md # stage the conflicted file
$ git commit
[master fe92c6b] Merge branch readme-refactor into master
```

### Other ways to merge

By default, Git merges two branches with Merge. When you merge branch B into branch A this way, all of B's commits are added to A's commit history.

Git also offers two other ways to combine branches: Squash and Rebase.

#### Squash

When you squash branch B into branch A, all the changes on B are combined into a single commit on A.

Add the `--squash` option to `git merge` to merge with Squash.

```console
$ git merge <branch> --squash
```

Note that after running the command above, Git only puts all of B's changes into A's staging area; you still need to run `git commit` to finish the merge.

Merging with Squash keeps the commit history simple, but it loses the per-commit details (who made each commit, what each commit changed, and so on), leaving only the combined information (the author of each commit is listed in the commit message as "Co-authored-by"). However, if you use Squash and Merge on GitHub, the original information can still be seen in the Pull Request.

#### Rebase

When you rebase branch B onto branch A, each commit on B is added to A separately, instead of creating a merge commit that combines the two branches as Merge does[^note2].

First switch to branch B, then rebase B onto A:

```console
$ git checkout B
$ git rebase A
```

Now switch back to branch A and run `git merge` once more to finish merging B's content into A.

```console
$ git checkout A
$ git merge B
```

Merging with Rebase keeps the commit history linear, and using Rebase correctly in the right situations can work better than Merge. But it rewrites the commit history, which increases the chance of conflicts both during the Rebase and in later merges, and done carelessly it can make the history messier instead. So if you don't fully understand Rebase, it's better not to use it.

## Managing remote repositories

After making changes locally, you may want to push them to a Git hosting platform such as GitHub. Repositories hosted on such platforms are remote repositories: you can fetch information from them and push your changes to them. Working with others usually involves remote repositories, so it's worth learning to manage them.

### Viewing remote repositories

The `git remote` command lists the current repository's remotes.

If the current repository was cloned, there should be a remote called origin, whose URL is the one you cloned from.

```console
$ git remote
origin
```

To see details about a remote, do this:

```console
$ git remote show origin
* remote origin
  Fetch URL: git@github.com:OI-wiki/OI-wiki.git
  Push  URL: git@github.com:OI-wiki/OI-wiki.git
  HEAD branch: master
  Remote branches:
    git             tracked
    master          tracked
  ...
```

### Configuring remote repositories

`git remote add <name> <url>` adds a remote named `name` with the URL `url`.

`git remote rename <oldname> <newname>` renames the remote `oldname` to `newname`.

`git remote rm <name>` removes the remote named `name`.

`git remote get-url <name>` shows the URL of the remote named `name`.

`git remote set-url <name> <newurl>` changes the URL of the remote named `name` to `newurl`.

### Fetching changes from a remote

Other people may push changes to the remote repository. The `git fetch` command fetches those changes to your machine.

```console
$ git fetch <remote-name> # fetch the changes from <remote-name>
```

Note that `git fetch` only fetches the remote's changes; it doesn't merge them into your local repository. To merge them, use `git pull`. By default, `git pull` is equivalent to `git fetch` followed by `git merge FETCH_HEAD`.

```console
$ git pull <remote-name> <branch> # fetch the changes from <remote-name>, then merge them into HEAD
```

### Pushing changes to a remote

After you finish some changes, the `git push` command pushes them to the remote repository.

```console
$ git push <remote> <from>:<to> # push the changes on local branch <from> to branch <to> on <remote>
```

Depending on the remote, you may be asked for the user name and password of your account there.

Note that your push only succeeds if two conditions hold: you have write access to the repository (branch), and your branch is newer than the corresponding remote branch (roughly, nobody else pushed while you were making your changes). When the remote branch has new changes that your current branch doesn't, run `git pull` to merge them first, then push.

If you need to force-push your local branch's changes to the remote, add the `-f` option. Then **the remote's commit history is overwritten by your local history**, so use this command with care. A better choice is the `--force-with-lease` option, which only overwrites if the remote hasn't been updated. Note that "updated" here is relative to your last fetch: if you use VS Code's Auto Fetch feature, you might miss an update, making `--force-with-lease` as dangerous as `-f`.

### Tracking remote branches

Setting a local branch to track a remote branch makes it easy to see the differences between them, and simplifies working with the remote branch.

Before you start tracking, run `git fetch <remote-name>` to get the remote's information.

Then run `git switch <remote-branch>`. Git automatically creates a new local branch named `<remote-branch>` and sets it to track the corresponding remote branch.

???+ note "Note"
    Note that Git only creates the branch automatically and sets it to track the remote branch when no local branch with that name exists and exactly one remote branch matches the name.

Now `git status` will show the differences between the current branch and the remote branch.

Since the local branch tracks a remote branch, pushing is also simpler: just run `git push`, and the changes on the local branch are pushed to the remote branch it tracks.

For an existing local branch, setting its upstream is also easy. Just run `git branch -u <remote-name>/<remote-branch>` on that branch, and the current local branch will track the remote branch `<remote-name>/<remote-branch>`.

### Connecting over ssh

Compared with HTTP(S), connecting to a remote repository over ssh is more convenient and secure.

Before connecting over ssh, you need to add an ssh key on your machine. Then upload the **public key** of that ssh key to your account on the remote platform.

Since this page is mainly a Git tutorial for **OI Wiki** contributors, we simply point you to [the tutorial in GitHub Docs](https://docs.github.com/cn/github/authenticating-to-github/connecting-to-github-with-ssh) for reference.

Once you've done the steps above, you can connect to remote repositories over ssh. Here is a command that clones the **OI Wiki** repository over ssh:

```console
$ git clone git@github.com:OI-wiki/OI-wiki.git
```

Pushing changes to a remote works the same way as with HTTP(S). But with ssh, you don't have to enter your account name and password.

## Git GUI Tools

For those not familiar with the command line, command-line-only Git can be hard to get started with, and GUI tools can make it somewhat easier. GUI tools also give a better experience than the command line when viewing diffs and logs.

Git comes with its own GUI, and there are also many good Git GUI tools, such as TortoiseGit[^note3] for Windows users and Sourcetree[^note4] for Windows and Mac.

Here is a quick introduction to TortoiseGit. After downloading and installing TortoiseGit, right-click inside the local repository's folder, and you'll see Git's features in the context menu.

![TortoiseGit Example](images/git11.png)

We won't go into the details here; see the documentation on the official website, such as the [TortoiseGit Manual](https://tortoisegit.org/docs/tortoisegit/index.html), or search online.

Many GUI tools officially support Chinese, such as Git Desktop and TortoiseGit. But some translations read awkwardly, so the English versions are recommended.

## External links

-   [Git Reference](https://git-scm.com/docs)
-   [Pro Git Book](https://git-scm.com/book/zh/v2)
-   [Learn Git Branching](https://learngitbranching.js.org/)

## References and notes

[^note1]: In fact, Git also has a system-wide configuration file that applies to every user and every repository on the system. It has the broadest scope and sits above the user configuration file. Since it is rarely used in practice, we won't go into it here.

[^note2]: The [Pro Git Book](https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%8F%98%E5%9F%BA) has diagrams that visualize the Rebase process; they can help you understand how Rebase works.

[^note3]: [TortoiseGit](https://tortoisegit.org/)

[^note4]: [Sourcetree](https://www.sourcetreeapp.com/)
