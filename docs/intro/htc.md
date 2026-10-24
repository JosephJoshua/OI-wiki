Before we begin: everyone on the **OI Wiki** team warmly welcomes you to contribute pages to this project. **OI Wiki** is what it is today thanks to hundreds of people like you!

This page mainly describes the process of writing for **OI Wiki**. Before you write or fix a Wiki page, please read the following carefully. It will help you produce higher-quality content.

## Contribution guidelines

Before editing, please read the [OI Wiki contribution guidelines](https://github.com/OI-wiki/OI-wiki/blob/master/.github/CONTRIBUTING.md) and the [project policies](./about.md#project-policies), so that you can work and communicate better with other community contributors.

## Collaborating

???+ warning "Warning"
    Before you start writing a piece of content, check the [Issues](https://github.com/OI-wiki/OI-wiki/issues) to make sure nobody else is doing the same work, then open a [new issue](https://github.com/OI-wiki/OI-wiki/issues/new) to record what you plan to write.

???+ tip "Tip"
    There are also many problems waiting to be fixed or solved in the Issues, especially in our Iteration Plan. Picking up a task there is a great way to start!

To keep entries professional and accurate, we suggest you consider the following before editing:

1.  **Choose areas you know well**: Please focus first on entries related to your expertise, background or interests. This helps you create high-quality content.
2.  **Be careful with new areas**: If you are still a beginner in a topic or don't know it well, we suggest you deepen your understanding by reading and studying first, and start editing once you feel confident.
3.  **Consult references**: When adding to or revising an entry, we suggest you first check authoritative literature and sources to make sure the information is accurate. You are also welcome to ask questions in the page's comment section or in our community and discuss with other editors.

We value every contributor's enthusiasm and effort, and we understand that everyone's level of expertise differs. Let's work together to take care of this garden of knowledge and help more readers with accurate, professional content. We look forward to your contributions! To quote Wikipedia:

> Don't be afraid to edit; be bold in updating pages![^ref1]

### Editing on GitHub

Writing for **OI Wiki** **requires** a GitHub account (you can sign up on [GitHub's sign-up page](https://github.com/signup)), but it does **not require** advanced GitHub skills. Even if you are a beginner, you can edit **very well** just by following the steps below.

???+ tip "Tip"
    Until your changes are merged into the main **OI Wiki** repository, none of your changes to **OI Wiki** will appear on the main **OI Wiki** site, so you don't need to worry about breaking the content currently shown on **OI Wiki**.
    
    If you are still worried, you can check out [GitHub's official tutorials](https://skills.github.com/).

#### Editing content on a single page

1.  Find the page on **OI Wiki**;
2.  Click the **"Edit this page"** (<i class="md-icon">edit</i>) button at the top right of the main text (left of the table of contents). After confirming that you have read this page and the [Format guide](./format.md), click the button and follow the prompts to go to GitHub and edit;
3.  Write your changes in the edit box. Note: while editing and during the following submission steps, please **turn off any automatic translation software**, because it can cause unnecessary trouble (for example, it sometimes wrongly renames the file you are editing, which breaks the directory structure);
4.  When you are done, scroll to the bottom of the page, fill in the commit message following the [commit message format](#commit-message-format) in this page, then click the **Propose changes** button to submit your change. After you click it, GitHub automatically creates a fork of the **OI Wiki** repository for you and adds your commit to that fork.
5.  GitHub automatically takes you to your fork's page. A green **Create pull request** button appears at the top; click it and GitHub takes you to a page for creating a Pull Request. Scroll down to check that your changes are correct, write the Pull Request message following the [Pull Request message format](#pull-request-message-format) section of this page, then click the green **Create pull request** button on the page to create the Pull Request.
6.  If all goes well, your Pull Request has now been submitted to the repository. Just wait for an administrator to review it and merge it into the main repository.

While you wait for the merge, you can comment on, upvote or downvote other people's Pull Requests. When there is news, a notification appears at the top right of the web page, and you also get an email (depending on the notification settings in your personal settings).

#### Editing content on multiple pages

If you need to edit several pages that are unrelated to each other, follow the [Editing content on a single page](#editing-content-on-a-single-page) section above to change all of them.

1.  Open the [OI-Wiki/OI-Wiki](https://github.com/OI-Wiki/OI-Wiki) repository and press the <kbd>.</kbd> key on your keyboard (or change `github.com` in the URL to `github.dev`)[^ref2] to open GitHub's web-based VS Code editor;
2.  Make your changes to the page source files in the editor. You can use the preview button at the top right (or the <kbd>Ctrl+K</kbd><kbd>V</kbd> shortcut) to open a preview on the right;
3.  When you are done, use the Source Control tab on the left, fill in the commit message following the [commit message format](#commit-message-format) in this page, and commit. When committing, you will be asked whether to create a fork of this repository; just click the green **Fork Repository** button.
4.  After committing, a prompt box pops up at the top center of the page. Enter the title in the first prompt and the name of the branch to commit to in the second. Then a notification pops up at the bottom right, saying something like `Created Pull Request #1 for OI-Wiki/OI-Wiki.`; click the blue link to view that Pull Request.

#### Adding changes to a Pull Request

1.  Open [OI-Wiki's Pull Request list](https://github.com/OI-wiki/OI-wiki/pulls), find the Pull Request you submitted and click it.
2.  Below the title of the Pull Request page there is a line of text like `<your ID> wants to merge x commits into OI-wiki:master from <your ID>:patch-1`. Click the `<your ID>:patch-1` part.
3.  You should be redirected to your fork, and the branch name at the top left of the file list should be the branch of your Pull Request (in this example, `patch-1`).
4.  Make the changes you need.
    -   If you need to edit a single file or several unrelated pages, find the file you want and change it directly. When you are done, scroll to the bottom of the page, fill in the commit message following the [commit message format](#commit-message-format) in this page, then click the **Commit changes** button to commit.
    -   If you need to edit several files, press the <kbd>.</kbd> key on your keyboard (or change `github.com` in the URL to `github.dev`)[^ref2] to open GitHub's web-based VS Code editor and make your changes. Then use the Source Control tab on the left, fill in the commit message following the [commit message format](#commit-message-format) in this page, and commit.
5.  Your changes are now added to your Pull Request automatically.

### Editing locally with Git

???+ warning "Warning"
    For most users, we recommend the GitHub web editor described above.

Although in most cases you can edit directly on GitHub, for some special cases (such as when you need GPG signing) we recommend editing locally with Git.

The general process is:

1.  Fork the main repository to your own account;
2.  Clone your fork to your local machine;
3.  Make changes locally and commit them;
4.  Push the changes to your fork;
5.  Open a Pull Request to the main repository.

For detailed steps, see the [Git](../tools/git.md) page.

#### Adding changes to a Pull Request

Keep making changes in your local clone of the fork, then commit and push them. Your changes are added to the Pull Request automatically.

### Previewing changes on the built site

You can find the test checks at the bottom of the Pull Request page. Click the Details link for netlify/oi-wiki/deploy-preview (as shown below) to open an automatically built version of the pages with your changes, for you to preview.

![deploy\_preview](./images/deploy_preview.png)

### Changes to the table of contents and links

Usually, if you need to add a new page or change an existing page's link in the table of contents, you need to edit the [`mkdocs.yml`](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) file.

To add a new page, you can follow the existing format. But unless you are restructuring or fixing a term, **we don't recommend changing the links of existing pages**. Unnecessary changes in Pull Requests will be rejected.

If you insist on changing a link, remember to update the author field and the redirect file.

### The author field

The GitHub API can't keep track of statistics after a file moves, so we keep an author list by hand in the file header to solve this. The author field is at the very start of the Markdown file, in the form `author: Ir1d, cjsoft`, with adjacent IDs separated by a comma and a space. Each ID is a GitHub user name, i.e. the one in the GitHub profile address (for example, `Ir1d` in <https://github.com/Ir1d>).

When you change a link, add every contributor of the current page to the author field.

### The redirect file

When you change a link, you need to update the redirect file, so that links from other sites don't break.

The [`_redirects`](https://github.com/OI-wiki/OI-wiki/blob/master/docs/_redirects) file is used to generate the [Netlify configuration](https://docs.netlify.com/routing/redirects/#syntax-for-the-redirects-file) and the [files used for redirects](https://github.com/OI-wiki/OI-wiki/blob/master/scripts/gen_redirect.py).

Each line is one redirect rule, giving the source and destination URLs (without the domain):

```text
/path/to/src /path/to/desc
```

Note: all redirects are 301 redirects. You only need to change this file when changing a URL in the table of contents creates a dead link.

### Commit message format

For the commit message you write when committing, please follow these basic rules:

1.  The commit summary should briefly describe what this commit changes. Keep the summary within 50 characters; anything longer is automatically moved into the body.
2.  If you need to describe the commit further, explain it in detail in the body.

For the commit summary, we recommend this format:

```text
<type>(<file name>): <what changed>
```

The types are:

-   `feat`: for adding content.
-   `fix`: for fixing errors in existing content.
-   `refactor`: for restructuring a page (larger-scale changes).
-   `revert`: for reverting earlier changes.

### Pull Request message format

For Pull Requests, please follow these rules:

1.  The title should state the purpose of the PR (**what** work it does, **what** problem it fixes).
2.  The description should briefly describe the changes. If it fixes an issue, add `fix #xxxx` to the description, where `xxxx` is the issue number.
3.  Please read the [contribution guidelines](https://github.com/OI-wiki/OI-wiki/blob/master/.github/CONTRIBUTING.md) and the [code of conduct](https://github.com/OI-wiki/OI-wiki/blob/master/CODE_OF_CONDUCT.md) carefully. If you agree, tick the boxes in the PR template to show that you accept them.

For the Pull Request title, we recommend this format:

```plain
<type>(<file name>): <what changed> (<related issue number>)
```

The types are:

-   `feat`: for adding content.
-   `fix`: for fixing errors in existing content.
-   `refactor`: for restructuring a page (larger-scale changes).
-   `revert`: for reverting earlier changes.

Examples:

-   `fix(ds/persistent-seg): make the code comments clearer`
-   `fix: tools/judger/index is missing from the table of contents (#3709)`
-   `feat(math/poly/fft): better proof`
-   `refactor(ds/stack): reorganize the page content`

### Collaboration workflow

1.  When a new Pull Request comes in, GitHub emails the reviewers;
2.  At the same time, two sets of checks run on [GitHub Actions](https://github.com/OI-wiki/OI-wiki/actions) and [Netlify](https://app.netlify.com/sites/oi-wiki), and their progress is shown at the bottom of the PR page. GitHub Actions mainly checks that the changes in the PR don't break the site build; Netlify builds the PR's changes so reviewers can check them easily (click Details after the checks finish to learn more);
3.  A reviewer may find problems and leave a `review`, or `suggested changes` (shown with a gray icon) / `requested changes` (required changes, shown with a red icon; this only appears when the reviewer has write access to the repo). Usually the reviewer also includes suggestions and the changes that need to be made. You will then need to add more changes to the Pull Request. For how to do this, see the `Adding changes to a Pull Request` part under `Editing on GitHub` or `Editing locally with Git`.
4.  A PR can be merged into the master branch only after enough reviewers approve it;
5.  After it is merged into master, GitHub Actions rebuilds the site and pushes the result to the gh-pages branch;
6.  Only then does the server pull the gh-pages update and redeploy the latest version of the content.

## References and notes

[^ref1]: [Wikipedia: Getting started/Editing (Chinese Wikipedia)](https://zh.wikipedia.org/wiki/Wikipedia:%E6%96%B0%E6%89%8B%E5%85%A5%E9%96%80/%E7%B7%A8%E8%BC%AF)

[^ref2]: [Web-based editor - GitHub Codespaces - GitHub Docs](https://docs.github.com/en/codespaces/developing-in-codespaces/web-based-editor)
