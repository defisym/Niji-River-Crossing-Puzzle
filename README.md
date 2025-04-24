# [虹咲过河问题](https://tieba.baidu.com/p/9663861117)

## 题目

虹咲学院偶像同好会13人要过河，河上只有一艘船，船上只能坐两个人，没有船家所以需要至少一人开船。但成员们存在如下关系：

1. 高咲侑会在步梦不在、身边只有一个人的情况下推倒除米娅以外的其他任何同好会成员。
2. 如果出现了高咲侑身边只有雪菜、小静子、ksks或仅有其中任意两个人的情况，侑都会把她们一起推倒。
3. 步梦只要和高咲侑在一个区域就可以看住高咲侑杜绝其一切DD行为。但如果只有她们二人在一起，高咲侑就会被她推倒。
4. 雪菜不会主动推倒任何人。
5. ksks和高咲侑处于同一区域、身边只有她们以外的一个人，且这个人不是步梦或小静子的时候，她会和高咲侑偷吃
6. 小静子在和ksks独处时会把ksks推倒
7. 小静子和高咲侑在同一区域时，如果该区域人数≤4且该区域没有步梦，她就会和高咲侑偷吃。
8. 小静子和彼方学姐独处时会推倒她。
9. 果林在和雪菜独处时会把她推倒。
10. 果林独自开船会迷路(不要纠结怎么迷的路( ͡°ᴥ ͡° ʋ))
11. 艾玛和果林独处时会把果林推倒。
12. 彼方一个人时会睡着，所以她不能独自开船。
13. 爱姐和果林、璃奈中任意一人独处时会把她推倒。
14. 爱姐和璃奈处于同一区域时如果该区域人数≥5就会因为没人注意她们开始偷吃。但前提是该区域不能存在米娅、果林或高咲侑中的任意一人。
15. 璃奈在和爱姐或米娅中任意一人独处时都会推倒她。且如果璃奈身边仅有此二人时会开启三人行。
16. 米娅在和璃奈独处时会开趴。
17. 岚珠在和栞子、米娅、步梦中任意一人独处时会强行将其推倒。
18. 岚珠在身边仅有栞子和米娅时会开启三人行。
19. 岚珠在身边仅有栞子、米娅、高咲侑时会开启四人行。（你和侑就是两个泰迪😂）
20. 栞子和步梦或雪菜独处时会推倒她们。

## 分析

这里只考虑经典的过河问题，也就是只有一个人类，没有考虑一人去一人回或者两人去两人回的换手问题，是考虑之后解空间的子集

在这个前提下，所有的解空间是13C2连乘到3C2，代表左岸选两个人乘船；再乘以12!，代表右岸选一个人乘船回来，总共3.488*10^23种可能，只要条件不互斥就大概率有解

花点时间定义一下成员和条件，用深度优先搜索就可以解决了，算是很基础的内容了，工科学过数据结构应该就能写出来

至于为什么不用动态规划……步梦OJ不会卡你复杂度然后报TLE的

@cﾒ*˶ˆ ᴗ ˆ˵ﾘ

## 其中一组解

```
============ Step 0 ============
====== Left -> Ship ======
Ship:
Yuu  Mia
Left:
Ayumu  Kasumi  Shizuku  Karin  Ai  Kanata  Setsuna  Emma  Rina  Shioriko  LanZhu
====== Right -> Ship ======
Ship:
Yuu
Right:
Mia

============ Step 1 ============
====== Left -> Ship ======
Ship:
Ayumu  Kasumi
Left:
Shizuku  Karin  Ai  Kanata  Setsuna  Emma  Rina  Shioriko  LanZhu  Yuu
====== Right -> Ship ======
Ship:
Mia
Right:
Ayumu  Kasumi

============ Step 2 ============
====== Left -> Ship ======
Ship:
Shizuku  Karin
Left:
Ai  Kanata  Setsuna  Emma  Rina  Shioriko  LanZhu  Yuu  Mia
====== Right -> Ship ======
Ship:
Ayumu
Right:
Kasumi  Shizuku  Karin

============ Step 3 ============
====== Left -> Ship ======
Ship:
Ai  Ayumu
Left:
Kanata  Setsuna  Emma  Rina  Shioriko  LanZhu  Yuu  Mia
====== Right -> Ship ======
Ship:
Kasumi
Right:
Shizuku  Karin  Ai  Ayumu

============ Step 4 ============
====== Left -> Ship ======
Ship:
Kanata  Setsuna
Left:
Emma  Rina  Shioriko  LanZhu  Yuu  Mia  Kasumi
====== Right -> Ship ======
Ship:
Shizuku
Right:
Karin  Ai  Ayumu  Kanata  Setsuna

============ Step 5 ============
====== Left -> Ship ======
Ship:
Emma  Rina
Left:
Shioriko  LanZhu  Yuu  Mia  Kasumi  Shizuku
====== Right -> Ship ======
Ship:
Ai
Right:
Karin  Ayumu  Kanata  Setsuna  Emma  Rina

============ Step 6 ============
====== Left -> Ship ======
Ship:
Shioriko  Mia
Left:
LanZhu  Yuu  Kasumi  Shizuku  Ai
====== Right -> Ship ======
Ship:
Ayumu
Right:
Karin  Kanata  Setsuna  Emma  Rina  Shioriko  Mia

============ Step 7 ============
====== Left -> Ship ======
Ship:
Shizuku  Ayumu
Left:
LanZhu  Yuu  Kasumi  Ai
====== Right -> Ship ======
Ship:
Setsuna
Right:
Karin  Kanata  Emma  Rina  Shioriko  Mia  Shizuku  Ayumu

============ Step 8 ============
====== Left -> Ship ======
Ship:
LanZhu  Kasumi
Left:
Yuu  Ai  Setsuna
====== Right -> Ship ======
Ship:
Mia
Right:
Karin  Kanata  Emma  Rina  Shioriko  Shizuku  Ayumu  LanZhu  Kasumi

============ Step 9 ============
====== Left -> Ship ======
Ship:
Yuu  Mia
Left:
Ai  Setsuna
====== Right -> Ship ======
Ship:
Ayumu
Right:
Karin  Kanata  Rina  Shizuku  LanZhu  Kasumi  Yuu  Mia

============ Step 10 ============
====== Left -> Ship ======
Ship:
Ai  Setsuna
Left:
Ayumu
====== Right -> Ship ======
Ship:
Rina
Right:
Karin  Kanata  Shizuku  LanZhu  Kasumi  Yuu  Mia  Ai  Setsuna

============ Step 11 ============
====== Left -> Ship ======
Ship:
Ayumu  Rina
====== End ======
```

## 余谈

~~花两个小时敲代码算这个，我真无聊~~

~~甚至还开了个Repo，无聊^2~~
