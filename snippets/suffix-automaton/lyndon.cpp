#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// Duval：Lyndon 分解の各片の開始位置を返す（最後に n を足す）
vector<int> lyndon_factorization(const string& s) {
    int n = s.size();
    vector<int> res = {0};
    int i = 0;
    while (i < n) {
        // s[i, k) は「Lyndon 語 w の繰り返し＋w の接頭辞」の形、周期は k - j
        int j = i, k = i + 1;
        while (k < n && s[j] <= s[k]) {
            if (s[j] < s[k]) j = i;  // ここまでが 1 つの Lyndon 語になる
            else j++;                // 周期を保って伸ばす
            k++;
        }
        while (i <= j) {  // 周期 k - j の片を切り出す
            i += k - j;
            res.push_back(i);
        }
    }
    return res;
}

// 辞書順最小の巡回シフトの開始位置：s + s を分解し、
// 開始位置が n 未満の片のうち最後のものから始める
int min_rotation(const string& s) {
    int n = s.size();
    vector<int> f = lyndon_factorization(s + s);
    int ans = 0;
    for (int p : f) {
        if (p < n) ans = p;
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    vector<int> f = lyndon_factorization(s);
    for (int i = 0; i < (int)f.size(); i++) cout << f[i] << (i + 1 == (int)f.size() ? '\n' : ' ');
    int n = s.size();
    int r = min_rotation(s);
    // 素朴に全シフトを比べた結果と一致するか
    string best = s;
    for (int k = 0; k < n; k++) best = min(best, s.substr(k) + s.substr(0, k));
    assert(s.substr(r) + s.substr(0, r) == best);
    cout << r << ' ' << best << '\n';
}
