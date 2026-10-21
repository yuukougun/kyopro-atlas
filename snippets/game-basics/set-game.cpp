// 集合を局面にするゲーム：表 a[i]・裏 b[i] のカードが n 枚（n ≤ 18）。
// 表どうしか裏どうしが等しい 2 枚を交互に取り除き、取り除けなくなった方が負け。
// 局面＝残っているカードの集合 mask。memo[mask] = 手番の人が勝てるか（-1 は未計算）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    assert(1 <= n && n <= 18);

    // --8<-- [start:core]
    vector<int> memo(1 << n, -1);
    auto win = [&](auto&& self, int mask) -> bool {
        if (memo[mask] != -1) return memo[mask];
        bool res = false;
        for (int i = 0; i < n && !res; i++) {
            if (!(mask >> i & 1)) continue;
            for (int j = i + 1; j < n; j++) {
                if (!(mask >> j & 1)) continue;
                if (a[i] != a[j] && b[i] != b[j]) continue;  // 取り除けない組
                int next = mask & ~(1 << i) & ~(1 << j);
                if (!self(self, next)) {  // 相手が負ける局面へ移れる
                    res = true;
                    break;
                }
            }
        }
        memo[mask] = res;  // 手がない局面は res = false（負け）
        return res;
    };
    cout << (win(win, (1 << n) - 1) ? "Takahashi" : "Aoki") << '\n';
    // --8<-- [end:core]
}
