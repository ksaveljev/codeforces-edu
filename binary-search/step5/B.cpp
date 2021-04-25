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

bool good(ll n, ll k, ll M) {
    ll count = 0;

    for (ll i = 1; i <= n; i++) {
        if (M % i == 0) {
            count += min(n, M / i - 1);
        } else {
            count += min(n, M / i);
        }
    }

    return count < k;
}

int main(void) {
    ll n, k;
    cin >> n >> k;

    ll L = 0;
    ll R = 1e18;
    while (R > L + 1) {
        ll M = (L + R) / 2;
        if (good(n, k, M)) {
            L = M;
        } else {
            R = M;
        }
    }

    cout << L << endl;

    return 0;
}
