#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int BLOCK_SIZE = 220;

struct Query {
    int l, r;
    int idx;
};

struct Edge {
    int u, v;
};

struct Snapshot {
    int pa, pb, sz, components;
};

struct DSU {
    int N;
    int components;
    vector<int> parent, sz;
    vector<Snapshot> snapshots;
    vector<int> versions;

    DSU(int n) {
        N = n;
        components = n;
        parent.resize(n+1);
        sz.resize(n+1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    void reset() {
        components = N;
        for (int i = 0; i <= N; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        snapshots.clear();
        versions.clear();
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
        int last = versions.back();
        versions.pop_back();
        while (snapshots.size() != last) {
            auto s = snapshots.back();
            snapshots.pop_back();
            components = s.components;
            sz[s.pb] = s.sz;
            parent[s.pa] = s.pa;
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    vector<Edge> edges(m);
    for (auto &e : edges) {
        cin >> e.u >> e.v;
    }

    int k;
    cin >> k;

    int number_of_blocks = k / BLOCK_SIZE + 1;
    vector<vector<Query>> queries(number_of_blocks);
    vector<int> result(k);

    int l, r;
    for (int i = 0; i < k; i++) {
        cin >> l >> r;
        l--, r--;

        if (l / BLOCK_SIZE == r / BLOCK_SIZE) {
            // calculate answer right away
            dsu.reset();
            for (int x = l; x <= r; x++) {
                dsu.join(edges[x].u, edges[x].v);
            }
            result[i] = dsu.components;
        } else {
            queries[l / BLOCK_SIZE].push_back({l, r, i});
        }
    }

    for (int i = 0; i < number_of_blocks; i++) {
        sort(queries[i].begin(), queries[i].end(), [](const Query &a, const Query &b) {
            return a.r < b.r;
        });

        dsu.reset();
        int r = BLOCK_SIZE * (i + 1);
        for (int j = 0; j < queries[i].size(); j++) {
            while (r <= queries[i][j].r) {
                dsu.join(edges[r].u, edges[r].v);
                r++;
            }

            dsu.persist();

            int l = BLOCK_SIZE * (i + 1) - 1;
            while (l >= queries[i][j].l) {
                dsu.join(edges[l].u, edges[l].v);
                l--;
            }

            result[queries[i][j].idx] = dsu.components;
            dsu.rollback();
        }
    }

    for (int i = 0; i < k; i++) {
        cout << result[i] << '\n';
    }

    return 0;
}
