#include <iostream>
#include <functional>
#include <vector>
#include <string>
using namespace std;

int main(void) {
    int n, m;
    cin >> n >> m;
    n++;

    vector<int> p(n), r(n), score(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = 1;
        score[i] = 0;
    }

    string cmd;
    int x, y, v;

    function<int(int)> get = [&](int x) {
        if (p[x] != x) {
            return get(p[x]);
        }
        return p[x];
    };

    function<int(int)> getScore = [&](int x) {
        int result = score[x];
        while (x != p[x]) {
            x = p[x];
            result += score[x];
        }
        return result;
    };

    while (m--) {
        cin >> cmd;
        if (cmd == "add") {
            cin >> x >> v;
            int px = get(x);
            score[px] += v;
        } else if (cmd == "join") {
            cin >> x >> y;
            int px = get(x);
            int py = get(y);
            if (px == py) continue;
            if (r[px] == r[py]) {
                r[px]++;
            }
            
            if (r[px] > r[py]) {
                p[py] = px;
                score[py] -= score[px];
            } else {
                p[px] = py;
                score[px] -= score[py];
            }
        } else { // get
            cin >> x;
            cout << getScore(x) << endl;
        }
    }

    return 0;
}
