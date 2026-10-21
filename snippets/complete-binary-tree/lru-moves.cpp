#include <bits/stdc++.h>
using namespace std;

// 素朴なシミュレーション（番号が小さいときの照合用）
long long naive(long long x, const string& s) {
    for (char c : s) {
        if (c == 'U') x /= 2;
        else if (c == 'L') x = 2 * x;
        else x = 2 * x + 1;
    }
    return x;
}

// --8<-- [start:core]
// 頂点 x から移動の列 s（'L'・'R'・'U'）に従って進んだ後の頂点
long long move_all(long long x, const string& s) {
    string st;  // まだ適用していない L・R（スタック）
    for (char c : s) {
        if (c == 'U') {
            if (!st.empty()) st.pop_back();  // 直前の L・R と打ち消す
            else x /= 2;                     // 打ち消す相手がないので今すぐ親へ
        } else {
            st.push_back(c);
        }
    }
    // 残りは L・R だけなので、番号は増える一方で最終値を超えない
    for (char c : st) x = (c == 'L' ? 2 * x : 2 * x + 1);
    return x;
}
// --8<-- [end:core]

int main() {
    // 小さい場合を素朴なシミュレーションと照合する（根で U はしない）
    mt19937 rng(1);
    for (int t = 0; t < 2000; t++) {
        long long x = rng() % 50 + 1;
        string s;
        long long cur = x;
        int len = rng() % 12;
        for (int i = 0; i < len; i++) {
            int r = rng() % 3;
            if (r == 0 && cur > 1) { s += 'U'; cur /= 2; }
            else if (r == 1) { s += 'L'; cur = 2 * cur; }
            else { s += 'R'; cur = 2 * cur + 1; }
        }
        assert(move_all(x, s) == naive(x, s));
    }
    long long x;
    string s;
    cin >> x >> s;
    if (s == "-") s = "";
    cout << move_all(x, s) << '\n';
}
