#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

// ntt
// black magic: https://www.cnblogs.com/bibibi/p/9613151.html
inline ll mul(ll a, ll b, ll p) {
  ll t = (a * b - (ll)((ld)a / p * b) * p);
  return (t < 0 ? t + p : (t > p ? t - p : t));
}
template<ll P,ll root,int MAXK,int MAXN>
struct NTT{
	static ll powi(ll a,ll b){
		ll ret=1;
		for(;b;b>>=1,a=mul(a, a, P)){
			if(b&1)	ret=mul(ret, a, P);
		}
		return ret;
	}
	static ll inv(ll a,ll b){
		if(a==1) return 1;
		return (((__int128)(a-inv(b%a,a))*b+1)/a)%b;
	}
	ll omega[MAXK+1],inv_omega[MAXK+1];
	NTT(){
		omega[MAXK]=powi(root,(P-1)>>MAXK);
		for(int i=MAXK-1;i>=0;i--)
			omega[i]=mul(omega[i+1], omega[i+1], P);
		for(int i=0;i<=MAXK;i++)
			inv_omega[i]=inv(omega[i],P);
	}
	void tran(int n,ll a[],bool inv_ntt=false){//n=2^i
		for(int i=1,j=0;i<n;i++){
			for(int k=n>>1;!((j^=k)&k);k>>=1);
			if(i<j) swap(a[i],a[j]);
		}
		ll *G=(inv_ntt?inv_omega:omega);
		for(int k=2,t=1;k<=n;k<<=1){
			int k2=k>>1;ll dw=G[t++];
			for(int j=0;j<n;j+=k){
				ll w=1;
				for(int i=j;i<j+k2;i++){
					ll x=a[i],y=mul(a[i+k2], w, P);
					a[i]=x+y; if(a[i]>=P) a[i]-=P;
					a[i+k2]=x-y; if(a[i+k2]<0) a[i+k2]+=P;
					w=mul(w, dw, P);
				}
			}
		}
		if(inv_ntt){
			ll inv_n=inv(n,P);
			for(int i=0;i<n;i++) a[i]=mul(a[i], inv_n, P);
		}
	}
};
const ll P=2061584302081,root=7;
const int MAXN=1048576,MAXK=20;//MAXN=2^i
struct PolyOp {
#define FOR(i, c) for (int i = 0; i < (c); ++i)
  NTT<P, root, MAXK, MAXN> ntt;
  ll aa[MAXN], bb[MAXN];
  static int nxt2k(int x) {
    int i = 1; for (; i < x; i <<= 1); return i;
  }
  void Mul(int n, ll a[], int m, ll b[], ll c[]) {
    int N = nxt2k(n+m);
    assert(N < MAXN);
    copy(a, a+n, aa); fill(aa+n, aa+N, 0);
    copy(b, b+m, bb); fill(bb+m, bb+N, 0);
    ntt.tran(N, aa); ntt.tran(N, bb);
    FOR(i, N) c[i] = mul(aa[i], bb[i], P);
    ntt.tran(N, c, 1);
  }
} polyop;
// ntt end

const int N = MAXN;

int n, sz[N];
ll ans[N], p1[N], p2[N], p3[N];
bitset<N> isp;
set<int> G[N];
map<int, int> cnt;

int dfs(int u, int p) {
  sz[u] = 1;
  for(auto v : G[u]) if(v != p) {
    sz[u] += dfs(v, u);
  }
  return sz[u];
}
int centroid(int u, int p, int nn) {
  for(auto v : G[u]) if(v != p) {
    if(sz[v] > nn / 2) return centroid(v, u, nn);
  }
  return u;
}
void dfs2(int u, int p, int d) {
  cnt[d]++;
  for(auto v : G[u]) if(v != p) {
    dfs2(v, u, d + 1);
  }
}
void Solve(int u, int p) {
  int nn = dfs(u, p), c = centroid(u, p, nn);
  vector<int> tmp(G[c].begin(), G[c].end());

  // calculate number of path that pass c
  // we used the fact mentioned above
  int len1 = nn;
  fill(p1, p1 + len1, 0); p1[0] = 1;
  fill(p3, p3 + len1, 0);
  for(auto v : tmp) {
    cnt.clear(); dfs2(v, c, 1);
    int len2 = cnt.rbegin()->first + 1;
    fill(p2, p2 + len2, 0);
    for(auto pp : cnt) p2[pp.first] = pp.second, p1[pp.first] += pp.second;
    polyop.Mul(len2, p2, len2, p2, p2);
    for(int i = 0 ; i < len2 * 2 ; ++i) p3[i] += p2[i]; // \sum x_i^2, note that p2[0] = 0
  }
  polyop.Mul(len1, p1, len1, p1, p1); // (\sum x_i)^2, note that p1[0] = 1, because we need to calculate paths that start at c
  for(int i = 0 ; i < len1 ; ++i) ans[i] += (p1[i] - p3[i]) / 2;

  // calculate answer recursively
  for(auto v : tmp) {
    G[c].erase(v); G[v].erase(c);
    Solve(v, c);
  }
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n - 1 ; ++i) {
    int a, b; cin >> a >> b;
    G[a].insert(b); G[b].insert(a);
  }
}
void solve() {
  Solve(1, 0);
  isp.set(); isp[0] = isp[1] = 0;
  for(int i = 2 ; i * i < N ; ++i) {
    for(int j = i * i ; j < N ; j += i) isp[j] = 0;
  }
  ll ccnt = 0, sum = 0;
  for(int i = 1 ; i <= n ; ++i) {
    if(isp[i]) ccnt += ans[i];
    sum += ans[i];
  }
  cout << fixed << setprecision(17) << (ld)ccnt / sum << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

