1. 
   
    1. `$ ./mlfq.py -n 2 -j 2 -m 3 -Q 1,1`
    
        Job List:
        Job  0: startTime   0 - runTime   2 - ioFreq   7
        Job  1: startTime   0 - runTime   1 - ioFreq   3
        Trace:
        time = 0: job 0 and 1 arrive
        time = 0: run job 0 on queue 1
        time = 1: run job 1 on queue 1; degrade job 0 to queue 0
        time = 2: job 1 finish; run job 0 on queue 0
    
    2. `$ ./mlfq.py -n 2 -j 2 -m 10 -Q 3,5`
       Job List:
       Job  0: startTime   0 - runTime   8 - ioFreq   7
       Job  1: startTime   0 - runTime   4 - ioFreq   3
       Trace:
       time = 0: job 0 and 1 arrive
       time = 0: run job 0 on queue 1
       time = 3: run job 1 on queue 1, degrade job 0 to queue 0
       time = 6: job 1 finish; run job 0 on queue 0
       time = 10: start job 0 IO request
       time = 15: job 0 IO done; run job 0 on queue 0
       time = 16: job 0 finish
    
2. 略

3. ? 

4. `$ ./mlfq.py -j 2 -S -l 0,10,9:0,10,10 -c -I -i 0`

    1. IO bump
    2. job 0 do IO before each QUANTUM ends
    3. job 0 IO time is very small
    4. forbid job 1 to run IO
    
5. ?

6. ?