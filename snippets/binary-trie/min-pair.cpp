#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 多重集合の「2 要素の XOR の最小値」を、追加・削除のたびに O(B) で直す
struct MinPairTrie {
    static constexpr long long INF = LLONG_MAX;
    int B;
    vector<array<int, 2>> ch;
    vector<int> cnt;
    vector<long long> xs;    // 部分木の要素の XOR（cnt == 1 ならその要素）
    vector<long long> best;  // 部分木の中の 2 要素の XOR の最小値（cnt < 2 なら INF）

    MinPairTrie(int b, int max_nodes) : B(b) {  // max_nodes は 1 + (追加の回数) * B
        ch.reserve(max_nodes);
        cnt.reserve(max_nodes);
        xs.reserve(max_nodes);
        best.reserve(max_nodes);
        new_node();
    }
    int new_node() {
        ch.push_back({-1, -1});
        cnt.push_back(0);
        xs.push_back(0);
        best.push_back(INF);
        return ch.size() - 1;
    }
    int c(int v) const { return v == -1 ? 0 : cnt[v]; }

    void add(long long a, int k) {  // k = 1 で追加、-1 で 1 個削除
        array<int, 64> path;  // path[i] は深さ i のノード（B <= 63）
        path[0] = 0;
        int v = 0;
        for (int b = B - 1; b >= 0; b--) {
            int d = (a >> b) & 1;
            if (ch[v][d] == -1) {
                int u = new_node();
                ch[v][d] = u;
            }
            v = ch[v][d];
            path[B - b] = v;
        }
        for (int i = B; i >= 0; i--) {  // 葉から根へ作り直す
            int u = path[i];
            cnt[u] += k;
            xs[u] ^= a;
            if (i == B) {  // 葉：同じ値が 2 個以上あれば 0
                best[u] = cnt[u] >= 2 ? 0 : INF;
                continue;
            }
            int l = ch[u][0], r = ch[u][1];
            best[u] = INF;
            if (c(l) >= 2) best[u] = min(best[u], best[l]);
            if (c(r) >= 2) best[u] = min(best[u], best[r]);
            if (c(l) == 1 && c(r) == 1) best[u] = xs[l] ^ xs[r];
        }
    }
    long long min_pair() const { return best[0]; }
};
// --8<-- [end:core]

int main() {
    mt19937 rng(2);
    for (int t = 0; t < 200; t++) {
        int B = 1 + rng() % 5;
        MinPairTrie tr(B, 1 + 40 * B);
        multiset<long long> ms;
        for (int q = 0; q < 40; q++) {
            long long a = rng() % (1 << B);
            if (rng() % 3 == 0 && ms.count(a)) {
                tr.add(a, -1);
                ms.erase(ms.find(a));
            } else {
                tr.add(a, 1);
                ms.insert(a);
            }
            long long want = MinPairTrie::INF;
            vector<long long> v(ms.begin(), ms.end());
            for (int i = 0; i < (int)v.size(); i++)
                for (int j = i + 1; j < (int)v.size(); j++) want = min(want, v[i] ^ v[j]);
            assert(tr.min_pair() == want);
        }
    }
    // 入力：Q 個のクエリ。0 a：追加、1 a：1 個削除（入っているときだけ来る）、2：最小値（なければ -1）
    int q;
    cin >> q;
    MinPairTrie tr(30, 1 + 30 * q);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            long long r = tr.min_pair();
            cout << (r == MinPairTrie::INF ? -1 : r) << '\n';
            continue;
        }
        long long a;
        cin >> a;
        tr.add(a, t == 0 ? 1 : -1);
    }
}
