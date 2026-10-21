// 相異なる整数の集合への追加・削除のたびに、2 要素の差の最小値を答える。
// 入力：Q 行の「+ x」（追加。まだないとする）・「- x」（削除。あるとする）。各行の後に答え（2 要素未満なら -1）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    // --8<-- [start:core]
    set<long long> st;        // 値の集合
    multiset<long long> gap;  // ソート順で隣り合う 2 要素の差（同じ差が何度も出るので multiset）
    auto add = [&](long long x) {
        auto it = st.insert(x).first;
        bool hasL = it != st.begin(), hasR = next(it) != st.end();
        if (hasL && hasR) gap.erase(gap.find(*next(it) - *prev(it)));  // 割り込まれた組を消す
        if (hasL) gap.insert(x - *prev(it));
        if (hasR) gap.insert(*next(it) - x);
    };
    auto remove = [&](long long x) {
        auto it = st.find(x);
        bool hasL = it != st.begin(), hasR = next(it) != st.end();
        if (hasL) gap.erase(gap.find(x - *prev(it)));  // 値ではなく find で 1 個だけ消す
        if (hasR) gap.erase(gap.find(*next(it) - x));
        if (hasL && hasR) gap.insert(*next(it) - *prev(it));  // 両隣が新しく隣り合う
        st.erase(it);
    };
    // --8<-- [end:core]
    while (q--) {
        char op;
        long long x;
        cin >> op >> x;
        if (op == '+') add(x);
        else remove(x);
        assert(gap.size() + 1 == max<size_t>(st.size(), 1));
        cout << (gap.empty() ? -1 : *gap.begin()) << '\n';
    }
}
