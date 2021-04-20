#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <numeric>
#include <cstdio>
#include <list>
#include <cassert>
#include <climits>
using namespace std;

#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define rep(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

bool good(int n, vector<int>& x, vector<int>& v, double M) {
    double L = -1e10;
    double R = 1e10;
    for (int i = 0; i < n; i++) {
        double xl = x[i] - M*v[i];
        double xr = x[i] + M*v[i];

        L = max(L, xl);
        R = min(R, xr);

        if (L > R) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int n;
    cin >> n;
    vector<int> x(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> v[i];
    }

    double L = 0;
    double R = 1e18;

    for (int i = 0; i < 100; i++) {
        double M = (L + R) / 2;

        if (good(n, x, v, M)) {
            R = M;
        } else {
            L = M;
        }
    }

    cout << setprecision(10) << R << endl;

    return 0;
}
