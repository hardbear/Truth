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
const int N = (int)1e6+7;

namespace DT {
  int dfn[N], pre[N], pt[N], sz;
  int semi[N], dsu[N], idom[N], best[N];
  int get(int x) {
    if (x == dsu[x]) return x;
    int y = get(dsu[x]);
    if (semi[best[x]] > semi[best[dsu[x]]]) best[x] = best[dsu[x]];
    return dsu[x] = y;
  }
  void dfs(int u, const vi succ[]) {
    dfn[u] = sz; pt[sz ++] = u;
    for (auto &v: succ[u]) if (!~dfn[v]) {
      dfs(v, succ); pre[dfn[v]] = dfn[u];
    }
  }
  void tarjan(const vi pred[], vi dom[]) {
    for (int j = sz - 1, u; u = pt[j], j > 0; -- j) {
      for (auto &tv: pred[u]) if (~dfn[tv]) {
        int v = dfn[tv]; get(v);
        if (semi[best[v]] < semi[j]) semi[j] = semi[best[v]];
      }
      dom[semi[j]].push_back(j);
      int x = dsu[j] = pre[j];
      for (auto &z: dom[x]) {
        get(z);
        if (semi[best[z]] < x) idom[z] = best[z];
        else idom[z] = x;
      }
      dom[x].clear();
    }
    for (int i = 1; i < sz; ++ i) {
      if (semi[i] != idom[i]) idom[i] = idom[idom[i]];
      dom[idom[i]].push_back(i);
    }
  }
  void build(int n, int s, const vi succ[], const vi pred[], vi dom[]) {
    for (int i = 0; i < n; ++i) {
      dfn[i] = -1; dom[i].clear();
      dsu[i] = best[i] = semi[i] = i;
    }
    sz = 0; dfs(s, succ); tarjan(pred, dom);
  }
}
vi e[N],_e[N],g[N];
int fa[N][30],dep[N];
void dfs(int u,int f,int d) {
    fa[u][0] = f;dep[u] = d;
    rep(j,1,30) fa[u][j] = fa[fa[u][j-1]][j-1];
    for(auto v:g[u]) {
        if(v != f) dfs(v,u,d+1);
    }
}
int lca(int u,int v) {
    if(dep[u] < dep[v]) swap(u,v);
    for(int i = 29,d = dep[u] - dep[v];i >= 0; --i) 
        if(d >> i & 1) u = fa[u][i];
    if(u == v) return u;
    per(i,0,30) if(fa[u][i] != fa[v][i]) 
        u = fa[u][i],v = fa[v][i];
    return fa[u][0];
}
int main()
{
    int T;scanf("%d",&T);
    while(T--) {
        int n,m;scanf("%d%d",&n,&m);
        rep(i,1,n+1) e[i].clear();
        rep(i,0,m) {
            int u,v;scanf("%d%d",&u,&v);
            e[u].pb(v);
        }
        rep(i,1,n+1) {
            if(sz(e[i]) == 0) e[i].pb(0);
        }
        n++;
        rep(i,0,n) _e[i].clear();
        rep(i,0,n) {
            for(int v:e[i]) _e[v].pb(i);
        }
        rep(i,0,n) g[i].clear();
        DT::build(n,0,_e,e,g);    
        dfs(0,0,0);
        int q;scanf("%d",&q);
        while(q--) {
            int u,v;
            scanf("%d%d",&u,&v);
            u = DT::dfn[u];
            v = DT::dfn[v];
            printf("%d\n",dep[u] + dep[v] - dep[lca(u,v)]);
        }
    }
    return 0;
}
