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

    struct node {
        ll sum;
        int cnt;
    };
    vector<node> tree;

    node combine(node a, node b) {
        if (a.cnt % 2 == 0) return { a.sum + b.sum, a.cnt + b.cnt };
        else return { a.sum - b.sum, a.cnt + b.cnt };
    }

    void build(vector<int> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2*size, {0, 0});
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx == lx + 1) {
            if (lx < a.size()) {
                tree[x] = {a[lx], 1};
            }
        } else {
            int m = (lx + rx) / 2;
            build(a, 2*x+1, lx, m);
            build(a, 2*x+2, m, rx);
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }

    void set(int idx, int v) {
        set(idx, v, 0, 0, size);
    }

    void set(int idx, int v, int x, int lx, int rx) {
        if (rx == lx + 1) {
            tree[x] = { v, 1 };
        } else {
            int m = (lx + rx) / 2;
            if (idx < m)
                set(idx, v, 2*x+1, lx, m);
            else
                set(idx, v, 2*x+2, m, rx);
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }

    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size).sum;
    }

    node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r) return { 0, 0 };
        if (rx <= l) return { 0, 0 };
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return combine(calc(l, r, 2*x+1, lx, m), calc(l, r, 2*x+2, m, rx));
    }
};

int main(void) {
    int n;
    cin >> n;

    vector<int> a(n);
    loop(n) cin >> a[i];

    segtree st;
    st.build(a);

    int m, cmd;
    cin >> m;
    while (m--) {
        cin >> cmd;
        if (cmd == 0) {
            int i, v;
            cin >> i >> v;
            --i;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << st.calc(l, r) << endl;
        }
    }

    return 0;
}
