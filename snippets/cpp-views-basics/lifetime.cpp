#include <bits/stdc++.h>
using namespace std;

vector<int> make(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i * i;
    return v;
}

// --8<-- [start:bad]
// 呼ぶと壊れる：v はこの関数を出ると消えるのに、返す view は v を指したまま
auto evens_bad(int n) {
    vector<int> v = make(n);
    return v | views::filter([](int x) { return x % 2 == 0; });
}
// --8<-- [end:bad]

// --8<-- [start:good]
// 安全：右辺値（一時オブジェクト）のコンテナを流すと、コンテナは view の中に移される
auto evens_good(int n) {
    return make(n) | views::filter([](int x) { return x % 2 == 0; });
}
// --8<-- [end:good]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    for (int x : make(n) | views::reverse) cout << x << ' ';  // make(n) の結果はループの間ずっと生きている
    cout << '\n';
    // --8<-- [end:core]
    for (int x : evens_good(n)) cout << x << ' ';
    cout << '\n';
    (void)&evens_bad;
}
