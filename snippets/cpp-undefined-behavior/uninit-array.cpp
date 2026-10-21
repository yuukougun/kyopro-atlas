#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long solve(const string& s) {
    int cnt[26];  // 初期化していない（-Wall -Wextra でも警告されない）
    for (char c : s) cnt[c - 'a']++;
    long long ans = 0;
    for (int i = 0; i < 26; i++) ans += (long long)cnt[i] * cnt[i];
    return ans;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    cout << solve(s) << '\n';
}
