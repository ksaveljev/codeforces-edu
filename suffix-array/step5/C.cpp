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

const int INF = 1e9+7;
const int maxN = 1e6;
int llog[maxN + 1];
int st[maxN][21];

void count_sort(vector<int> &p, vector<int> &c) {
    int n = p.size();

    vector<int> cnt(n);
    for (auto x : c) {
        cnt[x]++;
    }

    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i-1] + cnt[i-1];
    }

    vector<int> p_new(n);
    for (auto x : p) {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }

    p = p_new;
}

int main(void) {
    llog[1] = 0;
    for (int i = 2; i <= maxN; i++)
        llog[i] = llog[i/2] + 1;

    string input;
    cin >> input;

    input += " ";
    int n = input.size();

    vector<int> p(n), c(n);
    {
        vector<pair<char,int>> a(n);
        loop(n) {
            a[i] = {input[i], i};
        }

        sort(a.begin(), a.end());

        loop(n) {
            p[i] = a[i].second;
        }

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i-1].first) {
                c[p[i]] = c[p[i-1]];
            } else {
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1<<k) < n) {
        loop(n) {
            p[i] = (p[i] - (1<<k) + n) % n;
        }

        count_sort(p, c);

        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int,int> prev = { c[p[i-1]], c[(p[i-1] + (1<<k)) % n] };
            pair<int,int> now = { c[p[i]], c[(p[i] + (1<<k)) % n] };
            if (prev == now) {
                c_new[p[i]] = c_new[p[i-1]];
            } else {
                c_new[p[i]] = c_new[p[i-1]] + 1;
            }
        }

        c = c_new;
        k++;
    }

    vector<int> lcp(n);
    k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];
        int j = p[pi - 1];
        while (input[i+k] == input[j+k]) k++;
        lcp[pi] = k;
        k = max(k - 1, 0);
    }

    for (int i = 0; i < n; i++)
        st[i][0] = lcp[i];

    for (int j = 1; j <= 20; j++) {
        for (int i = 0; i + (1<<j) <= n; i++) {
            st[i][j] = min(st[i][j-1], st[i + (1<<(j-1))][j-1]);
        }
    }

    int N;
    cin >> N;
    vector<pair<int,int>> sub(N);
    loop(N) {
        cin >> sub[i].first >> sub[i].second;
    }

    auto theTruthIsOutThere = [&c, &lcp](pair<int,int> &a, pair<int,int> &b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        int ai = c[a.first - 1];
        int bi = c[b.first - 1];

        int xx = min(ai, bi);
        int yy = max(ai, bi);

        /*
        int diff = INF;
        while (yy > xx) {
            diff = min(diff, lcp[yy]);
            yy--;
        }
        */
        int j = llog[yy - xx];
        int diff = min(st[xx+1][j], st[yy - (1<<j) + 1][j]);

        int alen = a.second - a.first + 1;
        int blen = b.second - b.first + 1;

        if (diff > alen && diff > blen) {
            if (alen == blen) {
                return a.first < b.first;
            }
            return alen < blen;
        }
        if (diff > alen) {
            return true;
        }
        if (diff > blen) {
            return false;
        }

        if (diff == alen && diff == blen) {
            return a.first < b.first;
        }
        if (diff == alen) {
            return true;
        }
        if (diff == blen) {
            return false;
        }

        return ai < bi;
    };

    sort(sub.begin(), sub.end(), theTruthIsOutThere);

    for (auto [k,v] : sub) {
        cout << k << " " << v << endl;
    }

    return 0;
}
