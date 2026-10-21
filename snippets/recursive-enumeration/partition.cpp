#include <bits/stdc++.h>
using namespace std;

// N 人を組に分ける方法をすべて列挙し、全体の数と「ちょうど T 組」の数を出す
int main() {
    int n, t;
    cin >> n >> t;
    // --8<-- [start:core]
    vector<int> group(n);  // group[i] = 人 i が入った組の番号（条件の判定に使う）
    int k = 0;             // 今ある組の数
    long long all = 0, exact = 0;
    auto dfs = [&](auto&& self, int i) -> void {
        if (i == n) {  // 全員の組が決まった：分け方が 1 つできた
            all++;
            if (k == t) exact++;
            return;
        }
        for (int g = 0; g < k; g++) {  // 今ある組のどれかに入れる
            group[i] = g;
            self(self, i + 1);
        }
        group[i] = k;  // 新しい組を作る。番号は次の k だけを使う
        k++;
        self(self, i + 1);
        k--;  // 戻す
    };
    dfs(dfs, 0);
    // --8<-- [end:core]
    cout << all << ' ' << exact << '\n';
}
