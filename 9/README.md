1. 取mod就行了，略
2. `-l 10:1,10:100`
   1. job0 is hardly run
   2. with probability of `1/101`
   3. it basically becomes "long jobs run first" strategy
3. 谁先谁后结束五五开
4. quantum size 越小越fair
5. ticket value越大，stride越小，pass value增加的越慢，也就越经常被run