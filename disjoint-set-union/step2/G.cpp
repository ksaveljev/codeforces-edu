#include <iostream>
#include <vector>
#include <algorithm>
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

        if (sz[pa] > sz[pb]) swap(pa, pb);

        p[pa] = pb;
        sz[pb] += sz[pa];
    }

    int size(int x) {
        return sz[get(x)];
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<Edge> edges(k);
    for (int i = 0; i < k; i++) {
        cin >> edges[i].b >> edges[i].e >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    int result;
    for (Edge edge : edges) {
        dsu.join(edge.b, edge.e);
        if (dsu.size(1) == n) {
            result = edge.w;
            break;
        }
    }

    cout << result << '\n';

    return 0;
}
