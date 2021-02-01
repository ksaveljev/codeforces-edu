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
int z[maxN];
int counter[maxN], result[maxN];

int main(void) {
    fast_io;

    int q;
    cin >> q;

    while (q--) {
        string input;
        cin >> input;

        int l = 0, r = 0;
        int n = input.size();
        for (int i = 1; i < n; i++) {
            z[i] = 0;

            if (r >= i)
                z[i] = min(z[i - l], r - i + 1);

            while (i + z[i] < n && input[z[i]] == input[i + z[i]])
                z[i]++;

            if (r < i + z[i] - 1) {
                l = i;
                r = i + z[i] - 1;
            }

            if (z[i] > 0)
                counter[z[i]]++;
        }

        int sum = 0;
        for (int i = n - 1; i > 0; i--) {
            result[i-1] = sum + counter[i];
            sum += counter[i];
            counter[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << result[i] + 1;
            result[i] = 0;
        }
        cout << endl;
    }

    return 0;
}
