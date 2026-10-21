#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    for (int i = 0; auto x : a) {   // i の宣言だけを書ける（C++20）
        cout << i << ':' << x << ' ';
        i++;                         // 更新は自分で書く。忘れると i はずっと 0
    }
    cout << '\n';
    // --8<-- [end:core]
}
