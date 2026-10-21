#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto show = [](const auto& x) { cout << x << ' '; };  // 呼んだ型ごとに中身が作られる（C++14）
    show(3);
    show(2.5);
    show(string("ab"));
    cout << '\n';

    auto total = []<class T>(const vector<T>& v) {  // 要素の型 T に名前を付けたいとき（C++20）
        T s{};
        for (const T& x : v) s += x;
        return s;
    };
    cout << total(vector<int>{1, 2, 3}) << ' ' << total(vector<long long>{1LL << 40, 1}) << '\n';

    auto mul = [](long long a, long long b) static { return a * b; };  // キャプチャを持たない印（C++23）
    cout << mul(3, 4) << '\n';
    // --8<-- [end:core]
}
