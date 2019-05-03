/*<<head>> {{{*/
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
/*}}}*/
const int MOD = (int)1e9+7;
const int N = (int)3e4+7;

// --- var --- //

int n;

#define lson t[rt].l
#define rson t[rt].r
struct Treap {
	int rt, no, d;
	struct Node { int l, r, val, mx, len, totlen, rnd, sz; } t[N];
	void Clear() {
		rt = no = d = 0;
		t[0] = (Node){ 0, 0, 0, 0, 0, 0, rand(), 0 };
	}
	int newnode(int val, int len) {
		t[++no] = (Node){ 0, 0, val, val, len, len, rand(), 1 };
		return no;	
	}
	void PushUp(int rt) {
		t[rt].sz = t[lson].sz + t[rson].sz + 1;
		t[rt].totlen = t[lson].totlen + t[rson].totlen + t[rt].len;
		t[rt].mx = max(t[rt].val, max(t[lson].mx, t[rson].mx));
	}
	void split(int rt, int k, int &x, int &y) {
		//PushDown(rt);
		if (!k) { x = 0; y = rt; return ; }
		if (t[rt].sz <= k) { x = rt; y = 0; return ; }
		if (t[lson].sz >= k) { y = rt; split(lson, k, x, lson); }
		else { x = rt; split(rson, k-t[lson].sz-1, rson, y); }
		PushUp(rt);
	}
	int merge(int x, int y) {
		if (!x || !y) return x + y;
		//PushDown(x); PushDown(y);
		if (t[x].rnd < t[y].rnd) {
			t[x].r = merge(t[x].r, y);
			PushUp(x); return x;
		} else {
			t[y].l = merge(x, t[y].l);
			PushUp(y); return y;
		}
	}
	void ins(int pos, int val, int len) {
		int x, y;
		split(rt, pos, x, y);
		rt = merge(merge(x, newnode(val, len)), y);
	}
	void del(int pos, int len) {
		int x, y, z;
		split(rt, pos-1, x, y); split(y, len, y, z);
		rt = merge(x, z);
		d += len;
	}
	void build() {
		rt = merge(rt, newnode(0, 0));
	}
	void work(int pos, int white) {
		if (!white) return ;
		int len = t[pos].len;
		int black = len - white;
		ins(pos, t[pos].val, white);
		ins(pos, t[pos].val, black);
		del(pos, 1);
	}
	void work1(int pos, int white, int val, int tlen) {
		int len = t[pos].len;
		int black = len - white;
		ins(pos, t[pos].val, white);
		ins(pos, val, tlen);
		ins(pos, t[pos].val, black);
		del(pos, 1);
		dd(white); de(black);
	}
	int getnode(int pos) {
		int L = 1, R = no - d;
		while (L < R) {
			int M = L + ((R - L) >> 1);
			if (Qry(1, M, 2) >= pos) R = M;
			else L = M + 1;
		}
		/*
		int L;
		for (L = 1; ; L++) {
			de(Qry(1, L, 2));
			if (Qry(1, L, 2) >= pos) return L;
		}
		//return L;
		*/
	}
	void Insert(int pos, int val, int len) {
		int L = getnode(pos);
		//de(L);
		int tmp = Qry(1, L, 2);
		//de(tmp);
		//dd(val); de(len);
		if (tmp - pos != 0)	work1(L, tmp - pos, val, len);
		else ins(pos, val, len);
	}
	void Remove(int pos, int len) {
		int st = pos - 1, l, r;
		int L = getnode(st);
		l = L;
		int tmp = Qry(1, L, 2);
		work(L, tmp - st);

		L = getnode(st + len);
		r = L;
		tmp = Qry(1, L, 2);
		work(L, tmp - (st + len));
		del(l, r - l + 1);
	}
	int QQRY(int l, int r) {
		int tl, tr;
		int L = getnode(l-1);
		int tmp = Qry(1, L, 2);
		work(L, tmp - l + 1);
		tl = L + 1;

		L = getnode(r);
		tmp = Qry(1, L, 2);
		work(L, tmp - r);
		tr = L;
		return Qry(tl, tr, 1);
	}
	int Qry(int l, int r, int op) {
		int x, y, z;
		split(rt, l-1, x, y); split(y, r-l+1, y, z);
		int res;
		switch (op) {
			case 1 : res = t[y].mx; break;
			case 2 : res = t[y].totlen; break;
			case 3 : res = t[y].val; break;
		}
		rt = merge(merge(x, y), z);
		return res;
	}
	void debug() {
		rep(i, 1, no-d) {
			printf("%d ", Qry(i, i, 3));
		}
		puts("");
	}
} treap[26];

// --- fun --- //

void BUILD() {
	rep(i, 0, 26) treap[i].Clear();
	rep(i, 0, 26) treap[i].build();
}
void INSERT(int id, int num, char type) {
	int w = type - 'a';
	rep(i, 0, 26) {
		de(i);
		treap[i].Insert(id-1, (w==i), num);
		//dd((char)('a'+i)); de((w==i));
	}
}
void REMOVE(int id, int num) {
	rep(i, 0, 26) {
		treap[i].Remove(id, num);
	}
}
int QRY(int l, int r) {
	int res = 0;
	rep(i, 0, 26) {
		if (treap[i].QQRY(l, r)) res++;
		//dd((char)('a'+i)); de(res);
	}
	return res;
}

void Init() {
	BUILD();
}

int Solve() {
	while (n--) {
		char op[10];
		scanf("%s", op);
		int id, num; char type[10];
		if (op[0] == '+') {
			scanf("%d%d%s", &id, &num, type);
			INSERT(id, num, type[0]);
		} else if (op[0] == '-') {
			scanf("%d%d", &id, &num);
			REMOVE(id, num);
		} else {
			int l, r; scanf("%d%d", &l, &r);
			printf("%d\n", QRY(l, r));
		}
	}
	return 0;
}

// -- main --- //

int main()
{
	while (~scanf("%d", &n)) {
		Init();
		Solve();
	}
	return 0;
}
