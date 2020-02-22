#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = (int)1e9 + 7;

int n;
string s;

ll powmod(ll a, ll b) {
  if(b == 0) return 1;
  ll ans = powmod(a, b / 2);
  ans = ans * ans % M;
  if(b % 2) ans = ans * a % M;
  return ans;
}

void init() {
  cin >> n >> s;
}
void solve() {
  vector<int> v;
  v.push_back(0);
  ll cnt = 0;
  for(int i = 0 ; i < n ; ++i) {
    if(s[i] == '(') {
      v.back()++;
      v.push_back(0);
    }
    else if(s[i] == ')') {
      int num = v.back();
      cnt += (ll)(num + 1) * (n - i);
      if(v.size() >= 2) {
        v.pop_back();
        int num2 = v.back(); v.pop_back();
        if(v.size() > 0) v.back() += num + 1;
        else v.push_back(num + 1);
        v.push_back(num2);
      }
      else {
        v.back()++;
        v.push_back(0);
      }
    }
    else {
      v.back()++;
    }
  }
  //cerr << cnt << ' ' << (ll)n * (n + 1) / 2 << '\n';
  cout << cnt % M * 2 % M * powmod(n, M - 2) % M * powmod(n + 1, M - 2) % M << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
