#include <bits/stdc++.h>
using namespace std;

// レベル 0 は '#' 1 マス。レベル n は 3^n × 3^n で、9 個に分けた真ん中は白（'.'）、
// 残りの 8 個がレベル n-1。レベル n を描く。

// --8<-- [start:core]
vector<string> g;

// 左上が (top, left) の位置に、レベル n の図形を描く（g は最初すべて '.'）
void draw(int n, int top, int left) {
    if (n == 0) {
        g[top][left] = '#';
        return;
    }
    int s = 1;
    for (int i = 0; i < n - 1; i++) s *= 3;  // レベル n-1 の 1 辺 3^(n-1)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) continue;  // 真ん中は白のまま
            draw(n - 1, top + i * s, left + j * s);
        }
    }
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    int size = 1;
    for (int i = 0; i < n; i++) size *= 3;
    g.assign(size, string(size, '.'));
    draw(n, 0, 0);
    // 3 進数で同じ桁がどちらも 1 になる位置が白、という見方と一致するか
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool white = false;
            for (int a = i, b = j; a > 0 || b > 0; a /= 3, b /= 3) {
                if (a % 3 == 1 && b % 3 == 1) white = true;
            }
            assert(g[i][j] == (white ? '.' : '#'));
        }
    }
    for (int i = 0; i < size; i++) cout << g[i] << '\n';
}
