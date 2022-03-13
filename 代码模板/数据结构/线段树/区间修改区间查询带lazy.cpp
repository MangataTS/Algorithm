#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

#define ll long long

const int N = 1e5+10;

ll a[N];

struct Tnode{
	ll l,r,sum,lazy;
};

struct SegmentTree{
	
	Tnode tree[N<<2];
	
	inline void init_lazy(ll root){//清空lazy标记
		tree[root].lazy = 0;
	}
	
	inline void union_lazy(ll fa,ll son){//向下推lazy标记
		tree[son].lazy += tree[fa].lazy;
	}
	
	inline void cal_lazy(ll root){//将当前节点的lazy的权计算如sum中
		tree[root].sum += tree[root].lazy * (tree[root].r - tree[root].l + 1);
	}
	
	inline void push_up(ll root){//向上更新
		push_down(root<<1);
		push_down(root<<1 | 1);
		tree[root].sum = tree[root<<1].sum + tree[(root<<1) | 1].sum;
	}
	inline void push_down(ll root){//向下更新
		if(tree[root].lazy != 0){
			cal_lazy(root);//第一步计算lazy标记
			if(tree[root].l != tree[root].r){//第二步，下推lazy标记
				union_lazy(root,root<<1);
				union_lazy(root,(root<<1) | 1);
			}
			init_lazy(root);//第三步，清空root的lazy标记，因为已经下推过了
		}
	}
	
	void build(ll l,ll r,ll root){//建树
		tree[root].l = l;
		tree[root].r = r;
		init_lazy(root);//初始化lazy节点
		if(l == r) tree[root].sum = a[l];
		else{
			ll mid = ((r+l) >> 1);
			build(l,mid,root<<1);
			build(mid+1,r,(root<<1)+1);
			push_up(root);
		}
	}
	void update(ll l,ll r,ll root,ll add){//区间更新，在 [l,r] 区间都加上add
		push_down(root);//向下更新，因为有可能还存在lazy节点没更新
		if(tree[root].l >= l && tree[root].r <= r){
			tree[root].lazy = add;//这里的懒标记直接标记为add就好了
		}
		else{
			ll mid = ((tree[root].r+tree[root].l) >> 1);
			if(l <= mid) update(l,r,root<<1,add);
			if(r > mid)  update(l,r,(root<<1)+1,add);
			push_up(root);//向上更新
		}
	}
	ll query(ll l,ll r,ll root) {//区间查询
		push_down(root);//下推标记，可能还有lazy节点没更新
		if(tree[root].l >= l && tree[root].r <= r) return tree[root].sum;
		else{
			ll mid = tree[root].l + ((tree[root].r-tree[root].l) >> 1);
			ll ans = 0LL;
			if(l <= mid) ans += query(l,r,root<<1);//如果我们查询区间的左边界比当前节点的中间点小，那么说明查询区间要往左走
			if(r > mid)  ans += query(l,r,(root<<1) + 1);//如果我们查询的右边界要比当前节点的中间节点大，那么说明查询区间要往右走
			return ans;
		}
	}
}Tree;

int n,m;

int main()
{
	cin>>n>>m;
	for(int i = 1;i <= n; ++i) cin>>a[i];
	Tree.build(1,n,1);
	ll op,k,l,r;
	for(int t = 1;t <= m; ++t){
		cin>>op>>l>>r;
		if(op == 1){
			cin>>k;
			Tree.update(l,r,1,k);
		}
		else{
			cout<<Tree.query(l,r,1)<<endl;
		}
	}
}
/*

Testcase：
input

5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4

output:

11
8
20


 */

