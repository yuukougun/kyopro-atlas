#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 全山の XOR（ニム和）。0 なら手番の人（先手）の負け
long long nim_sum(const vector<long long>& a) {
    long long s = 0;
    for (long long x : a) s ^= x;
    return s;
}

// 勝つための手：{山の番号, 取った後の個数}。ニム和が 0 なら {-1, -1}
pair<int, long long> winning_move(const vector<long long>& a) {
    long long s = nim_sum(a);
    if (s == 0) return {-1, -1};
    for (int i = 0; i < (int)a.size(); i++) {
        long long t = a[i] ^ s;           // この山を t にすれば全体の XOR が 0
        if (t < a[i]) return {i, t};      // 減らす向きでなければ取れない
    }
    return {-1, -1};                      // ここには来ない（s の最上位 bit を持つ山がある）
}
// --8<-- [end:core]

// --8<-- [start:bounded]
// 1 回に 1〜k 個だけ取れる Nim：各山を k+1 で割った余りの Nim と同じ
bool bounded_first_wins(const vector<long long>& a, long long k) {
    long long s = 0;
    for (long long x : a) s ^= x % (k + 1);
    return s != 0;
}
// --8<-- [end:bounded]

// 小さい山で、全局面の勝敗を DP で求めて上の結論と比べる（3 山、各 0〜7）
void self_check() {
    const int V = 8;
    // win[a][b][c]：通常（最後に取った方が勝ち）、mis：逆形（最後に取った方が負け）
    // bwin[k][a][b]：1〜k 個だけ取れる 2 山の Nim（各 0〜11）
    static bool win[V][V][V], mis[V][V][V];
    for (int t = 0; t < 3 * V; t++) {     // 石の総数の小さい順に埋める
        for (int a = 0; a < V; a++) for (int b = 0; b < V; b++) for (int c = 0; c < V; c++) {
            if (a + b + c != t) continue;
            bool w = false, m = (t == 0);  // 逆形：石がなければ直前に取った相手の負け＝手番の勝ち
            for (int x = 0; x < a; x++) { w |= !win[x][b][c]; m |= !mis[x][b][c]; }
            for (int x = 0; x < b; x++) { w |= !win[a][x][c]; m |= !mis[a][x][c]; }
            for (int x = 0; x < c; x++) { w |= !win[a][b][x]; m |= !mis[a][b][x]; }
            win[a][b][c] = w;
            mis[a][b][c] = m;
            vector<long long> v = {a, b, c};
            assert(w == (nim_sum(v) != 0));
            // 逆形の結論：すべて 1 以下なら 1 の山が偶数個のとき先手勝ち、そうでなければ通常と同じ
            bool small = (a <= 1 && b <= 1 && c <= 1);
            bool expect = small ? ((a + b + c) % 2 == 0) : (nim_sum(v) != 0);
            assert(m == expect);
            auto [i, nv] = winning_move(v);
            if (w) { v[i] = nv; assert(nim_sum(v) == 0); }
        }
    }
    const int B = 12;
    for (int k = 1; k <= 4; k++) {
        static bool bw[B][B];
        for (int t = 0; t < 2 * B; t++) {
            for (int a = 0; a < B; a++) for (int b = 0; b < B; b++) {
                if (a + b != t) continue;
                bool w = false;
                for (int d = 1; d <= k; d++) {
                    if (a - d >= 0) w |= !bw[a - d][b];
                    if (b - d >= 0) w |= !bw[a][b - d];
                }
                bw[a][b] = w;
                assert(w == bounded_first_wins({a, b}, k));
            }
        }
    }
}

int main() {
    self_check();
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    auto [i, t] = winning_move(a);
    if (i < 0) {
        cout << "Second" << '\n';
    } else {
        cout << "First" << '\n' << i << ' ' << t << '\n';
    }
}
