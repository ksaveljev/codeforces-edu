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
using namespace std;

#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

int main(void) {
    string s;
    cin >> s;
    s += "$";
    int n = s.size();

    vector<int> p(n), c(n);
    {
        // k = 0
        vector<pair<char, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = {s[i], i};
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < n; i++) {
            p[i] = v[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (v[i].first == v[i-1].first) {
                c[p[i]] = c[p[i-1]];
            } else {
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
    }

    {
        int k = 0;
        while ((1 << k) < n) {
            vector<pair<pair<int,int>, int>> v(n);
            for (int i = 0; i < n; i++) {
                v[i] = {{c[i], c[(i + (1<<k))%n]}, i};
            }
            sort(v.begin(), v.end());
            for (int i = 0; i < n; i++) {
                p[i] = v[i].second;
            }
            c[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (v[i].first == v[i-1].first) {
                    c[p[i]] = c[p[i-1]];
                } else {
                    c[p[i]] = c[p[i-1]] + 1;
                }
            }

            k++;
        }
    }

    for (int x : p) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
