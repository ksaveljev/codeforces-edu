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
using namespace std;

#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

struct segtree {
    int size;
    vector<int> vv;

    void build(vector<int> &v) {
        size = 1;
        while (size < v.size()) size *= 2;
        vv.assign(2 * size, INT_MAX);
        build(v, 0, 0, size);
    }

    void build(vector<int> &v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) {
                vv[x] = v[lx];
            }
        } else {
            int m = (lx + rx) / 2;
            build(v, 2*x+1, lx, m);
            build(v, 2*x+2, m, rx);
            vv[x] = ::min(vv[2*x+1], vv[2*x+2]);
        }
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            vv[x] = v;
        } else {
            int m = (lx + rx) / 2;
            if (i < m) set(i, v, 2*x+1, lx, m);
            else set(i, v, 2*x+2, m, rx);
            vv[x] = ::min(vv[2*x+1], vv[2*x+2]);
        }
    }

    int min(int l, int r) {
        return min(l, r, 0, 0, size);
    }

    int min(int l, int r, int x, int lx, int rx) {
        if (rx <= l) return INT_MAX;
        if (lx >= r) return INT_MAX;
        if (lx >= l && rx <= r) return vv[x];
        int m = (lx + rx) / 2;
        int a = min(l, r, 2*x+1, lx, m);
        int b = min(l, r, 2*x+2, m, rx);
        return ::min(a, b);
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<int> nums(n);

    loop(n) {
        cin >> nums[i];
    }

    segtree st;
    st.build(nums);

    int cmd;
    while (m--) {
        cin >> cmd;
        if (cmd == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.min(l, r) << endl;
        }
    }

    return 0;
}
