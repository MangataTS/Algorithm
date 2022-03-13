//例题：https://loj.ac/p/133

#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 5e3;

ll tree[N][N<<2];
int n,m;

int lowbit(int x) {
	return -x & x;
}

inline void updata(int x,int y,int k) {
	while(x <= n) {
		int temp = y;
		while(y <= m) {
			tree[x][y] += k;
			y += lowbit(y);
		}
		x += lowbit(x);
		y = temp;
	}
}

inline ll get(int x,int y) {
	ll ans = 0;
	while(x) {
		int temp = y;
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
	scanf("%d%d",&n,&m);
	int a,b,c,d,op;
	while(~scanf("%d",&op)) {
		if(op == 1) {
			scanf("%d%d%d",&a,&b,&c);
			updata(a,b,c);
		}
		else {
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%lld\n",get(c,d)-get(c,b-1)-get(a-1,d) + get(a-1,b-1));
		}
	}
	return 0;
 } 
