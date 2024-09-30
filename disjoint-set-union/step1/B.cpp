#include <iostream>
#include <string>
#include <functional>
using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;

    n++;
    vector<int> p(n), r(n), sz(n), _min(n), _max(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = 1;
        sz[i] = 1;
        _min[i] = i;
        _max[i] = i;
    }

    function<int(int)> get = [&](int x) {
        if (p[x] != x) {
            p[x] = get(p[x]);
        }
        return p[x];
    };

    string cmd;
    int u, v;

    while (m--) {
        cin >> cmd;
        if (cmd == "union") {
            cin >> u >> v;
            int pa = get(u);
            int pb = get(v);
            if (pa == pb) {
                continue;
            }
            if (r[pa] == r[pb]) {
                r[pa]++;
                p[pb] = pa;
                sz[pa] += sz[pb];
                _min[pa] = min(_min[pa], _min[pb]);
                _max[pa] = max(_max[pa], _max[pb]);
            } else if (r[pa] > r[pb]) {
                p[pb] = pa;
                sz[pa] += sz[pb];
                _min[pa] = min(_min[pa], _min[pb]);
                _max[pa] = max(_max[pa], _max[pb]);
            } else {
                p[pa] = pb;
                sz[pb] += sz[pa];
                _min[pb] = min(_min[pa], _min[pb]);
                _max[pb] = max(_max[pa], _max[pb]);
            }
        } else {
            cin >> v;
            int pa = get(v);
            cout << _min[pa] << " " << _max[pa] << " " << sz[pa] << endl;
        }
    }

    return 0;
}
