#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int b, e, w;
};

struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.resize(n+1);
        sz.resize(n+1);
        for (int i = 0; i <= n; i++) {
            p[i] = i;
            sz[i] = 1;
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

        if (sz[pa] > sz[pb]) {
            swap(pa, pb);
        }

        p[pa] = pb;
        sz[pb] += sz[pa];
    }

    int getSize(int x) {
        int px = get(x);
        return sz[px];
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].b >> edges[i].e >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    int result = INT_MAX;

    for (int i = 0; i < m; i++) {
        DSU dsu(n);
        int j = i;
        while (j < m && dsu.getSize(1) < n) {
            dsu.join(edges[j].b, edges[j].e);
            j++;
        }
        if (dsu.getSize(1) == n) {
            result = min(result, edges[j-1].w - edges[i].w);
        }
    }

    if (result == INT_MAX) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << result << "\n";
    }

    return 0;
}
