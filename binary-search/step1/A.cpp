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

int find_lower(vector<int>& v, int x) {
    int l = - 1, r = v.size();

    while (r > l + 1) {
        int m = (l + r) / 2;
        if (v[m] > x) r = m;
        else l = m;
    }

    return l;
}

bool find(vector<int>& v, int x) {
    int i = find_lower(v, x);
    return i >= 0 && v[i] == x;
}

int main(void) {
    int n, k;

    cin >> n >> k;

    vector<int> nums(n);
    for (auto& x : nums) {
        cin >> x;
    }

    while (k--) {
        int x;
        cin >> x;
        if (find(nums, x)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}
