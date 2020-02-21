#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 150 + 1;

int n, cnt, s1[N], s2[N];
string s[N];
bitset<N * N> dp[N];

void init() {
  cin >> n;
  cnt = 0;
  for(int i = 0 ; i < n ; ++i) {
    cin >> s[i];
    s1[i] = s2[i] = 0;
    for(int j = 0 ; j < n / 2 ; ++j) s1[i] += (s[i][j] - '0');
    for(int j = n / 2 ; j < n ; ++j) s2[i] += (s[i][j] - '0');
    cnt += s1[i] + s2[i];
  }
}
void solve() {
  dp[0][0] = 1;
  for(int i = 1 ; i <= n ; ++i) {
    dp[i] = (dp[i - 1] << s1[i - 1]) | (dp[i - 1] << s2[i - 1]);
  }
  int best = cnt / 2;
  while(!dp[n][best]) best--;
  for(int i = n - 1 ; i >= 0 ; --i) {
    if(best >= s1[i] && dp[i][best - s1[i]]) best -= s1[i];
    else best -= s2[i], reverse(s[i].begin(), s[i].end());
  }
  for(int i = 0 ; i < n ; ++i) cout << s[i] << "\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
