// 0 〜 N-1 の順列の先頭を末尾へ回す操作を N-1 回行い、各時点の転倒数を出力する（差分で更新）
// 入力：N、P_0 … P_{N-1}。出力：k = 0, 1, …, N-1 回回した列の転倒数を 1 行ずつ
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

long long brute(const vector<int>& p) {
    long long c = 0;
    for (int i = 0; i < (int)p.size(); i++)
        for (int j = i + 1; j < (int)p.size(); j++)
            if (p[i] > p[j]) c++;
    return c;
}

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    // --8<-- [start:core]
    atcoder::fenwick_tree<int> bit(n);
    long long inv = 0;
    for (int j = 0; j < n; j++) {
        inv += bit.sum(p[j] + 1, n);  // 値が 0〜N-1 なので座標圧縮は要らない
        bit.add(p[j], 1);
    }
    vector<long long> ans(n);
    for (int k = 0; k < n; k++) {
        ans[k] = inv;           // k 回回した列の先頭は p[k]
        int x = p[k];
        inv -= x;               // 先頭の x が抜ける：後ろにある x 未満の x 個との転倒が消える
        inv += n - 1 - x;       // 末尾に x が入る：前にある x 超の N-1-x 個との転倒が増える
    }
    // --8<-- [end:core]
    vector<int> q = p;
    for (int k = 0; k < n; k++) {
        assert(ans[k] == brute(q));
        rotate(q.begin(), q.begin() + 1, q.end());
        cout << ans[k] << '\n';
    }
}
