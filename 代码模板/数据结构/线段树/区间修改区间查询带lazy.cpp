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
	
	inline void init_lazy(ll root){//���lazy���
		tree[root].lazy = 0;
	}
	
	inline void union_lazy(ll fa,ll son){//������lazy���
		tree[son].lazy += tree[fa].lazy;
	}
	
	inline void cal_lazy(ll root){//����ǰ�ڵ��lazy��Ȩ������sum��
		tree[root].sum += tree[root].lazy * (tree[root].r - tree[root].l + 1);
	}
	
	inline void push_up(ll root){//���ϸ���
		push_down(root<<1);
		push_down(root<<1 | 1);
		tree[root].sum = tree[root<<1].sum + tree[(root<<1) | 1].sum;
	}
	inline void push_down(ll root){//���¸���
		if(tree[root].lazy != 0){
			cal_lazy(root);//��һ������lazy���
			if(tree[root].l != tree[root].r){//�ڶ���������lazy���
				union_lazy(root,root<<1);
				union_lazy(root,(root<<1) | 1);
			}
			init_lazy(root);//�����������root��lazy��ǣ���Ϊ�Ѿ����ƹ���
		}
	}
	
	void build(ll l,ll r,ll root){//����
		tree[root].l = l;
		tree[root].r = r;
		init_lazy(root);//��ʼ��lazy�ڵ�
		if(l == r) tree[root].sum = a[l];
		else{
			ll mid = ((r+l) >> 1);
			build(l,mid,root<<1);
			build(mid+1,r,(root<<1)+1);
			push_up(root);
		}
	}
	void update(ll l,ll r,ll root,ll add){//������£��� [l,r] ���䶼����add
		push_down(root);//���¸��£���Ϊ�п��ܻ�����lazy�ڵ�û����
		if(tree[root].l >= l && tree[root].r <= r){
			tree[root].lazy = add;//����������ֱ�ӱ��Ϊadd�ͺ���
		}
		else{
			ll mid = ((tree[root].r+tree[root].l) >> 1);
			if(l <= mid) update(l,r,root<<1,add);
			if(r > mid)  update(l,r,(root<<1)+1,add);
			push_up(root);//���ϸ���
		}
	}
	ll query(ll l,ll r,ll root) {//�����ѯ
		push_down(root);//���Ʊ�ǣ����ܻ���lazy�ڵ�û����
		if(tree[root].l >= l && tree[root].r <= r) return tree[root].sum;
		else{
			ll mid = tree[root].l + ((tree[root].r-tree[root].l) >> 1);
			ll ans = 0LL;
			if(l <= mid) ans += query(l,r,root<<1);//������ǲ�ѯ�������߽�ȵ�ǰ�ڵ���м��С����ô˵����ѯ����Ҫ������
			if(r > mid)  ans += query(l,r,(root<<1) + 1);//������ǲ�ѯ���ұ߽�Ҫ�ȵ�ǰ�ڵ���м�ڵ����ô˵����ѯ����Ҫ������
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

Testcase��
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

