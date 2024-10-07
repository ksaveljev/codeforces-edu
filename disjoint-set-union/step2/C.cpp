#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> n, p, r, mx;
    DSU(int n) {
        p.resize(n + 1);
        r.resize(n + 1);
        mx.resize(n + 1);

        for (int i = 0; i <= n; i++) {
            p[i] = i;
            r[i] = 1;
            mx[i] = i;
        }
    }

    int get(int x) {
        if (x != p[x]) p[x] = get(p[x]);
        return p[x];
    }

    void join(int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;

        if (r[pa] == r[pb]) r[pa]++;

        if (r[pa] > r[pb]) {
            p[pb] = pa;
            mx[pa] = max(mx[pa], mx[pb]);
        } else {
            p[pa] = pb;
            mx[pb] = max(mx[pa], mx[pb]);
        }
    }

    int getMax(int x) {
        return mx[x];
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    DSU dsu(n);
    DSU dsuSeg(n);

    int t, x, y;
    while (q--) {
        cin >> t >> x >> y;

        if (t == 1) {
            dsu.join(x, y);
        } else if (t == 2) {
            int c = dsuSeg.getMax(dsuSeg.get(x));
            while (c < y) {
                dsu.join(c, y);
                dsuSeg.join(c, c + 1);
                c = dsuSeg.getMax(dsuSeg.get(c));
            }
            dsu.join(c, y);
        } else {
            cout << (dsu.get(x) == dsu.get(y) ? "YES" : "NO") << '\n';
        }
    }
}
