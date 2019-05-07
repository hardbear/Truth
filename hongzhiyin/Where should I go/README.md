# Where should I go

## combinatorics

### 组合数求和

- 二项式展开 $$\large (a+b)^n = \sum_{i=0}^{n}C_n^ia^ib^{n-i}$$

## data structures

### 线段覆盖

- 逆向思维，线段覆盖点 转化为 被点与点构成的线段完全覆盖

- 保证右端点被覆盖时，树状数组加入左端点

## dynamic programming

### 实现转移方程

- 想象二维、三维立方块

- 每个方块由哪些方块转移而来

- 初始方块如何设置

## Number Theory

### gcd / lcm

- $$gcd(a, b) = gcd(b-a, b) = gcd(b-a, a)$$

- 分解质因数 $$O(n\sqrt{n})$$

- 枚举因数的倍数 $$O(nlogn)$$

### 多项式操作

- 操作后多项式与原始多项式比较，化为 dp 转移式
