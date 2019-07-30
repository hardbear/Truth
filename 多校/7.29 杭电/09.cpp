#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int MOD = (int)1e9+7;
const int N = (int)5e3+7;
const int M = (int)1e7+7;

// var //

struct FastIO {
	static const int S = 1310720;
	int wpos; char wbuf[S];
	FastIO() : wpos(0) {}
	inline int rchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len) return -1;
		return buf[pos++];
	}
	inline int rint() {
		int s = 1, c = rchar(), x = 0;
		while (c <= 32) c = rchar();
		if (c == '-') s = -1, c = rchar();
		for (; '0' <= c && c <= '9'; c = rchar())
			x = x * 10 + c - '0';
		return x * s;
	}
} io;

struct MinCost {
	struct Edge {
		int s, t, cap, cost, net;
		Edge () {}
		Edge(int s, int t, int cap, int cost, int net) : s(s), t(t), cap(cap), cost(cost), net(net) {}
	} e[M<<1];
	ll dis[N];
	queue <int> Q;
	int n, no, pre[N], vis[N], head[N];
	void init(int _n) {
		n = _n, no = 0;
		memset(head, -1, sizeof(head[0]) * n);
	}
	void addEdge(int s, int t, int cap, int cost) {
	//	dd(s),dd(t),dd(cap),de(cost);
		e[no] = Edge(s, t, cap, cost, head[s]), head[s] = no++;
		e[no] = Edge(t, s, 0, -cost, head[t]), head[t] = no++;
	}
	bool bfs(int S, int T) {
		rep(i, 0, n) pre[i] = -1, dis[i] = LINF, vis[i] = false;
		dis[S] = 0, vis[S] = true, Q.push(S);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = head[u]; ~i; i = e[i].net) {
				int v = e[i].t;
				if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
					pre[v] = i, dis[v] = dis[u] + e[i].cost;
					if (!vis[v]) vis[v] = true, Q.push(v);
				}
			}
			vis[u] = false;
		}
		return dis[T] != LINF;
	}
	pair<ll, ll> solve(int S, int T) {
		ll maxflow = 0, mincost = 0;
		if (bfs(S, T)) {
			ll flow = LINF;
			for (int i = pre[T]; ~i; i = pre[e[i].s]) flow = min(flow, (ll)e[i].cap);
			for (int i = pre[T]; ~i; i = pre[e[i].s]) e[i].cap -= flow, e[i^1].cap += flow;
			maxflow += flow, mincost += flow * dis[T];
		}
		return mp(maxflow, mincost);
	}
}mc;
int a[N];
void solve() {
	int n,k;
	n = io.rint(),k = io.rint();
	rep(i,1,n+1) {
		a[i] = io.rint();
	}
	a[0] = 0;
	int S = 0,T = 2*n + 1;
	mc.init(T+1);
	deque<int> q;
	rep(i,0,n+1) {
		int mn = INF;
		rep(j,i+1,n+1) {
			if(a[j] >= a[i] && a[j] < mn) {
				if(i) mc.addEdge(2*i-1,2*j-1,1000,0);
				mc.addEdge(2*i,2*j-1,1000,0);
				mn = min(a[j],mn);
			}
		}
		if(i) mc.addEdge(2*i,T,1000,0);	
	}
/*
	per(i,0,n+1) {
		while(!q.empty() && a[i] <= a[q.front()]) 
			dd(i),de(q.front());
			if(i) mc.addEdge(2*i-1,2*q.front()-1,1000,0);
			mc.addEdge(2*i,2*q.front()-1,1000,0);
		}
		if(i) mc.addEdge(2*i,T,1000,0);
		q.push_front(i);
	}
	*/
	rep(i,1,n+1) mc.addEdge(2*i-1,2*i,1,-a[i]);
	int ans = 0;
	rep(i,0,k) {
		pair<ll,ll> t = mc.solve(S,T);
		ans += t.se;
	}
	printf("%d\n",-ans);
}
int main()
{
	int T;scanf("%d",&T);
	while(T--) {
		solve();
	}
}
