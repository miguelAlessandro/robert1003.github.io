#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;

const int N = (int)2e5 + 5;
const int K = 50 + 5;
const ld inf = (ld)1e18;

struct CHT {
  deque<pair<ld, ld> > dq;

  ld value(pair<ld, ld> l, ld x) {
    return l.F * x + l.S;
  }
  bool better(pair<ld, ld> L, pair<ld, ld> L1, pair<ld, ld> L2) {
    return (L2.S - L.S) * (L1.F - L2.F) <= (L.F - L2.F) * (L2.S - L1.S);
  }
  void init() {
    dq.clear();
    dq.push_back({0, 0});
  }
  void add(ld m, ld b) {
    while((int)dq.size() >= 2 && better({m, b}, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
    dq.push_back({m, b});
  }
  ld query(ld x) {
    while((int)dq.size() >= 2 && value(dq[0], x) < value(dq[1], x)) dq.pop_front();
    return value(dq.front(), x);
  }
} cht;

int n, k, t[N];
ll sum[N];
ld dp[2][N], fsum[N], psum[N];

ld calc(int i, int j) {
  return psum[j] - psum[i - 1] - (ld)sum[i - 1] * (fsum[j] - fsum[i - 1]);
}

void init() {
  cin >> n >> k;
  for(int i = 1 ; i <= n ; ++i) {
    cin >> t[i];
    sum[i] = sum[i - 1] + t[i];
    fsum[i]= fsum[i - 1] + 1.0 / t[i];
    psum[i] = psum[i - 1] + (ld)sum[i] / t[i];
  }
}
void solve() {
  for(int i = 0 ; i < 2 ; ++i) fill(dp[i], dp[i] + n + 1, inf);
  dp[0][0] = 0;
  int cur = 1;
  for(int j = 1 ; j <= k ; ++j) {
    cht.init();
    for(int i = 1 ; i <= n ; ++i) {
      dp[cur][i] = psum[i] - cht.query(fsum[i]);
      cht.add(sum[i], -fsum[i] * sum[i] + psum[i] - dp[cur ^ 1][i]);
    }
    cur ^= 1;
  }
  cout << fixed << setprecision(10) << dp[cur ^ 1][n] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
