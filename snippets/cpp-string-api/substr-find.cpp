#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    // --8<-- [start:core]
    cout << s.substr(1, 3) << '\n';  // 1 文字目から 3 文字（足りなければあるだけ）。O(3) のコピー
    cout << s.substr(1) << '\n';     // 1 文字目から最後まで

    size_t p = s.find(t);            // 最初に現れる位置。なければ string::npos
    if (p == string::npos) {
        cout << "none\n";
    } else {
        cout << p << '\n';
    }

    vector<size_t> pos;              // t が現れる位置をすべて（重なりも含む）
    for (size_t q = s.find(t); q != string::npos; q = s.find(t, q + 1)) {
        pos.push_back(q);
    }
    // --8<-- [end:core]
    cout << pos.size() << '\n';
}
