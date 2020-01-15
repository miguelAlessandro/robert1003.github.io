#include <bits/stdc++.h>
using namespace std;

bitset<10000001> isp;

int main() {
  isp.set();
  for(int i = 2 ; i * i <= 10000000 ; ++i) if(isp[i]) {
    for(int j = i * i ; j <= 10000000 ; j += i) isp[j] = 0;
  }
  int n; cin >> n;
  for(int i = 2 ; i <= n / 2 ; ++i) {
    if(isp[i] && isp[n - i]) {
      cout << i << ' ' << n - i << '\n';
      return 0;
    }
  }
  cout << "-1\n";
}
