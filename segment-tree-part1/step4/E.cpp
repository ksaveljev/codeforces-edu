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

const int INF = 1e9+7;

struct segtree {
    int size;
    vector<int> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2*size, INF);
    }

    void set(int idx, int v) {
        set(idx, v, 0, 0, size);
    }

    void set(int idx, int v, int x, int lx, int rx) {
        if (rx == lx + 1) {
            tree[x] = v;
        } else {
            int m = (lx + rx) / 2;
            if (idx < m)
                set(idx, v, 2*x+1, lx, m);
            else
                set(idx, v, 2*x+2, m, rx);
            tree[x] = min(tree[2*x+1], tree[2*x+2]);
        }
    }

    int calc(int l, int r, int p) {
        return calc(l, r, p, 0, 0, size);
    }

    int calc(int l, int r, int p, int x, int lx, int rx) {
        if (rx <= l) return 0;
        if (lx >= r) return 0;
        if (tree[x] > p) return 0;

        if (rx == lx + 1) {
            tree[x] = INF;
            return 1;
        } else {
            int m = (lx + rx) / 2;
            int s1 = calc(l, r, p, 2*x+1, lx, m);
            int s2 = calc(l, r, p, 2*x+2, m, rx);
            tree[x] = min(tree[2*x+1], tree[2*x+2]);
            return s1 + s2;
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
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r, p;
            cin >> l >> r >> p;
            cout << st.calc(l, r, p) << endl;
        }
    }

    return 0;
}
