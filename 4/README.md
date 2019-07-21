### Homework
##### 1. 
The CPU utilization should be 100%, since both processes are CPU-only(no I/O needed).
##### 2.
PID 0 takes 4 time units, while PID 1 takes 5 time units.
##### 3.
Switching matters since while PID 0, which is now pure I/O only, is running, CPU can handle PID 1.
#### 4.
By turning on SWITCH_ON_END, while I/O is doing it's job, CPU is blocked and cannot do anything.
##### 5.
This should be the same as 3.
##### 6.
What happens?
- PID 0 issues I/O and finishes the first one immediately but it doesn't run the reset two until all CPU processes are finished.

Are the system resources utilized effectively?

- Not really. Because CPU cannot utilize the spare time unit while I/O is running.

##### 7.
I/Os are all finished as soon as possible. And while I/Os are running, CPU can also work on PID 1,2 and 3. So overall it's much more effecient utilization of system resources.