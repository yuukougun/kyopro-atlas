// (min,+) の 2×2 行列をセグメント木に載せ、長さ K の窓ごとに DP を求める
// 題材：各位置 i は費用 a_i で 1 にでき、両隣が 1 の位置は費用なしで 1 にできる。
//       K 個続く 1 を作る費用の最小を求める（0 ≤ a_i、1 ≤ K ≤ N）
// 入力：N K、a_0 … a_{N-1}
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // (min,+) の零元（「その遷移はない」）
using Mat = array<array<long long, 2>, 2>;

// 行列の (p, q) 成分：直前の位置が状態 p のとき、今の位置を状態 q にする費用
// 状態 0 ＝ 費用なしで 1 にした、状態 1 ＝ 費用を払って 1 にした
Mat op(Mat a, Mat b) {  // a の区間の後に b の区間が続く
    Mat c;
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q++) {
            c[p][q] = INF;
            for (int k = 0; k < 2; k++) c[p][q] = min(c[p][q], a[p][k] + b[k][q]);
            // c を INF から始めるので、結果は INF を超えない（INF + INF が積み重ならない）
        }
    }
    return c;
}
Mat e() { return {{{0, INF}, {INF, 0}}}; }  // 単位行列：対角が 0、ほかは INF

Mat leaf(long long x) {
    // 費用なしにできるのは直前が払った位置のとき（費用なしの位置は隣り合えない）
    return {{{INF, x}, {0, x}}};
}
// --8<-- [end:core]

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:query]
    vector<Mat> init(n);
    for (int i = 0; i < n; i++) init[i] = leaf(a[i]);
    atcoder::segtree<Mat, op, e> seg(init);
    long long ans = INF;
    for (int l = 0; l + k <= n; l++) {
        // 窓の手前を「費用なし」の状態とみなすと、窓の先頭は払うしかない
        ans = min(ans, seg.prod(l, l + k)[0][1]);  // 窓の末尾を払う
        if (l + k < n) ans = min(ans, seg.prod(l, l + k + 1)[0][1]);  // 窓の次の位置を払う
    }
    // --8<-- [end:query]

    if (n <= 12) {  // 払う位置の集合を全探索して確かめる
        long long brute = INF;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> x(n);
            long long cost = 0;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) x[i] = 1, cost += a[i];
            }
            bool changed = true;
            while (changed) {  // 費用なしで 1 にできる位置を、できなくなるまで埋める
                changed = false;
                for (int i = 1; i + 1 < n; i++) {
                    if (!x[i] && x[i - 1] && x[i + 1]) x[i] = 1, changed = true;
                }
            }
            int run = 0;
            bool ok = false;
            for (int i = 0; i < n; i++) {
                run = x[i] ? run + 1 : 0;
                if (run >= k) ok = true;
            }
            if (ok) brute = min(brute, cost);
        }
        assert(ans == brute);
    }
    cout << ans << '\n';
}
