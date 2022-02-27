# DFS和BFS

# 配套视频
[https://www.bilibili.com/video/BV1RD4y1F7Fq](https://www.bilibili.com/video/BV1RD4y1F7Fq)
# 二、DFS（深度优先搜索）

## 问题引出

我们想知道在一个迷宫里面是否有一个路线能让我们从起点走到终点，无论改路径是否是最优的

例题：[http://acm.mangata.ltd/p/E427](http://acm.mangata.ltd/p/E427)

## 思路

由于我们只想知道这个迷宫有没有解，所以我们期望能够一条路就走到终点，然后保存这个信息，但是这个过程中我们很可能就走到了一个死路，正常的思维会怎么想呢？退回来，一只退回到有没走过的岔路口，然后走向另一个方向，然后重复这个过程直到找到了终点，或者说所有的点都走过了，那么我们就退出，这就是深度优先的思想。

## 重点

重点理解一下这个递归的过程，递的过程其实就是往下一个地方走，归的过程就是走到死胡同了，我们要返回到岔路口。这里归的过程也就是**回溯**，回溯的状态是非常关键的，有的时候我们要利用回溯这个过程记录一些信息，比如**路径**、**权值和**等，所以DFS不仅能运用到路径的搜索，在很多地方都能用到



## 实现的方式

实现的方式也就是通过递归实现，不断向下探索，然后遇到死胡同就归上来

给出一个模板：

```cpp
void dfs(int x,int y){//x、y表示的是坐标点的位置
	if(vis[x][y]) return;//这个表示已经访问过了
	vis[x][y] = true;//如果没有访问过，那么我们现在访问过了
	ans++;
	for(int i = 0;i < 4; ++i) {//这里就是往上下左右四个方向遍历
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!vis[nx][ny] && nx > 0 && nx <= H && ny > 0 && ny <= W && mp[nx][ny] != '#') {//我们这里就是看下一个位置是否能递归访问
			dfs(nx,ny);
		}
	}
}
```



# 三、BFS（广度优先搜索）

## 问题引出

我们想知道在一个迷宫里面是否有一个路线能让我们从起点走到终点，并且路线是最优的，然后输出最优路径的长度

例题：[http://acm.mangata.ltd/p/E427](http://acm.mangata.ltd/p/E427)

## 思路

由于我们现在的这个问题转变为了最优路径求解，所以我们经量就不要使用DFS（因为递归的过程很耗时间），这个时候就需要BFS（广度优先搜索），什么意思呢，我们尽可能地找到靠近我们当前这个点的周围的点。然后将这个周围的点加入我们即将探寻的这个**队列**里面。这个过程大概就是一层一层的去访问这些可行的点，这也就是广度优先搜索。

1.我们先将起点放进队列，然后逐步去找起点周围的点，然后将这个周围的点也放进队列，然后将起点移出队首。

2.我们再取出当前队首的点，然后重复上面的过程，直到取出的点是终点。

## 重点

重点就是这个入队的过程的理解，你要知道广度优先搜索的工作方式是优先将**靠近当前点的周围的点放进队列**，然后逐步去访问操作，在后续的过程中我们可以根据这个思维去优化SPFA算法以及优化。

## 实现方式

实现方式也就是队列的应用，主要理解的这个思路是**广度优先**

```cpp
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
int bfs(int sx,int sy){
    int cnt = 0;
    q.push(node{sx,sy,0});//压入队列
    while(!q.empty()){//队列不为空
        node p=q.top();//取出队列第一个元素
        q.pop();//弹出
        if(p.x == ex,p.y == ey){//找到终点然后直接返回路径的长度
            return p.k;
        }
        if(vis[p.x][p.y]) continue;//已去过就不去了
        vis[p.x][p.y] = true;//标记已去过
        for(int i=0;i < 4;++i){
           int nx = x + dx[i];
           int ny = y + dy[i];
           if(check(nx,ny)){
               que.push(node{nx,ny,p.k+1});
           }
        }
    }
    return -1;//没有路径的
}
```



# 四、总结两种方式

## 维护方式

DFS用递归的形式，用到了栈结构，先进后出。

BFS选取状态用队列的形式，先进先出。

## 复杂度

DFS的复杂度与BFS的复杂度大体一致，不同之处在于遍历的方式与对于问题的解决出发点不同，DFS适合目标明确，而BFS适合大范围的寻找。

## 思想

思想上来说这两种方法都是穷竭列举所有的情况。但是不同的是，DFS可以通过剪枝等操作优化，而BFS必须穷举出所有情况





# 我的堆优化加链式前向星优化的迪杰斯特拉的板子

这个算法也就是BFS加上了一个贪心的思想，然后加上了一个链式前向星的优化最后写出来的一个最短路算法。只要你理解了BFS这个算法也就不会有什么问题。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>//
using namespace std;
const int N=2e5+5;//数据范围
struct edge{//存储边
    int u,v,w,next;//u为起点，v为终点，w为权值，next为前继
};
edge e[N];
int head[N],dis[N],n,m,s,cnt;//head为链中最上面的，dis表示当前答案，n为点数，m为边数，s为起点，cnt记录当前边的数量
bool vis[N];//vis表示这个点有没有走过
struct node{
    int w,to;//w表示累加的权值，to表示到的地方
    bool operator <(const node &x)const{//重载“<”号
        return w>x.w;
    }
};
priority_queue<node>q;//优先队列（堆优化）
void add(int u,int v,int w){
    ++cnt;//增加边的数量
    e[cnt].u=u;//存起点
    e[cnt].v=v;//存终点
    e[cnt].w=w;//存权值
    e[cnt].next=head[u];//存前继
    head[u]=cnt;//更新链最上面的序号
}//链式前向星（加边）
void Dijkstra(){
    memset(dis,0x3f3f3f3f,sizeof(dis));//初始化，为dis数组附一个极大值，方便后面的计算
    dis[s]=0;//起点到自己距离为0
    q.push(node{0,s});//压入队列
    while(!q.empty()){//队列不为空
        node x=q.top();//取出队列第一个元素
        q.pop();//弹出
        int u=x.to;//求出起点
        if(vis[u]) continue;//已去过就不去了
        vis[u]=true;//标记已去过
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].v;//枚举终点
            if(dis[v]>dis[u]+e[i].w){//若中转后更优，就转
                dis[v]=dis[u]+e[i].w;//更新
                q.push(node{dis[v],v});//压入队列
            }
        }
    }
}
int main(){
    int u,v,w = 1;
    s = 1;
    scanf("%d%d",&n,&m);//输入
    for(int i=1;i<=m;++i){
        scanf("%d%d",&u,&v);
        add(u,v,w);
        add(v,u,w);
    }
    Dijkstra();//DJ
    printf("%d\n",dis[n]-1);//输出1-n的最短路
    return 0;
}
```

