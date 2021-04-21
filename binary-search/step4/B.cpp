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

const int maxN = 1e5+1;
int n, m;
vector<pair<int,int>> adj[maxN];

bool good(double M) {
    vector<double> dp(n+1, 1e18);
    dp[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [k, w] : adj[i]) {
            dp[k] = min(dp[k], dp[i] + w - M);
        }
    }

    return dp[n] <= 0;
}

int main(void) {
    cin >> n >> m;

    int a, b, c;
    while (m--) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    double L = -1;
    double R = 101;
    for (int i = 0; i < 80; i++) {
        double M = (L + R) / 2;
        if (good(M)) {
            R = M;
        } else {
            L = M;
        }
    }

    vector<double> dp(n+1, 1e18);
    vector<int> parent(n+1);
    dp[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [k, w] : adj[i]) {
            if (dp[k] > dp[i] + w - R) {
                parent[k] = i;
                dp[k] = dp[i] + w - R;
            }
        }
    }

    vector<int> result;
    int x = n;
    while (x != 1) {
        result.push_back(x);
        x = parent[x];
    }
    result.push_back(1);
    reverse(result.begin(), result.end());

    cout << result.size() - 1 << endl;
    for (auto x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
