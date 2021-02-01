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

const int maxN = 1e5, maxM = 1e5;
int cubes[2*maxN+5];
int z[2*maxN+5];

int main(void) {
    fast_io;
    int n;
    int m;
    cin >> n >> m;

    loop(n) {
        cin >> cubes[i];
    }
    cubes[n] = maxM + 1;
    for (int i = n - 1; i >= 0; i--) {
        cubes[n+n-i] = cubes[i];
    }

    int l = 0, r = 0;
    int N = n + n + 1;

    /*
    cout << "N = " << N << endl;
    loop(N) {
        cout << cubes[i] << " ";
    }
    cout << endl;
    */

    for (int i = 1; i < N; i++) {
        if (r >= i) {
            z[i] = min(z[i - l], r - i + 1);
        }

        while (i + z[i] < N && cubes[z[i]] == cubes[i + z[i]])
            z[i]++;

        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    /*
    for (int i = 0; i < N; i++) {
        cout << z[i] << " ";
    }
    cout << endl;
    */

    bool first = true;
    int x = n / 2;
    for (int i = x; i >= 1; i--) {
        if (z[N-2*i] >= i) {
            if (!first) cout << " ";
            first = false;
            cout << n - i;
        }
    }
    if (!first) cout << " ";
    cout << n << endl;

    return 0;
}
