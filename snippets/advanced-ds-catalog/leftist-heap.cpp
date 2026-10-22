#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 最小が先頭の leftist heap。全体に足す値（lazy）を持つ。節点は配列で持ち、0 を空とする
struct LeftistHeap {
    vector<long long> key, lazy;
    vector<int> lc, rc, dist;  // dist：右の子をたどって空に着くまでの節点の数
    LeftistHeap() : key(1), lazy(1), lc(1), rc(1), dist(1, 0) {}
    int make(long long x) {
        key.push_back(x); lazy.push_back(0);
        lc.push_back(0); rc.push_back(0); dist.push_back(1);
        return (int)key.size() - 1;
    }
    void push(int v) {  // 保留の加算を子へ降ろす
        if (lazy[v] == 0) return;
        for (int c : {lc[v], rc[v]}) if (c) { key[c] += lazy[v]; lazy[c] += lazy[v]; }
        lazy[v] = 0;
    }
    int meld(int a, int b) {  // 根が a・b のヒープを併合し、新しい根を返す
        if (a == 0) return b;
        if (b == 0) return a;
        if (key[b] < key[a]) swap(a, b);
        push(a);
        rc[a] = meld(rc[a], b);  // 右の背骨だけを降りる
        if (dist[lc[a]] < dist[rc[a]]) swap(lc[a], rc[a]);
        dist[a] = dist[rc[a]] + 1;
        return a;
    }
    int pop(int a) { push(a); return meld(lc[a], rc[a]); }  // 根を除いた残りの根
    void add_all(int a, long long c) { if (a) { key[a] += c; lazy[a] += c; } }
};
// --8<-- [end:core]

int main() {
    // 乱択で multiset と比べる（ヒープ 5 本、操作 20000 回）
    {
        mt19937 rng(12345);
        LeftistHeap h;
        vector<int> root(5, 0);
        vector<multiset<long long>> ref(5);
        for (int it = 0; it < 20000; it++) {
            int t = rng() % 4, i = rng() % 5, j = rng() % 5;
            if (t == 0) {
                long long x = (long long)(rng() % 2001) - 1000;
                root[i] = h.meld(root[i], h.make(x));
                ref[i].insert(x);
            } else if (t == 1 && i != j) {
                root[i] = h.meld(root[i], root[j]);
                root[j] = 0;
                ref[i].insert(ref[j].begin(), ref[j].end());
                ref[j].clear();
            } else if (t == 2) {
                long long c = (long long)(rng() % 21) - 10;
                h.add_all(root[i], c);
                multiset<long long> s;
                for (long long x : ref[i]) s.insert(x + c);
                ref[i] = s;
            } else if (t == 3 && root[i]) {
                assert(h.key[root[i]] == *ref[i].begin());
                root[i] = h.pop(root[i]);
                ref[i].erase(ref[i].begin());
            }
            assert((root[i] == 0) == ref[i].empty());
        }
    }
    // 入力：ヒープの本数 n と操作の数 q。操作は
    // 0 h x：ヒープ h に x を入れる / 1 a b：b を a に併合する（a ≠ b） / 2 h c：h の全体に c を足す / 3 h：h の最小を取り出して出力（空なら -1）
    int n, q;
    cin >> n >> q;
    LeftistHeap h;
    vector<int> root(n, 0);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) { int i; long long x; cin >> i >> x; root[i] = h.meld(root[i], h.make(x)); }
        if (t == 1) { int a, b; cin >> a >> b; root[a] = h.meld(root[a], root[b]); root[b] = 0; }
        if (t == 2) { int i; long long c; cin >> i >> c; h.add_all(root[i], c); }
        if (t == 3) {
            int i; cin >> i;
            if (root[i] == 0) { cout << -1 << '\n'; continue; }
            cout << h.key[root[i]] << '\n';
            root[i] = h.pop(root[i]);
        }
    }
}
