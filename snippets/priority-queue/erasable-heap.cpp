// 削除できるヒープ（遅延削除）：本体 q と削除予定 del の 2 つの最大ヒープを持つ。
// 保つ性質：del の中身（多重集合）は q の中身に含まれる。実際の集合は q − del。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct ErasableHeap {
    priority_queue<long long> q, del;

    void push(long long x) { q.push(x); }
    void erase(long long x) { del.push(x); }  // x が今の集合にあるときだけ呼ぶ
    void clean() {  // 両方の top が同じ間、両方から捨てる
        while (!del.empty() && q.top() == del.top()) {
            q.pop();
            del.pop();
        }
    }
    bool empty() { return q.size() == del.size(); }
    int size() { return (int)(q.size() - del.size()); }
    long long top() {  // 空のときに呼ばない
        clean();
        return q.top();
    }
    void pop() {
        clean();
        q.pop();
    }
};
// --8<-- [end:core]

int main() {
    // 乱数で multiset と突き合わせる
    mt19937 rng(2026);
    for (int t = 0; t < 200; t++) {
        ErasableHeap h;
        multiset<long long> s;
        for (int step = 0; step < 200; step++) {
            int op = rng() % 4;
            if (op == 0 || s.empty()) {
                long long x = rng() % 10;
                h.push(x);
                s.insert(x);
            } else if (op == 1) {  // 今ある要素から 1 つ選んで消す
                auto it = next(s.begin(), rng() % s.size());
                h.erase(*it);
                s.erase(it);
            } else if (op == 2) {
                assert(h.top() == *s.rbegin());
            } else {
                h.pop();
                s.erase(prev(s.end()));
            }
            assert(h.size() == (int)s.size());
            assert(h.empty() == s.empty());
        }
    }
    // クエリ：1 x（追加）、2 x（x を 1 個削除。x はある）、3（最大を出力。空なら -1）
    int q;
    cin >> q;
    ErasableHeap h;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long x;
            cin >> x;
            h.push(x);
        } else if (type == 2) {
            long long x;
            cin >> x;
            h.erase(x);
        } else {
            cout << (h.empty() ? -1 : h.top()) << '\n';
        }
    }
}
