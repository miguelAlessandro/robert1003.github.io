#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1000 + 5;
const int inf = 100000;

int n, k, d[N];
vector<int> G[N];

void init() {
  cin >> n >> k;
  for(int i = 0 ; i < n ; ++i) G[i].clear(), d[i] = inf;
  for(int i = 0 ; i < n ; ++i) {
    string s; cin >> s;
    for(int j = max(0, i - k) ; j <= min(n - 1, i + k) ; ++j) if(j != i && s[j] == '1') G[i].push_back(j);
  }
}
void solve() {
  d[0] = 0;
  queue<int> q; q.push(0);
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(auto v : G[u]) if(d[v] == inf) {
      d[v] = d[u] + 1;
      if(v == n - 1) { cout << d[v] << '\n'; return; }
      q.push(v);
    }
  }
  cout << "-1\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
