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
    // 素朴な方法（substr のコピーと比較の繰り返し）と結果を比べる
    int naive = 0;
    for (size_t i = 0; i + p.size() <= s.size() && s.substr(i, p.size()) == p; i += p.size()) naive++;
    assert(count_prefix(s, p) == naive);
    cout << count_prefix(s, p) << '\n';
    string_view v = s;
    cout << v.substr(1, 2) << '\n';  // string_view の substr はコピーしない。O(1)
}
