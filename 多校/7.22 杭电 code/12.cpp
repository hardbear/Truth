#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<ll> vi;
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
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define ls (rt<<1)
#define rs (ls|1)
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int mod = (int)998244353;
const int N = (int)1e6+5;
vi a, c1, c2, c3;
ll fac[N<<3], inv[N<<3];
int n;
inline ll qpow(ll a,ll b) {
    ll r=1; 
    for(a%=mod;b; a=a*a%mod, b>>=1) 
        if(b&1) r=r*a%mod;
    return r;
}
inline ll mul(ll a,ll b){   return 1ll*a*b%mod; }
inline ll add(ll a,ll b){   return a*b%mod; }
inline ll C(ll a,ll b){ return mul(fac[a],mul(inv[b],inv[a-b])); }

ll w[2][N*2+5], rev[N*2+5], tmp;
struct NTT{
    vi aa,bb;
    int maxlen = 1000000;
    void ntt(vi &A,int m,int op){
        int n = 1<<m; int w0 = qpow(3,(mod-1)/n);
        w[0][0] = w[1][0] = 1;
        rep(i,1,n) w[0][i] = w[1][n-i] = (ll) w[0][i-1] * w0 %mod;
        rep(i,1,n) rev[i] = (rev[i>>1] >> 1)|(i&1) <<(m-1);
        rep(i,0,n) if(i<rev[i]) swap(A[i], A[rev[i]]);
        for(int i=1;i<n;i<<=1)
            for(int j=0, t=n/(i<<1); j< n; j+= i<<1)
                for(int k=j,l=0;k<j+i;k++,l+=t){
                    ll x = A[k], y = (ll)w[op][l] * A[k+i] %mod;
                    A[k] =(x+y)%mod, A[k+i] = (x-y+mod)%mod;
                }
        if(op) {
            tmp = qpow(n,mod-2);
            rep(i,0,n) A[i] = (ll)A[i]*tmp %mod;
        }
    }
}l;
void fft(vi &a,vi& b,int L,int len){
    l.ntt(a, L ,0), l.ntt(b,L,0);
    rep(i,0,len) a[i] = mul(b[i], a[i]);
    l.ntt(a,L,1);
    rep(i,n,len) a[i] =0;
}
int main()
{
    int T;
    scanf("%d",&T);
    fac[0] =1;
    rep(i,1,3e6+1) fac[i] = mul(fac[i-1], i);
    inv[3000000] = qpow(fac[3000000],mod-2);
    for(int i=3e6-1;i>=0;i--) inv[i] = mul(inv[i+1], i+1);
    while(T--){
        int m;
        scanf("%d%d",&n,&m);
        a.clear(); 
        ll x;
        c1.clear(), c2.clear(), c3.clear();
        int t1=0, t2=0, t3=0;
        rep(i,0,n) scanf("%lld",&x), a.pb(x);
        while(m--){
            int x;
            scanf("%d",&x);
            if(x==1) t1++;
            else if(x==2) t2++;
            else t3++;
        }
        int len = 1, L = 0;
        rep(i,0,n) c1.pb(C(t1-1+i,i));// de(c1[i]);
        rep(i,0,n) c2.pb(0), c3.pb(0);
        c2[0] = 1, c3[0] = 1; c1[0] =1;
        rep(i,1,n/2+(n&1)) c2[i*2] = C(t2-1+i,i);
        rep(i,1,n/3+(n%3!=0)) c3[i*3] = C(t3-1+i,i);
        while(len < 2*n) len<<=1, ++L;
        a.resize(len), c2.resize(len),
        c3.resize(len), c1.resize(len);
        fft(a,c1, L, len);
        fft(a,c2, L, len);
        fft(a,c3, L, len);
        ll ans = 0;
        rep(i,0,n)
            ans ^= (1ll* (i+1)*a[i]);
        printf("%lld\n",ans);
    }
    return 0;
}
