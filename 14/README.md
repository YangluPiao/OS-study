1. Seg fault

2. `gdb` stops at SIGSEGV

   ```
   Program received signal SIGSEGV, Segmentation fault.
   0x000055555555465e in main () at 14.c:6
   6	  printf("%d\n", (*pa));
   ```

3. `valgrind` catches the `NULL`

   ```
   ==5556== Invalid read of size 4
   ==5556==    at 0x10865E: main (14.c:6)
   ==5556==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
   ```

4. The program runs fine since the un-freed memory will be handled by OS after program ends.

   But `valgrind` still reports this:

   ```
   ==5622== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
   ==5622==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==5622==    by 0x1086C7: f2 (14.c:10)
   ==5622==    by 0x1086DC: main (14.c:14)
   ```

5. It runs fine. But this has index-out-of-bound issue.

   `valgrind` knows that:

   ```
   ==5706== Invalid write of size 4
   ==5706==    at 0x10873F: f3 (14.c:15)
   ==5706==    by 0x108761: main (14.c:20)
   ==5706==  Address 0x522d1d0 is 0 bytes after a block of size 400 alloc'd
   ==5706==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==5706==    by 0x108730: f3 (14.c:14)
   ==5706==    by 0x108761: main (14.c:20)
   ```

6. The program prints 0, which is NOT the number I set.

   `valgrind` knows:

   ```
   ==6134== Invalid read of size 4
   ==6134==    at 0x108784: f4 (14.c:23)
   ==6134==    by 0x1087A9: main (14.c:27)
   ==6134==  Address 0x522d040 is 0 bytes inside a block of size 12 free'd
   ==6134==    at 0x4C30D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==6134==    by 0x10877F: f4 (14.c:22)
   ==6134==    by 0x1087A9: main (14.c:27)
   ==6134==  Block was alloc'd at
   ==6134==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==6134==    by 0x108765: f4 (14.c:20)
   ==6134==    by 0x1087A9: main (14.c:27)
   ```

7. The program fails to run:

   ```
   munmap_chunk(): invalid pointer
   ```

8. reference: http://www.cplusplus.com/reference/cstdlib/realloc/

9. skip

