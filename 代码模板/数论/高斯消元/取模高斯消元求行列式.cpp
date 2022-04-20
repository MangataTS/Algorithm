#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define endl "\n"
#define PII pair<int,int>
#define INF 0x3f3f3f3f

const int N = 1e2+10;

ll n,a[N][N],delt;

ll ksm(ll a,ll b){
	ll ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

ll inv(ll x){
	return ksm(x,mod-2);
}

void guss(){
	ll ans = 1LL;
	for(int i = 1;i <= n; ++i) {//ö�ٵ�ǰ�����ڼ���
		for(int j = i;j <= n; ++j) {//�ҵ�һ����i�в�Ϊ�յ���
			if(a[j][i]) {
				for(int k = i;k <= n; ++k) //����i,j��
					swap(a[i][k],a[j][k]);
				if(i != j) ans = -ans;
				break;
			}
		}
		if(!a[i][i]) return ;
		//������ǽ���i�����������еĵ�i����գ����һ�������͵ľ���
		for(ll j = i + 1,iv = inv(a[i][i]);j <= n; ++j) {
			ll t = a[j][i] * iv % mod;
			for(ll k = i;k <= n; ++k) {
				a[j][k] = (a[j][k] - t * a[i][k] % mod + mod) % mod;
			}
		}
		//�������i������������У��������ǽ���a[i,i]����ans��
		ans = (ans * a[i][i] + mod) % mod;
	}
	//���˵����ͨ��ȡģ����Ľ����delt��ͬ����ô��˵�����������ʽ������
	//��Ϊ����Ǹ����Ļ������������������ʽ����delt����������ʽ�ľ���ֵ����ô�϶����в�ͬ
	if(ans == delt) cout<<"+"<<endl;
	else cout<<"-"<<endl;
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s;
	int t;
	cin>>t;
	while(t--){
		cin>>n>>s;
		delt = 0LL;
		for(int i = 0,l = s.size();i < l; ++i) {
			delt = (delt * 10LL + s[i] - '0') % mod;
		}
		for(int i = 1;i <= n; ++i) 
			for(int j = 1;j <= n; ++j)
				cin>>a[i][j];
		guss();
	}
	
	
	return 0;
}

