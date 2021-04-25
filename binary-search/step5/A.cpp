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

bool good(int n, int k, vector<pair<ll,ll>>& v, ll M) {
    ll count = 0;
    for (int i = 0; i < n; i++) {
        if (M > v[i].second) {
            count += min(v[i].second, M) - v[i].first + 1;
        } else if (M > v[i].first) {
            count += M - v[i].first;
        }
    }

    return count <= k;
}

int main(void) {
    int n, k;
    cin >> n >> k;

    vector<pair<ll,ll>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    ll L = -1e10;
    ll R = 1e10;
    while (R > L + 1) {
        ll M = (L + R) / 2;
        if (good(n, k, v, M)) {
            L = M;
        } else {
            R = M;
        }
    }

    cout << L << endl;

    return 0;
}
