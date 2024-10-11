#include <iostream>
#include <vector>
using namespace std;

struct Snapshot {
    int pa;
    int pb;
    int sz;
    int count;
};

struct DSU {
    int count;
    vector<int> parent, sz;
    vector<Snapshot> snapshots;
    vector<int> versions;

    DSU(int n) {
        count = n;
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

        snapshots.push_back({
            pa, pb, sz[pb], count
        });

        parent[pa] = pb;
        sz[pb] += sz[pa];
        count--;
    }

    void persist() {
        versions.push_back(snapshots.size());
    }

    void rollback() {
        int version = versions.back();
        versions.pop_back();
        while (snapshots.size() > version) {
            auto [_pa, _pb, _sz, _count] = snapshots.back();
            snapshots.pop_back();
            count = _count;
            sz[_pb] = _sz;
            parent[_pa] = _pa;
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

    string cmd;
    int a, b;

    while (m--) {
        cin >> cmd;
        if (cmd[0] == 'p') {
            dsu.persist();
        } else if (cmd[0] == 'u') {
            cin >> a >> b;
            dsu.join(a, b);
            cout << dsu.count << '\n';
        } else { // cmd[0] == 'r'
            dsu.rollback();
            cout << dsu.count << '\n';
        }
    }

    return 0;
}
