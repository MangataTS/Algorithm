# B-树和B+树

## 一、前言
前面学习了平衡二叉树（ $AVL$ 树），我们知道了平衡的概念就是让树尽量的 “胖” ，让它的高度不会线性增长，那么这篇笔记主要是分享 $B$ 树和 $B+$ 树的原理、应用（不涉及代码实现，也许有一天会补上，谁知道呢）


## 二、定义
$B$ 树（又称 $B-$ 树）和 $B+$ 树其实差别不是很大，所以我会着重介绍 $B$ 树，然后最后指出 $B+$ 树的不同点

那么什么是 $B$ 树呢？

> $B$ 树，又称 **多路平衡查找树** ， $B$ 树中 **所有结点的孩子个数的最大值** 称为 $B$ 树的 **阶** ，通常用 $m$ 表示。

这里的多路其实就是指这一颗树可能不只是最多有两颗子树，具体多少颗是由 $B$ 树的阶决定的，作为一颗 $B$ 树应该满足一下要求：

- ①若根节点不是 **叶结点** ，则至少有两个子树（即一个关键字）
- ②除了根结点外，其他每个结点至少有 $\frac{m}{2}$ 个子树，最多有 $m$ 个子树，对应的每一个结点至少有 $\left \lceil \frac{m}{2} -1 \right \rceil$ 个关键字
- ③每一个结点的关键字从左到右升序排列
- ④ $B$ 树是一个严格的多路平衡查找树，它的左右子树的高度室相等的，且叶结点处于同一层（即所有结点的平衡因子都为 $0$ ）

> 上面提到的关键字就是对于每一个结点可能会存在**多个值**的情况，这些值按照升（降）序排列，用于划分子树区间，之前的二叉平衡树我们对于每一个结点只有一个关键字，我们就有两个分支，显然若是有 $m$ 个关键字则会有 $m+1$ 个分支，其实这就是一个简单的区间划分（相邻关键字划分一个区间、前后俩结点单独一个分区）


**PS：这里需要注意一下，在王道的书上是将叶结点（P285页）定义成了不存在的一层，但是在严蔚敏的书上定义的就是最后一层有关键字的结点，比如下图中，王道将第四层定义为叶子节点，严蔚敏的书上认为叶子结点（终端节点）是第三层，而笔者也认为第三层才是叶子节点或者称为终端节点**

