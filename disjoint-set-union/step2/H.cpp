#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct Edge {
    int b, e;
    ll w;
    int idx;
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

    int n, m;
    ll s;

    cin >> n >> m >> s;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].b >> edges[i].e >> edges[i].w;
        edges[i].idx = i + 1;
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w > b.w;
    });

    DSU dsu(n);
    vector<Edge> remaining;

    for (int i = 0; i < m; i++) {
        if (dsu.size(1) == n) {
            remaining.push_back(edges[i]);
            continue;
        }

        int pb = dsu.get(edges[i].b);
        int pe = dsu.get(edges[i].e);
        if (pb == pe) {
            remaining.push_back(edges[i]);
        } else {
            dsu.join(pb, pe);
        }
    }

    ll x = 0;
    vector<int> result;
    for (int i = remaining.size() - 1; i >= 0; i--) {
        if (x + remaining[i].w <= s) {
            x += remaining[i].w;
            result.push_back(remaining[i].idx);
        } else {
            break;
        }
    }

    cout << result.size() << '\n';
    for (int i = 0; i < result.size(); i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << '\n';

    return 0;
}
