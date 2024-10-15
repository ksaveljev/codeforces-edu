#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    vector<int> cnt(100001, 0);
    vector<int> a(100001, 0);
    int n, m, k;
    while (t--) {
        cin >> n >> m >> k;

        cnt.assign(100001, 0);

        bool simple = true;

        for (int i = 0; i < k; i++) {
            cin >> a[i];
            cnt[a[i]]++;
            if (cnt[a[i]] > 1) {
                if (!(i == k - 1 && a[0] == a[k-1])) {
                    simple = false;
                }
            }
        }

        int u, v;
        set<pair<int,int>> edges;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            if (u > v) swap(u, v);
            edges.insert({u, v});
        }

        bool connected = true;
        for (int i = 1; i < k; i++) {
            u = a[i-1];
            v = a[i];
            if (u > v) swap(u, v);
            if (!edges.contains({u,v})) {
                connected = false;
                break;
            }
        }

        if (!connected) {
            cout << "none\n";
        } else if (a[0] == a[k-1] && simple) {
            cout << "simple cycle\n";
        } else if (a[0] == a[k-1]) {
            cout << "cycle\n";
        } else if (simple) {
            cout << "simple path\n";
        } else {
            cout << "path\n";
        }
    }

    return 0;
}
