#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    n += 2;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    function<int(int)> get = [&](int x) {
        if (x != p[x]) p[x] = get(p[x]);
        return p[x];
    };

    // make b parent of a
    function<void(int, int)> join = [&](int a, int b) {
        int pa = get(a);
        int pb = get(b);
        if (pa == pb) return;
        p[pa] = pb;
    };

    char cmd;
    int v;

    while (m--) {
        cin >> cmd >> v;
        if (cmd == '?') {
            int pv = get(v);
            if (pv == n - 1) {
                cout << -1 << endl;
            } else {
                cout << pv << endl;
            }
        } else {
            join(v, v + 1);
        }
    }

    return 0;
}
