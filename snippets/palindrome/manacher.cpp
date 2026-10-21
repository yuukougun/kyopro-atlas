// Manacher：文字の間に区切りを挟んだ T（長さ 2N + 1）で各中心の最長回文半径を O(N) で求め、
// 中心 c = l + r（0 ≤ c ≤ 2N）ごとの最長回文の長さ len[c] を出す。
// S[l, r) が回文 ⇔ len[l + r] ≥ r − l。出力は c = 1, …, 2N − 1 の len[c]。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// len[c] = 中心が c / 2 の位置（c が奇数なら文字の上、偶数なら文字の間）にある最長回文の長さ
vector<int> manacher(const string& s) {
    int n = s.size();
    string t(2 * n + 1, '#');  // t = # s0 # s1 # … # （t[2i + 1] = s[i]）
    for (int i = 0; i < n; i++) t[2 * i + 1] = s[i];
    int m = t.size();
    vector<int> d(m);  // d[j]：t[j − d + 1, j + d) が回文になる最大の d（中心を含む半径）
    int c = 0, r = 0;  // 右端 r = c + d[c] が最も右にある回文の中心 c
    for (int j = 0; j < m; j++) {
        int k = 1;
        if (j < r) k = min(d[2 * c - j], r - j);  // 鏡の位置の半径を、r を越えない範囲で写す
        while (j - k >= 0 && j + k < m && t[j - k] == t[j + k]) k++;  // はみ出した分だけ比べる
        d[j] = k;
        if (j + k > r) {
            c = j;
            r = j + k;
        }
    }
    vector<int> len(m);
    for (int j = 0; j < m; j++) len[j] = d[j] - 1;  // 両端が # なので、s での長さは d − 1
    return len;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> len = manacher(s);
    // 素朴に確かめる：S[l, r) が回文 ⇔ len[l + r] ≥ r − l
    if (n <= 200) {
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                string u = s.substr(l, r - l);
                bool pal = equal(u.begin(), u.end(), u.rbegin());
                assert(pal == (len[l + r] >= r - l));
            }
        }
    }
    for (int c = 1; c <= 2 * n - 1; c++) cout << len[c] << (c == 2 * n - 1 ? '\n' : ' ');
}
