#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;

int n, valid[N];
vector<int> G[N];
deque<ll> dp1[N], dp2[N];
ll ans;

void dfs(int u, int p) {
  dp1[u] = {valid[u]};
  dp2[u] = {0};
  for(auto v : G[u]) if(v != p) {
    dfs(v, u);
    dp1[v].push_front(0);
    dp2[v].pop_front();
    if(dp1[v].size() > dp1[u].size()) {
      swap(dp1[u], dp1[v]);
      swap(dp2[u], dp2[v]);
    }
    if(dp2[u].size() < dp1[v].size()) {
      dp2[u].insert(dp2[u].end(), dp1[v].size() - dp2[u].size(), 0);
    }
    for(int i = 0 ; i < (int)dp1[v].size() ; ++i) ans += dp1[v][i] * dp2[u][i];
    for(int i = 0 ; i < (int)dp2[v].size() ; ++i) ans += dp2[v][i] * dp1[u][i];
    for(int i = 0 ; i < (int)dp1[v].size() ; ++i) dp2[u][i] += dp1[u][i] * dp1[v][i];
    for(int i = 0 ; i < (int)dp1[v].size() ; ++i) dp1[u][i] += dp1[v][i];
    for(int i = 0 ; i < (int)dp2[v].size() ; ++i) dp2[u][i] += dp2[v][i];
  }
}

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) G[i].clear();
  for(int i = 1 ; i < n ; ++i) {
    int a, b; cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i = 1 ; i <= n ; ++i) cin >> valid[i];
}
void solve() {
  ans = 0;
  dfs(1, 0);
  cout << ans * 6 << '\n'; 
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
