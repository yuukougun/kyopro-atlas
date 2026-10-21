#include <bits/stdc++.h>
using namespace std;

// H×W のマス目を 1×2 のドミノで隙間なく敷き詰める方法の数
int main() {
    int h, w;
    cin >> h >> w;
    // --8<-- [start:core]
    vector<vector<bool>> used(h, vector<bool>(w, false));
    auto dfs = [&](auto&& self, int pos) -> long long {
        // 行優先の順で最初の空きマス（左上の空きマス）まで進む
        while (pos < h * w && used[pos / w][pos % w]) pos++;
        if (pos == h * w) return 1;  // 全部埋まった：敷き詰めが 1 つできた
        int i = pos / w, j = pos % w;
        long long res = 0;
        if (j + 1 < w && !used[i][j + 1]) {  // 横に置く
            used[i][j] = used[i][j + 1] = true;
            res += self(self, pos + 1);
            used[i][j] = used[i][j + 1] = false;  // 戻す
        }
        if (i + 1 < h) {  // 縦に置く（真下のマスはまだ空いている）
            assert(!used[i + 1][j]);
            used[i][j] = used[i + 1][j] = true;
            res += self(self, pos + 1);
            used[i][j] = used[i + 1][j] = false;  // 戻す
        }
        return res;
    };
    long long ans = dfs(dfs, 0);
    // --8<-- [end:core]
    cout << ans << '\n';
}
