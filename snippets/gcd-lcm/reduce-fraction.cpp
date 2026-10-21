#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 分数 p / q（q != 0）を、既約で分母が正の組 (p, q) に直す
pair<long long, long long> normalize(long long p, long long q) {
    long long g = gcd(p, q);  // 負の数は絶対値で計算する。p = 0 なら |q|
    p /= g;
    q /= g;
    if (q < 0) {  // 分母を正にそろえる（-1/2 と 1/-2 を同じにする）
        p = -p;
        q = -q;
    }
    return {p, q};  // p = 0 なら (0, 1)
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    set<pair<long long, long long>> st;
    for (int i = 0; i < n; i++) {
        long long p, q;
        cin >> p >> q;
        st.insert(normalize(p, q));
    }
    cout << st.size() << '\n';  // 値の違う分数の個数
}
