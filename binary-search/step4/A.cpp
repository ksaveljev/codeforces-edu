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
#include <cassert>
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

pair<int,int> good(int n, int d, vector<int>& a, double M) {
    vector<double> pre(n+1), pmin(n+1);
    vector<int> pminidx(n+1);

    pre[0] = a[0] - M;
    pmin[0] = pre[0];
    pminidx[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + a[i] - M;

        if (pre[i] < pmin[i-1]) {
            pmin[i] = pre[i];
            pminidx[i] = i;
        } else {
            pmin[i] = pmin[i-1];
            pminidx[i] = pminidx[i-1];
        }
    }

    for (int R = d; R <= n; R++) {
        if (pre[R] >= pmin[R-d]) {
            int L = pminidx[R-d] + 1;
            return {L, R};
        }
    }

    return {-1, -1};
}

int main(void) {
    int n, d;
    cin >> n >> d;

    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    double L = -1;
    double R = 101;

    pair<int,int> current, result;
    for (int i = 0; i < 100; i++) {
        double M = (L + R) / 2;
        current = good(n, d, a, M);
        if (current.first == -1) {
            R = M;
        } else {
            result = current;
            L = M;
        }
    }

    cout << result.first << " " << result.second << endl;

    return 0;
}
