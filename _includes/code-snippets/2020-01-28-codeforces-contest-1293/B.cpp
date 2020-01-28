#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int n;

void init() {
  cin >> n;
}
void solve() {
  ld ans = 0.0;
  while(n > 0) {
    ans += 1.0 / n;
    n--;
  }
  cout << fixed << setprecision(15) << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
