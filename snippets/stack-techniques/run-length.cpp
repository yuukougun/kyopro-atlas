// ランレングスを積む：値 k の玉が k 個続くとまとめて消える筒に、玉を順に入れる。
// 入れるたびに筒の中の玉の数を出力する。スタックには (値, 続いている個数) を積む。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<pair<int, int>> st;  // (値, その値が末尾に続いている個数)
    long long total = 0;        // 筒の中の玉の数
    for (int i = 0; i < n; i++) {
        if (!st.empty() && st.back().first == a[i]) st.back().second++;
        else st.push_back({a[i], 1});
        total++;
        if (st.back().second == st.back().first) {  // 値 k が k 個そろった
            total -= st.back().second;
            st.pop_back();  // 塊ごと消す。新しい先頭は個数が値より少ないままなので、連鎖は起きない
        }
        cout << total << '\n';
    }
    // --8<-- [end:core]
}
