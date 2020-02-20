解释：

```
$ ./paging-linear-translate.py  -v  
ARG address space size 16k
ARG phys mem size 64k
ARG page size 4k  
  [       0]   0x8000000c
  [       1]   0x00000000
  [       2]   0x00000000
  [       3]   0x80000006

Virtual Address Trace
  VA 0x00003229 (decimal:    12841) --> 00006229 (decimal    25129) [VPN 3]
  VA 0x00001369 (decimal:     4969) -->  Invalid (VPN 1 not valid)
```

首先，因为address space是16KB，所以总共是14个bit。又因为有4个page frame，所以我们得到：

- 2个头bit来表示page
- 12个offset bit

对于VA 1，二进制表示是`[11] [0010 0010 1001]`，所以显然它是virtual page 3。又因为是page 3，所以我们对应到`0x80000006`这个page entry。显然，它的最高位是`1`，所以是valid的page。我们不动offset，将virtual page number(`3`) 换成 physical page frame(`6`)，就得到了最终答案`0x6229`

类似地，对于VA 2，我们知道它对应virtual page number `1`，但是不幸的是它invalid（最高位不是1），所以是page fault。

[视频](https://www.youtube.com/watch?v=KNUJhZCQZ9c)

1. `page table size == number of virtual pages == address space size / page size`

   Big page table takes up too much memory.

2. `-u 0`: all invalid

   `-u 100`: all valid

3. `-P 8 -a 32 -p 1024 -v -s 1`: too small

   `-P 8k -a 32k -p 1m -v -s 2`: OK

   `-P 1m -a 256m -p 512m -v -s 3`: too big

4. 略