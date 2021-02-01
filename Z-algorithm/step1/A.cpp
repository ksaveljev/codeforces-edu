#include <iostream>
#include <string>
using namespace std;

int main(void) {
    int n;
    string input;

    cin >> n;

    while (n--) {
        cin >> input;
        int best = 1;

        for (int i = input.size() - 1; i >= 1; i--) {
            bool ok = true;
            for (int a = 0; i - a >= a; a++) {
                if (input[i-a] != input[a]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                best = i + 1;
                break;
            }
        }

        cout << best << endl;
    }

    return 0;
}
