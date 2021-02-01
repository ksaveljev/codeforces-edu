#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    int n;
    string input;
    string str;

    cin >> n;

    while (n--) {
        cin >> input;
        cin >> str;

        int count = 0;

        if (str.size() > input.size()) {
            count = input.size() * (1 + input.size()) / 2;
        } else {
            for (int i = 1; i < str.size(); i++) {
                count += input.size() - i + 1;
            }

            int start = 0;

            for (int i = 0; i < input.size(); i++) {
                bool ok = true;
                for (int j = 0; j < str.size(); j++) {
                    if (i + j >= input.size()) {
                        ok = false;
                        break;
                    }
                    if (input[i + j] != str[j]) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    int end = i + str.size() - 1;
                    int len = end - start;
                    for (int x = str.size(); x <= len; x++) {
                        count += len - x + 1;
                    }
                    start = i + 1;
                }
            }

            int end = input.size() - 1;
            int len = end - start + 1;
            for (int x = str.size(); x <= len; x++) {
                count += len - x + 1;
            }
        }

        cout << count << endl;
    }

    return 0;
}
