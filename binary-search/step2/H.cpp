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

bool good(ll rb, ll rs, ll rc, ll nb, ll ns, ll nc, ll pb, ll ps, ll pc, ll sum, ll M) {
    ll mb = M * rb;
    ll ms = M * rs;
    ll mc = M * rc;

    ll x = 0;
    x += max(mb - nb, 0LL) * pb;
    x += max(ms - ns, 0LL) * ps;
    x += max(mc - nc, 0LL) * pc;

    return x <= sum;
}

int main(void) {
    string r;
    ll nb, ns, nc;
    ll pb, ps, pc;
    ll sum;

    cin >> r;
    cin >> nb >> ns >> nc;
    cin >> pb >> ps >> pc;
    cin >> sum;

    ll rb = 0, rs = 0, rc = 0;
    for (int i = 0; i < r.size(); i++) {
        if (r[i] == 'B') {
            rb++;
        } else if (r[i] == 'S') {
            rs++;
        } else {
            rc++;
        }
    }

    ll L = 0;
    ll R = 1e15;

    while (R > L + 1) {
        ll M = (L + R) / 2;
        if (good(rb, rs, rc, nb, ns, nc, pb, ps, pc, sum, M)) {
            L = M;
        } else {
            R = M;
        }
    }

    cout << L << endl;

    return 0;
}
