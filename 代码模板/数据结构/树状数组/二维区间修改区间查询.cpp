#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 3e3;

ll n,m;
ll tree[N][N][4];

ll read()
{
	ll X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}

ll write(ll X)
{
	if(X<0) {putchar('-'); X=~(X-1);}
	int s[65],top=0;
	while(X) {s[++top]=X%10; X/=10;}
	if(!top) s[++top]=0;
	while(top) putchar(s[top--]+'0');
}


inline ll lowbit(ll x) {
	return -x & x;
}

void add(ll x,ll y,ll k) {
	for(ll i = x;i <= n; i += lowbit(i)) {
		for(ll j = y;j <= m; j += lowbit(j)) {
			tree[i][j][0] += k;
			tree[i][j][1] += k * x;
			tree[i][j][2] += k * y;
			tree[i][j][3] += k * x * y;
		}
	}
}

void updata(ll x1,ll y1,ll x2,ll y2,ll k) {
	add(x1,y1,k);
	add(x1,y2 + 1,-k);
	add(x2 + 1,y1,-k);
	add(x2 + 1,y2 + 1,k);
}

ll ask(ll x,ll y) {
	ll ans = 0;
	for(ll i = x;i; i -= lowbit(i)) {
		for(ll j = y;j; j -= lowbit(j)) {
			ans += (x + 1) * (y + 1) * tree[i][j][0] 
				-  (y + 1) * tree[i][j][1] 
				-  (x + 1) * tree[i][j][2] 
				+  			 tree[i][j][3];
		}
	}
	return ans;
}

ll query(ll x1,ll y1,ll x2,ll y2) {
	return ask(x1-1,y1-1) - ask(x1 - 1,y2) - ask(x2,y1 - 1) + ask(x2,y2);
}

int main()
{
	n = read();
	m = read();
	int op;
	ll x1,x2,y1,y2,k;
	while(~scanf("%d",&op)) {
		if(op == 1) {
			scanf("%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&k);
			updata(x1,y1,x2,y2,k);
		}
		else {
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			ll kk = query(x1,y1,x2,y2);
			printf("%lld\n",kk);
		}
	}
	
	
	
	return 0;
}
