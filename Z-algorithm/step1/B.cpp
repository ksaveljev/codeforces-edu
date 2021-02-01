#include <iostream>
#include <string>
using namespace std;

int main(void) {
    int n;
    string input;

    cin >> n;

    while (n--) {
        cin >> input;

        int result = 0;

        for (int i = 0; i < input.size(); i++) {
            for (int j = i; j < input.size(); j++) {
                bool prefix = true;
                bool suffix = true;
                for (int k = i; k <= j; k++) {
                    // prefix
                    if (input[k] != input[k-i]) {
                        prefix = false;
                    }
                    // suffix
                    if (input[k] != input[input.size() - 1 - j + k]) {
                        suffix = false;
                    }

                    if (!prefix && !suffix) {
                        break;
                    }
                }

                if ((prefix && suffix) || (!prefix && !suffix)) {
                    continue;
                }

                result++;
            }
        }

        cout << result << endl;
    }

    return 0;
}
