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
    struct node {
        int freq[41];
        ll cnt;
    };

    int size;
    vector<node> tree;
    node ZERO;

    node combine(node a, node b) {
        node result;
        memset(result.freq, 0, sizeof result.freq);

        loop(41) result.freq[i] = a.freq[i] + b.freq[i];
        ll count = a.cnt + b.cnt;

        rep (i, 0, 41) {
            rep (j, i + 1, 41) {
                count += b.freq[i] * a.freq[j];
            }
        }

        result.cnt = count;

        return result;
    }

    void build(vector<int> &a) {
        memset(ZERO.freq, 0, sizeof ZERO.freq);
        ZERO.cnt = 0;

        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, ZERO);
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx == lx + 1) {
            if (lx < a.size()) {
                memset(tree[x].freq, 0, sizeof tree[x].freq);
                tree[x].freq[a[lx]]++;
                tree[x].cnt = 0;
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
            memset(tree[x].freq, 0, sizeof tree[x].freq);
            tree[x].freq[v]++;
            tree[x].cnt = 0;
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
        return (calc(l, r, 0, 0, size)).cnt;
    }

    node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r) return ZERO;
        if (rx <= l) return ZERO;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return combine(calc(l, r, 2*x+1, lx, m), calc(l, r, 2*x+2, m, rx));
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    loop(n) cin >> a[i];;

    segtree st;
    st.build(a);

    int cmd;
    while (q--) {
        cin >> cmd;
        if (cmd == 1) {
            int L, R;
            cin >> L >> R, --L;
            cout << st.calc(L, R) << endl;
        } else {
            int i, v;
            cin >> i >> v, --i;
            st.set(i, v);
        }
    }

    return 0;
}
