// A を何回回転（先頭の文字を末尾へ）すると B になるかの最小（なければ -1）
// 入力：A B（長さが同じ英小文字、空でない）
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

// --8<-- [start:core]
int min_rotation(const string& a, const string& b) {
    int n = a.size();
    vector<int> v;  // B、区切り −1、A + A
    for (char c : b) v.push_back(c);
    v.push_back(-1);
    for (int rep = 0; rep < 2; rep++) for (char c : a) v.push_back(c);
    vector<int> z = atcoder::z_algorithm(v);
    for (int k = 0; k < n; k++) {  // 開始位置 n は 0 回転と同じなので見ない
        if (z[n + 1 + k] == n) return k;
    }
    return -1;
}
// --8<-- [end:core]

int main() {
    string a, b;
    cin >> a >> b;
    int ans = min_rotation(a, b);
    // 素朴な方法と一致するか確かめる
    int chk = -1;
    string c = a;
    for (int k = 0; k < (int)a.size(); k++) {
        if (c == b) { chk = k; break; }
        c = c.substr(1) + c[0];
    }
    assert(ans == chk);
    cout << ans << '\n';
}
