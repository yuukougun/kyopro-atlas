#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n), pos(n);  // p[i] = 位置 i の値、pos[v] = 値 v のある位置
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    // --8<-- [start:core]
    // 位置 x と位置 y の値を入れ替える
    auto swap_positions = [&](int x, int y) {
        swap(p[x], p[y]);
        pos[p[x]] = x;
        pos[p[y]] = y;
    };
    // 値 a と値 b の置き場所を入れ替える（逆置換の側では位置の入れ替え）
    auto swap_values = [&](int a, int b) {
        swap(pos[a], pos[b]);
        p[pos[a]] = a;
        p[pos[b]] = b;
    };
    // 逆置換に置き換える：2 つの配列の役目を入れ替えるだけ
    auto invert = [&]() { swap(p, pos); };
    // --8<-- [end:core]
    for (int k = 0; k < q; k++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            swap_positions(x - 1, y - 1);
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            swap_values(a - 1, b - 1);
        } else {
            invert();
        }
        for (int i = 0; i < n; i++) assert(pos[p[i]] == i);
    }
    for (int i = 0; i < n; i++) cout << p[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
