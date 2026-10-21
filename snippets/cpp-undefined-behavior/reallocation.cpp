#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:bad]
// 呼ぶと壊れる：push_back で g の要素が新しい領域へ移り、row は古い領域を指したまま
void bad() {
    vector<vector<int>> g = {{1}};
    auto& row = g[0];
    g.push_back({2});
    row.push_back(3);  // AddressSanitizer で heap-use-after-free
}
// --8<-- [end:bad]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<vector<int>> g = {{1}};
    for (int i = 0; i < n; i++) {
        g.push_back({i});
        g[0].push_back(i);  // 参照を持ち続けず、使うたびに g[0] と添字で書く
    }
    // --8<-- [end:core]
    cout << g.size() << ' ' << g[0].size() << '\n';
    (void)&bad;
}
