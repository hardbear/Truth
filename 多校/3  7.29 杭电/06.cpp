
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
ll p , s;
inline bool check(ll x){
	for(ll i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}
ll mul(ll a,ll b){
	return (__int128)a*b%p;
}
ll qm(ll a,ll b){
	ll s =1;
	while(b){
		if(b&1) s = mul(s,a);
		a= mul(a,a);
		b>>=1;
	}
	return s;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&p);
		s = p-1;
		while(!check(s)) s--;
		ll ans = p-1;
		for(ll i=p-1;i>s;i--)
			ans = mul(ans, qm(i,p-2));
		printf("%lld\n",ans);
	}
	return 0;
}
