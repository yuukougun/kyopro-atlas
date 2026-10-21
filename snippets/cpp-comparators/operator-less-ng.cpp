#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Seg {
    int l, r;
    bool operator<(const Seg& o) { return r < o.r; }  // const を忘れた
};
// --8<-- [end:core]

int main() {
    vector<Seg> v = {{1, 5}, {2, 3}};
    sort(v.begin(), v.end());  // これは通る
    set<Seg> st(v.begin(), v.end());  // ここでコンパイルエラー
}
