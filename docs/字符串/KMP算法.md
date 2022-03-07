![img](../image/字符串/KMP算法/字数统计.png)

# KMP算法

## 前言
配套视频：

[www.bilibili.com/video/BV18f4y1L7Uh](https://www.bilibili.com/video/BV18f4y1L7Uh)

KMP算法（也叫看猫片算法(bushi）是Knuth、Pratt 和 Morris 在 1977 年共同发布一个在线性时间(O(n+m))字符串查找或匹配算法，常用于在一个文本串 S 内查找一个模式串 P 的出现位置。

## 一、前缀和后缀

### 1.1前缀

是指的从串首到某个位置i结束的一个子串

### 1.2真前缀

是指的是除开该串本身的前缀

### 1.3后缀

指从某个位置i开始到整个串末尾结束的一个子串

### 1.4真后缀

是指的是除开该串本身的后缀

## 二、前缀函数(next)

给定一个长度为 n的字符串 S，其 **前缀函数** 被定义为一个长度为n的数组 next。 其中next[i]的定义是：

1.如果子串S[0,……,i]有一对相等的真前缀与真后缀：S[0,……,k-1]和S[i-(k-1)……i]，那么next[i]就是这个相等的真前缀的长度(或者真后缀，因为这两个值是相等的)，即next[i] = k;

2.如果不止有一对相等的，那么next[i]就是最长的那个

3.如果没有相等的那么next[i]就是0

假定字符串S为 $abcabca$

那么next数组的值为

| next[i] | 值   |
| ------- | ---- |
| next[0] | -1   |
| next[1] | 0    |
| next[2] | 0    |
| next[3] | 0    |
| next[4] | 1    |
| next[5] | 2    |
| next[6] | 3    |
| next[7] | 4    |

这里就能看出字符串abcabca的前缀函数数组为[-1,0,0,0,1,2,3,4],注意一下这里的next[0]是用于辅助计算前缀值的，next数组求出的前缀值是求的长度为i的字符串的最大真前缀长度，也就是最大i-1

不难发现next数组的值的增加是一步一步的，也就是相邻的两个next值的差值最大为1，也就是说匹配成功后我们可以接着使用这个数据，失败则通过我们的next数组进行回溯，因为前后缀相同，我们不难得出下面的计算next数组的代码

```cpp
const int N = 1e6+10;

int nextt[N];
char S[N];
int len1;

void get_next() {
	int i = 0,j = -1;
	nextt[0] = -1;//这个是辅助计算next值得
	while(i < len1) {
		if(j == -1 || S[i] == S[j]) nextt[++i] = ++j;//如果匹配成功或者第一次匹配
		else j = nextt[j];	//否则j进行回溯
	}
	
}
```

KMP最核心的东西也就是 **next数组** ，请一定要领会

## 三、KMP字符串匹配

匹配的方式和朴素算法一致，但是每当匹配失败时，子串的指针移到next[i]的位置上去

代码实现

```cpp
//S表示的是子串(匹配串)，T表示的是主串(文本)
int kmp(){//返回的是子串在主串中存在的次数 
    int cnt = 0;//表示的是子串在主串中存在的次数 
    int i = 0,j = 0;
    get_next();
    while(i < len2)
    {
        if(j == -1 || T[i] == S[j])
        　　i++,j++;
        else 
        　　j = nextt[j];
        if(j == len1)//表示的是子串在主串中存在的次数 
        　　j=0,cnt++;//子串指针归零 
    }
    return cnt;
}
```

### 3.1 完整的KMP代码如下

以fjutoj2149为例

```cpp
#include<bits/stdc++.h>
using namespace std;

const  int N = 1e6+10;

char S[N],T[N];
int nextt[N];
int len1,len2;

void get_next() {
    int i = 0,j = -1;
    nextt[0] = -1;
    while(i < len2) {
        if(j == -1 || S[i] == S[j]) nextt[++i] = ++j;
        else j = nextt[j];
    }
}

int kmp() {
    int i = 0,j = 0;
    get_next();
    while(i < len1) {
        if(j == -1 || S[j] == T[i]) ++i,++j;
        else j = nextt[j];
        if(j == len2) return i-len2;
    }
    return -1;
}


int main()
{
    while(~scanf("%s %s",T,S)) {
        len1 = strlen(T);
        len2 = strlen(S);
        printf("%d\n",kmp());
    }
    return 0;
}
```




## 四、关于KMPのnext

### 4.1 周期问题

通过next数组我们可以求得字符串的最小周期

先说结论 **next数组，i-next[i]就能得到前i个字符组成的字符串的最小循环周期长度**  

原理：我们假设求解的字符串是有一个不成循环的尾部(这个尾部可以为0)，那么前缀函数求解的时候，条件是前缀和后缀最长相等数，我们通过n-next[n]也就是减去了多段循环节(可能为0)+尾部，剩下的就是最小循环周期，大家可以动手验算一下

### 4.2 压缩优化

对于这种子串，aaaaab，通过前缀函数求得[-1,0,1,2,3,4,0]，如果最后一个a匹配失败，我们正常的kmp匹配操作会不断让j=next[j]，此时对于这个子串则是会让j变为

j = 4 -> j = 3 -> j = 2 -> j = 1 -> j = 0，其实我们会发现对于这种情况我们其实可以直接让最后一个a直接指向0，这样在我们匹配的过程中就能减少很多不必要的操作

代码实现:

```cpp
const int N = 1e6+10;

int nextt[N];
char S[N];
int n;

void get_next() {
	int i = 0,j = -1;
	nextt[0] = -1;//这个是辅助计算next值得
	while(i < n) {
		if(j == -1 || S[i] == S[j]) {
			++i,++j;
			if(S[i] == S[j]) nextt[j] = next[i];//压缩路径
			else nextt[i] = j;
		}
		else j = nextt[j];	//否则j进行回溯
	}
}
```

 注意的是 **并不是每一个题目都要使用路径压缩** ，例如next数组在求解最小周期的时候是有用的，如果使用压缩路径之后中间的next值就不能帮助我们计算最小周期

## 五、附上例题

| 题目连接                                                     | 题目名                       |
| ------------------------------------------------------------ | ---------------------------- |
| [http://120.78.128.11/Problem.jsp?pid=2149](http://120.78.128.11/Problem.jsp?pid=2149) | KMP算法                      |
| [https://acm.dingbacode.com/showproblem.php?pid=1711](https://acm.dingbacode.com/showproblem.php?pid=1711) | Number Sequence              |
| [https://acm.dingbacode.com/showproblem.php?pid=1686](https://acm.dingbacode.com/showproblem.php?pid=1686) | Oulipo                       |
| [https://acm.dingbacode.com/showproblem.php?pid=2087](https://acm.dingbacode.com/showproblem.php?pid=2087) | 剪花布条                     |
| [https://acm.dingbacode.com/showproblem.php?pid=2203](https://acm.dingbacode.com/showproblem.php?pid=2203) | 亲和串                       |
| [https://acm.dingbacode.com/showproblem.php?pid=3336](https://acm.dingbacode.com/showproblem.php?pid=3336) | Count the string             |
| [https://acm.dingbacode.com/showproblem.php?pid=2406](https://acm.dingbacode.com/showproblem.php?pid=2406) | Power Strings                |
| [http://poj.org/problem?id=2752](http://poj.org/problem?id=2752) | Seek the Name, Seek the Fame |
| [https://acm.dingbacode.com/showproblem.php?pid=1358](https://acm.dingbacode.com/showproblem.php?pid=1358) | Period                       |
| [https://acm.dingbacode.com/showproblem.php?pid=1867](https://acm.dingbacode.com/showproblem.php?pid=1867) | A + B for you again          |
| [https://acm.dingbacode.com/showproblem.php?pid=3746](https://acm.dingbacode.com/showproblem.php?pid=3746) | Cyclic Nacklace              |
| [http://120.78.128.11/Problem.jsp?pid=2655](http://120.78.128.11/Problem.jsp?pid=2655) | 娜娜梦游仙境系列——村民的怪癖 |