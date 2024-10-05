#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main(void) {
    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 0; i <= n; i++) {
        p[i] = i;
    }

    function<int(int)> get = [&](int x) {
        if (x != p[x]) p[x] = get(p[x]);
        return p[x];
    };

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        int px = get(x);
        if (px == n) {
            p[px] = 1;
        } else {
            p[px] = px + 1;
        }

        cout << px << endl;
    }

    return 0;
}
