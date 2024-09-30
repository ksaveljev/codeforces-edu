#include <iostream>
#include <vector>
#include <functional>
#include <string>
using namespace std;

const int ASK = 0;
const int CUT = 1;

struct cmd {
    int t, u, v;
};

int main(void) {
    int n, m, k;
    cin >> n >> m >> k;

    n++;

    vector<int> p(n), r(n);
    vector<cmd> cmds(k);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = 1;
    }

    function<int(int)> get = [&](int x) {
        if (x != p[x]) {
            p[x] = get(p[x]);
        }
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

    string s;
    int u, v;

    while (m--) {
        cin >> u >> v;
    }

    int cnt = 0;
    for (int i = 0; i < k; i++) {
        cin >> s >> u >> v;
        if (s == "ask") {
            cmds[i] = {ASK, u, v};
            cnt++;
        } else {
            cmds[i] = {CUT, u, v};
        }
    }

    vector<bool> result(cnt);
    for (int i = k - 1; i >= 0; i--) {
        if (cmds[i].t == ASK) {
            int pa = get(cmds[i].u);
            int pb = get(cmds[i].v);
            result[--cnt] = pa == pb;
        } else {
            join(cmds[i].u, cmds[i].v);
        }
    }

    for (int i = 0; i < result.size(); i++) {
        if (result[i]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}
