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
#include <list>
#include <cassert>
#include <climits>
using namespace std;

#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define rep(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

bool good(int n, int k, vector<int>& v, int M) {
    int c = 1;
    int p = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] - v[p] >= M) {
            c++;
            p = i;
        }
    }

    return c >= k;
}

int main(void) {
    int n, k;
    cin >> n >> k;

    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int L = 0;
    int R = 1e9+5;

    while (R > L + 1) {
        int M = (L + R) / 2;
        if (good(n, k, v, M)) {
            L = M;
        } else {
            R = M;
        }
    }

    cout << L << endl;

    return 0;
}
