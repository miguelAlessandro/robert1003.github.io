#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const long double PI = 3.141592653589793;

int main() {
  long double n, s;
  cin >> n >> s;
  long double theta = (PI - 2 * PI / n) / 2, r = s * sin(theta) / sin(2 * PI / n);
  cout << fixed << setprecision(15) << r * r * PI << '\n';
}
