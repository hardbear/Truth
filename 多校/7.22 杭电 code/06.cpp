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
const int MOD = (int)1e9+7;     // when MOD = 1e9+7, inv2 = 500000004
const int N = (int)5e6+7;

struct NODE {
    int ch[26];
    int len,fa;
    void clear() {
        memset(ch,0,sizeof(ch));
        len = 0;
    }
}dian[N<<1];
int last,tot;
void init() {
    last = 1,tot = 1;
    dian[1].clear();
}
void add(int c) {
    int p = last;int np = last = ++tot;
    dian[np].clear();
    dian[np].len = dian[p].len+1;
    for(;p&&!dian[p].ch[c];p = dian[p].fa) dian[p].ch[c] = np;
    if(!p) dian[np].fa = 1;
    else {
        int q = dian[p].ch[c];
        if(dian[q].len == dian[p].len+1) dian[np].fa = q;
        else {
            int nq = ++tot;dian[nq].clear();
            dian[nq] = dian[q];
            dian[nq].len = dian[p].len+1;
            dian[q].fa = dian[np].fa = nq;
            for(;p&&dian[p].ch[c] == q;p = dian[p].fa) dian[p].ch[c] = nq;
        }
    }
}
char s[N];
ll dp[N];
int main()
{
    while(scanf("%s",s+1) != EOF) {
        int p,q; scanf("%d%d",&p,&q);
        init();
        int n = strlen(s+1);
        memset(dp,0x3f,sizeof(ll)*(n+2));
        dp[0] = 0;
        int j = 0,ps = 1;
        rep(i,1,n+1) {
            int c = s[i] - 'a';
            while(j && !dian[ps].ch[c]) {
                add(s[i-j]-'a');
                while(dian[dian[ps].fa].len >= j) ps = dian[ps].fa;
                j--;
                if(dian[dian[ps].fa].len >= j) ps = dian[ps].fa;
            }
            if(!dian[ps].ch[c]) add(s[i]-'a');
            else ps = dian[ps].ch[c],j++;
            dp[i] = min(dp[i-1]+p,dp[i-j]+q);
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}
