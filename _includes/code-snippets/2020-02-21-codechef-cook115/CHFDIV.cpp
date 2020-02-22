#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;
const int M = (int)1e9 + 7;

bool isp[N];
ll n, k;

void build() {
  fill(isp, isp + N, 1);
  for(int i = 2 ; (ll)i * i < N ; ++i) if(isp[i]) {
    for(int j = i * i ; j < N ; j += i) isp[j] = 0;
  }
}
void init() {
  cin >> n >> k;
}
void solve() {
  ll ans = 1;
  for(int i = 2 ; i <= n ; ++i) if(isp[i] && k % i != 0) {
    int m = n;
    while(m >= i) {
      for(int j = 0 ; j < m / i ; ++j) ans = ans * i % M;
      m /= i;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  build();
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
