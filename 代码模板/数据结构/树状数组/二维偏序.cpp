//例题：  https://www.acwing.com/problem/content/1267/

#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

#define ll long long

const int N = 2e5+10;

ll n,m,ans[N];

pair<ll,ll> a[N];


struct BinaryTree{
	ll tree[N<<2];
	
	ll lowbit(ll x){
		return -x & x;
	}
	
	void update(ll loc,ll k){
		for(;loc < N;loc += lowbit(loc)) tree[loc] += k;
	}
	
	ll query(ll loc){
		ll ans = 0LL;
		for(;loc; loc -= lowbit(loc)) ans += tree[loc];
		return ans;
	}
	
	void build(){
		cin>>n;
		for(int i = 1;i <= n; ++i)
			cin>>a[i].second>>a[i].first;
		sort(a+1,a+1+n);
	}
	
	
}BT;

int main()
{
	BT.build();
	for(int i = 1;i <= n; ++i) {
		ll x = a[i].second,y = a[i].first;
		
		ans[BT.query(x + 1)]++;
		BT.update(x + 1,1);
	}
	for(int i = 0;i < n; ++i)
		cout<<ans[i]<<"\n";
	
}
/*

input:
5
1 1
5 1
7 1
3 3
5 5

output:
1
2
1
1
0


*/