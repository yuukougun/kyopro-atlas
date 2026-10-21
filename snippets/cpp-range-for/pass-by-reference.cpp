#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 値渡し：呼ぶたびに a 全体（N 個）をコピーする。深さ N の再帰で O(N^2)
long long sum_copy(vector<int> a, int i) {
    if (i == (int)a.size()) return 0;
    return a[i] + sum_copy(a, i + 1);
}

// const 参照：コピーしない。書き換えもできない。深さ N の再帰で O(N)
long long sum_ref(const vector<int>& a, int i) {
    if (i == (int)a.size()) return 0;
    return a[i] + sum_ref(a, i + 1);
}

// 参照：呼び出し元の vector を書き換えたいとき（DFS で訪問済みの印を付けるなど）
void mark(vector<bool>& seen, int v) { seen[v] = true; }
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<bool> seen(n + 1, false);
    mark(seen, n);
    assert(seen[n]);
    long long s = sum_ref(a, 0);
    if (n <= 1000) assert(sum_copy(a, 0) == s);
    cout << s << '\n';
}
