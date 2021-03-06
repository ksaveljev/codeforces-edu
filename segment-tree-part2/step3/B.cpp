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
        int sum;
        bool inverse;
    };

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2*size, {0, false});
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].inverse == false || rx == lx + 1) return;
        int m = (lx + rx) / 2;
        tree[2*x+1].inverse = !tree[2*x+1].inverse;
        tree[2*x+1].sum = (m - lx) - tree[2*x+1].sum;
        tree[2*x+2].inverse = !tree[2*x+2].inverse;
        tree[2*x+2].sum = (rx - m) - tree[2*x+2].sum;
        tree[x].inverse = false;
    }

    void update(int l, int r) {
        update(l, r, 0, 0, size);
    }

    void update(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].inverse = true;
            tree[x].sum = (rx - lx) - tree[x].sum;
        } else {
            int m = (lx + rx) / 2;
            update(l, r, 2*x+1, lx, m);
            update(l, r, 2*x+2, m, rx);
            tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
        }
    }

    int get(int k) {
        return get(k, 0, 0, size);
    }

    int get(int k, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (rx == lx + 1) {
            return lx;
        }
        int m = (lx + rx) / 2;
        if (tree[2*x+1].sum <= k) {
            return get(k - tree[2*x+1].sum, 2*x+2, m, rx);
        }
        return get(k, 2*x+1, lx, m);
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
            int l, r;
            cin >> l >> r;
            st.update(l, r);
        } else {
            int k;
            cin >> k;
            cout << st.get(k) << endl;
        }
    }

    return 0;
}
