#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    // --8<-- [start:core]
    // ランレングス圧縮："aaabccdd" → (a, 3) (b, 1) (c, 2) (d, 2)
    vector<pair<char, int>> runs;
    for (auto r : s | views::chunk_by(equal_to{})) {
        runs.emplace_back(r.front(), ranges::distance(r));
    }
    // --8<-- [end:core]
    for (auto [c, len] : runs) cout << c << ' ' << len << '\n';
}
