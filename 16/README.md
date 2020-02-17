1. 

   1. `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0`

      0: seg 1, physical addr = 492

      1, 2, 3, 4: seg fault

   2. `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1` 

      0: seg 0, physical addr = 17

      1: seg 1: physical addr = 492

      2, 3, 4: seg fault

   3. `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2`

      0: seg 1, physical addr = 506

      1: seg 1, physical addr = 505

      2: seg 0, physical addr = 7

      3: seg 0, physical addr = 10

      4: seg fault

2. 

   1. 19

   2. 108

   3. lowest: 21 highest: 107

   4. `-A 19`

      `-A 108`

      `-A 20`

      `-A 107`

3. `$ ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 128 --l1 2 -c`

4. `-l` and `-a`, lengh should cover 90% of address space

5. `$ ./segmentation.py -s 100 -a 16 -p 32 -c --l0 0 --l1 0`