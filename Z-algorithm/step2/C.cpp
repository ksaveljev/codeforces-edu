#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    int t;
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    cin >> t;

    while (t--) {
        int len;
        cin >> len;

        vector<int> z(len);
        string result = "";

        bool ok = true;

        for (int i = 0; i < len; i++) {
            cin >> z[i];
            if (z[i] >= len) {
                ok = false;
            }
            result += chars[i];
        }

        if (z[0] != 0) {
            ok = false;
        }

        if (!ok) {
            cout << "!" << endl;
        } else {
            for (int i = 1; i < len; i++) {
                if (z[i] > 0) {
                    for (int j = 0; j < z[i]; j++) {
                        result[i+j] = result[j];
                    }
                }
            }

            if (!ok) {
                cout << "!" << endl;
            } else {
                vector<int> test(len);
                for (int i = 0; i < len; i++) {
                    test[i] = 0;
                }

                for (int i = 1; i < len; i++) {
                    while (test[i] + i < len && result[test[i] + i] == result[test[i]]) {
                        test[i]++;
                    }
                }

                for (int i = 0; i < len; i++) {
                    if (z[i] != test[i]) {
                        ok = false;
                        break;
                    }
                }

                if (!ok) {
                    cout << "!" << endl;
                } else {
                    cout << result << endl;
                }
            }
        }
    }
}
