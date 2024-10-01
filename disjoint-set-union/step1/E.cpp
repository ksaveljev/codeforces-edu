#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;

    n++;
    vector<pair<int,int>> monkies(n);
    vector<int> parent(n), rank(n), result(n, -1);
    vector<vector<int>> group(n);
    for (int i = 1; i < n; i++) {
        parent[i] = i;
        rank[i] = 1;
        group[i].push_back(i);
        cin >> monkies[i].first >> monkies[i].second;
    }

    vector<int> p(m), h(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i] >> h[i];
        if (h[i] == 1) {
            h[i] = monkies[p[i]].first;
            monkies[p[i]].first = -1;
        } else {
            h[i] = monkies[p[i]].second;
            monkies[p[i]].second = -1;
        }
    }

    function<int(int)> get = [&](int x) {
        if (x != parent[x]) parent[x] = get(parent[x]);
        return parent[x];
    };

    function<void(int, int, int)> join = [&](int a, int b, int t) {
        int top = get(1);
        int pa = get(a);
        int pb = get(b);

        if (pa == pb) {
            return;
        }

        if (rank[pa] == rank[pb]) {
            rank[pa]++;
        }

        if (pa == top) {
            for (int i : group[pb]) {
                result[i] = t;
            }
        } else if (pb == top) {
            for (int i : group[pa]) {
                result[i] = t;
            }
        }

        if (rank[pa] > rank[pb]) {
            parent[pb] = pa;
            for (int i : group[pb]) {
                group[pa].push_back(i);
            }
            group[pb].clear();
        } else {
            parent[pa] = pb;
            for (int i : group[pa]) {
                group[pb].push_back(i);
            }
            group[pa].clear();
        }
    };

    for (int i = 1; i < n; i++) {
        if (monkies[i].first != -1) {
            join(i, monkies[i].first, -1);
        }
        if (monkies[i].second != -1) {
            join(i, monkies[i].second, -1);
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        join(p[i], h[i], i);
    }

    for (int i = 1; i < n; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
