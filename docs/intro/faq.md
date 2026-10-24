This page answers some frequently asked questions.

## I have some questions about this Wiki

Q: Why did you want to make this Wiki?

A: When you were learning **OI**, did you ever feel lost and helpless in front of such a huge body of knowledge? What **OI Wiki** wants to do is perhaps something like "making training resources easy to reach for students who don't have many contest resources". Of course, that is not the whole story. The motivation for making the Wiki may also be simple: we just want to make a tiny contribution to the development of **OI**. XD

***

Q: I'm interested. How can I take part?

A: **OI Wiki** is currently hosted on GitHub. You can visit this [repo](https://github.com/OI-wiki/OI-wiki) directly to see the latest progress. You can take part by opening an [Issue](https://github.com/OI-wiki/OI-wiki/issues) or a [Pull Request](https://github.com/OI-wiki/OI-wiki/pulls) on GitHub, sharing your ideas in the discussion groups, or sending contributions directly to the administrators. Right now we use [MkDocs](https://mkdocs.readthedocs.io), a framework written in Python. It supports Markdown (including math formulas).

***

Q: But I'm not very strong... I don't know what I could do.

A: Everything starts with passion. You can help review other people's changes, help us spread the word about **OI Wiki**, and help build a good atmosphere for learning and discussion in the community!

***

Q: Who is mainly working on this right now? It feels like a huge, never-ending project. Can it really be done well?

A: At first it was mainly some retired veteran contestants. Later we met many like-minded people: active contestants, retired players, and also friends who have never taken part in **OI**. Today the project is mainly maintained by the **OI Wiki** team (below is a group photo).

<a href="https://github.com/OI-wiki/OI-wiki/graphs/contributors"><img src="https://opencollective.com/oi-wiki/contributors.svg?width=890&button=false"/></a>

Of course, it is very hard for us to make this project perfect on our own, so we sincerely invite you to help improve **OI Wiki** together.

***

Q: How do you make sure the content we add won't suddenly disappear?

A: Our content is hosted on [GitHub](https://github.com/OI-wiki/OI-wiki), so even if our servers crash, nothing is lost. We also back up everyone's hard work regularly, so even if GitHub shut down one day (?), our content would not be lost.

***

Q: **OI Wiki** seems to have some empty pages!

A: Yes. Limited by the skill and time of the team members, we can't finish these empty pages for now. So we are calling for contributions and recruiting here, hoping to meet people who share the same idea, so that we can complete **OI Wiki** together.

***

Q: Why not just write for the [Chinese Wikipedia](https://zh.wikipedia.org/)?

A: Because we want to truly help more contestants and anyone interested in these topics. Also, for well-known reasons, the content of the Chinese Wikipedia can't be accessed without barriers (in mainland China).

## I want to get involved!

Q: How do I communicate with the team?

A: You can contact us using the [ways to get in touch on the About page](./about.md#how-to-get-in-touch).

***

Q: How do I contribute code or content?

Please see the [How to contribute](./htc.md) page.

***

Q: Where is the table of contents?

A: The table of contents is in the [mkdocs.yml](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml#L17) file in the project's root directory.

***

Q: How do I edit the content of a topic?

A: There is an edit button <i class="md-icon">edit</i> at the top right of each page. Click it, confirm that you have read [How to contribute](./htc.md), and you will be taken to the corresponding file on GitHub.

Alternatively, you can read the table of contents [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) yourself to find where the file is.

***

Q: How do I add a topic?

A: There are two options:

-   Open an Issue describing the content you would like added.
-   Open a Pull Request that adds the new topic to the table of contents [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) and creates an empty `.md` file at the matching place in the [docs](https://github.com/OI-wiki/OI-wiki/tree/master/docs) folder. For formatting details, see the [Format guide](./format.md#requirements-for-contributed-documents).

***

Q: I have trouble accessing GitHub.

A: We recommend adding the following lines to your hosts file[^ref1]:

```text
# GitHub Start
140.82.114.25                 alive.github.com
140.82.113.5                  api.github.com
185.199.110.153               assets-cdn.github.com
185.199.111.133               avatars.githubusercontent.com
185.199.111.133               avatars0.githubusercontent.com
185.199.111.133               avatars1.githubusercontent.com
185.199.111.133               avatars2.githubusercontent.com
185.199.111.133               avatars3.githubusercontent.com
185.199.111.133               avatars4.githubusercontent.com
185.199.111.133               avatars5.githubusercontent.com
185.199.111.133               camo.githubusercontent.com
140.82.112.22                 central.github.com
185.199.111.133               cloud.githubusercontent.com
140.82.114.9                  codeload.github.com
140.82.113.22                 collector.github.com
185.199.111.133               desktop.githubusercontent.com
185.199.111.133               favicons.githubusercontent.com
140.82.112.3                  gist.github.com
52.216.163.147                github-cloud.s3.amazonaws.com
52.217.124.1                  github-com.s3.amazonaws.com
52.216.144.83                 github-production-release-asset-2e65be.s3.amazonaws.com
52.217.121.249                github-production-repository-file-5c1aeb.s3.amazonaws.com
52.217.206.57                 github-production-user-asset-6210df.s3.amazonaws.com
192.0.66.2                    github.blog
140.82.114.4                  github.com
140.82.113.18                 github.community
185.199.110.154               github.githubassets.com
151.101.1.194                 github.global.ssl.fastly.net
185.199.110.153               github.io
185.199.111.133               github.map.fastly.net
185.199.110.153               githubstatus.com
140.82.112.25                 live.github.com
185.199.111.133               media.githubusercontent.com
185.199.111.133               objects.githubusercontent.com
13.107.42.16                  pipelines.actions.githubusercontent.com
185.199.111.133               raw.githubusercontent.com
185.199.111.133               user-images.githubusercontent.com
13.107.253.40                 vscode.dev
140.82.112.21                 education.github.com
# GitHub End
```

You can find the latest version and more information at [GitHub520](https://gitee.com/klmahuaw/GitHub520).

Linux and macOS users can try the [gh-check script](https://gist.github.com/lilydjwg/93d33ed04547e1b9f7a86b64ef2ed058) by [lilydjwg (Yiyun)](https://github.com/lilydjwg/) to find the fastest IPs. The `--hosts` option updates the hosts file directly, and `--help` shows usage help. You need Python 3 and aiohttp installed first (`pip install aiohttp -i https://pypi.tuna.tsinghua.edu.cn/simple/`). Yiyun's blog post about it: [Finding the fastest GitHub IP](https://blog.lilydjwg.me/2019/8/16/gh-check.214730.html).

You can also use the [Gitclone](https://www.gitclone.com/) service to speed up cloning; see the instructions on its home page.

If you only want to clone the **OI Wiki** repository:

```bash
git clone https://gitclone.com/github.com/OI-wiki/OI-wiki
```

If you want to contribute to **OI Wiki**, first fork the **OI Wiki** repository, then run the following (replace `username` with your user name). Note that this example makes you connect to GitHub over SSH[^only-ssh-connect]:

```bash
git clone https://gitclone.com/github.com/username/OI-wiki
git remote set-url origin git@github.com:username/OI-wiki.git
```

***

Q: pip is way too slow for me!

A: You can switch to a mirror in mainland China[^ref2], or:

```bash
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

***

Q: I cloned this project in a client, and it was too slow.

A: If you have `git bash` installed, you can add a few limits to reduce the download size.[^ref3]

```bash
git clone https://github.com/OI-wiki/OI-wiki.git --depth=1 -b master
```

***

Q: I have never installed Python 3.

A: Visit the [official Python website](https://www.python.org/downloads/) for more information.

***

Q: It seems to say my pip version is too old.

A: Open cmd/shell and run the following command:

```bash
python -m pip install --upgrade pip
```

***

Q: Installing the dependencies failed.

A: Check: your network? Permissions? What does the error message say?

***

Q: I've already cloned it. Why can't I deploy it?

A: Check whether the dependencies are installed properly.

***

Q: I cloned the repo a long time ago. How do I update it to the new version?

A: See GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork).

***

Q: How do I update dependencies I installed earlier?

A: Run the following command:

```bash
pip install -U -r requirements.txt
```

***

Q: Why is my Markdown formatting broken?

A: You can read [cyent's notes](https://web.archive.org/web/20221103014610/https://cyent.github.io/markdown-with-mkdocs-material/) or the [MkDocs usage guide](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) (in Chinese).

We currently use [remark-lint](https://github.com/remarkjs/remark-lint) to fix formatting automatically. Some parts of the [configuration](https://github.com/OI-wiki/OI-wiki/blob/master/.remarkrc) may not be good enough yet; feel free to point them out.

***

Q: Does GitHub not show my math formulas?

A: Right, GitHub's preview does not render math formulas. But don't worry: MkDocs supports math formulas and they work normally. Any syntax supported by MathJax can be used.

***

Q: Why are my math formulas garbled?

A: If it is a display formula (using `$$`), the known issue is that you need a blank line on both sides of the `$$` block, and each `$$` must be on a line **by itself** (with no spaces in front). The format is:

```text
// blank line
$$
a_i
$$
// blank line
```

***

Q: Why doesn't my formula show up properly in the table of contents? It seems to appear twice.

A: Yes, this is a bug in python-markdown and may be fixed soon.

To avoid doubled formulas in the table of contents, see [how the SAM page under the string section writes its headings](https://github.com/OI-wiki/OI-wiki/blame/master/docs/string/sam.md#L73).

```text
End position <script type="math/tex">endpos</script>
```

In the table of contents it becomes

```text
End position endpos
```

Note: please avoid putting MathJax formulas in headings for now.

***

Q: How do I declare copyright information for a single page?

A: Just add one line at the start of the page.[^ref4]

For example:

```text
copyright: SATA
```

Note: the default is CC BY-SA 4.0 and SATA.

***

Q: Why is my name missing from the author list?

A: If you wrote part of a page but were not recorded in the author list, you can add your GitHub ID to the [author field](./htc.md#the-author-field) in the file header.

***

Thank you for reading to the end. What we need most right now is your help.

The **OI Wiki** team

2018.8

## References and notes

[^ref1]: [GitHub520](https://gitee.com/klmahuaw/GitHub520)

[^ref2]: [Switching the pip source to a mirror in mainland China - L Yu - CSDN Blog](https://blog.csdn.net/lambert310/article/details/52412059) (in Chinese)

[^ref3]: [GIT: learn it step by step (Windows Git Bash)](https://blog.csdn.net/FreeApe/article/details/46845555) (in Chinese)

[^ref4]: [Metadata - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage)

[^only-ssh-connect]: GitHub has removed password-based authentication over HTTPS; you must connect with SSH or a Personal Access Token. See [Which remote URL should I use?](https://docs.github.com/cn/github/using-git/which-remote-url-should-i-use), [Creating a personal access token](https://docs.github.com/cn/github/authenticating-to-github/creating-a-personal-access-token) and [Connecting to GitHub with SSH](https://docs.github.com/cn/github/authenticating-to-github/connecting-to-github-with-ssh).
