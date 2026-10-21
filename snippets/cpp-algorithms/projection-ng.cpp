#include <bits/stdc++.h>
using namespace std;

struct P {
    string name;
    int score;
};

int main() {
    vector<P> ps = {{"a", 2}, {"b", 1}};
    // --8<-- [start:core]
    ranges::sort(ps, &P::score);  // 比較の {} を省くと、&P::score が比較関数の位置に入る：コンパイルエラー
    // --8<-- [end:core]
}
