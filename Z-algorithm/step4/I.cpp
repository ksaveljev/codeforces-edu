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

const int maxN = 1e6;
int z1[2*maxN+5];
int z2[2*maxN+5];

int main(void) {
    fast_io;

    int k;
    string t, p;
    cin >> t >> p >> k;

    string a = p + "$" + t;
    reverse(t.begin(), t.end());
    reverse(p.begin(), p.end());
    string b = p + "$" + t;

    int n = a.size();
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (r >= i) {
            z1[i] = min(z1[i - l], r - i + 1);
        }

        while (i + z1[i] < n && a[z1[i]] == a[i + z1[i]])
            z1[i]++;

        if (r < i + z1[i] - 1) {
            l = i;
            r = i + z1[i] - 1;
        }
    }

    l = r = 0;
    for (int i = 1; i < n; i++) {
        if (r >= i) {
            z2[i] = min(z2[i - l], r - i + 1);
        }

        while (i + z2[i] < n && b[z2[i]] == b[i + z2[i]])
            z2[i]++;

        if (r < i + z2[i] - 1) {
            l = i;
            r = i + z2[i] - 1;
        }
    }

    /*
    cout << a << endl;
    cout << b << endl;
    for (int i = 0; i < n; i++) {
        cout << z1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << z2[i] << " ";
    }
    cout << endl;
    */

    int count = 0;
    vector<int> idx;
    /*
    cout << "n = " << n << endl;
    cout << "i < " << n - p.size() << endl;
    */
    for (int i = p.size() + 1; i < n - p.size() + 1; i++) {
        //cout << " i = " << i << " z1[i] = " << z1[i] << " z2[n-z1[i]] = " << z2[n-(i-p.size()-1)-z1[i]-(p.size() - z1[i])] << endl;
        if (z1[i] + k >= p.size()) {
            //cout << "!!!!!" << endl;
            count++;
            idx.push_back(i - p.size());
        } else if (z1[i] + k + z2[n-i+1] >= p.size()) {
            //cout << "????" << endl;
            count++;
            idx.push_back(i - p.size());
        }
    }

    cout << count << endl;
    for (int i = 0; i < idx.size(); i++) {
        if (i > 0) cout << " ";
        cout << idx[i];
    }
    cout << endl;

    return 0;
}
