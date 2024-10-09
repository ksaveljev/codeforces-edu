#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
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

    bool connected(int a, int b) {
        return get(a) == get(b);
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    DSU dsu(n<<1);
    int a, b;
    int result = -1;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--;

        dsu.join((a << 1) | 0, (b << 1) | 1);
        dsu.join((a << 1) | 1, (b << 1) | 0);

        if (dsu.connected((a << 1) | 0, (a << 1) | 1)) {
            result = i + 1;
            break;
        }
    }

    cout << result << '\n';

    return 0;
}
