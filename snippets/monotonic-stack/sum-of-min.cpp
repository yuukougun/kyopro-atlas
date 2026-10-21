// 寄与の数え上げ：すべての区間の最小値の和を、各 i が最小になる区間の数 (i - L)(R - i) から求める
// 同じ値は「左は < で止める（≥ を降ろす）、右は ≤ で止める（> を降ろす）」にして二重に数えない
// 入力：N、A_0 … A_{N-1}。出力：すべての区間 [l, r) の最小値の和
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long sum_of_min(const vector<long long>& a) {
    int n = a.size();
    vector<int> L(n), R(n), st;
    for (int i = 0; i < n; i++) {  // L[i]：左で初めて a[i] より小さい位置
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {  // R[i]：右で初めて a[i] 以下になる位置
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i] * (i - L[i]) * (R[i] - i);
    return sum;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long naive = 0;
    for (int l = 0; l < n; l++) {
        long long mn = LLONG_MAX;
        for (int r = l; r < n; r++) {
            mn = min(mn, a[r]);
            naive += mn;
        }
    }
    long long res = sum_of_min(a);
    assert(res == naive);
    cout << res << '\n';
}
