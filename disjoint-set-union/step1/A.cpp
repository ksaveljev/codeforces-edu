#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;

    n++;
    vector<int> p(n), r(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = 1;
    }

    string cmd;
    int a, b;

    function<int(int)> get = [&](int x) {
        if (x != p[x]) {
            p[x] = get(p[x]);
        }
        return p[x];
    };

    while (m--) {
        cin >> cmd >> a >> b;
        if (cmd == "union") {
            int pa = get(a);
            int pb = get(b);
            if (r[pa] == r[pb]) {
                r[pa]++;
                p[pb] = pa;
            } else if (r[pa] > r[pb]) {
                p[pb] = pa;
            } else {
                p[pa] = pb;
            }
        } else { // get
            int pa = get(a);
            int pb = get(b);
            if (pa == pb) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }

    return 0;
}
