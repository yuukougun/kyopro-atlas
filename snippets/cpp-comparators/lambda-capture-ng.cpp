#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> w = {50, 10, 30};
    auto by_w = [&](int i, int j) { return w[i] < w[j]; };
    set<int, decltype(by_w)> idx;  // C++20 でもコンパイルエラー（キャプチャを持つラムダ）
    idx.insert(0);
}
