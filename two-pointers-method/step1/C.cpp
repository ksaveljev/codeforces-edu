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
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int main(void) {
    map<int,int> mem;

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    ll result = 0;

    loop(n) cin >> a[i];
    loop(m) cin >> b[i];

    int i = 0;
    for (int j = 0; j < m; j++) {
        if (mem.find(b[j]) == mem.end()) {
            while (i < n && a[i] < b[j]) i++;
            int c = 0;
            while (i < n && a[i] == b[j]) {
                i++, c++;
            }
            mem[b[j]] = c;
            result += c;
        } else {
            result += mem[b[j]];
        }
    }

    cout << result << endl;

    return 0;
}
