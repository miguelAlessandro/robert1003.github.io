#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;

int n, m, p[N], x[N], y[N], ans[N];
pair<int, int> history[N][4];

void init() {
  cin >> n >> m;
  for(int i = 1 ; i <= m ; ++i) cin >> x[i] >> y[i];
}
void solve() {
  if(n & 1) p[n] = n; 
  for(int i = 1 ; i <= n / 2 ; ++i) {
    p[2 * i] = 2 * i - 1;
    p[2 * i - 1] = 2 * i;
  }
  for(int i = 1 ; i <= m ; ++i) {
    // a balancer between x, y make x, y into a new pair
    history[i][0] = {x[i], p[x[i]]};
    history[i][1] = {y[i], p[y[i]]};
    history[i][2] = {p[x[i]], x[i]};
    history[i][3] = {p[y[i]], y[i]};
    if(p[y[i]] == y[i]) swap(x[i], y[i]);
    if(p[x[i]] == x[i]) {
      p[p[y[i]]] = p[y[i]]; // p[y[i]] becomes single
    }
    else if(p[x[i]] != y[i]) { // change pairing
      int px = p[x[i]], py = p[y[i]];
      p[px] = py;
      p[py] = px;
    }
    p[x[i]] = y[i];
    p[y[i]] = x[i];
  }
  // choose the smaller element in the pairing to be activate
  for(int i = 1 ; i <= n ; ++i) ans[i] = (i <= p[i]);
  // find the settings
  string setting;
  for(int i = m ; i >= 1 ; --i) {
    for(int j = 0 ; j < 4 ; ++j) p[history[i][j].F] = history[i][j].S;
    // if x[i] is on and x[i] is lower, then set '^'
    // if x[i] is on and x[i] is upper, then set 'v'
    // if y[i] is on and y[i] is lower, then set '^'
    // if y[i] is on and y[i] is upper, then set 'v'
    setting.push_back(ans[x[i]] ^ (x[i] > y[i]) ? '^' : 'v');
    // update ans
    // if x[i] is a single one, then it must be set
    if(p[x[i]] == x[i]) ans[x[i]] = 1, ans[y[i]] = 0;
    // otherwise if x[i] y[i] changed pairing, then we need to change wire setting
    else if(p[x[i]] != y[i]) ans[x[i]] = ans[p[y[i]]], ans[y[i]] = ans[p[x[i]]];
  }
  reverse(setting.begin(), setting.end());
  cout << setting << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
