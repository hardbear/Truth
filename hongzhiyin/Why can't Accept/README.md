# Why can't Accept

## Wrong Answer

- 【1】 询问区间的边界未初始化或赋值
  - 如：询问了端点 0 ，但之前未对端点 0 赋值
- 【1】 没注意数据范围，int 溢出

## Runtime Error

- 【1】 树的总结点数超过 N

## Time limit exceeded

- 【1】 快速幂指数为负数，造成死循环

---

## Solution

- 程序中插入 assert(布尔表达式);  当表达式为假时，返回 Runtime Error 。
