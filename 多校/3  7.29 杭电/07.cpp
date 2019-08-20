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
const int N = (int)2e5+7;

int a[N];
int main()
{
	int Q;scanf("%d",&Q);
	while(Q--) {
		int n,m;scanf("%d%d",&n,&m);
		rep(i,0,n) scanf("%d",&a[i]);
		priority_queue<int> qx,qn;
		ll sum = 0,sx = 0;
		rep(i,0,n) {
			sum += a[i];
			if(!qx.empty()) {
				qn.push(-qx.top());
				sx += qx.top();
				qx.pop();
			}
			while(sum - sx > m) {
				qx.push(-qn.top());
				sx += qn.top();
				qn.pop();
			}
			//dd(sum),de(sx);
			printf("%d%c",sz(qx)," \n"[i==n-1]);
			qn.push(a[i]);
		}
	}
	return 0;
}
