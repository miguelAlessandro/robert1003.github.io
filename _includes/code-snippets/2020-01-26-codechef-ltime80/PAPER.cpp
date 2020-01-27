#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;

const int N = 2000 + 5;
const ll inf = (ll)1e15;

int n, m, w, h, xs, ys;
string s;
vector<pair<ll, ll> > v;
vector<ll> x, y;
ll U[N], D[N], R[N], L[N];
ll bu, bd, br, bl;

ll dis2(pair<ll, ll> a, pair<ll, ll> b) {
  ld dx = a.F - b.F, dy = a.S - b.S;
  return dx * dx + dy * dy;
}
ll getId(vector<ll>& vec, ll val) {
  return lower_bound(vec.begin(), vec.end(), val) - vec.begin();
}

void init() {
  cin >> n >> m >> w >> h >> s;
  x.clear(); y.clear();
  v.resize(m);
  for(int i = 0 ; i < m ; ++i) {
    cin >> v[i].F >> v[i].S;
    x.push_back(v[i].F);
    y.push_back(v[i].S);
  }
  sort(x.begin(), x.end()); x.resize(unique(x.begin(), x.end()) - x.begin()); xs = (int)x.size();
  sort(y.begin(), y.end()); y.resize(unique(y.begin(), y.end()) - y.begin()); ys = (int)y.size();
  for(int i = 0 ; i < m ; ++i) {
    v[i].F = getId(x, v[i].F);
    v[i].S = getId(y, v[i].S);
  }
  for(int i = 0 ; i < xs ; ++i) U[i] = -inf, D[i] = inf;
  for(int i = 0 ; i < ys ; ++i) R[i] = -inf, L[i] = inf;
  for(int i = 0 ; i < m ; ++i) {
    int tx = v[i].F, ty = v[i].S;
    U[tx] = max(U[tx], y[ty]);
    D[tx] = min(D[tx], y[ty]);
    R[ty] = max(R[ty], x[tx]);
    L[ty] = min(L[ty], x[tx]);
  }
  bu = h; bd = 0; br = w; bl = 0;
}
void solve() {
  ll ans = (ll)1e19;
  for(int i = n - 1 ; i >= 0 ; --i) {
    if(s[i] == 'U') {
      ld newbu = bd + (bu - bd) * 2;
      for(int j = 0 ; j < xs ; ++j) {
        ans = min(ans, (bu - U[j]) * 2);
        U[j] = newbu - (D[j] - bd); 
      }
      bu = newbu;
    }
    else if(s[i] == 'D') {
      ld newbd = bu - (bu - bd) * 2;
      for(int j = 0 ; j < xs ; ++j) {
        ans = min(ans, (D[j] - bd) * 2);
        D[j] = newbd + (bu - U[j]);
      }
      bd = newbd;
    }
    else if(s[i] == 'R') {
      ld newbr = bl + (br - bl) * 2;
      for(int j = 0 ; j < ys ; ++j) {
        ans = min(ans, (br - R[j]) * 2);
        R[j] = newbr - (L[j] - bl);
      }
      br = newbr;
    }
    else {
      ld newbl = br - (br - bl) * 2;
      for(int j = 0 ; j < ys ; ++j) {
        ans = min(ans, (L[j] - bl) * 2);
        L[j] = newbl + (br - R[j]);
      }
      bl = newbl;
    }
    /*
    cerr << s[i] << '\n';
    fprintf(stderr, "bl=%lld, br=%lld, bu=%lld, bd=%lld\n", bl, br, bu, bd);
    cerr << "U: ";
    for(int j = 0 ; j < xs ; ++j) cerr << U[j] << " \n"[j == xs-1];
    cerr << "D: ";
    for(int j = 0 ; j < xs ; ++j) cerr << D[j] << " \n"[j == xs-1];
    cerr << "L: ";
    for(int j = 0 ; j < ys ; ++j) cerr << L[j] << " \n"[j == ys-1];
    cerr << "R: ";
    for(int j = 0 ; j < ys ; ++j) cerr << R[j] << " \n"[j == ys-1];
    cerr << "ans: " << ans << '\n';
    */
  }
  ll ans2 = (ll)1e19;
  for(int i = 0 ; i < m ; ++i) {
    for(int j = i + 1 ; j < m ; ++j) {
      ans2 = min(ans2, dis2({x[v[i].F], y[v[i].S]}, {x[v[j].F], y[v[j].S]}));
    }
  }
  cout << fixed << setprecision(15) << min((ld)ans, (ld)sqrt(ans2)) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
