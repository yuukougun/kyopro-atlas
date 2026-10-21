#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, d;
    cin >> s >> d;
    // --8<-- [start:core]
    array<int, 26> cnt{};             // 英小文字の出現回数
    for (char c : s) cnt[c - 'a']++;  // 'a' → 0, 'b' → 1, …, 'z' → 25
    string t;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) t += char('a' + i);  // 0 → 'a'。char に戻してから足す
    }
    int sum = 0;
    for (char c : d) sum += c - '0';  // 数字の文字 '7' → 7
    // --8<-- [end:core]
    cout << t << ' ' << sum << '\n';
}
