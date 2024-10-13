#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int t;
    cin >> t;

    vector<int> count(100001, 0);

    int n, m;
    while (t--) {
        cin >> n >> m;

        count.assign(100001, 0);

        int a, b;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            count[a]++;
            count[b]++;
        }

        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << count[i];
        }
        cout << '\n';
    }

    return 0;
}
