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

struct segtree {
    struct node {
        int max;
        int modify;
    };

    const int NO_OP = INT_MAX;

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {0, NO_OP});
    }

    int _modify(int a, int b) {
        if (a == NO_OP) return b;
        return a + b;
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].modify == NO_OP || rx == lx + 1) return;
        tree[2*x+1].modify = _modify(tree[2*x+1].modify, tree[x].modify);
        tree[2*x+1].max = tree[2*x+1].max + tree[x].modify;
        tree[2*x+2].modify = _modify(tree[2*x+2].modify, tree[x].modify);
        tree[2*x+2].max = tree[2*x+2].max + tree[x].modify;
        tree[x].modify = NO_OP;
    }

    void update(int l, int r, int v) {
        update(l, r, v, 0, 0, size);
    }

    void update(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].modify = v;
            tree[x].max += v;
        } else {
            int m = (lx + rx) / 2;
            update(l, r, v, 2*x+1, lx, m);
            update(l, r, v, 2*x+2, m, rx);
            tree[x].max = max(tree[2*x+1].max, tree[2*x+2].max);
        }
    }

    int get(int v, int l) {
        return get(v, l, 0, 0, size);
    }

    int get(int v, int l, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (rx <= l) return -1;
        if (tree[x].max < v) return -1;
        if (rx == lx + 1) return lx;

        int m = (lx + rx) / 2;
        int res = get(v, l, 2*x+1, lx, m);
        if (res == -1)
            res = get(v, l, 2*x+2, m, rx);
        return res;
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
            st.update(l, r, v);
        } else {
            int x, l;
            cin >> x >> l;
            cout << st.get(x, l) << endl;
        }
    }

    return 0;
}
