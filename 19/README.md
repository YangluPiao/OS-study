**access** means access the **page**

1. 精度是微秒（microsecond, us)，所以操作要至少大于微秒级。

2. 略

3. ```
   $ ./run.sh 100000
   num_trials: 100000
   num_pages:    1, time per access: 7.710000 ns
   num_pages:    2, time per access: 10.025000 ns
   num_pages:    4, time per access: 7.040000 ns
   num_pages:    8, time per access: 6.443750 ns
   num_pages:   16, time per access: 4.552500 ns
   num_pages:   32, time per access: 3.567813 ns
   num_pages:   64, time per access: 3.737188 ns
   num_pages:  128, time per access: 5.620781 ns
   num_pages:  256, time per access: 5.371367 ns
   num_pages:  512, time per access: 5.270059 ns
   num_pages: 1024, time per access: 5.872744 ns
   num_pages: 2048, time per access: 12.054097 ns
   num_pages: 4096, time per access: 17.971013 ns
   num_pages: 8192, time per access: 17.242042 ns
   ```

4. skip

5. Compile with `-O0`

6. ```C
     // use one cpu
     cpu_set_t set;
     CPU_ZERO(&set);
     CPU_SET(0, &set);
     if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1)
       exit(1);
   
   ```

7. Use `calloc`

