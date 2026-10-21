// 8 近傍の連結成分の数：H×W のグリッドで、上下左右と斜めに隣り合う '#' を 1 つのまとまりと見て、
// まとまりの数を数える。外周に '.' の番兵を 1 周置き、マス (i, j) を 1 次元の番号にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    assert(h >= 1 && w >= 1);
    for (int i = 0; i < h; i++) assert(ssize(s[i]) == w);

    // --8<-- [start:core]
    // 番兵込みの幅 W2 = W + 2。元の (i, j) は番号 (i + 1) * W2 + (j + 1) に置く
    const int w2 = w + 2;
    vector<char> g((h + 2) * w2, '.');  // 外周は '.'（番兵）のまま
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) g[(i + 1) * w2 + (j + 1)] = s[i][j];

    // 8 近傍は番号の差で書ける。番兵があるので範囲の判定は要らない
    const int off[8] = {-w2 - 1, -w2, -w2 + 1, -1, 1, w2 - 1, w2, w2 + 1};
    vector<bool> seen(g.size(), false);
    int count = 0;
    for (int v = 0; v < ssize(g); v++) {
        if (g[v] != '#' || seen[v]) continue;
        count++;  // 新しいまとまりを見つけた
        vector<int> st = {v};  // 再帰を使わずスタックで探索する
        seen[v] = true;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int d : off) {
                int nu = u + d;
                if (g[nu] == '#' && !seen[nu]) {
                    seen[nu] = true;
                    st.push_back(nu);
                }
            }
        }
    }
    cout << count << '\n';
    // 番号から元のマスへ戻すときは i = v / w2 - 1、j = v % w2 - 1
    // --8<-- [end:core]
}
