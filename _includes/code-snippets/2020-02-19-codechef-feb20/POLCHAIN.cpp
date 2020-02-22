#include <bits/stdc++.h>
#define F first
#define S second
#define l(i) 4 * (i) + 0
#define r(i) 4 * (i) + 1
#define d(i) 4 * (i) + 2
#define u(i) 4 * (i) + 3
using namespace std;
typedef long long ll;
typedef long double ld;

const ld eps = 1e-9, oo = numeric_limits<ld>::infinity();

typedef vector<ld> vec;
typedef vector<vec> mat;

ld simplexMethodPD(mat &A, vec &b, vec &c) {
  int n = c.size(), m = b.size();
  mat T(m + 1, vec(n + m + 1));
  vector<int> base(n + m), row(m);

  for(int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i)
      T[j][i] = A[j][i];
    T[j][n + j] = 1;
    base[row[j] = n + j] = 1;
    T[j][n + m] = b[j];
  }

  for (int i = 0; i < n; ++i)
    T[m][i] = c[i];

  while (1) {
    int p = 0, q = 0;
    for (int i = 0; i < n + m; ++i)
      if (T[m][i] <= T[m][p])
        p = i;

    for (int j = 0; j < m; ++j)
      if (T[j][n + m] <= T[q][n + m])
        q = j;

    ld t = min(T[m][p], T[q][n + m]);

    if (t >= -eps) {
      vec x(n);
      for (int i = 0; i < m; ++i)
        if (row[i] < n) x[row[i]] = T[i][n + m];
      // x is the solution
      return -T[m][n + m]; // optimal
    }

    if (t < T[q][n + m]) {
      // tight on c -> primal update
      for (int j = 0; j < m; ++j)
        if (T[j][p] >= eps)
          if (T[j][p] * (T[q][n + m] - t) >=
            T[q][p] * (T[j][n + m] - t))
            q = j;

      if (T[q][p] <= eps)
        return oo; // primal infeasible
    }
    else {
      // tight on b -> dual update
      for (int i = 0; i < n + m + 1; ++i)
        T[q][i] = -T[q][i];

      for (int i = 0; i < n + m; ++i)
        if (T[q][i] >= eps)
          if (T[q][i] * (T[m][p] - t) >=
            T[q][p] * (T[m][i] - t))
            p = i;

      if (T[q][p] <= eps)
        return -oo; // dual infeasible
    }

    for (int i = 0; i < m + n + 1; ++i)
      if (i != p) T[q][i] /= T[q][p];

    T[q][p] = 1; // pivot(q, p)
    base[p] = 1;
    base[row[q]] = 0;
    row[q] = p;

    for (int j = 0; j < m + 1; ++j)
      if (j != q) {
        ld alpha = T[j][p];
        for (int i = 0; i < n + m + 1; ++i)
          T[j][i] -= T[q][i] * alpha;
      }
  }

  return oo;
}

struct Pt {
  int x, y;

  Pt operator+(const Pt p) { return {x + p.x, y + p.y}; }
  Pt operator-(const Pt p) { return {x - p.x, y - p.y}; }
  ld operator*(const Pt p) { return x * p.x + y * p.y; }
  ld operator^(const Pt p) { return x * p.y - y * p.x; }
};

typedef vector<Pt> Poly;
vector<pair<Poly, int> > polys;
int n;

int area(Poly& v) {
  int m = (int)v.size() - 1;
  int ans = 0;
  for(int i = 0 ; i < m ; ++i) {
    ans += v[i] ^ v[i + 1];
  }
  return ans;
}

void init() {
  cin >> n; polys.resize(n);
  for(int i = 0 ; i < n ; ++i) {
    int m; cin >> m; polys[i].F.resize(m);
    for(int j = 0 ; j < m ; ++j) cin >> polys[i].F[j].x >> polys[i].F[j].y;
    polys[i].F.push_back(polys[i].F[0]);
    polys[i].S = area(polys[i].F);
  }
  sort(polys.begin(), polys.end(), [&](auto a, auto b) { return a.S < b.S; });
}
void solve() {
  int cc = 0;
  for(int i = 0 ; i < n - 1 ; ++i) {
    cc += (int)(polys[i].F.size() - 1) * (polys[i + 1].F.size() - 1);
  }
  // target
  vec C(4 * n, 1);
  // condition
  mat A(cc, vec(4 * n, 0));
  vec B(cc, 0);
  int cnt = 0;
  for(int i = 0 ; i < n - 1 ; ++i) {
    for(int j = 0 ; j < (int)polys[i].F.size() - 1 ; ++j) {
      for(int k = 0 ; k < (int)polys[i + 1].F.size() - 1 ; ++k) {
        Pt v = polys[i].F[j] - polys[i + 1].F[k];
        Pt w = polys[i + 1].F[k + 1] - polys[i + 1].F[k];
        B[cnt] = w ^ v;
        A[cnt][l(i)] -= w.y; A[cnt][l(i + 1)] += w.y;
        A[cnt][r(i)] += w.y; A[cnt][r(i + 1)] -= w.y;
        A[cnt][d(i)] += w.x; A[cnt][d(i + 1)] -= w.x;
        A[cnt][u(i)] -= w.x; A[cnt][u(i + 1)] += w.x;
        cnt++;
      }
    }
  }
  // answer
  ld ans = simplexMethodPD(A, B, C);
  if(isinf(ans)) cout << "-1\n";
  else cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
