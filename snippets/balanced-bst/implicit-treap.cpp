#include <bits/stdc++.h>
using namespace std;

// 位置で分割・結合する treap（implicit treap）。ノードは配列に置き、子は番号で持つ（-1 は空）
mt19937 rng(20261022);

struct Node {
    long long val, sum;  // 自分の値と、部分木の値の和
    unsigned pri;        // ランダムな優先度（親は子以上）
    int sz = 1;          // 部分木の要素数。位置はこれで決まる
    bool rev = false;    // 部分木を反転する保留
    int l = -1, r = -1;
};
vector<Node> t;

int new_node(long long x) {
    t.push_back(Node{x, x, (unsigned)rng()});
    return (int)t.size() - 1;
}
int size_of(int v) { return v < 0 ? 0 : t[v].sz; }
long long sum_of(int v) { return v < 0 ? 0 : t[v].sum; }

// --8<-- [start:node]
// 子から sz と sum を作り直す
void pull(int v) {
    t[v].sz = size_of(t[v].l) + 1 + size_of(t[v].r);
    t[v].sum = sum_of(t[v].l) + t[v].val + sum_of(t[v].r);
}
// 反転の保留を 1 段だけ子へ降ろす
void push(int v) {
    if (!t[v].rev) return;
    swap(t[v].l, t[v].r);
    if (t[v].l >= 0) t[t[v].l].rev ^= true;
    if (t[v].r >= 0) t[t[v].r].rev ^= true;
    t[v].rev = false;
}
// --8<-- [end:node]

// --8<-- [start:core]
// 木 v を「先頭の k 個」と「残り」に分ける
pair<int, int> split(int v, int k) {
    if (v < 0) return {-1, -1};
    push(v);
    if (k <= size_of(t[v].l)) {
        auto [a, b] = split(t[v].l, k);
        t[v].l = b;
        pull(v);
        return {a, v};
    }
    auto [a, b] = split(t[v].r, k - size_of(t[v].l) - 1);
    t[v].r = a;
    pull(v);
    return {v, b};
}
// 木 a の後ろに木 b をつなぐ。優先度の大きい根を新しい根にする
int join(int a, int b) {
    if (a < 0) return b;
    if (b < 0) return a;
    if (t[a].pri > t[b].pri) {
        push(a);
        t[a].r = join(t[a].r, b);
        pull(a);
        return a;
    }
    push(b);
    t[b].l = join(a, t[b].l);
    pull(b);
    return b;
}
// --8<-- [end:core]

// --8<-- [start:ops]
// 位置 i の直前に x を挿入する（0 <= i <= 要素数）
int insert_at(int root, int i, long long x) {
    auto [a, b] = split(root, i);
    return join(join(a, new_node(x)), b);
}
// 位置 i の要素を取り除く
int erase_at(int root, int i) {
    auto [a, bc] = split(root, i);
    auto [b, c] = split(bc, 1);
    return join(a, c);  // b は捨てる
}
// [l, r) を反転する。切り出した木の根に保留を付けるだけ
int reverse_range(int root, int l, int r) {
    auto [a, bc] = split(root, l);
    auto [b, c] = split(bc, r - l);
    if (b >= 0) t[b].rev ^= true;
    return join(join(a, b), c);
}
// [l, r) の和を返す。切り出した木の根の sum を読み、元に戻す
long long range_sum(int& root, int l, int r) {
    auto [a, bc] = split(root, l);
    auto [b, c] = split(bc, r - l);
    long long s = sum_of(b);
    root = join(join(a, b), c);
    return s;
}
// --8<-- [end:ops]

// 部分木の深さ（確かめ用）
int depth(int v) {
    if (v < 0) return 0;
    return 1 + max(depth(t[v].l), depth(t[v].r));
}

int main() {
    // 乱数の操作を vector の愚直な方法と比べる
    {
        mt19937 gen(1);
        int root = -1;
        vector<long long> naive;
        for (int step = 0; step < 20000; step++) {
            int n = (int)naive.size();
            int type = gen() % 4;
            if (type == 0 || n == 0) {
                int i = gen() % (n + 1);
                long long x = gen() % 1000;
                root = insert_at(root, i, x);
                naive.insert(naive.begin() + i, x);
            } else if (type == 1) {
                int i = gen() % n;
                root = erase_at(root, i);
                naive.erase(naive.begin() + i);
            } else {
                int l = gen() % (n + 1), r = gen() % (n + 1);
                if (l > r) swap(l, r);
                if (type == 2) {
                    root = reverse_range(root, l, r);
                    reverse(naive.begin() + l, naive.begin() + r);
                } else {
                    long long s = accumulate(naive.begin() + l, naive.begin() + r, 0LL);
                    assert(range_sum(root, l, r) == s);
                }
            }
            assert(size_of(root) == (int)naive.size());
        }
        // 10^5 個を末尾に挿入しても（BST なら一直線になる順でも）深さは小さい
        t.clear();
        root = -1;
        for (int i = 0; i < 100000; i++) root = insert_at(root, i, i);
        assert(depth(root) < 60);
        t.clear();
    }

    // 入力：N Q、列、クエリ（0 l r：反転、1 l r：和を出力、2 i x：挿入、3 i：削除）
    int n, q;
    cin >> n >> q;
    int root = -1;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        root = join(root, new_node(x));
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r;
            cin >> l >> r;
            root = reverse_range(root, l, r);
        } else if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << range_sum(root, l, r) << '\n';
        } else if (type == 2) {
            int i;
            long long x;
            cin >> i >> x;
            root = insert_at(root, i, x);
        } else {
            int i;
            cin >> i;
            root = erase_at(root, i);
        }
    }
}
