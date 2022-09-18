#include<bits/stdc++.h>
using namespace std;
//----------------自定义部分----------------
#define ll long long
#define mod 1000000007
#define endl "\n"
#define PII pair<int,int>
#define INF 0x3f3f3f3f
const int N = 2e6+10;
//----------------自定义部分----------------
int n,m,q,d[N],vis[N];
vector<int> V[N],ans;

bool topsort(){
	queue<int> que;
	for(int i = 1;i <= n; ++i) {
		if(!d[i]) que.push(i);
	}
	while(!que.empty()){
		int t = que.front();
		que.pop();
		ans.push_back(t);
		for(int i = 0,l = V[t].size();i < l; ++i){
			d[V[t][i]]--;
			if(!d[V[t][i]]) que.push(V[t][i]);
		}
	}
	return ans.size()==n;
}

void slove(){
	if(topsort()){
		for(int i = 0;i < n; ++i) {
			cout<<ans[i]<<" \n"[i==n-1];
		}
	}
	else{
		cout<<"-1"<<endl;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	cin>>n>>m;
	int u,v;
	for(int i = 0;i < m; ++i) {
		cin>>u>>v;
		V[u].push_back(v);
		d[v]++;
	}
	slove();
	
	return 0;
}


