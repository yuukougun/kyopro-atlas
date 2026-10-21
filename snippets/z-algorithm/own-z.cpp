// Z 配列を自分で書く（ACL と同じく z[0] = n とする）
// 入力：文字列 S（空でない）。出力：z[0] … z[N-1]
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// z[i] = S と S[i, n) の最長共通接頭辞の長さ
vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    if (n == 0) return z;
    z[0] = n;
    int l = 0, r = 0;  // Z-box：s[l, r) = s[0, r - l) で、r が最も右のもの
    for (int i = 1; i < n; i++) {
        int k = 0;
        if (i < r) k = min(r - i, z[i - l]);  // 箱の内側は z[i - l] をコピー（r で頭打ち）
        while (i + k < n && s[k] == s[i + k]) k++;  // はみ出した分だけ比べる
        z[i] = k;
        if (i + k > r) { l = i; r = i + k; }  // 右端が伸びたら箱を取り替える
    }
    return z;
}
// --8<-- [end:core]

vector<int> naive(const string& s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 0; i < n; i++) {
        int k = 0;
        while (i + k < n && s[k] == s[i + k]) k++;
        z[i] = k;
    }
    return z;
}

int main() {
    // 小さい文字列を全部試して素朴な方法と一致するか確かめる
    for (int n = 1; n <= 10; n++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            string t(n, 'a');
            for (int i = 0; i < n; i++) if (mask >> i & 1) t[i] = 'b';
            assert(z_function(t) == naive(t));
        }
    }
    string s;
    cin >> s;
    vector<int> z = z_function(s);
    for (int i = 0; i < (int)z.size(); i++) cout << z[i] << (i + 1 < (int)z.size() ? ' ' : '\n');
}
