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

string input;

int find_lower(string &s, vector<int> &p, int L, int R) {
    int result = -1;

    while (L <= R) {
        int mid = (L + R) / 2;

        string tmp = input.substr(p[mid], s.size());
        if (tmp >= s) {
            R = mid - 1;
        } else {
            result = mid;
            L = mid + 1;
        }
    }

    return result;
}

int find_upper(string &s, vector<int> &p, int L, int R) {
    int result = p.size();

    while (L <= R) {
        int mid = (L + R) / 2;

        string tmp = input.substr(p[mid], s.size());
        if (tmp == s) {
            result = mid;
            L = mid + 1;
        } else if (tmp > s) {
            R = mid - 1;
        } else {
            result = mid;
            L = mid + 1;
        }
    }

    return result;
}

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
    cin >> input;
    input += "$";

    int n = input.size();
    vector<int> p(n), c(n);

    {
        vector<pair<char,int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { input[i], i };
        }

        sort(a.begin(), a.end());

        for (int i = 0 ; i < n; i++)
            p[i] = a[i].second;

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
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) {
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

    int t;
    cin >> t;

    string x;
    while (t--) {
        cin >> x;
        int a = find_lower(x, p, 0, n - 1);
        int b = find_upper(x, p, 0, n - 1);
        cout << b - a << endl;
    }
}
