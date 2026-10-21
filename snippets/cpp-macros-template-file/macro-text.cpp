#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
#define SQ(x) x * x            // 括弧がない
#define SQ2(x) ((x) * (x))     // 引数と全体を括弧で囲む

int calls = 0;
vector<int> make() { calls++; return {3, 1, 2}; }

int main() {
    cout << SQ(1 + 2) << ' ' << SQ2(1 + 2) << '\n';  // 1 + 2 * 1 + 2 = 5 と 9
    auto v = make();
    // all(make()) と書くと make().begin(), make().end() に置き換わり、
    // 別々の vector のイテレータの組になる（未定義動作）。先に変数に入れる
    sort(v.begin(), v.end());
    cout << calls << '\n';
}
// --8<-- [end:core]
