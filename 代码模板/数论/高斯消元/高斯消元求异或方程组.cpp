#include<bits/stdc++.h>
using namespace std;
//----------------自定义部分----------------
#define ll long long
#define mod 1000000007
#define endl "\n"
#define PII pair<int,int>
#define INF 0x3f3f3f3f

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

ll ksm(ll a,ll b) {
	ll ans = 1;
	for(;b;b>>=1LL) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
	}
	return ans;
}

ll lowbit(ll x){return -x & x;}

const int N = 1e2+10;
//----------------自定义部分----------------
int t,n,m,q,a[N][N];

int guss(){
	int c,r;
	for(c=0,r=0;c <= n; ++c){
		int t = r;
		for(int i = r;i < n; ++i){//找到一个不为0的行
			if(a[i][c]) {
				t = i;
				break;
			}
		}
		if(!a[t][c]) continue;
		
		for(int i = 0;i <= n; ++i) swap(a[t][i],a[r][i]);
		
		for(int i = r + 1;i < n; ++i) {//消元
			if(a[i][c])
				for(int j = c;j <= n; ++j) 
					a[i][j] ^= a[r][j];
		}
		r++;
	}
	if(r < n){
		for(int i = r;i < n; ++i) 
			if(a[i][n]) return 1;
		return 2;
	}
	for(int i = n-1;i >= 0; --i) {
		for(int j = i + 1;j < n; ++j) {
			a[i][n] ^= a[i][j] * a[j][n];
		}
	}
	return 0;
}

void slove(){
	cin>>n;
	for(int i = 0;i < n; ++i)
		for(int j = 0;j <= n; ++j)
			cin>>a[i][j];
	
	int t = guss();
	if(t == 1) puts("No solution");
	else if(t == 2) puts("Multiple sets of solutions");
	else {
		for(int i = 0;i < n; ++i) cout<<a[i][n]<<endl;
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	t = 1;
	while(t--){
		slove();
	}
	
	return 0;
}

