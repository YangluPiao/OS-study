1. Two; still two?

2. `$ ./paging-multilevel-translate.py -s 0`

   主要是根据README和Figure 20.6算的。

   Use virtual address `611c` as example.

   - `611c => 110 0001 0001 1100`

   前10-bit是VPN，后5-bit是offset，即

   - `[110 0001 000][1 1100]`

   VPN中的前5-bit是page directory index(PDIndex)，即

   - `[110 00] => 24`

   根据`PBDR = 108`，我们就找#108 page table的#24 byte：

   - ```
     page 108:
     83 fe e0 da 7f d4 7f eb
     be 9e d5 ad e4 ac 90 d6
     92 d8 c1 f8 9f e1 ed e9
     (a1) e8 c7 c2 a9 d1 db ff
     ```

   所以我们就找到了page directory entry(PDE)，就是`0xa1`

   - `0xa1 => 1010 0001`

   根据README中对PDE的定义我们知道，第一个bit是valid bit，因为是1，所以这个地址合法。剩下的

   - `[010 0001] => 33`

   即#33 page table就是我们的page table base address。

   VPN的前10位中的后5为为page table index(PTIndex)，所以

   - `[01 000] => 8`

   所以我们在这里找#33 page table的#8 byte：

   - ```
     page  33:
     7f 7f 7f 7f 7f 7f 7f 7f
     (b5) 7f 9d 7f 7f 7f 7f 7f
     7f 7f 7f 7f 7f 7f 7f 7f
     7f 7f f6 b1 7f 7f 7f 7f
     ```

   这个就是page table entry(PTE)，就是`0xb5`

   - `0xb5 => 1011 0101`

   之后根据README中对PTE的定义，首位valid bit是1，所以地址合法；后7位是

   - `[011 0101] => 53`

   就是physical frame number(PFN)。

   最后physical memory是12bit，其中7位就是刚才的PFN，5位offset就是开头的virtual memory的后5位

   - `[1 1100] => 28`

   所以我们定位到#53 page的#28 byte：

   - ```
     page  53:
     0f 0c 18 09 0e 12 1c 0f
     08 17 13 07 1c 1e 19 1b
     09 16 1b 15 0e 03 0d 12
     1c 1d 0e 1a (08) 18 11 00
     ```

   最后答案就是`0x08 => 8`！！！

3. 直觉上，因为进行了多次memory的reference，而且并没有任何规律可言，cache能起到的作用应该很有限。