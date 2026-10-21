#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3}, b = {1, 2};
    // --8<-- [start:core]
    auto starts = [](const vector<int>& s, const vector<int>& t) {  // s が t で始まるか
        return s.size() >= t.size() && equal(t.begin(), t.end(), s.begin());
    };
    cout << starts(a, b) << ' ' << starts(b, a) << '\n';
    // --8<-- [end:core]
}
