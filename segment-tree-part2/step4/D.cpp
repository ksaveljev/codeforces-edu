#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

struct segtree {
    struct node {
        ll d;
        ll s;
        ll ws;
    };

    ll size;
    vector<node> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {0, 0, 0});
    }

    void propagate(ll x, ll lx, ll rx) {
        if (tree[x].d == 0 || rx - lx == 1) return;

        tree[2*x+1].d += tree[x].d;
        tree[2*x+2].d += tree[x].d;

        ll m = (lx + rx) / 2;

        tree[2*x+1].s += (m - lx) * tree[x].d;
        tree[2*x+1].ws += tree[x].d * (m - lx) * (m - lx + 1) / 2;

        tree[2*x+2].s += (rx - m) * tree[x].d;
        tree[2*x+2].ws += tree[x].d * (rx - m) * (rx - m + 1) / 2;

        tree[x].d = 0;
    }

    void modify(ll l, ll r, ll d) {
        modify(l, r, d, 0, 0, size);
    }

    void modify(ll l, ll r, ll d, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].d += d;
            tree[x].s += d * (rx - lx);
            tree[x].ws += d * (rx - lx) * (rx - lx + 1) / 2;
        } else {
            ll m = (lx + rx) / 2;
            modify(l, r, d, 2 * x + 1, lx, m);
            modify(l, r, d, 2 * x + 2, m, rx);
            tree[x].s = tree[2 * x + 1].s + tree[2 * x + 2].s;
            tree[x].ws = tree[2 * x + 1].ws + tree[2 * x + 2].ws + (m - lx) * tree[2 * x + 2].s;
        }
    }

    ll query(ll l, ll r) {
        return query(l, r, 0, 0, size).ws;
    }

    node add(node s1, node s2, ll d) {
        if (s1.d == 0 && s1.s == LLONG_MIN && s1.ws == LLONG_MIN) return s2;
        if (s2.d == 0 && s2.s == LLONG_MIN && s2.ws == LLONG_MIN) return s1;
        return {0, s1.s + s2.s, s1.ws + s2.ws + d * s2.s};
    }

    node query(ll l, ll r, ll x, ll lx, ll rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return {0, LLONG_MIN, LLONG_MIN};
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        node s1 = query(l, r, 2 * x + 1, lx, m);
        node s2 = query(l, r, 2 * x + 2, m, rx);

        return add(s1, s2, m - max(lx, l));
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    segtree st;
    st.init(n);

    int v;
    for (int i = 0; i < n; i++) {
        cin >> v;
        st.modify(i, i + 1, v);
    }

    int t, l, r, d;
    while (m--) {
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            cin >> d;
            st.modify(l, r, d);
        } else {
            cout << st.query(l, r) << endl;
        }
    }

    return 0;
}
