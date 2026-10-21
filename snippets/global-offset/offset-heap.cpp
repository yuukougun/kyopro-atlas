#include <bits/stdc++.h>
using namespace std;

// 全体に足した量 d を別に持つ最小ヒープ。
// 保つ性質：実際の値 = 格納値 + d（すべての要素で同じ d）
struct OffsetMinHeap {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    long long d = 0;
    // --8<-- [start:core]
    void push(long long v) { pq.push(v - d); }     // 入れるときに引く
    void add_all(long long x) { d += x; }          // 全体への加算は d だけ
    long long top() const { return pq.top() + d; } // 出すときに足す
    void pop() { pq.pop(); }
    // --8<-- [end:core]
    bool empty() const { return pq.empty(); }
};

int main() {
    // 入力：Q と、Q 行の操作。"P v"（v を入れる）・"A x"（全体に x を足す）・"M"（最小を取り出して出力）
    int q;
    cin >> q;
    OffsetMinHeap h;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 'P') {
            long long v;
            cin >> v;
            h.push(v);
        } else if (t == 'A') {
            long long x;
            cin >> x;
            h.add_all(x);
        } else {
            assert(!h.empty());
            cout << h.top() << '\n';
            h.pop();
        }
    }
}
