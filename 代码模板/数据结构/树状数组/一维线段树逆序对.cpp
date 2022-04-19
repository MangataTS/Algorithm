#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define endl "\n"
#define PII pair<int,int>
#define INF 0x3f3f3f3f

const int N = 1e6 + 10;
ll a[N],ans[N],n;

struct BIT{
	ll tree[N<<2];
	ll lowbit(ll x) {return -x & x;}
	
	void update(ll x,ll k) {
		while(x < N) {
			tree[x] += k;
			x += lowbit(x);
		}
	}
	ll query(ll x) {
		ll ans = 0LL;
		while(x){
			ans += tree[x];
			x -= lowbit(x);
		}
		return ans;
	}
	void clear(){
		memset(tree,0,sizeof tree);
	}
}bit;



int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i = 1;i <= n; ++i) cin>>a[i],a[i]++;
	
	for(ll i = 1;i <= n; ++i) {
		bit.update(a[i],1LL);
		ans[i] = i - bit.query(a[i]);
	}
	bit.clear();
	for(ll i = n;i >= 1; --i) {
		bit.update(a[i],1LL);
		ans[i] += bit.query(a[i] - 1LL);
	}
	ll res = 0LL;
	for(int i = 1;i <= n; ++i)  
		res += (ans[i] + 1LL) * ans[i] / 2LL;
	cout<<res<<endl;
	
	
	return 0;
}