![在这里插入图片描述](https://img-blog.csdnimg.cn/cd7e9fb3490b414fbb50089d5a8a0f51.png)



## 三、原理

### 3.1 树的高度

假设一颗二叉树包含 $n(n>=1)$ 个关键字、高度为 $h$ ，阶数为 $m$ 的 $B$ 树

- 至少高度：
既然是至少高度，那么我们应该尽量希望每个结点的关键字都是满即 $m-1$ 的，于是我们得到了如下不等式：

$$
∵ n <=(m-1)(1+m+m^2+……+m^{h-1}) \\
n <= m^h  - 1 \\
∴ h>=log_m(n+1)
$$

- 至多高度：

既然是至多，那么我们尽可能希望每一个结点的关键字都是最少的即 $\left \lceil \frac{m}{2} \right \rceil$ ，前面也提到了根节点可以特殊一下 **最少一个关键字**

那么我们会发现，第一层至少有 $1$ 个结点，第二层至少有 $2$ 个结点，第三层至少有 $2\left \lceil \frac{m}{2} \right \rceil$ 个结点……第 $h+1$ 层至少有 $2\left \lceil \frac{m}{2} \right \rceil ^{h-2}$ 这一层就是不包含关键字的一层，即查找失败的一层，又因为关键字的个数为 $n$ 那么说明第 $h+1$ 层最少 $n+1$ 个结点，于是我们得到：

$$
∵n+1>=2(\left \lceil \frac{m}{2} \right \rceil)^{h-1} \\ 
\\
∴ h <= log_{\left \lceil \frac{m}{2} \right \rceil}\frac{n+1}{2} + 1
$$

假设一颗 $3$ 阶 $B$ 树一共有 $8$ 个关键字，那么其树的高度范围为： $2<=h<=3.17$ 

### 3.2 查找操作
前面也说了 $B$ 树的每一个结点在内部都是有序排列的，并且结点与结点之间也是有一定关系的，在之前的平衡二叉树中，我们有两条路的分支，但是在 $B$ 树的查找中我们需要根据结点的多路分支做决定，那么其实查找操作和前面的平衡二叉树|二叉查找树是一样的啦

- ①先让查找值和 $B$ 树的根节点的第一个关键字比较，若是匹配，则查找成功
- ②若是匹配不成功继续和后面的关键字匹配，若是找到匹配，则匹配成功
- ③若是找到一个大于查找值的关键字，那么就需要往这个关键字和前一个关键字之间的分支结点往下搜索，继续重复上面的关键字匹配操作
- ④若是当前结点最后一个关键字比当前查找的值还小，那么就继续往该结点的最右分支往下继续搜索，重复上面的操作
- ⑤若是结点查找到了空结点，那么说明查找失败


### 3.3 插入操作
先通过上面的定位操作定位到一个查找失败的结点，然后检查该节点的父结点的关键字个数，若是关键字个数小于 $m-1$ 那么说明可以直接插入到该节点（叶子节点），否则的话插入后会引起结点的分裂，因为要维护平衡的关系

分裂的方法：
- 取一个新结点，在插入 $key$ 后的原结点， 从中间位置 $\left \lceil \frac{m}{2} \right \rceil$将其中的关键宇分为两部分
-  **左部分包含的关键宇放在原结点中， 右部分包含的关键宇放到新结点中，中间位置 $\left \lceil \frac{m}{2} \right \rceil$ 的结点插入原结点的父结点** 。
- 若此时导致其父结点的关键字个数也超过了上限，则继续进行这种分裂操作， **直至这个过程传到根结点为止** ，进而导致 $B$ 树高度增 $1$

例如下面的分裂操作：

![在这里插入图片描述](https://img-blog.csdnimg.cn/6d6d3403a7b0414193085dd7ccc63429.png)
我们可以来观察这个过程：

![在这里插入图片描述](https://img-blog.csdnimg.cn/3fd25095c07442e0a62db45e0e5b5266.gif)


实际上就是将 $\left \lceil \frac{m}{2} \right \rceil$ 位置的关键字直接变为其左边和右边关键字的父节点，然后因为要往上贡献一个关键字，这可能会导致父节点层分裂，然后继续向上贡献一个关键字，以此类推，直到停止贡献，或者到达根节点，分裂出新的根，比如在上面的插入 $52$ 后我们再插入 $61、62$ 就会让这棵树的高度拔高一层，流程如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/d04bca36556c4ec8aac7529894bc0fb5.gif)


### 3.4 删除操作
删除操作要更加复杂一点，大体分为两种情况：

#### 3.4.1 删除关键字是非叶子结点

那么我们直接将该结点的前驱（后驱）关键字拿来顶替就行，例如下图删除 $80$ 的情况![在这里插入图片描述](https://img-blog.csdnimg.cn/d428fcb858a145f8a4db06b7a2b89abc.png)



#### 3.4.2 删除关键字是叶子结点
主要分为三种情况：

- 一、如果删除关键字后该结点的关键字个数仍然大于等于  $\left \lceil \frac{m}{2} \right \rceil$ 那么直接删除就完事
- 二、如果删除关键字后该结点的关键字个数等于 $\left \lceil \frac{m}{2}-1 \right \rceil$
	- ①如果兄弟结点够借，即与此结点同一层的临近的右（左）兄弟结点的关键字个数大于等于 $\left \lceil \frac{m}{2} \right \rceil$ 那么就可以将父结点的关键字填充到当前结点，然后再将兄弟结点的关键字移到父结点上
![在这里插入图片描述](https://img-blog.csdnimg.cn/7acf91d492384cacb5db6620f59b256d.png)
	- ②如果兄弟结点不够借，即与此结点同一层的临近的右（左）兄弟结点的关键字个数等于 $\left \lceil \frac{m}{2} -1\right \rceil$ 那么需要将该结结点删除后，和其左兄弟（或者右兄弟）结点以及父结点进行合并操作，若是合并之后超出了关键字的限制，则进行向上分裂操作

我们可以注意到在合并的过程中双亲结点的关键字会减一，那么就会出现下列的情况：
- 如果双亲结点是根结点，且合并后根节点的关键字个数减少为 $0$ , 那么就直接删除该结点，让合并的结点作为新的根节点
-  如果双亲结点不是根结点，且在合并的过程中关键字个数减少到 $\left \lceil \frac{m}{2} -2\right \rceil$ 则该结点需要继续和其兄弟结点进行和并，当然若是出现合并后结点关键字个数超过 $\left \lceil m -1\right \rceil$ 则需要向上分裂，重复以上的操作，直到满足 $B$ 树的要求


## 四、B+树

 > $B+$ 树是从 $B$ 树改进过来的，他和 $B$ 树的主要区别在于：
 > -  $B+$ 树中保存元素的结点都在叶子结点上， **非叶子结点只起到索引** 的作用
 > -  $B+$ 树的所有叶子结点都通过指针链接起来了
 > - $B+$ 树每一个关键字对应一棵子树，假设一个结点最多有 $n$ 个关键字，那么其结点只有 $n$ 颗子树
 > - 一个 $m$ 阶 $B+$ 树除跟节点外，其余结点的关键字个数 $n$ 的范围为 $\left \lceil \frac{m}{2} \right \rceil<=n<=m$ ，根节点的关键字区间为：$1<=n<=m$
 

一个 $m$ 阶的 $B+$ 树满足如下条件：

- ①每一个分支节点最多有 $m$ 颗子树
- ②非根结点至少有两颗子树，其他每个分支结点至少有 $\left \lceil \frac{m}{2} \right \rceil$ 棵子树
- ③结点的子树个数与关键字个数相等
- ④叶结点按照关键字升序（降序）排列，且相邻叶结点通过指针链接起来

比如下面就是一颗 $B+$ 树：
![在这里插入图片描述](https://img-blog.csdnimg.cn/fe9793fefc124d8c8d17b98afccf9d7e.png)
> 为什么B+树的叶子节点要用指针连接起来？
> 这个是和业务场景有关的。$B+$ 树常用来保存数据库索引，数据库`select`数据，不一定只选一条，很多时候会选多条。如果选多条的话， $B$ 树需要进行局部的中序遍历，才能获取到所有符合条件的元素，而且很可能要跨层访问。而$B+$ 树因为所有元素都在叶子节点上，且不同子树的叶子节点已经用指针连接起来了，当需要选择多条数据时，$B+$ 树就会有很大的优势。

## 五、应用

B+树主要用于 **磁盘IO** 的读取， **数据库的索引**

众所周知磁盘 $IO$ 的读取相比 $CPU$ 的处理是非常慢的，所以我们需要尽可能一次性多读取一些数据到内存，然后进行处理，那么我们就希望尽可能减少文件树的高度，但是并不是越低越好，因为假如这颗 $B+$ 树的关键字就等于所有的元素树，那么就变成了一个线性表了，反而会拖慢检索时间，并且我们磁盘每次的读写是由一定限制的，一般磁盘块和页内存都是 $4kb$ 

磁盘有预读机制，每次读的时候都是加载一个磁盘页到内存里面，所以我们的每一个结点关键字的总大小应该是尽可能的贴近磁盘页的大小，这样以来可以达到最好的读写效率也充分的利用了磁盘`cache`的预读机制


参考文章：

- 【经典数据结构】B树与B+树的解释：[https://www.cnblogs.com/makai/p/10861296.html](https://www.cnblogs.com/makai/p/10861296.html)
- B-树木（B树）和B+树：[https://www.cnblogs.com/xuechengmeigui/p/13500628.html](https://www.cnblogs.com/xuechengmeigui/p/13500628.html)
- 深入理解什么是B+树：[https://cloud.tencent.com/developer/article/1425602](https://cloud.tencent.com/developer/article/1425602)
