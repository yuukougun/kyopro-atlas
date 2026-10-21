// パターン P の本文 T での全出現（T を 1 文字ずつ読む照合）
// 入力：P T。出力：出現の個数と、出現の開始位置（0-indexed）を 1 行に 1 つ
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

// --8<-- [start:core]
// P（空でない）が T に現れる開始位置をすべて返す
vector<int> find_all(const string& p, const string& t) {
    int m = p.size();
    vector<int> pi = prefix_function(p);
    vector<int> res;
    int j = 0;                                   // T のいま読んだ所までの末尾が P[0, j) と一致
    for (int i = 0; i < (int)t.size(); i++) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];  // 失敗したら border までずらす
        if (t[i] == p[j]) j++;
        if (j == m) {                            // P 全体と一致した
            res.push_back(i - m + 1);
            j = pi[m - 1];                       // 重なった次の出現も探せるようにずらす
        }
    }
    return res;
}
// --8<-- [end:core]

int main() {
    string p, t;
    cin >> p >> t;
    vector<int> res = find_all(p, t);
    // 素朴な方法と比べる
    vector<int> naive;
    for (int i = 0; i + (int)p.size() <= (int)t.size(); i++) {
        if (t.compare(i, p.size(), p) == 0) naive.push_back(i);
    }
    assert(res == naive);
    cout << res.size() << '\n';
    for (int x : res) cout << x << '\n';
}
