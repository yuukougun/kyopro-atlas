// 二分ヒープ（最小ヒープ）の自作。0-indexed の配列で、v の子は 2v+1 と 2v+2、親は (v-1)/2。
// 保つ性質：どの v についても d[par(v)] <= d[v]。よって d[0] が最小。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct MinHeap {
    vector<long long> d;

    MinHeap() {}
    // まとめて構築：下の方の親から順に下げる。全体で O(N)
    explicit MinHeap(vector<long long> a) : d(move(a)) {
        for (int v = (int)d.size() / 2 - 1; v >= 0; v--) down(v);
    }
    bool empty() const { return d.empty(); }
    int size() const { return (int)d.size(); }
    long long top() const { return d[0]; }  // 空のときに呼ばない

    void push(long long x) {  // 末尾に置き、親より小さい間は上げる。O(log N)
        d.push_back(x);
        int v = (int)d.size() - 1;
        while (v > 0) {
            int p = (v - 1) / 2;
            if (d[p] <= d[v]) break;
            swap(d[p], d[v]);
            v = p;
        }
    }
    void pop() {  // 根を末尾と入れ替えて消し、新しい根を下げる。O(log N)
        swap(d[0], d.back());
        d.pop_back();
        if (!d.empty()) down(0);
    }

  private:
    void down(int v) {  // 子の小さい方より大きい間は下げる
        int n = (int)d.size();
        while (true) {
            int c = 2 * v + 1;
            if (c >= n) break;                     // 子がない（葉）
            if (c + 1 < n && d[c + 1] < d[c]) c++;  // 小さい方の子
            if (d[v] <= d[c]) break;
            swap(d[v], d[c]);
            v = c;
        }
    }
};
// --8<-- [end:core]

int main() {
    // 乱数で std::priority_queue と突き合わせる
    mt19937 rng(12345);
    for (int t = 0; t < 200; t++) {
        int n = rng() % 30;
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 21) - 10;
        MinHeap h(a);
        priority_queue<long long, vector<long long>, greater<long long>> q(a.begin(), a.end());
        for (int s = 0; s < 100; s++) {
            if (!q.empty() && rng() % 2) {
                assert(h.top() == q.top());
                h.pop();
                q.pop();
            } else {
                long long x = (long long)(rng() % 21) - 10;
                h.push(x);
                q.push(x);
            }
            assert(h.size() == (int)q.size());
        }
    }
    // 入力の列をまとめて構築し、小さい順に取り出す
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    MinHeap h(a);
    while (!h.empty()) {
        cout << h.top() << ' ';
        h.pop();
    }
    cout << '\n';
}
