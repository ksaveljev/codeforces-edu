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
#define rep(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

struct segtree {
    int size;
    vector<ll> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2*size, 0);
    }

    void set(int idx, int v) {
        set(idx, v, 0, 0, size);
    }

    void set(int idx, int v, int x, int lx, int rx) {
        if (rx == lx + 1) {
            tree[x] += v;
        } else {
            int m = (lx + rx) / 2;
            if (idx < m)
                set(idx, v, 2*x+1, lx, m);
            else
                set(idx, v, 2*x+2, m, rx);
            tree[x] = tree[2*x+1] + tree[2*x+2];
        }
    }

    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r) return 0;
        if (rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return sum(l, r, 2*x+1, lx, m) + sum(l, r, 2*x+2, m, rx);
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    segtree st;
    st.build(n);

    int cmd;
    while (m--) {
        cin >> cmd;
        if (cmd == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            st.set(l, v);
            if (r < n)
                st.set(r, -v);
        } else {
            int i;
            cin >> i;
            cout << st.sum(0, i+1) << endl;
        }
    }

    return 0;
}
