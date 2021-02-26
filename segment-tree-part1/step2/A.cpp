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
    struct node {
        ll sum, pref, suf, seg;
    };
    vector<node> tree;

    const node ZERO = { 0, 0, 0, 0 };

    node combine(node a, node b) {
        return {
            a.sum + b.sum,
            max(a.pref, a.sum + b.pref),
            max(b.suf, a.suf + b.sum),
            max(max(a.seg, b.seg), a.suf + b.pref)
        };
    }

    node one_element(int v) {
        return {
            v,
            max(v, 0),
            max(v, 0),
            max(v, 0)
        };
    }

    void build(vector<int> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, ZERO);
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx == lx + 1) {
            if (lx < a.size()) {
                tree[x] = one_element(a[lx]);
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
            tree[x] = one_element(v);
        } else {
            int m = (lx + rx) / 2;
            if (idx < m) {
                set(idx, v, 2*x+1, lx, m);
            } else {
                set(idx, v, 2*x+2, m, rx);
            }
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    loop(n) cin >> a[i];

    segtree st;
    st.build(a);

    cout << st.tree[0].seg << endl;

    int i, v;
    while (m--) {
        cin >> i >> v;
        st.set(i, v);
        cout << st.tree[0].seg << endl;
    }

    return 0;
}
