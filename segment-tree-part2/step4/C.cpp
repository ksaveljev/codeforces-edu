#include <iostream>
#include <vector>
using namespace std;

int MOD = 500000;

struct segtree {
    struct val {
        int count;
        int sum;
        char left;
        char right;
    };

    struct node {
        char paint;
        val value;
    };

    char NO_OP = 'N';

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, {NO_OP, {0, 0, 'W', 'W'}});
    }

    val combine(val &a, val &b) {
        int new_count = a.count + b.count;
        if (a.right == 'B' && b.left == 'B') {
            new_count--;
        }

        return {
            new_count,
            a.sum + b.sum,
            a.left,
            b.right
        };
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].paint == NO_OP || rx - lx == 1) return;

        int m = (lx + rx) / 2;

        tree[2*x+1].paint = tree[x].paint;
        tree[2*x+2].paint = tree[x].paint;

        if (tree[x].paint == 'W') {
            tree[2*x+1].value = {0, 0, 'W', 'W'};
            tree[2*x+2].value = {0, 0, 'W', 'W'};
        } else {
            tree[2*x+1].value = {1, m - lx, 'B', 'B'};
            tree[2*x+2].value = {1, rx - m, 'B', 'B'};
        }

        tree[x].paint = NO_OP;
    }

    void modify(int l, int r, char v) {
        modify(l, r, v, 0, 0, size);
    }

    void modify(int l, int r, char v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            if (v == 'W') {
                tree[x].paint = 'W';
                tree[x].value = {0, 0, 'W', 'W'};
            } else {
                tree[x].paint = 'B';
                tree[x].value = {1, rx - lx, 'B', 'B'};
            }
        } else {
            int m = (lx + rx) / 2;
            modify(l, r, v, 2 * x + 1, lx, m);
            modify(l, r, v, 2 * x + 2, m, rx);
            tree[x].value = combine(tree[2*x+1].value, tree[2*x+2].value);
        }
    }

    node info() {
        return info(0, 0, size);
    }

    node info(int x, int lx, int rx) {
        propagate(x, lx, rx);
        return tree[0];
    }
};

int main(void) {
    int n;
    cin >> n;

    segtree st;
    st.build(1e6);

    char c;
    int x, l;

    for (int i = 0; i < n; i++) {
        cin >> c >> x >> l;
        x += MOD;

        st.modify(x, x + l, c);
        auto x = st.info();
        cout << x.value.count << " " << x.value.sum << endl;
    }

    return 0;
}
