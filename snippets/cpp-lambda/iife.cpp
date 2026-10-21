#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    // 先頭から正の数が続く長さ。求め終えたら変えないので const にしたい
    const int k = [&] {
        int r = 0;
        while (r < n && a[r] > 0) r++;
        return r;
    }();  // 最後の () で、作ったラムダをその場で呼ぶ
    // --8<-- [end:core]
    cout << k << '\n';
}
