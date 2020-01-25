#pragma GCC optimize ("O3,no-stack-protector")
#pragma GCC target ("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;
const int K = 10 + 1;

struct BIT {
  int n, a[2 * N];

  void init(int _n) {
    n = _n;
    for(int i = 0 ; i <= 2 * n ; ++i) a[i] = 0;
  }
  inline int lowbit(int x) { return x & (-x); }
  void upd(int x, int v) {
    for(int i = x ; i <= 2 * n ; i += lowbit(i)) a[i] += v;
  }
  int qry(int x) {
    int ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += a[i];
    return ans;
  }
  void update(int x, int v) {
    upd(x + n, v);
  }
  int query(int x) {
    return qry(x + n);
  }
} cnt[K];

int n, k, d[N][K], sz[N];
map<int, int> G[N];

int dfs(int u, int p) {
  //fprintf(stderr, "dfs: (u, p)=(%d, %d)\n", u, p);
  sz[u] = 1;
  for(auto it : G[u]) if(it.first != p) {
    sz[u] += dfs(it.first, u);
  }
  return sz[u];
}
void dfs2(int u, int p, int c, ll& ans) {
  //fprintf(stderr, "dfs2: (u, p, c, ans)=(%d, %d, %d, %d)\n", u, p, c, ans);
  for(int i = 1 ; i <= k ; ++i) d[u][i] = d[p][i] + 1;
  d[u][c] -= 2;
  /*
  for(int i = 1 ; i <= k ; ++i) {
    fprintf(stderr, "d[%d][%d]=%d, cnt[%d].query(%d)=%d\n", u, i, d[u][i], i, -d[u][i]-1, cnt[i].query(-d[u][i]-1));
  }
  */
  for(int i = 1 ; i <= k ; ++i) ans += cnt[i].query(-d[u][i] - 1) + (d[u][i] < 0);
  for(auto it : G[u]) if(it.first != p) dfs2(it.first, u, it.second, ans);
}
void dfs3(int u, int p) {
  for(int i = 1 ; i <= k ; ++i) cnt[i].update(d[u][i], 1);
  for(auto it : G[u]) if(it.first != p) dfs3(it.first, u);
}
void dfs4(int u, int p) {
  for(int i = 1 ; i <= k ; ++i) cnt[i].update(d[u][i], -1);
  for(auto it : G[u]) if(it.first != p) dfs4(it.first, u);
}
int centroid(int u, int p, int nn) {
  for(auto it : G[u]) if(it.first != p) {
    if(sz[it.first] > nn / 2) return centroid(it.first, u, nn);
  }
  return u;
}
ll Solve(int u, int p) {
  //fprintf(stderr, "Solve: (u, p)=(%d, %d)\n", u, p);
  int nn = dfs(u, p), c = centroid(u, p, nn);
  for(int i = 1 ; i <= k ; ++i) d[c][i] = 0;
  //fprintf(stderr, "nn=%d, c=%d\n", nn, c);
  ll ans = 0;
  for(auto it : G[c]) {
    dfs2(it.first, c, it.second, ans);
    dfs3(it.first, c);
  }
  for(auto it : G[c]) {
    dfs4(it.first, c);
  }
  //fprintf(stderr, "ans: %d\n", ans);
  vector<int> tmp;
  for(auto it : G[c]) tmp.push_back(it.first);
  for(auto v : tmp) {
    G[c].erase(v); G[v].erase(c);
    ans += Solve(v, c);
  }
  return ans;
}

void init() {
  cin >> n >> k;
  for(int i = 1 ; i <= n ; ++i) G[i].clear();
  for(int i = 1 ; i < n ; ++i) {
    int u, v, w; cin >> u >> v >> w;
    G[u][v] = G[v][u] = w;
  }
  for(int i = 1 ; i <= k ; ++i) cnt[i].init(n);
}
void solve() {
  cout << (ll)n * (n - 1) / 2 - Solve(1, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
