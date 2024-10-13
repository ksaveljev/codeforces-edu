#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <functional>
using namespace std;

struct Edge {
    int u, v;
};

struct Snapshot {
    int pa, pb, sz, components;
};

struct DSU {
    int components;
    vector<int> parent, sz;
    vector<Snapshot> snapshots;
    vector<int> versions;

    DSU(int n) {
        components = n;
        parent.resize(n+1);
        sz.resize(n+1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int get(int x) {
        if (parent[x] == x) return x;
        return get(parent[x]);
    }

    void join(int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;

        if (sz[pa] > sz[pb]) swap(pa, pb);

        snapshots.push_back({pa, pb, sz[pb], components});

        parent[pa] = pb;
        sz[pb] += sz[pa];
        components--;
    }

    void persist() {
        versions.push_back(snapshots.size());
    }

    void rollback() {
        int version = versions.back();
        versions.pop_back();
        while (snapshots.size() > version) {
            auto s = snapshots.back();
            snapshots.pop_back();
            parent[s.pa] = s.pa;
            sz[s.pb] = s.sz;
            components = s.components;
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    if (m == 0) return 0;

    DSU dsu(n);
    vector<int> queries(m, 0);
    vector<vector<Edge>> edges(4*m);

    function<void(int,int,int,int,int,int,int)> add = [&](int x, int lx, int rx, int l, int r, int u, int v) {
        if (lx >= r || rx <= l) {
            return;
        }
        if (lx >= l && rx <= r) {
            edges[x].push_back({u, v});
        } else {
            int m = (lx + rx) / 2;
            add(2*x+1, lx, m, l, r, u, v);
            add(2*x+2, m, rx, l, r, u, v);
        }
    };

    char t;
    int u, v;
    map<pair<int,int>, int> left;
    set<pair<int,int>> open;
    int nQueries = 0;

    for (int i = 0; i < m; i++) {
        cin >> t;
        if (t == '?') {
            nQueries++;
            queries[i] = 1;
        } else {
            cin >> u >> v;
            if (u > v) swap(u, v);
            if (t == '+') {
                left[{u, v}] = i;
                open.insert({u, v});
            } else {
                add(0, 0, m, left[{u, v}], i, u, v);
                open.erase({u, v});
            }
        }
    }

    for (const auto &p : open) {
        add(0, 0, m, left[p], m, p.first, p.second);
    }

    if (nQueries == 0) return 0;

    vector<int> result(nQueries);
    int q = 0;

    function<void(int,int,int)> solve = [&](int x, int lx, int rx) {
        dsu.persist();

        for (const auto &edge : edges[x]) {
            dsu.join(edge.u, edge.v);
        }

        if (rx - lx == 1) {
            if (queries[lx] == 1) {
                result[q++] = dsu.components;
            }
        } else {
            int m = (lx + rx) / 2;

            solve(2*x+1, lx, m);
            solve(2*x+2, m, rx);
        }
        dsu.rollback();
    };

    solve(0, 0, m);

    for (int i = 0; i < nQueries; i++) {
        cout << result[i] << '\n';
    }

    return 0;
}
