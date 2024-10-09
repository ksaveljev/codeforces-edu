#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;

    DSU(int n) {
        p.resize(n+1);
        r.resize(n+1);
        for (int i = 0; i <= n; i++) {
            p[i] = i;
            r[i] = 1;
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
        } else {
            p[pa] = pb;
        }
    }

    bool connected(int a, int b) {
        return get(a) == get(b);
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    DSU dsu(n << 1);
    int shift = 0;
    int t, a, b;

    while (m--) {
        cin >> t >> a >> b;
        int x = (a + shift) % n;
        int y = (b + shift) % n;

        if (t == 0) {
            dsu.join((x << 1) | 0, (y << 1) | 1);
            dsu.join((x << 1) | 1, (y << 1) | 0);
        } else {
            bool connected = dsu.connected((x << 1) | 0, (y << 1) | 0) || dsu.connected((x << 1) | 1, (y << 1) | 1);
            if (connected) {
                cout << "YES\n";
                shift = (shift + 1) % n;
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
