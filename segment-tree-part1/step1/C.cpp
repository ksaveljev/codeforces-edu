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
    vector<pair<int,int>> vv;

    pair<int,int> combine(pair<int,int> a, pair<int,int> b) {
        if (a.first < b.first) return a;
        if (b.first < a.first) return b;
        return { a.first, a.second + b.second };
    }

    void build(vector<int> &v) {
        size = 1;
        while (size < v.size()) size *= 2;
        vv.resize(2 * size, { INT_MAX, 0 });
        build(v, 0, 0, size);
    }

    void build(vector<int> &v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) {
                vv[x] = { v[lx], 1 };
            }
        } else {
            int m = (lx + rx) / 2;
            build(v, 2*x+1, lx, m);
            build(v, 2*x+2, m, rx);
            vv[x] = combine(vv[2*x+1], vv[2*x+2]);
        }
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            vv[x] = { v, 1 };
        } else {
            int m = (lx + rx) / 2;
            if (i < m)
                set(i, v, 2*x+1, lx, m);
            else
                set(i, v, 2*x+2, m, rx);
            vv[x] = combine(vv[2*x+1], vv[2*x+2]);
        }
    }

    pair<int,int> calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

    pair<int,int> calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r) return { INT_MAX, 0 };
        if (rx <= l) return { INT_MAX, 0 };
        if (lx >= l && rx <= r) return vv[x];
        int m = (lx + rx) / 2;
        auto a = calc(l, r, 2*x+1, lx, m);
        auto b = calc(l, r, 2*x+2, m, rx);
        return combine(a, b);
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
            auto [a, b] = st.calc(l, r);
            cout << a << " " << b << endl;
        }
    }

    return 0;
}
