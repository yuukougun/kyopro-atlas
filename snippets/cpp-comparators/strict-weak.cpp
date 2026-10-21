#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& t : s) cin >> t;
    // --8<-- [start:core]
    // a が b より前に来るべきときだけ true を返す（長さが等しければ false）
    auto shorter = [](const string& a, const string& b) { return a.size() < b.size(); };
    // 長さの等しい文字列はこの比較関数では「同じ」なので、sort では順が決まらない。
    // stable_sort は「同じ」ものを入力の順のまま残す
    stable_sort(s.begin(), s.end(), shorter);
    // --8<-- [end:core]
    assert(!shorter("ab", "ab"));  // 同じものどうしは false
    for (int i = 0; i < n; i++) cout << s[i] << " \n"[i == n - 1];
    if (n == 0) cout << '\n';
}
