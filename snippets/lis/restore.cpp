// 最長増加部分列（狭義）を 1 つ復元する。L には値ではなく添字を入れ、各要素の直前の要素 prev を記録する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<int> L;           // L[k]：長さ k + 1 の増加部分列の末尾として最小の値を持つ要素の添字
    vector<int> prev(n, -1);  // prev[i]：a[i] で終わる列で a[i] の直前に置く要素の添字（先頭なら -1）
    for (int i = 0; i < n; i++) {
        // a[L[k]] < a[i] を満たさない最初の k（狭義の lower_bound を添字の列で行う）
        int k = lower_bound(L.begin(), L.end(), i, [&](int j, int cur) { return a[j] < a[cur]; }) - L.begin();
        if (k > 0) prev[i] = L[k - 1];  // 長さ k の列の末尾につなぐ
        if (k == (int)L.size()) L.push_back(i);
        else L[k] = i;
    }
    vector<long long> seq;
    for (int i = L.back(); i != -1; i = prev[i]) seq.push_back(a[i]);  // 最長の列の末尾から逆にたどる
    reverse(seq.begin(), seq.end());
    // --8<-- [end:core]

    cout << seq.size() << '\n';
    for (int i = 0; i < (int)seq.size(); i++) cout << seq[i] << (i + 1 < (int)seq.size() ? ' ' : '\n');
}
