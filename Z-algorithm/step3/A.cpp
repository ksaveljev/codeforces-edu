#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int main(void) {
   string input;

   cin >> input;

   vector<int> z(input.size());

   for (int i = 1, l = 0, r = 0; i < input.size(); i++) {
      if (i <= r) {
         z[i] = min(z[i-l], r - i + 1);
      }
      while (i + z[i] < input.size() && input[z[i]] == input[i+z[i]]) {
         z[i]++;
      }
      if (i + z[i] - 1 > r) {
         l = i;
         r = i + z[i] - 1;
      }
   }

   for (int i = 0; i < input.size(); i++) {
      if (i > 0) cout << " ";
      cout << z[i];
   }
   cout << endl;
}
