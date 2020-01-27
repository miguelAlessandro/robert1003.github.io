#include <bits/stdc++.h>
#define rep(a, b, c) for(int a = (b) ; a < (c) ; ++a)
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const int M = (int)1e9 + 7;

// Usage: linearRec({0, 1}, {1, 1}, k) //k'th fib
typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
  int n = tr.size();
  auto combine = [&](Poly& a, Poly& b) {
    Poly res(n * 2 + 1);
    rep(i,0,n+1) rep(j,0,n+1)
      res[i+j]=(res[i+j] + a[i]*b[j])%M;
    for(int i = 2*n; i > n; --i) rep(j,0,n)
      res[i-1-j]=(res[i-1-j] + res[i]*tr[j])%M;
    res.resize(n + 1);
    return res;
  };
  Poly pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  rep(i,0,n) res=(res + pol[i+1]*S[i])%M;
  return res;
}

ll n, m;

void init() {
  cin >> n >> m;
  m %= M;
}
void solve() {
  cout << linearRec({m % M, m * m % M}, {(m - 1) % M, (m - 1) % M}, n - 1) << '\n';
  /*
  dp[0] = 1;
  dp[1] = m;
  dp[2] = m * m % M;
  for(int i = 3 ; i <= n ; ++i) dp[i] = ((m - 1) * dp[i - 1] % M + (m - 1) * dp[i - 2] % M) % M;
  cout << dp[n] << '\n';
  */
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
