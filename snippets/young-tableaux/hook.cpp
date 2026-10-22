// Young 図形 lambda（各行の長さ、非増加）の標準タブローの数をフック長公式で求める。
// 確認として、小さい N で「角を 1 つ外す漸化式」による数と一致すること、
// RS 対応の挿入で 1 行目の長さが LIS・行数が LDS になること、
// 形ごとの (f^lambda)^2 の和が N! になることを assert で確かめる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// lambda[i] は i 行目の長さ（非増加）。法 p は N より大きい素数とする
mint count_syt(const vector<int>& lambda) {
    int rows = lambda.size();
    int n = 0;
    for (int len : lambda) n += len;
    // col[j] は j 列目の長さ（転置した図形）
    vector<int> col(rows == 0 ? 0 : lambda[0], 0);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < lambda[i]; j++) col[j]++;
    mint num = 1, den = 1;
    for (int k = 1; k <= n; k++) num *= k;          // N!
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < lambda[i]; j++) {
            int arm = lambda[i] - 1 - j;   // 右にある箱の数
            int leg = col[j] - 1 - i;      // 下にある箱の数
            den *= arm + leg + 1;          // フック長
        }
    }
    return num / den;                               // 逆元で割る
}
// --8<-- [end:core]

// --8<-- [start:rs]
// RS 対応の挿入：x を 1 行目に入れ、x より大きい最小の値を追い出して次の行へ入れる
void rs_insert(vector<vector<int>>& p, int x) {
    for (auto& row : p) {
        auto it = upper_bound(row.begin(), row.end(), x);
        if (it == row.end()) { row.push_back(x); return; }
        swap(*it, x);                  // 追い出した値を次の行へ持っていく
    }
    p.push_back({x});                  // どの行にも収まらなければ新しい行を作る
}
// --8<-- [end:rs]

// 角を 1 つ外す漸化式で標準タブローを数える（確認用、小さい図形だけ）
long long count_syt_naive(vector<int> lambda, map<vector<int>, long long>& memo) {
    while (!lambda.empty() && lambda.back() == 0) lambda.pop_back();
    if (lambda.empty()) return 1;
    if (auto it = memo.find(lambda); it != memo.end()) return it->second;
    long long res = 0;
    for (int i = 0; i < (int)lambda.size(); i++) {
        // 最大の値 N は角（右にも下にも箱がない箱）に入る
        bool corner = (i + 1 == (int)lambda.size() || lambda[i + 1] < lambda[i]);
        if (!corner) continue;
        lambda[i]--;
        res += count_syt_naive(lambda, memo);
        lambda[i]++;
    }
    return memo[lambda] = res;
}

int lis_naive(const vector<int>& a, bool increasing) {
    int n = a.size(), best = 0;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (increasing ? a[j] < a[i] : a[j] > a[i]) dp[i] = max(dp[i], dp[j] + 1);
        best = max(best, dp[i]);
    }
    return best;
}

void self_check() {
    map<vector<int>, long long> memo;
    for (int n = 1; n <= 7; n++) {
        vector<int> a(n);
        iota(a.begin(), a.end(), 1);
        map<vector<int>, long long> shape_count;   // 形ごとの順列の数
        do {
            vector<vector<int>> p;
            for (int x : a) rs_insert(p, x);
            int first_row = p[0].size(), rows = p.size();
            assert(first_row == lis_naive(a, true));   // 1 行目の長さ = LIS
            assert(rows == lis_naive(a, false));       // 行数 = LDS
            vector<int> shape;
            for (auto& row : p) shape.push_back(row.size());
            shape_count[shape]++;
        } while (next_permutation(a.begin(), a.end()));
        long long fact = 1;
        for (int k = 1; k <= n; k++) fact *= k;
        long long total = 0;
        for (auto& [shape, cnt] : shape_count) {
            long long f = count_syt_naive(shape, memo);
            assert((long long)count_syt(shape).val() == f % 998244353);
            assert(cnt == f * f);              // その形の順列の数 = (f^lambda)^2
            total += f * f;
        }
        assert(total == fact);                 // 形について和を取ると N!
    }
}

int main() {
    self_check();
    int k;
    cin >> k;
    vector<int> lambda(k);
    for (int i = 0; i < k; i++) cin >> lambda[i];
    cout << count_syt(lambda).val() << '\n';
}
