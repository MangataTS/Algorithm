#include<bits/stdc++.h>
using namespace std;
//----------------自定义部分----------------
#define ll long long
#define mod 1000000007
#define endl "\n"
#define PII pair<int,int>
#define INF 0x3f3f3f3f
const double EPS = 1e-8;

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
int t,n,m,q;
double a[N][N];

void out(){
	for(int i = 0;i < n; ++i){
		for(int j = 0;j <= n; ++j){
			printf("%.2lf ",a[i][j]);
		}
		puts("");
	}
	puts("");
}

int guss(){
	int c,r;
	for(c=0,r=0; c < n; ++c){
		
		int t = r;
		for(int j = r + 1;j < n; ++j) 
			if(fabs(a[j][c]) > fabs(a[t][c])) 
				t = j;
		if(fabs(a[t][c]) < EPS) continue;//当前已经被消元过了
		
		for(int i = c; i <= n; ++i) swap(a[t][i],a[r][i]);//将绝对值最大的这一行与最上面的交换
		for(int i = n;i >= c; --i) a[r][i] /= a[r][c];//将当前这个方程的第c列系数变为1
		//将下面的方程的第c列全部消为0
		for(int i = r + 1;i < n; ++i){
			if(fabs(a[i][c]) > EPS){//如果需要消元的话
				for(int j = n;j >= c; --j)
					a[i][j] -= a[r][j] * a[i][c];//方程相加减
			}
		}	
		r++;
	}
	if(r < n){
		for(int i = r;i < n; ++i)
			if(fabs(a[i][n]) > EPS) 
				return 2;
		return 1;
	}
	//最后一部从下往上递推方程的每一个解
	for(int i = n-1;i >= 0; --i) {
		for(int j = i + 1;j <= n; ++j)
			a[i][n] -= a[i][j] * a[j][n];
		if(fabs(a[i][n]) < EPS) a[i][n] = 0.0;//防止-0.0的情况
	}
	return 0;
}

void slove(){
	cin>>n;
	for(int i = 0;i < n; ++i)
		for(int j = 0;j <= n; ++j)
			scanf("%lf",&a[i][j]);
	
	int t = guss();
	if(t == 1) puts("Infinite group solutions");
	else if(t == 2) puts("No solution");
	else{
		for(int i = 0;i < n; ++i)
			printf("%.2lf\n",a[i][n]);
	}
	
}

int main()
{
	//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	t = 1;
	while(t--){
		slove();
	}
	
	return 0;
}

