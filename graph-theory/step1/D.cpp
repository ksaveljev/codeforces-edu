#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n+1);
        sz.resize(n+1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int get(int x) {
        if (x != parent[x]) parent[x] = get(parent[x]);
        return parent[x];
    }

    void join(int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;

        if (sz[pa] > sz[pb]) swap(pa, pb);

        parent[pa] = pb;
        sz[pb] += sz[pa];
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    vector<int> a(100001, 0);

    int n, m, k;
    while (t--) {
        cin >> n >> m >> k;

        a.assign(100001, 0);

        int x;
        for (int i = 0; i < k; i++) {
            cin >> x;
            a[x] = 1;
        }

        DSU dsu(n);
        int u, v;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            dsu.join(u, v);
        }

        set<int> s;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) {
                s.insert(dsu.get(i));
            }
        }

        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 0) {
                int p = dsu.get(i);
                if (s.contains(p)) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
