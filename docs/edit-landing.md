disqus:

## Before you edit

First of all, thank you for being willing to contribute to **OI Wiki**.

Before you start, please read and get familiar with [How to contribute](./intro/htc.md) and the [Format guide](./intro/format.md), so you can avoid unnecessary trouble while editing.

When you have finished reading, click the button below to start editing.

???+ note "Please note"
    -   Remember to add your GitHub ID after the author field at the top of the file, following the format there;
    -   According to Issue [#3061](https://github.com/OI-wiki/OI-wiki/issues/3061), your changes will now be merged by either Rebase or Squash, depending on the quality of your commit messages. Please note that with Squash, you may become the author of the commit rather than the committer.

<a id="btn-startedit" style="padding: 0.75em 1.25em; display: inline-block; line-height: 1; text-decoration: none; white-space: nowrap; cursor: pointer; border: 1px solid #6190e8; border-radius: 5px; background-color: #6190e8; color: #fff; outline: none; font-size: 0.75em;">Start editing</a>

<script>
    function getQueryVariable(name, dft)
    {
        var reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)', 'i');
        var r = window.location.search.substr(1).match(reg);
        if (r != null)
        {
            return unescape(r[2]);
        }
        return dft;
    }
    document.getElementById("btn-startedit").href = "https://github.com/OI-wiki/OI-wiki/edit/master/docs" + getQueryVariable("ref", "");
</script>
