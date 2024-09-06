#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct segtree {
    struct op {
        int min;
        int max;
    };
    struct node {
        op modify;
        int value;
    };
    int size;
    vector<node> tree;

    op NO_OP = {INT_MAX, INT_MIN};

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {NO_OP, 0});
    }

    op _modify(op &a, op &b) {
        if (a.min == NO_OP.min && a.max == NO_OP.max) return b;

        if (b.max <= a.min) return {b.max, b.max};
        if (b.min >= a.max) return {b.min, b.min};
        if (b.min <= a.min && a.max <= b.max) return a;
        if (a.min <= b.min && b.max <= a.max) return b;
        if (b.min <= a.min) return {a.min, b.max};
        return {b.min, a.max};
    }

    int _modify(int a, op &b) {
        // make sure a is in the range of b, adjusting it in case it is out of range
        return max(min(a, b.max), b.min);
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].modify.min == NO_OP.min && tree[x].modify.max == NO_OP.max) return;
        if (rx - lx == 1) return;

        tree[2*x+1].modify = _modify(tree[2*x+1].modify, tree[x].modify);
        tree[2*x+1].value = _modify(tree[2*x+1].value, tree[x].modify);
        tree[2*x+2].modify = _modify(tree[2*x+2].modify, tree[x].modify);
        tree[2*x+2].value = _modify(tree[2*x+2].value, tree[x].modify);

        tree[x].modify = NO_OP;
    }

    void update(int l, int r, op v) {
        update(l, r, v, 0, 0, size);
    }

    void update(int l, int r, op v, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].modify = _modify(tree[x].modify, v);
            tree[x].value = _modify(tree[x].value, v);
        } else {
            int m = (lx + rx) / 2;
            update(l, r, v, 2 * x + 1, lx, m);
            update(l, r, v, 2 * x + 2, m, rx);
            tree[x].value = min(tree[2*x+1].value, tree[2*x+2].value);
        }
    }

    void collect(vector<int> &result) {
        collect(result, 0, 0, size);
    }

    void collect(vector<int> &result, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < result.size()) {
                result[lx] = tree[x].value;
            }
        } else {
            propagate(x, lx, rx);
            int m = (lx + rx) / 2;
            collect(result, 2 * x + 1, lx, m);
            collect(result, 2 * x + 2, m, rx);
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    segtree st;
    st.init(n+1);

    int t, l, r, h;
    while (k--) {
        cin >> t >> l >> r >> h;
        if (t == 1) {
            st.update(l, r+1, {h, INT_MAX});
        } else {
            st.update(l, r+1, {INT_MIN, h});
        }
    }

    vector<int> result(n);
    st.collect(result);

    for (int i = 0; i < n; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
