#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    string input;

    cin >> input;

    vector<int> v(input.size());

    for (int i = 0; i < input.size(); i++) {
        v[i] = 0;
    }

    for (int i = 1; i < input.size(); i++) {
        while (v[i] + i < input.size() && input[i + v[i]] == input[v[i]]) {
            v[i]++;
        }
    }

    for (int i = 0; i < input.size(); i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << endl;

    return 0;
}
