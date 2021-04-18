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

bool good(ll n, ll x, ll y, ll m) {
    ll lowest = min(x, y);
    if (m < lowest) return false;

    ll result = 1;
    m -= lowest;
    result += m / x;
    result += m / y;
    return result >= n;
}

int main(void) {
    ll n, x, y;
    cin >> n >> x >> y;

    ll l = 0;
    ll r = 2e9+5;

    while (r > l + 1) {
        ll m = (l + r) / 2;
        if (good(n, x, y, m)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r << endl;

    return 0;
}
