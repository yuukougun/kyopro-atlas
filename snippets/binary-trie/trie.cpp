#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0 以上 2^B 未満の整数の多重集合。ノード 0 が根。
struct BinaryTrie {
    int B;
    vector<array<int, 2>> ch;  // 子の番号（-1 はなし）
    vector<int> cnt;           // 部分木に入っている要素の個数

    BinaryTrie(int b, int max_nodes) : B(b) {
        ch.reserve(max_nodes);
        cnt.reserve(max_nodes);
        ch.push_back({-1, -1});
        cnt.push_back(0);
    }
    int size() const { return cnt[0]; }

    // a を k 個足す（k = -1 で 1 個消す。消すのは入っているときだけ）
    void add(long long a, int k) {
        int v = 0;
        cnt[v] += k;
        for (int b = B - 1; b >= 0; b--) {
            int c = (a >> b) & 1;
            if (ch[v][c] == -1) {
                ch[v][c] = ch.size();
                ch.push_back({-1, -1});
                cnt.push_back(0);
            }
            v = ch[v][c];
            cnt[v] += k;
        }
    }
    int count(long long a) const {
        int v = 0;
        for (int b = B - 1; b >= 0; b--) {
            v = ch[v][(a >> b) & 1];
            if (v == -1) return 0;
        }
        return cnt[v];
    }
    bool has(int v) const { return v != -1 && cnt[v] > 0; }

    // min (a xor x)。集合が空でないこと
    long long xor_min(long long x) const {
        int v = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int c = (x >> b) & 1;          // x と同じ側へ降りれば bit b は 0
            if (!has(ch[v][c])) {
                c ^= 1;
                res |= 1LL << b;
            }
            v = ch[v][c];
        }
        return res;
    }
    long long xor_max(long long x) const {
        return xor_min(x ^ ((1LL << B) - 1)) ^ ((1LL << B) - 1);
    }
    // {a xor x} の中で小さい方から k 番目（0-indexed）。k < size() であること
    long long kth(int k, long long x) const {
        int v = 0;
        long long res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int c = (x >> b) & 1;          // a xor x の bit b が 0 になる側
            int l = ch[v][c];
            int lc = (l == -1 ? 0 : cnt[l]);
            if (k >= lc) {
                k -= lc;
                c ^= 1;
                res |= 1LL << b;
            }
            v = ch[v][c];
        }
        return res;
    }
};
// --8<-- [end:core]

int main() {
    // 乱択で素朴な方法と比べる
    mt19937 rng(1);
    for (int t = 0; t < 200; t++) {
        int B = 1 + rng() % 5;
        BinaryTrie tr(B, 1 + 40 * B);
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
            assert(tr.size() == (int)ms.size());
            assert(tr.count(a) == (int)ms.count(a));
            if (ms.empty()) continue;
            long long x = rng() % (1 << B);
            long long mn = LLONG_MAX, mx = -1;
            vector<long long> v;
            for (long long e : ms) {
                mn = min(mn, e ^ x);
                mx = max(mx, e ^ x);
                v.push_back(e ^ x);
            }
            sort(v.begin(), v.end());
            assert(tr.xor_min(x) == mn);
            assert(tr.xor_max(x) == mx);
            for (int k = 0; k < (int)v.size(); k++) assert(tr.kth(k, x) == v[k]);
        }
    }

    // 入力：Q 個のクエリ。0 a：a を足す、1 a：a を 1 個消す、2 x：min (a xor x)、3 k x：K 番目
    int q;
    cin >> q;
    BinaryTrie tr(30, 1 + 30 * q);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            long long a;
            cin >> a;
            tr.add(a, 1);
        } else if (t == 1) {
            long long a;
            cin >> a;
            if (tr.count(a) > 0) tr.add(a, -1);
        } else if (t == 2) {
            long long x;
            cin >> x;
            if (tr.size() == 0) cout << -1 << '\n';
            else cout << tr.xor_min(x) << '\n';
        } else {
            int k;
            long long x;
            cin >> k >> x;
            cout << tr.kth(k, x) << '\n';
        }
    }
}
