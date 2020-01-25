#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;

ll n, sum, a[N];
map<ll, int> m1, m2;

void init() {
  cin >> n;
  m1.clear();
  m2.clear();
  sum = 0;
  for(int i = 1 ; i <= n ; ++i) {
    cin >> a[i];
    sum += a[i];
    if(i != n) m2[sum]++; // be careful that the last element can't be included
  }
}
void solve() {
  ll ans = 0, sum2 = 0;
  
  for(int i = 1 ; i <= n ; ++i) {
    ll target = (sum - a[i]);
    if(target % 2 == 0) {
      target >>= 1;
      ans += m1[target] + m2[target + a[i]];
    }
    sum2 += a[i];
    m2[sum2]--;
    m1[sum2]++;
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
