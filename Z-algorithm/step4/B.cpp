#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <numeric>
#include <cstdio>
using namespace std;

#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

const int maxN = 3e6+5;
int z[maxN];

int main(void) {
    fast_io;

    int q;
    cin >> q;

    while (q--) {
        string s, t;
        cin >> s >> t;

        string x = t + "$" + s + s;
        int n = x.size();

        int result = -1;
        int r = 0, l = 0;
        for (int i = 1; i < n; i++) {
            z[i] = 0;

            if (r >= i) {
                z[i] = min(z[i - l], r - i + 1);
            }

            while (i + z[i] < n && x[z[i]] == x[i + z[i]])
                z[i]++;

            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }

            if (z[i] == t.size()) {
                result = i - t.size() - 1;
                break;
            }
        }

        cout << result << endl;
    }

    return 0;
}
