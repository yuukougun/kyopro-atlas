// priority_queue の基本：最大を取り出す向き（既定）と最小を取り出す向き（greater）、pair の比較順。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    priority_queue<int> mx;                             // top() が最大
    priority_queue<int, vector<int>, greater<int>> mn;  // top() が最小
    priority_queue<pair<int, int>> ps;                  // (値, 添字) の辞書順で最大
    for (int i = 0; i < n; i++) {
        mx.push(a[i]);
        mn.push(a[i]);
        ps.push({a[i], i});  // 値が同じなら添字の大きい方が先に出る
    }
    while (!mx.empty()) {  // 空の priority_queue の top() は未定義動作
        cout << mx.top() << ' ';
        mx.pop();
    }
    cout << '\n';
    while (!mn.empty()) {
        cout << mn.top() << ' ';
        mn.pop();
    }
    cout << '\n';
    while (!ps.empty()) {
        auto [v, i] = ps.top();  // 値をコピーしてから pop する（参照のまま pop しない）
        ps.pop();
        cout << v << ':' << i << ' ';
    }
    cout << '\n';
    // --8<-- [end:core]
}
