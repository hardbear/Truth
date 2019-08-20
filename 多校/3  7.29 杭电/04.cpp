
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
const int N = (int)-1;
const int maxn = 2e5+5;
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

int n, m, k, f[maxn], nn , v0;
int a[maxn];
vector < ll > V;
ll s[maxn];
inline int qry(int x){
	int ans = -0x3f3f3f3f;
	x= nn-x+1;
	while(x){
		ans = max(f[x],ans);
		x-= x&-x;
	}
	return ans;
}
inline void upd(int x,int s){
	x = nn - x+ 1;
	for(;x<=nn; x+=(x&-x))
		 f[x] = max(f[x], s);
}
inline int check(ll x){
	rep(i,1,nn+1) f[i] = -0x3f3f3f3f;
	upd(v0,0);
	int ans = 0;
	rep(i,1,n+1){
		ll m = s[i] - x;
		int t = lower_bound(all(V),m) - V.begin() + 1;
		int sum = qry(t) + 1, tt=lower_bound(all(V),s[i]) - V.begin() + 1;
		upd(tt,sum);
		ans = max(ans,sum);
	}
	return ans;
}
int main()
{
	int T;
	T = io.rint();
	while(T--){
		n = io.rint();
		k = io.rint();
		V.clear();
		rep(i,1,n+1)
			a[i] = io.rint(), s[i] = s[i-1] + a[i], V.pb(s[i]);
		V.pb(0);
		sort(all(V));
		V.erase(unique(all(V)),V.end());
		v0 = lower_bound(all(V),0) - V.begin() + 1;
		nn = sz(V);
		ll l = -1e15-1, r=1e9+1;
		while(l<=r){
			ll mid = (l+r)/2;
			if(check(mid)>=k) r=mid-1;
			else l = mid+1;
		}
		printf("%lld\n", r+1);
	}
	return 0;
}
