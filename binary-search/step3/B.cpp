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

bool good(int n, int k, vector<ll>& v, ll M) {
    int c = 1;

    ll s = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] > M) return false;

        if (s + v[i] > M) {
            s = v[i];
            c++;
        } else {
            s += v[i];
        }
    }

    return c <= k;
}

int main(void) {
    int n, k;
    cin >> n >> k;

    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ll L = 0;
    ll R = 1e16;
    while (R > L + 1) {
        ll M = (L + R) / 2;
        if (good(n, k, v, M)) {
            R = M;
        } else {
            L = M;
        }
    }

    cout << R << endl;

    return 0;
}
