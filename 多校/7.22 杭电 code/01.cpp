/*Sodaine*/
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
//INF = 1 061 109 567 ; INF + INF = 2 122 219 134 ;
//LINF = 4 557 430 888 798 830 399 ; LINF + LINF = 9 114 861 777 597 660 798 ;
const int INF = 0x3f3f3f3f;     // -INF: 0xc0   abs(-INF) = INF + 1
const ll LINF = 0x3f3f3f3f3f3f3f3f;
/*}}}*/                         // zr, zm
const int MOD = (int)998244353;     // when MOD = 1e9+7, inv2 = 500000004
const int N = (int)103;
inline void add(int &a,int b) {
//    a += b;
    if((a += b) >= MOD) a -= MOD;
}
inline bool check(int b,int c,int d,int l,int x) {
    int cnt = 1;
    if(b >= l) cnt++;
    if(c >= l) cnt++;
    if(d >= l) cnt++;
    return cnt == x;
}
int dp[2][N][N][N];
vector<pii> ban[N];
int main()
{
    int T;scanf("%d",&T);
    while(T--) {
        int n,m;scanf("%d%d",&n,&m);
        rep(i,0,n+1) ban[i].clear();
        rep(i,0,m) {
            int l,r,x;scanf("%d%d%d",&l,&r,&x);
            ban[r].pb(mp(l,x));
        }
        memset(dp,0,sizeof(dp));
        dp[0][0][0][0] = 1;
        int ans = 0;
        rep(a,0,n+1) {
            rep(b,0,a+1) rep(c,0,max(b,1)) rep(d,0,max(c,1)) {
                dp[~a&1][b][c][d] = 0;        
            }
            rep(b,0,max(a,1)) rep(c,0,max(b,1)) rep(d,0,max(c,1)) {
                bool f = 1;
                rep(i,0,sz(ban[a])) {
                    f &= check(b,c,d,ban[a][i].fi,ban[a][i].se);
                }
                if(!f) {
                    dp[a&1][b][c][d] = 0;
                    continue;
                }
                int t = dp[a&1][b][c][d];
                add(dp[~a&1][b][c][d],t);
                add(dp[~a&1][a][c][d],t);
                add(dp[~a&1][a][b][d],t);
                add(dp[~a&1][a][b][c],t);
                if(a == n) add(ans,t);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
