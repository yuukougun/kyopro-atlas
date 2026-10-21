// 下位 K 個の和を保つ 2 つの multiset：L＝小さい方の K 個、R＝残り。L の和 sum_l を持つ
// 入力：K Q、続く Q 行は「1 x」（x を追加）・「2 x」（x を 1 個削除。必ずある）・「3」（小さい方から K 個の和を出力。K 個未満なら全部の和）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct BottomK {
    int k;
    multiset<long long> L, R;  // 保つ性質：L の個数は min(K, 全体の個数)、L の最大 ≤ R の最小
    long long sum_l = 0;       // L の和（これが答え）
    BottomK(int k) : k(k) {}

    // 1 回の追加・削除で L の個数は 1 しか変わらないので、境界の 1 個を移せば性質が戻る
    void fix() {
        if ((int)L.size() > k) {  // 多すぎる：L の最大を R へ
            auto it = prev(L.end());
            sum_l -= *it;
            R.insert(*it);
            L.erase(it);
        } else if ((int)L.size() < k && !R.empty()) {  // 足りない：R の最小を L へ
            auto it = R.begin();
            sum_l += *it;
            L.insert(*it);
            R.erase(it);
        }
    }
    void insert(long long x) {
        if (L.empty() || x <= *prev(L.end())) {
            L.insert(x);
            sum_l += x;
        } else {
            R.insert(x);
        }
        fix();
    }
    void erase(long long x) {  // x は集合に 1 個以上あること
        if (!L.empty() && x <= *prev(L.end())) {  // L の最大以下なら L にある
            L.erase(L.find(x));                   // L.erase(x) は同じ値をすべて消す
            sum_l -= x;
        } else {
            R.erase(R.find(x));
        }
        fix();
    }
};
// --8<-- [end:core]

int main() {
    int k, q;
    cin >> k >> q;
    BottomK st(k);
    vector<long long> naive;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            long long x;
            cin >> x;
            st.insert(x);
            naive.push_back(x);
        } else if (t == 2) {
            long long x;
            cin >> x;
            st.erase(x);
            naive.erase(find(naive.begin(), naive.end(), x));
        } else {
            vector<long long> s = naive;
            sort(s.begin(), s.end());
            long long expect = 0;
            for (int j = 0; j < min<int>(k, s.size()); j++) expect += s[j];
            assert(st.sum_l == expect);
            assert((int)st.L.size() == min<int>(k, naive.size()));
            assert(st.L.empty() || st.R.empty() || *prev(st.L.end()) <= *st.R.begin());
            cout << st.sum_l << '\n';
        }
    }
}
