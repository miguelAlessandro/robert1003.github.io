#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

int n, a[N], cnt[32];

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) cin >> a[i];
}
void solve() {
  for(int i = 0 ; i < n ; ++i) {
    for(int j = 0 ; j < 17 ; ++j) if(a[i] & (1 << j)) cnt[j]++;
  }
  ll ans = 0;
  for(int i = 0 ; i < 17 ; ++i) {
    ans += ((ll)(1 << n) - (1 << (n - cnt[i]))) * (1 << i);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
