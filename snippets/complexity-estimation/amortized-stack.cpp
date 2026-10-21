// ならし計算量の例：各 i について、左側で a[i] より小さい最も近い要素の添字を求める（なければ -1）。
// for の中に while があるが、各添字はスタックに 1 回入って高々 1 回出るので、全体で O(N)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<int> left(n, -1);
    vector<int> st;  // 添字のスタック。下から上へ a の値が狭義に増える
    long long pops = 0;  // 取り出した回数の合計（ならしの確認用）
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();  // 一度出た添字は二度と入らない
            pops++;
        }
        if (!st.empty()) left[i] = st.back();
        st.push_back(i);  // 各添字は 1 回だけ入る
    }
    assert(pops <= n);  // while の回数の合計は入った回数 n 以下
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) cout << left[i] << (i + 1 == n ? '\n' : ' ');
    if (n == 0) cout << '\n';
}
