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

int main(void) {
    double c;
    cin >> c;

    double l = 0;
    double r = 1e6;
    for (int i = 0; i < 100; i++) {
        double x = (r + l) / 2;
        double result = x * x + sqrt(x);
        if (result > c) {
            r = x;
        } else {
            l = x;
        }
    }

    cout << setprecision(10) << r << endl;

    return 0;
}
