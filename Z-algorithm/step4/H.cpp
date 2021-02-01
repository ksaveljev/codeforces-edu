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

int z[8001];

ll calc(string s) {
    int l = 0, r = 0;
    int best = 0;
    ll result = 0;
    for (int i = 1; i < s.size(); i++) {
        z[i] = 0;
        if (r >= i) {
            z[i] = min(z[i - l], r - i + 1);
        }

        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            z[i]++;

        best = max(best, z[i]);

        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = best + 1; i <= s.size(); i++) {
        result += i;
    }

    return result;
}

int main(void) {
    fast_io;
    string input;

    cin >> input;

    ll sum = 0;
    int n = input.size();
    for (int i = n - 1; i >= 0; i--) {
        sum += calc(input.substr(i));
    }
    cout << sum << endl;

    return 0;
}
