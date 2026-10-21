// パターン P の T の中のすべての出現位置（ACL の z_algorithm と P＋区切り＋T）
// 入力：P T（どちらも英小文字、空でない）。出力：出現の個数と、出現位置（0-indexed）を 1 行に 1 つ
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

// --8<-- [start:core]
vector<int> find_all(const string& p, const string& t) {
    int m = p.size(), n = t.size();
    vector<int> v;  // P、区切り −1、T をつないだ int の列（−1 はどの文字とも違う）
    for (char c : p) v.push_back(c);
    v.push_back(-1);
    for (char c : t) v.push_back(c);
    vector<int> z = atcoder::z_algorithm(v);
    vector<int> res;
    for (int j = 0; j + m <= n; j++) {
        if (z[m + 1 + j] == m) res.push_back(j);  // 区切りがあるので z は m を超えない
    }
    return res;
}
// --8<-- [end:core]

int main() {
    string p, t;
    cin >> p >> t;
    vector<int> res = find_all(p, t);
    // 素朴な方法と一致するか確かめる
    vector<int> chk;
    for (int j = 0; j + (int)p.size() <= (int)t.size(); j++) {
        if (t.compare(j, p.size(), p) == 0) chk.push_back(j);
    }
    assert(res == chk);
    cout << res.size() << '\n';
    for (int j : res) cout << j << '\n';
}
