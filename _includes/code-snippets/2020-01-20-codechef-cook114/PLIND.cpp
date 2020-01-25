#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;
const int M = (int)1e9 + 7;
const int K = 10;

int dp[N][K + 1][2], cnt[N][K], odd[N], small[N];
string L, R;

int DP(string& s) {
  if(!s[0]) return 0;
  int n = (int)s.size();
  // calculate cnt & odd & small
  for(int i = 0 ; i < K ; ++i) cnt[0][i] = 0;
  cnt[0][s[0]] = 1;
  odd[0] = 1;
  small[0] = 0;
  for(int i = 1 ; i < n ; ++i) {
    memcpy(cnt[i], cnt[i - 1], sizeof(cnt[i - 1]));
    if(cnt[i][s[i]] % 2) odd[i] = odd[i - 1] - 1;
    else odd[i] = odd[i - 1] + 1;
    cnt[i][s[i]] += 1;
    int cc = 0;
    for(int j = 0 ; j < s[i] ; ++j) cc += (cnt[i - 1][j] & 1);
    small[i] = cc;
  }
  //  for(int i = 0 ; i < n ; ++i) fprintf(stderr, "odd[%d]=%d, small[%d]=%d\n", i, odd[i], i, small[i]);
  // calculate dp
  for(int i = 0 ; i <= 1 ; ++i) dp[n][i][0] = dp[n][i][1] = 1;
  for(int i = 2 ; i <= K ; ++i) dp[n][i][0] = dp[n][i][1] = 0;
  for(int i = n - 1 ; i >= 1 ; --i) {
    for(int j = 0 ; j <= K ; ++j) {
      // k = 0
      if(j == odd[i - 1]) {
        dp[i][j][0] = ((ll)dp[i + 1][odd[i]][0] + (ll)small[i] * dp[i + 1][odd[i - 1] - 1][1] % M + (ll)(s[i] - small[i]) * dp[i + 1][odd[i - 1] + 1][1] % M) % M;
      }
      // k = 1
      dp[i][j][1] = 0;
      if(j < K) dp[i][j][1] = ((ll)dp[i][j][1] + (ll)dp[i + 1][j + 1][1] * (K - j)) % M;
      if(j > 0) dp[i][j][1] = ((ll)dp[i][j][1] + (ll)dp[i + 1][j - 1][1] * j % M) % M;
    }
  }
  /*
  for(int i = 0 ; i <= n ; ++i) {
    for(int j = 0 ; j <= K ; ++j) {
      fprintf(stderr, "dp[%d][%d][%d]=%d, dp[%d][%d][%d]=%d\n", i, j, 0, dp[i][j][0], i, j, 1, dp[i][j][1]);
    }
  }
  */
  int ans = ((ll)dp[1][1][0] + (s[0] > 0 ? (ll)(s[0] - 1) * dp[1][1][1] % M : 0)) % M; 
  for(int i = 1 ; i < n ; ++i) ans = (ans + 9LL * dp[i + 1][1][1] % M) % M;
  //cerr << ans << '\n';
  return ans;
}

void init() {
  string s;
  cin >> s >> R;
  int tag = -1;
  L.clear();
  for(int i = (int)s.size() - 1 ; i >= 0 ; --i) {
    if(s[i] == '0' && tag == -1) L.push_back('9');
    else L.push_back(s[i] + tag), tag = 0;
  }
  //cerr << L << ' ' << R << '\n';
  while((int)L.size() > 1 && L.back() == '0') L.pop_back();
  reverse(L.begin(), L.end());
  //cerr << L << ' ' << R << '\n';
  for(auto &i : L) i -= '0';
  for(auto &i : R) i -= '0';
}
void solve() {
  cout << (DP(R) - DP(L) + M) % M << '\n';
}

int main() {
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
