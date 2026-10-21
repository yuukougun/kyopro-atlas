// 全体への加算と組む：オフセット add を持ち、入れるときに引き、出すときに足す。
// クエリ：1 x（x を追加）、2 d（全要素に d を加算）、3（最大を取り出して出力。空なら -1）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    // --8<-- [start:core]
    priority_queue<long long> pq;  // 中身は「実際の値 − add」（add は今までの全体への加算の合計）
    long long add = 0;             // これまでの全体への加算の合計
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long x;
            cin >> x;
            pq.push(x - add);  // 入れるときに引く
        } else if (type == 2) {
            long long d;
            cin >> d;
            add += d;  // 中身は書き換えない
        } else {
            if (pq.empty()) {
                cout << -1 << '\n';
                continue;
            }
            cout << pq.top() + add << '\n';  // 出すときに足す
            pq.pop();
        }
    }
    // --8<-- [end:core]
}
