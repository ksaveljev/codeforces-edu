#include <iostream>
#include <set>
using namespace std;

int main(void) {
    int t;
    cin >> t;

    int n, m;
    while (t--) {
        cin >> n >> m;

        int a, b;
        bool ok = true;
        set<pair<int,int>> s;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            if (a > b) swap(a, b);
            if (a == b || s.contains({a,b})) {
                ok = false;
            }
            s.insert({a,b});
        }

        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
