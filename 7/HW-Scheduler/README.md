1. 
- FIFO:

  `./scheduler.py -p FIFO -j 3 -l 200,200,200`

  turnaround time:

  0: 200, 1: 400, 2: 600

  response time: 

  0: 0, 1: 200, 3: 400

- SJF: 

  `./scheduler.py -p SJF -j 3 -l 200,200,200`
  
  turnaround time and response time are the same as FIFO

2. 

- FIFO:

  `./scheduler.py -p FIFO -j 3 -l 100,200,300`
  
  turnaround time:0: 100, 1: 30
  
  0, 2: 600
  
  response time: 
  
  0: 0, 1: 100, 3: 300

- SJF: 

  `./scheduler.py -p SJF -j 3 -l 100,200,300`
   turnaround time and response time are the same as FIFO

3. 

- RR: 
  
   `./scheduler.py -p RR -j 3 -l 100,200,300`
   turnaround time:
   0: 298, 1: 499, 2: 600
   response time:
   0: 0, 1: 1, 2: 2

4. When the jobs have same exact length; or the order or jobs are sorted from
   shortest length to the longest.

5. When the job lengths are the same and time-slice(quantum length) of RR is
   equal to the job length.
6. Increases.
   -m 100: avg response time = 25.33
   -m 200: avg response time = 50.33
   -m 300: avg response time = 75.00
7. Increases.
   -m 100 -q 1: ave response time = 1.00
   -m 100 -q 20: ave response time = 16.67
   The worst case happens when all jobs arrives at the same time, one of them
   will be the last one to respond. Where the time is `(N - 1) * q`.

