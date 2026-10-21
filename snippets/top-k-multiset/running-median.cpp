// 追加だけのときの中央値と Σ|x − a_i| の最小値：2 つのヒープ
// 入力：Q、続く Q 行に追加する整数 a。追加のたびに「中央値（偶数個なら小さい方） Σ|m − a_i|」を出力する
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct RunningMedian {
    priority_queue<long long> L;                                     // 小さい半分（最大ヒープ）
    priority_queue<long long, vector<long long>, greater<long long>> R;  // 大きい半分（最小ヒープ）
    long long sum_l = 0, sum_r = 0;
    // 保つ性質：L の最大 ≤ R の最小、L の個数 = R の個数 か R の個数 + 1

    void insert(long long a) {
        if (L.empty() || a <= L.top()) {
            L.push(a);
            sum_l += a;
        } else {
            R.push(a);
            sum_r += a;
        }
        if (L.size() > R.size() + 1) {  // L が 2 個多い：L の最大を R へ
            long long v = L.top();
            L.pop();
            sum_l -= v;
            R.push(v);
            sum_r += v;
        } else if (R.size() > L.size()) {  // R が多い：R の最小を L へ
            long long v = R.top();
            R.pop();
            sum_r -= v;
            L.push(v);
            sum_l += v;
        }
    }
    long long median() const { return L.top(); }  // 1 個以上あること
    long long min_abs_sum() const {              // x = 中央値 m のときの Σ|x − a_i|
        long long m = L.top();
        return (m * (long long)L.size() - sum_l) + (sum_r - m * (long long)R.size());
    }
};
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    RunningMedian rm;
    vector<long long> naive;
    for (int i = 0; i < q; i++) {
        long long a;
        cin >> a;
        rm.insert(a);
        naive.push_back(a);
        vector<long long> s = naive;
        sort(s.begin(), s.end());
        long long m = s[(s.size() - 1) / 2];
        long long best = LLONG_MAX;
        for (long long x : s) {
            long long t = 0;
            for (long long y : s) t += llabs(x - y);
            best = min(best, t);
        }
        assert(rm.median() == m);
        assert(rm.min_abs_sum() == best);
        cout << rm.median() << ' ' << rm.min_abs_sum() << '\n';
    }
}
