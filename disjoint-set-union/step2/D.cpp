#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, steps;

    DSU(int n) {
        p.resize(n+1);
        steps.resize(n+1);
        for (int i = 0; i <= n; i++) {
            p[i] = i;
            steps[i] = 0;
        }
    }

    int get(int x) {
        if (p[x] == x) return x;

        int px = get(p[x]);
        if (p[x] != px) {
            steps[x] += steps[p[x]];
            p[x] = px;
        }
        return px;
    }

    void join(int child, int parent) {
        p[child] = parent;
        steps[child] += 1;
    }

    int count(int x) {
        int px = get(x);
        int result = steps[x];

        if (px != p[x]) {
            result += count(p[x]);
        }

        return result;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    int t, a, b, c;
    while (m--) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b;
            dsu.join(a, b);
        } else {
            cin >> c;
            cout << dsu.count(c) << '\n';
        }
    }

    return 0;
}
