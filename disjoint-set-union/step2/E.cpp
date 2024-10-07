#include <iostream>
#include <vector>
#include <functional>
using namespace std;

struct Edge {
    int b, e, w;
};

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<int> p(n+1), r(n+1);
    for (int i = 0; i <= n; i++) {
        p[i] = i;
        r[i] = 1;
    }

    function<int(int)> get = [&](int x) {
        if (x != p[x]) p[x] = get(p[x]);
        return p[x];
    };

    function<void(int, int)> join = [&](int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;

        if (r[pa] == r[pb]) r[pa]++;

        if (r[pa] > r[pb]) {
            p[pb] = pa;
        } else {
            p[pa] = pb;
        }
    };

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].b >> edges[i].e >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    long long result = 0;

    for (auto edge : edges) {
        int pb = get(edge.b);
        int pe = get(edge.e);
        if (pb == pe) continue;
        result += edge.w;
        join(edge.b, edge.e);
    }

    cout << result << endl;

    return 0;
}
