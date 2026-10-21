#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:by-value]
long long first_slow(vector<int> v) { return v[0]; }        // 呼ぶたびに v を丸ごとコピーする（O(N)）
long long first_fast(const vector<int>& v) { return v[0]; }  // 参照で受けるのでコピーしない（O(1)）
// --8<-- [end:by-value]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:set-lower-bound]
    set<int> st;
    for (int i = 0; i < n; i++) st.insert(2 * i);
    auto it1 = lower_bound(st.begin(), st.end(), 5);  // 遅い：1 回 O(N)
    auto it2 = st.lower_bound(5);                     // 速い：1 回 O(log N)
    // --8<-- [end:set-lower-bound]
    assert(it1 == it2);
    // --8<-- [start:string-append]
    string s, t;
    for (int i = 0; i < n; i++) s = s + 'a';  // 遅い：毎回 s をコピーした新しい文字列を作る（全体 O(N^2)）
    for (int i = 0; i < n; i++) t += 'a';     // 速い：末尾に足すだけ（全体 O(N)）
    // --8<-- [end:string-append]
    assert(s == t);
    // --8<-- [start:recursion]
    function<long long(int)> fib1 = [&](int k) -> long long {  // 遅い：呼ぶたびに間接呼び出し
        return k < 2 ? k : fib1(k - 1) + fib1(k - 2);
    };
    auto fib2 = [&](auto&& self, int k) -> long long {  // 速い：自分を引数で受け取る
        return k < 2 ? k : self(self, k - 1) + self(self, k - 2);
    };
    // --8<-- [end:recursion]
    vector<int> v(max(n, 1), 7);
    assert(first_slow(v) == first_fast(v));
    cout << *it2 << ' ' << t.size() << ' ' << fib1(20) << ' ' << fib2(fib2, 20) << '\n';
}
