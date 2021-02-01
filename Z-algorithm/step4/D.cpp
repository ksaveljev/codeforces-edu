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

const int maxN = 1e6;
int z[maxN];

int main(void) {
    fast_io;

    string input;

    cin >> input;

    string x = input;
    reverse(input.begin(), input.end());
    x += "$" + input;

    int n = x.size();

    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (r >= i)
            z[i] = min(z[i - l], r - i + 1);

        while (i + z[i] < n && x[z[i]] == x[i + z[i]])
            z[i]++;

        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }

        if (i + z[i] == n) {
            cout << z[i] << endl;
            break;
        }
    }

    return 0;
}
