// 単調スタック：各 i について、左で初めて A_i より大きい要素の位置 L_i（なければ -1）を求める
// 入力：N、A_0 … A_{N-1}。出力：L_0 … L_{N-1}
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<int> prev_greater(const vector<long long>& a) {
    int n = a.size();
    vector<int> L(n);
    vector<int> st;  // 添字を積む。底から上へ a の値は狭義減少
    for (int i = 0; i < n; i++) {
        // a[i] 以下の要素は、i より右から見ると i に隠れるので降ろす
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return L;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> L = prev_greater(a);
    for (int i = 0; i < n; i++) {
        // 素朴に左へ見ていく O(N^2) と比べる
        int naive = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] > a[i]) {
                naive = j;
                break;
            }
        }
        assert(L[i] == naive);
        cout << L[i] << (i + 1 < n ? ' ' : '\n');
    }
    if (n == 0) cout << '\n';
}
