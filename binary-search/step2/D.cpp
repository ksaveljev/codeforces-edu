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

struct helper {
    ll t, z, y;
};

ll blown(helper x, int time) {
    ll result = 0;

    result += x.z * (time / (x.t * x.z + x.y));
    ll rem = time % (x.t * x.z + x.y);
    if (rem >= (x.t * x.z)) result += x.z;
    else result += rem / x.t;

    return result;
}

bool good(int m, vector<helper>& h, int time) {
    ll result = 0;

    for (const auto& x : h) {
        result += blown(x, time);
    }

    return result >= m;
}

int main(void) {
    ll m, n;
    cin >> m >> n;

    vector<helper> h(n);
    for (auto& x : h) {
        cin >> x.t >> x.z >> x.y;
    }

    ll l = -1;
    ll r = 2e9+1;

    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (good(m, h, mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r << endl;
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";

        ll x = blown(h[i], r);
        cout << min(m, x);
        m -= min(m, x);
    }
    cout << endl;

    return 0;
}
