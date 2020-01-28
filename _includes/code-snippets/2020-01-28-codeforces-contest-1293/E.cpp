#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3000 + 5;

int n, pa[N][N], sz[N][N];
ll dp[N][N];
vector<int> G[N];

int dfs(int u, int p, int id) {
  pa[id][u] = p; sz[id][u] = 1;
  for(auto v : G[u]) if(v != p) {
    sz[id][u] += dfs(v, u, id);
  }
  return sz[id][u];
}
ll DP(int u, int v) {
  if(u == v) return 0;
  if(dp[u][v] >= 0) return dp[u][v];
  return dp[u][v] = dp[v][u] = (ll)sz[u][v] * sz[v][u] + max(DP(pa[v][u], v), DP(u, pa[u][v]));
}

void init() {
  cin >> n;
  for(int i = 1 ; i < n ; ++i) {
    int a, b; cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
}
void solve() {
  for(int i = 1 ; i <= n ; ++i) dfs(i, 0, i);
  memset(dp, -1, sizeof(dp));
  ll ans = 0;
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = i + 1 ; j <= n ; ++j) ans = max(ans, DP(i, j));
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
