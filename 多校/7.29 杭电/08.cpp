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
const int MOD = (int)1e9+7;     // when MOD = 1e9+7, inv2 = 500000004
const int N = (int)3e6+7;
struct Query {
    int l,r,id,tim;
}q[N];
int cg[N],be[N];
bool cmp(const Query& a,const Query& b) {
    return be[a.l] == be[b.l] ? (be[a.r] == be[b.r] ? a.tim < b.tim : a.r < b.r) : a.l < b.l;
}
int cnt[N],a[N],sum[N];
ll ans,out[N];
void add(int p) {
    ans += cnt[sum[p]];
    cnt[sum[p]]++;
//    dd(p),dd(sum[p]),dd(cnt[sum[p]]),de(ans);
}
void sub(int p) {
    cnt[sum[p]]--;
    ans -= cnt[sum[p]];
}
void change(int p,int l,int r) {
    if(l <= p && p <= r) sub(p); 
    swap(a[p],a[p+1]);
    sum[p] = sum[p-1] ^ a[p];
    if(l <= p && p <= r) add(p);
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        ans = 0;
        rep(i,1,n+1) scanf("%d",&a[i]);
        rep(i,1,n+1) sum[i] = a[i] ^ sum[i-1];
        int unit = pow(n,2.0/3);
        rep(i,1,n+1) be[i] = i / unit + 1;
        int d = 0,tim = 0;
        rep(i,0,m) {
            int op; scanf("%d",&op);
            if(op == 1) {
                int l,r;scanf("%d%d",&l,&r);
                q[++d].l = l-1, q[d].r = r;
                q[d].tim = tim, q[d].id = d;
            }else {
                int pos;scanf("%d",&pos);
                cg[++tim] = pos;
            }
        }
        sort(q+1,q+d+1,cmp);
        tim = 0;
        int l = 1, r = 0;
        rep(i,1,d+1) {
            while(tim < q[i].tim) change(cg[tim+1],l,r),tim++;
            while(tim > q[i].tim) change(cg[tim],l,r),tim--;
            while(l < q[i].l) sub(l),l++;
            while(l > q[i].l) add(l-1),l--;
            while(r < q[i].r) add(r+1),r++;
            while(r > q[i].r) sub(r),r--;
            out[q[i].id] = (ll)(r-l+1)*(r-l)/2-ans;
        }
        rep(i,1,d+1) printf("%lld\n",out[i]);
        rep(i,1,n+1) cnt[sum[i]] = 0;
    }
    return 0;
}
