#include <bits/stdc++.h>
using namespace std;

int main() {
  long long s, x; cin >> s >> x;
  int ans = 0;
  while(s > 0) {
    ans++;
    s /= x;
  }
  cout << ans << '\n';
}
