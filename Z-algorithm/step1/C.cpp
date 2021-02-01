#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    int n;
    string input, joker;

    cin >> n;

    while (n--) {
        cin >> input;
        cin >> joker;

        int count = 0;
        vector<int> indexes;

        for (int i = 0; i < input.size(); i++) {
            bool ok = true;
            for (int j = 0; j < joker.size(); j++) {
                if (i + j >= input.size()) {
                    ok = false;
                    break;
                }
                if (joker[j] == '?') {
                    continue;
                }
                if (input[i+j] != joker[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                count++;
                indexes.push_back(i);
            }
        }

        cout << count << endl;
        for (int i = 0; i < indexes.size(); i++) {
            if (i > 0) cout << " ";
            cout << indexes[i];
        }
        cout << endl;
    }

    return 0;
}
