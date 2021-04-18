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

bool good(string& a, string& b, vector<int>& v, int m) {
    int idx = 0;

    for (int i = 0; i < a.size() && idx < b.size(); i++) {
        if (v[i] <= m) continue;
        if (a[i] == b[idx]) {
            idx++;
        }
    }

    return idx == b.size();
}

int main(void) {
    string a, b;
    cin >> a >> b;

    int x;
    vector<int> v(a.size());
    for (int i = 1; i <= a.size(); i++) {
        cin >> x;
        v[x-1] = i;
    }

    int l = 0;
    int r = a.size();
    while (r > l + 1) {
        int m = (l + r) / 2;
        if (good(a, b, v, m)) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << l << endl;

    return 0;
}
