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

    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x] += v;
            return;
        }

        int m = (lx + rx) / 2;
        add(l, r, v, 2*x+1, lx, m);
        add(l, r, v, 2*x+2, m, rx);
    }

    ll get(int idx) {
        return get(idx, 0, 0, size);
    }

    ll get(int idx, int x, int lx, int rx) {
        if (rx == lx + 1) {
            return tree[x];
        }

        int m = (lx + rx) / 2;
        if (idx < m)
            return get(idx, 2*x+1, lx, m) + tree[x];
        else
            return get(idx, 2*x+2, m, rx) + tree[x];
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
            st.add(l, r, v);
        } else {
            int i;
            cin >> i;
            cout << st.get(i) << endl;
        }
    }

    return 0;
}
