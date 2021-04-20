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

const int maxN = 1e6;
int n, m, d;
map<int, map<int,int>> edges;
map<int, bool> visited;
int parent[maxN];

bool good(int limit) {
    queue<pair<int,int>> q;
    q.push({1, 0});
    visited[1] = true;
    while (!q.empty()) {
        auto [current, taken] = q.front();
        q.pop();

        if (current == n) {
            return true;
        }

        if (taken == d) continue;

        for (auto [k, w] : edges[current]) {
            if (w > limit || visited[k]) continue;
            visited[k] = true;
            parent[k] = current;
            q.push({k, taken+1});
        }
    }

    return false;
}

int main(void) {
    cin >> n >> m >> d;

    int a, b, c;
    int L = INT_MAX;
    int R = INT_MIN;

    while (m--) {
        cin >> a >> b >> c;
        edges[a][b] = c;
        L = min(L, c);
        R = max(R, c);
    }

    L--;
    R++;
    bool found = false;
    while (R > L + 1) {
        int M = (L + R) / 2;
        visited.clear();
        if (good(M)) {
            found = true;
            R = M;
        } else {
            L = M;
        }
    }

    if (!found) {
        cout << -1 << endl;
    } else {
        visited.clear();
        assert(good(R));
        vector<int> result;
        int x = n;
        while (x != 1) {
            result.push_back(x);
            x = parent[x];
        }
        result.push_back(1);
        cout << result.size() - 1 << endl;
        for (auto it = result.rbegin(); it != result.rend(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;
}
