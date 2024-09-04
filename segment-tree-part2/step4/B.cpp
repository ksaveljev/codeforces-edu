#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

struct segtree {
    struct node {
        ll a, d;
    };

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {0, 0});
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].a == 0 && tree[x].d == 0) return;
        if (rx - lx == 1) return;

        int m = (lx + rx) / 2;

        tree[2*x+1].a += tree[x].a;
        tree[2*x+1].d += tree[x].d;

        tree[2*x+2].a += tree[x].a + (m - lx) * tree[x].d;
        tree[2*x+2].d += tree[x].d;

        tree[x].a = tree[x].d = 0;
    }

    void modify(int l, int r, ll a, ll d) {
        modify(l, r, a, d, 0, 0, size);
    }

    void modify(int l, int r, ll a, ll d, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].a += a + (lx - l) * d;
            tree[x].d += d;
        } else {
            int m = (lx + rx) / 2;
            modify(l, r, a, d, 2 * x + 1, lx, m);
            modify(l ,r, a, d, 2 * x + 2, m, rx);
        }
    }

    ll get(int i) {
        return get(i, 0, 0, size);
    }

    ll get(int i, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (rx - lx == 1) {
            return tree[x].a;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            return get(i, 2 * x + 1, lx, m);
        } else {
            return get(i, 2 * x + 2, m, rx);
        }
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
            int l, r, a, d;
            cin >> l >> r >> a >> d;
            l--;
            st.modify(l, r, a, d);
        } else {
            int i;
            cin >> i;
            i--;
            cout << st.get(i) << endl;
        }
    }

    return 0;
}
