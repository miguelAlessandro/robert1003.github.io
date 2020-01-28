#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int K = 5000 + 1;

map<int, map<int, int> > fac;
vector<int> sum;
map<int, int> v;
int n;

void build() {
  bitset<K> isp;
  isp.set();
  for(int i = 2 ; i * i < K ; ++i) if(isp[i]) {
    for(int j = i * i ; j < K ; j += i) isp[j] = 0;
  }
  vector<int> p;
  for(int i = 2 ; i < K ; ++i) if(isp[i]) p.push_back(i);
  map<int, int> m;
  sum.resize(K);
  int cnt = 0;
  for(int i = 2 ; i < K ; ++i) {
    int x = i, j = 0;
    while(x > 1) {
      if(isp[x]) {
        m[x]++;
        cnt++;
        break;
      }
      int cc = 0;
      while(x % p[j] == 0) cc++, x /= p[j];
      if(cc) m[p[j]] += cc, cnt += cc;
      j++;
    }
    fac[i] = m;
    sum[i] = cnt;
  }
}
void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int a; cin >> a; 
    if(a > 1) v[a]++;
  }
}
void solve() {
  ll ans = 0;
  for(auto [i, j] : v) {
    ans += (ll)sum[i] * j;
  }
  while(1) {
    map<int, int> tmp;
    for(auto [i, j] : v) {
      tmp[fac[i].rbegin()->first] += j;
    }
    int mx = 0, val = 0;
    for(auto [i, j] : tmp) if(j > val) mx = i, val = j;
    if(val < n - val) break;
    ans += n - val - val;
    vector<int> tt;
    for(auto [i, j] : v) {
      if(fac[i].rbegin()->first == mx) {
        fac[i].rbegin()->second--;
        if(fac[i].rbegin()->second == 0) {
          fac[i].erase(fac[i].rbegin()->first);
          if(fac[i].empty()) tt.push_back(i);
        }
      }
      else tt.push_back(i);
    }
    for(auto t : tt) v.erase(t);
  }
  cout << ans << '\n';
}

int main() {
  build();
  init();
  solve();
}
