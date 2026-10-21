// border の連鎖：S の全 border と、各接頭辞が S に何回現れるか
// 入力：S（空でない）。出力：1 行目に全 border の長さ（長い順。なければ空行）、2 行目に長さ 1..N の接頭辞の出現回数
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pi = prefix_function(s);

    // --8<-- [start:core]
    // 全 border を長い順に：pi[n-1], pi[pi[n-1]-1], ...
    vector<int> borders;
    for (int b = pi[n - 1]; b > 0; b = pi[b - 1]) borders.push_back(b);

    // cnt[k] = 長さ k の接頭辞が S に現れる回数
    vector<long long> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) cnt[pi[i]]++;          // 位置 i で終わる最長の border
    for (int k = n; k >= 1; k--) cnt[pi[k - 1]] += cnt[k];  // 短い border へ受け渡す
    for (int k = 1; k <= n; k++) cnt[k]++;             // 接頭辞そのものの出現
    // --8<-- [end:core]

    // 定義どおりに確かめる
    vector<int> naive_b;
    for (int k = n - 1; k >= 1; k--) {
        if (s.compare(0, k, s, n - k, k) == 0) naive_b.push_back(k);
    }
    assert(borders == naive_b);
    for (int k = 1; k <= n; k++) {
        long long c = 0;
        for (int i = 0; i + k <= n; i++) if (s.compare(i, k, s, 0, k) == 0) c++;
        assert(cnt[k] == c);
    }
    for (int i = 0; i < (int)borders.size(); i++) cout << borders[i] << (i + 1 < (int)borders.size() ? " " : "");
    cout << '\n';
    for (int k = 1; k <= n; k++) cout << cnt[k] << (k < n ? ' ' : '\n');
}
