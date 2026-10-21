#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    vector<mint> v = {3, 1, 2};
    // --8<-- [start:core]
    sort(v.begin(), v.end());  // コンパイルエラー：mint には < がない
    set<mint> st;              // set も < を使うので、insert でエラーになる
    st.insert(v[0]);
    // --8<-- [end:core]
}
