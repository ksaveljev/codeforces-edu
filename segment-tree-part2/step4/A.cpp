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
        ll assign;
        ll add;
        ll sum;
    };

    const ll NO_OP = LLONG_MIN;

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, { NO_OP, NO_OP, 0 });
    }

    ll _modify(ll a, ll b) {
        if (a == NO_OP) return b;
        return a + b;
    }

    void propagate(int x, int lx, int rx) {
        if ((tree[x].assign == NO_OP && tree[x].add == NO_OP) || rx == lx + 1) return;
        int m = (lx + rx) / 2;

        if (tree[x].assign != NO_OP) {
            tree[2*x+1].assign = tree[x].assign;
            tree[2*x+1].add = NO_OP;
            tree[2*x+1].sum = (m - lx) * tree[x].assign;

            tree[2*x+2].assign = tree[x].assign;
            tree[2*x+2].add = NO_OP;
            tree[2*x+2].sum = (rx - m) * tree[x].assign;
        }

        if (tree[x].add != NO_OP) {
            tree[2*x+1].add = _modify(tree[2*x+1].add, tree[x].add);
            tree[2*x+1].sum += (m - lx) * tree[x].add;

            tree[2*x+2].add = _modify(tree[2*x+2].add, tree[x].add);
            tree[2*x+2].sum += (m - lx) * tree[x].add;
        }

        tree[x].assign = tree[x].add = NO_OP;
    }

    void assign(int l, int r, ll v) {
        assign(l, r, v, 0, 0, size);
    }

    void assign(int l, int r, ll v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].assign = v;
            tree[x].add = NO_OP;
            tree[x].sum = (rx - lx) * v;
        } else {
            int m = (lx + rx) / 2;
            assign(l, r, v, 2*x+1, lx, m);
            assign(l, r, v, 2*x+2, m, rx);
            tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
        }
    }

    void add(int l, int r, ll v) {
        add(l, r, v, 0, 0, size);
    }

    void add(int l, int r, ll v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].add = _modify(tree[x].add, v);
            tree[x].sum += (rx - lx) * v;
        } else {
            int m = (lx + rx) / 2;
            add(l, r, v, 2*x+1, lx, m);
            add(l, r, v, 2*x+2, m, rx);
            tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
        }
    }

    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return 0;
        if (rx <= l) return 0;
        if (lx >= l && rx <= r) {
            return tree[x].sum;
        } else {
            int m = (lx + rx) / 2;
            ll v1 = sum(l, r, 2*x+1, lx, m);
            ll v2 = sum(l, r, 2*x+2, m, rx);
            return v1 + v2;
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    segtree st;
    st.build(n);

    int cmd, l, r, v;
    while (m--) {
        cin >> cmd >> l >> r;
        if (cmd == 1) {
            cin >> v;
            st.assign(l, r, v);
        } else if (cmd == 2) {
            cin >> v;
            st.add(l, r, v);
        } else {
            cout << st.sum(l, r) << endl;
        }
    }

    return 0;
}
