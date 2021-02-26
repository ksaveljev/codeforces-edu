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
#define rep(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

int r;
struct matrix {
    int a,b,c,d;
};

struct segtree {
    int size;
    vector<matrix> tree;

    matrix combine(matrix a, matrix b) {
        return {
            (a.a * b.a + a.b * b.c) % r,
            (a.a * b.b + a.b * b.d) % r,
            (a.c * b.a + a.d * b.c) % r,
            (a.c * b.b + a.d * b.d) % r
        };
    }

    void build(vector<matrix> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2*size, {1,0,0,1});
        build(a, 0, 0, size);
    }

    void build(vector<matrix> &a, int x, int lx, int rx) {
        if (rx == lx + 1) {
            if (lx < a.size()) {
                tree[x] = a[lx];
            }
        } else {
            int m = (lx + rx) / 2;
            build(a, 2*x+1, lx, m);
            build(a, 2*x+2, m, rx);
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }

    matrix calc(int L, int R) {
        return calc(L, R, 0, 0, size);
    }

    matrix calc(int L, int R, int x, int lx, int rx) {
        if (lx >= R) return {1,0,0,1};
        if (rx <= L) return {1,0,0,1};
        if (lx >= L && rx <= R) return tree[x];
        int m = (lx + rx) / 2;
        return combine(calc(L, R, 2*x+1, lx, m), calc(L, R, 2*x+2, m, rx));
    }
};

int main(void) {
    int n, m;
    cin >> r >> n >> m;

    vector<matrix> a(n);
    loop(n) {
        scanf("%d%d%d%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
    }

    segtree st;
    st.build(a);

    int L, R;
    while (m--) {
        cin >> L >> R, --L;
        matrix result = st.calc(L, R);
        printf("%d %d\n%d %d\n", result.a, result.b, result.c, result.d);
        if (m > 0) printf("\n");
    }

    return 0;
}
