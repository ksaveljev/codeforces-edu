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

const int maxN = 1e5+100;
int z1[maxN];
int z2[maxN];

int main(void) {
    fast_io;

    string s, t;
    cin >> s >> t;

    if (s.size() != t.size()) {
        cout << "No" << endl;
        return 0;
    }

    string a = t + "$" + s;
    reverse(t.begin(), t.end());
    string b = t + "$" + s;

    int n = a.size();
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z1[i] = 0;

        if (r >= i)
            z1[i] = min(z1[i - l], r - i + 1);

        while (i + z1[i] < n && a[z1[i]] == a[i + z1[i]])
            z1[i]++;

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

        while (i + z2[i] < n && b[z2[i]] == b[i + z2[i]])
            z2[i]++;

        if (r < i + z2[i] - 1) {
            l = i;
            r = i + z2[i] - 1;
        }
    }

    int N = s.size();
    int result = -1;
    for (int i = 0; i <= s.size(); i++) {
        if ((i == N || z1[N+i+1] == N-i) && z2[N+1] >= i) {
            result = i;
            break;
        }
    }



    if (result == -1) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        cout << result << endl;
    }

    return 0;
}
