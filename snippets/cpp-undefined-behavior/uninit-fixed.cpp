#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long solve(const string& s) {
    array<int, 26> cnt{};  // {} で 0 に初期化する（int cnt[26] = {}; でも同じ）
    for (char c : s) cnt[c - 'a']++;
    long long ans = 0;     // 和は 0 から始める
    for (int i = 0; i < 26; i++) ans += (long long)cnt[i] * cnt[i];
    return ans;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    cout << solve(s) << '\n';
}
