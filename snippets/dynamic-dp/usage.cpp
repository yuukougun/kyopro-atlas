// 0・1・? の文字列の 1 文字の書き換えのたびに、? を 0 か 1 に置き換えてできる
// 文字列の部分列として現れうる、空でない文字列の種類数（mod 998244353）を答える
// 入力：N Q、S、続く Q 行に「p c」（S[p] を文字 c に書き換える。0-indexed）
#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/segtree>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// 状態は横ベクトル (x0, x1, 1)。x0・x1 は末尾が 0・1 の異なる部分列の数
// 行列の (p, q) 成分は「状態 p から状態 q への係数」で、1 文字読むと v ← v T
struct Mat {
    array<array<mint, 3>, 3> a;  // vector<vector> にしない（積のたびに確保が起きて遅い）
};

Mat op(Mat x, Mat y) {  // x の区間の後に y の区間が続く：積 xy
    Mat z;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) z.a[i][j] = 0;
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) z.a[i][j] += x.a[i][k] * y.a[k][j];
        }
    }
    return z;
}

Mat e() {  // 単位行列（0 で埋めた行列ではない）
    Mat z;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) z.a[i][j] = (i == j ? 1 : 0);
    }
    return z;
}

Mat leaf(char c) {
    Mat z = e();
    // 文字 d を読めるなら x_d ← x0 + x1 + 1（d の列を (1, 1, 1) にする）
    for (int d = 0; d < 2; d++) {
        if (c == '?' || c - '0' == d) {
            for (int k = 0; k < 3; k++) z.a[k][d] = 1;
        }
    }
    return z;
}
// --8<-- [end:core]

long long brute(const string& s) {  // ? の置き換えと部分列をすべて列挙する
    int n = s.size();
    set<string> all;
    for (int rep = 0; rep < (1 << n); rep++) {
        string t = s;
        for (int i = 0; i < n; i++) {
            if (t[i] == '?') t[i] = (rep >> i & 1) ? '1' : '0';
        }
        for (int mask = 1; mask < (1 << n); mask++) {
            string u;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) u += t[i];
            }
            all.insert(u);
        }
    }
    return all.size();
}

int main() {
    int n, q;
    string s;
    cin >> n >> q >> s;

    // --8<-- [start:query]
    vector<Mat> init(n);
    for (int i = 0; i < n; i++) init[i] = leaf(s[i]);
    atcoder::segtree<Mat, op, e> seg(init);  // 構築 O(3^3 N)

    vector<pair<string, long long>> checks;  // 全探索で確かめる用
    for (int i = 0; i < q; i++) {
        int p;
        char c;
        cin >> p >> c;
        seg.set(p, leaf(c));  // 1 点の書き換え O(3^3 log N)
        Mat t = seg.all_prod();  // 全体の積は根の値
        // 初めのベクトル (0, 0, 1) に掛けると、t の添字 2 の行が (x0, x1, 1) になる
        mint ans = t.a[2][0] + t.a[2][1];
        cout << ans.val() << '\n';
        s[p] = c;
        checks.push_back({s, ans.val()});
    }
    // --8<-- [end:query]

    if (n <= 10) {
        for (auto& [str, v] : checks) assert(v == brute(str));
    }
}
