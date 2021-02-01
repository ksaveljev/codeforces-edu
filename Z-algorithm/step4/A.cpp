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
char input[maxN+1];
int z[maxN];

int main(void) {
    int t;
    cin >> t;

    while (t--) {
        scanf("%s", input);

        int l = 0, r = 0;
        int n = strlen(input);
        int result = -1;
        for (int i = 1; i < n; i++) {
            z[i] = 0;

            if (r >= i)
                z[i] = min(z[i - l], r - i + 1);

            while (i + z[i] < n && input[z[i]] == input[z[i] + i])
                z[i]++;

            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }

            if (i + z[i] == n) {
                result = i;
                break;
            }
        }

        if (result == -1) {
            printf("%s\n", input);
        } else {
            printf("%.*s\n", result, input);
        }
    }
}
