#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    __int128 p = (__int128)a * b;
    println("{}", p);              // __int128 は format・println なら出せる
    mint m = mint(a) * b;
    cout << m.val() << '\n';       // modint は .val() で整数を取り出して出す
    vector<long long> v = {a, b};
    println("{}", v);              // [a, b] と出る（AtCoder の形式ではない）
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << " \n"[i == (int)v.size() - 1];
    // --8<-- [end:core]
}
