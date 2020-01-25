#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = (int)1e9 + 7;

ll L, R;

void init() {
  cin >> L >> R;
}
void solve() {
  ll ans = 0;
  for(int i = 0 ; i < 63 ; ++i) if(L & (1LL << i)) {
    ll next_bit = ((L >> i) << i) + (1LL << i) - 1; 
    ans = (ans + ((1LL << i) % M) * ((min(next_bit, R) - L + 1) % M) % M) % M;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
