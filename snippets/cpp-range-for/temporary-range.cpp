#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

vector<int> make(int n) { return vector<int>(n, 1); }

int main() {
    int n, m;
    cin >> n >> m;
    atcoder::dsu d(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d.merge(a, b);
    }
    // --8<-- [start:core]
    // 関数の戻り値そのものを回す：どの版でも安全（一時オブジェクトはループの終わりまで生きる）
    int s = 0;
    for (int x : make(n)) s += x;

    // 戻り値の中身（[0] やメンバ）を回すときは、いったん変数に受ける：どの版でも安全
    auto groups = d.groups();
    for (int v : groups[0]) cout << v << ' ';
    cout << '\n';
    // for (int v : d.groups()[0])  // C++23 の規則（GCC 15 以降）でだけ安全
    // --8<-- [end:core]
    cout << s << '\n';
}
