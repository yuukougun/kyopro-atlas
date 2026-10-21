// 盤面を動かして全部試す：H×W の盤面（'.' が空き、'#' が埋まり）に、小さな型 P（'#' の部分）を
// 90 度単位の回転と平行移動で置くとき、型のすべての '#' が盤面の空きマスに乗る置き方（回転と移動量の組）を数える。
#include <bits/stdc++.h>
using namespace std;

// 型を時計回りに 90 度回す：h×w の (i, j) は w×h の (j, h − 1 − i) に移る
vector<string> rotate90(const vector<string>& p) {
    int h = p.size(), w = p[0].size();
    vector<string> q(w, string(h, '.'));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) q[j][h - 1 - i] = p[i][j];
    return q;
}

int main() {
    int H, W, h, w;
    cin >> H >> W;
    vector<string> board(H);
    for (auto& row : board) cin >> row;
    cin >> h >> w;
    vector<string> p(h);
    for (auto& row : p) cin >> row;
    assert(1 <= H && H <= 50 && 1 <= W && W <= 50 && 1 <= h && h <= 10 && 1 <= w && w <= 10);

    // --8<-- [start:core]
    // 型を左上が (di, dj) に来るように置けるか。盤面の外にはみ出した '#' は不可にする
    auto fits = [&](const vector<string>& q, int di, int dj) -> bool {
        for (int i = 0; i < (int)q.size(); i++) {
            for (int j = 0; j < (int)q[0].size(); j++) {
                if (q[i][j] != '#') continue;
                int y = di + i, x = dj + j;
                if (y < 0 || y >= H || x < 0 || x >= W) return false;  // はみ出し
                if (board[y][x] != '.') return false;                  // 埋まったマスに重なる
            }
        }
        return true;
    };

    long long count = 0;
    vector<string> q = p;
    for (int r = 0; r < 4; r++) {  // 回転 4 通り
        int qh = q.size(), qw = q[0].size();
        // 型の端に '.' があると左上は盤面の外に出うるので、負の移動量から試す
        for (int di = -(qh - 1); di <= H - 1; di++) {
            for (int dj = -(qw - 1); dj <= W - 1; dj++) {
                if (fits(q, di, dj)) count++;
            }
        }
        q = rotate90(q);
    }
    cout << count << '\n';
    // --8<-- [end:core]
}
