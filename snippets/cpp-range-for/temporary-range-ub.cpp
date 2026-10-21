#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// 版によって動きが変わる書き方。check_snippets では g++-15 の C++23（AtCoder と同じ）だけで動かす
int main() {
    atcoder::dsu d(4);
    d.merge(0, 2);
    d.merge(2, 3);
    // --8<-- [start:core]
    for (int v : d.groups()[0]) cout << v << ' ';  // C++23 の規則では、groups() の戻り値がループの終わりまで生きる
    // --8<-- [end:core]
    cout << '\n';
}
