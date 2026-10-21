#include <bits/stdc++.h>
// --8<-- [start:include]
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// --8<-- [end:include]
using namespace std;

// --8<-- [start:type]
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// --8<-- [end:type]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    ordered_set<pair<int, int>> s;                // (値, 通し番号) で重複を許す
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s.insert({a, i});
    }
    int x;
    cin >> x;
    cout << s.order_of_key({x, -1}) << '\n';      // x 未満の個数（通し番号は 0 以上なので -1 で x 未満だけ数える）
    if (!s.empty()) cout << s.find_by_order(s.size() / 2)->first << '\n';  // 0 から数えて size/2 番目（中央値）
    // --8<-- [end:core]
}
