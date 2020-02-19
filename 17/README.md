解释：

```
$ ./malloc.py -S 100 -b 1000 -H 4 -a 4 -l ADDRSORT -p BEST -n 5 -c
ptr[0] = Alloc(3)  returned 1004 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1008 sz:92 ]
```

Alloc 3 byte, 但是要allign到4个byte，所以return是1004。加上4个byte的header，所以free list（next）从1008开始。

1. 

   1. return: 1003

      free list: [addr: 1003 sz: 97]

   2. return: 0

      free list: [addr: 1000 sz: 3] [addr: 1003 sz: 97]

   3. return: 1008

      free list: [addr: 1000 sz: 3] [addr: 1008 sz: 92]

   4. return: 0

      free list: [addr: 1000 sz: 3] [addr: 1003 sz: 5] [addr: 1008 sz: 92]

      ...后略

2. 被分成更多fragment，所以也会做更多search

3. 搜索fewer element，但是效果和BEST差不多

4. sort不会影响BEST和WORST，因为它们都是exhaustive search。但是会影响FIRST。

5. 如果不merge，那free list会非常长。并且配合上`-l ADDRSORT`，会非常快。

6. Alloc得越多越容易fail；反之基本就是空的

7. `-p WORST`挺容易highly-fragmented的

