#include<bits/stdc++.h>

using namespace std;
#define ll long long 

const int N = 5e3+10;
ll tree[N][N];
ll t,n,m;

ll lowbit(ll x) {
	return -x & x;
}

void add(ll x,ll y,ll k) {//单点更新 
	while(x <= n) {
		ll temp = y;
		while(y <= m) {
			tree[x][y] += k;
			y += lowbit(y);
		}
		x += lowbit(x);
		y = temp;
	}
}

void updata(ll x1,ll y1,ll x2,ll y2,ll k) {//矩阵更新 
	add(x1,y1,k);
	add(x1,y2 + 1,-k);
	add(x2 + 1,y1,-k);
	add(x2 + 1,y2 + 1,k); 
}

ll query(ll x,ll y) {//单点查询
	ll ans = 0;
	while(x) {
		ll temp = y;
		while(y) {
			ans += tree[x][y];
			y -= lowbit(y);
		}
		x -= lowbit(x);
		y = temp;
	}
	return ans;
}


int main()
{
	ll x1,x2,y1,y2,k;
	memset(tree,0,sizeof tree);
	scanf("%lld%lld",&n,&m);//n X m的矩阵 
	int op;
	while(~scanf("%d",&op)) {
		if(op == 1) {
			scanf("%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&k);
			updata(x1,y1,x2,y2,k);
		}
		else {
			scanf("%lld%lld",&x1,&y1);
			ll kk = query(x1,y1);
			printf("%lld\n",kk);
		}
	}
	return 0;
}
