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
#include <cassert>
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

bool good(int n, int k, vector<pair<int,int>>& v, double M) {
    vector<double> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = v[i].first - v[i].second * M;
    }
    sort(x.begin(), x.end());
    double s = 0;
    for (int i = 1; i <= k; i++) {
        s += x[n - i];
    }
    return s <= 0;
}

int main(void) {
    int n, k;
    cin >> n >> k;

    vector<pair<int,int>> v(n);
    for (auto& x : v) {
        cin >> x.first >> x.second;
    }

    double L = -1;
    double R = 1e18;
    for (int i = 0; i < 100; i++) {
        double M = (L + R) / 2;
        if (good(n, k, v, M)) {
            R = M;
        } else {
            L = M;
        }
    }

    cout << setprecision(10) << R << endl;

    return 0;
}
