#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    int t;
    vector<string> gray;

    gray.push_back("a");
    int idx = 1;
    for (char c = 'b'; c <= 'z'; c++) {
        gray.push_back(gray[idx-1] + c + gray[idx-1]);
        idx++;
    }

    cin >> t;

    while (t--) {
        int k, j;
        cin >> k >> j;

        if (j == 0) {
            cout << 0 << endl;
        } else {
            int result = 0;

            while (result + j < gray[k-1].size() && gray[k-1][j + result] == gray[k-1][result]) {
                result++;
            }

            cout << result << endl;
        }
    }

    return 0;
}
