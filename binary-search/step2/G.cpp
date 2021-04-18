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

bool good(int k, int n, vector<ll> v, ll m) {
    ll sum = 0;

    for (auto x : v) {
        sum += min(m, x);
    }

    return sum >= m * k;
}

int main(void) {
    int k, n;
    cin >> k >> n;

    vector<ll> v(n);
    for (auto& x : v) {
        cin >> x;
    }

    ll l = 0;
    ll r = 1e17;
    while (r > l + 1) {
        ll m = (l + r) / 2;
        if (good(k, n, v, m)) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << l << endl;

    return 0;
}
