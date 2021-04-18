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

int main(void) {
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for (auto& x: v) {
        cin >> x;
    }

    double l = 0;
    double r = 1e8;

    for (int i = 0; i < 100; i++) {
        double m = (l + r) / 2;
        int s = 0;
        for (int j = 0; j < n; j++) {
            s += (int)(v[j] / m);
        }
        if (s >= k) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << setprecision(10) << l << endl;

    return 0;
}
