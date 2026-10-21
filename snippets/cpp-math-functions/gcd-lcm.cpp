#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    auto g = gcd(a, 18LL);                   // int と long long を混ぜてよい。結果は long long
    long long l = lcm((long long)a, b);      // int 同士の lcm は int で返るので、片方を long long にする
    long long l2 = (long long)a / gcd(a, b) * b;  // 自分で書くなら、先に割ってから掛ける
    // --8<-- [end:core]
    static_assert(is_same_v<decltype(g), long long>);
    assert(l == l2);
    cout << g << ' ' << gcd(-a, b) << ' ' << l << '\n';
}
