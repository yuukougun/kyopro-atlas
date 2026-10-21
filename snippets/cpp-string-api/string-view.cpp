#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 引数を string_view で受けると、string も文字列リテラルもコピーせずに渡せる
int count_prefix(string_view s, string_view p) {
    int res = 0;
    while (s.starts_with(p)) {
        s.remove_prefix(p.size());   // 見る範囲を前から縮めるだけ。O(1)
        res++;
    }
    return res;
}
// --8<-- [end:core]

int main() {
    string s, p;
    cin >> s >> p;
    cout << count_prefix(s, p) << '\n';
    string_view v = s;
    cout << v.substr(1, 2) << '\n';  // string_view の substr はコピーしない。O(1)
}
