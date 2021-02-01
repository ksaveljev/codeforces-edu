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

const int maxN = 2e6+10;
int z1[maxN];
int z2[maxN];

int main(void) {
    fast_io;
    int q;
    string a, b;

    cin >> q;
    while (q--) {
        cin >> a >> b;
        string aa = a + "$" + b;
        string bb = b + "$" + a;

        int z1max = 0;
        int z2max = 0;

        int l = 0, r = 0;
        int n = aa.size();
        for (int i = 1; i < n; i++) {
            z1[i] = 0;

            if (r >= i)
                z1[i] = min(z1[i - l], r - i + 1);

            while (i + z1[i] < n && aa[z1[i]] == aa[i+z1[i]])
                z1[i]++;

            if (i > a.size()) {
                if (z1[i] == a.size()) {
                    z1max = z1[i];
                } else if (i + z1[i] == aa.size()) {
                    z1max = max(z1max, z1[i]);
                }
            }

            if (r < i + z1[i] - 1) {
                l = i;
                r = i + z1[i] - 1;
            }
        }

        l = r = 0;
        for (int i = 1; i < n; i++) {
            z2[i] = 0;

            if (r >= i)
                z2[i] = min(z2[i - l], r - i + 1);

            while (i + z2[i] < n && bb[z2[i]] == bb[i+z2[i]])
                z2[i]++;

            if (i > b.size()) {
                if (z2[i] == b.size()) {
                    z2max = z2[i];
                } else if (i + z2[i] == bb.size()) {
                    z2max = max(z2max, z2[i]);
                }
            }

            if (r < i + z2[i] - 1) {
                l = i;
                r = i + z2[i] - 1;
            }
        }

        if (z1max == a.size()) {
            cout << b << endl;
        } else if (z2max == b.size()) {
            cout << a << endl;
        } else if (z1max >= z2max) {
            cout << b.substr(0, b.size() - z1max) << a << endl;
        } else {
            cout << a.substr(0, a.size() - z2max) << b << endl;
        }
    }

    return 0;
}
