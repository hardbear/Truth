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

const int mod = (int)998244353;
const int N = (int)1e7+2;
const int inv2 =(mod+1)/2; 
const int maxn = 1e7+5;
template <class T>
void read(T &x) {
    static char ch;static bool neg;
    for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
    for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
    x=neg?-x:x;
}
int phi[maxn], f[maxn], p[maxn], cnt;
inline int add(int a,int b){
    if((a+=b)>=mod) a-=mod;
    return a;
}
inline int mul(int a,int b){
    return 1ll*a*b%mod;
}
void shai(int N){
    phi[1]=1;
    rep(i,2,N+1){
        if(!f[i]){
            p[++cnt] = i;
            f[i] = i;
            phi[i] = i-1;
        }
        for(int j=1,k;j<=cnt&&p[j]<=f[i]&&i*p[j]<=N;j++){
            f[k=i*p[j]] = p[j];
            if(p[j] < f[i])
                phi[k] = mul(phi[i],phi[p[j]]);
            else phi[k] = mul(phi[i], p[j]);
        }
    }
}

int main()
{
    shai(N+1);
    int T;
    scanf("%d",&T);
    while(T--){
        __int128 n;
        read(n);
        __int128 r=1, l=1e7;
        //for(r=1;r*r*r<=n;r++);
        while(r<=l){
            __int128 mid = l+r>>1;
            if(mid*mid*mid > n) l = mid-1;
            else r = mid+1;
        }
        r = l;
        l=r*r*r - 1;
        int ans = 0;
        for(int i=1;i*i<=r;i++)
        if(r%i==0){
            __int128 s=n/i-l/i;
            s= s*phi[i]%mod;
            //de((int)s);
            ans = add(ans,(int)s);
            int j = r/i;
            if(j==i) break;
            s=n/j - l/j;
            s = s*phi[j]%mod;
            ans = add(ans,(int)s);
        }
        r--;
         for(int d=1;d<=r;d++){
            int t= (r/d);
            int s = mul(mul(d,t),mul(t+1,2*t+1));
            s=mul(s,inv2);
            s = add(s,mul(3*(t+1),mul(t,inv2)));
            s = mul(phi[d],add(s,t));
            ans = add(ans,s); 
        }
        printf("%d\n", ans);
    }
    return 0;
}
