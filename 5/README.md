1.
    See inlined comments
2.
    Yes. Doesn't matter, looks like it's a blocking operation.
3.
    Use `sleep`?
4.
    exec[l]: followed by **list** of arguments
    exec[v]: followed by an **array** of arguments
    execl[e]: also specifies environment variables
5.
    See inlined comments
6.
    It's more flexible since we can feed various `pid` and `option`s
7.
    See inlined comments
8.
    Note: create only one `pipe` and close respective unused read/write end in
    different children processes. One process writes and the other one reads.
