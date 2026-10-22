// 赤青 Hackenbush の茎（地面から伸びる 1 本の辺の列）に数を割り当て、
// 和の符号で勝敗を判定する。総当たりの勝敗と一致することを assert で確かめる。
// 入力：茎の本数 n と、n 個の文字列（地面に近い方から。B は左（先手側）だけが、R は右だけが切れる）
// 出力：各茎の値、和、勝者（Left・Right・Second のどれか）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 値は分母を 2^K に固定した整数で持つ（v は v / 2^K を表す）
const int K = 20;
const long long ONE = 1LL << K;

// 左の選択肢の最大 l と右の選択肢の最小 r の間にある、最も単純な数を返す
// （選択肢がない側は has_l・has_r を false にする）
long long simplest(bool has_l, long long l, bool has_r, long long r) {
    assert(!has_l || !has_r || l < r);  // l < r でなければ数にならない
    // 1. 間に整数があれば、絶対値が最小の整数
    if ((!has_l || l < 0) && (!has_r || r > 0)) return 0;
    if (!has_r || (has_l && l >= 0)) {  // 区間が正の側にある
        long long n = l / ONE + 1;      // l より大きい最小の整数
        if (!has_r || n * ONE < r) return n * ONE;
    } else {                            // 区間が負の側にある
        long long n = -((-r) / ONE + 1);  // r より小さい最大の整数
        if (!has_l || n * ONE > l) return n * ONE;
    }
    // 2. 整数がなければ、分母 2^d が最小のもの（d = 1, 2, ...）
    for (int d = 1; d <= K; d++) {
        long long step = ONE >> d;
        long long m = (l >= 0 ? l / step : -((-l + step - 1) / step)) + 1;  // l より大きい最小の step の倍数
        if (m * step < r) return m * step;
    }
    assert(false);  // 分母が 2^K を超えた
    return 0;
}

map<string, long long> memo;

// 茎 s の値：左の選択肢の最大と右の選択肢の最小の間の、最も単純な数
long long value(const string& s) {
    if (auto it = memo.find(s); it != memo.end()) return it->second;
    bool has_l = false, has_r = false;
    long long l = 0, r = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        long long v = value(s.substr(0, i));  // 辺 i を切ると、その上も地面から離れて消える
        if (s[i] == 'B') { l = has_l ? max(l, v) : v; has_l = true; }
        else             { r = has_r ? min(r, v) : v; has_r = true; }
    }
    return memo[s] = simplest(has_l, l, has_r, r);
}
// --8<-- [end:core]

// 総当たり：手番の人（turn = 0 が左、1 が右）が勝つか
map<pair<vector<string>, int>, bool> win_memo;
bool win(vector<string> pos, int turn) {
    sort(pos.begin(), pos.end());
    auto key = make_pair(pos, turn);
    if (auto it = win_memo.find(key); it != win_memo.end()) return it->second;
    char mine = (turn == 0 ? 'B' : 'R');
    bool res = false;
    for (int j = 0; j < (int)pos.size() && !res; j++) {
        for (int i = 0; i < (int)pos[j].size() && !res; i++) {
            if (pos[j][i] != mine) continue;
            vector<string> next = pos;
            next[j] = pos[j].substr(0, i);
            if (next[j].empty()) next.erase(next.begin() + j);
            if (!win(next, 1 - turn)) res = true;  // 相手を負けの局面に送れる
        }
    }
    return win_memo[key] = res;
}

string to_fraction(long long v) {
    long long den = ONE;
    while (den > 1 && v % 2 == 0) { v /= 2; den /= 2; }
    return den == 1 ? to_string(v) : to_string(v) + "/" + to_string(den);
}

int main() {
    int n;
    cin >> n;
    vector<string> pos(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
        long long v = value(pos[i]);
        sum += v;
        cout << to_fraction(v) << (i + 1 < n ? ' ' : '\n');
    }
    if (n == 0) cout << '\n';
    cout << "sum " << to_fraction(sum) << '\n';

    // 和の符号から決めた勝者
    string by_value = sum > 0 ? "Left" : sum < 0 ? "Right" : "Second";
    // 総当たりの勝者（左が先手のときと右が先手のときの両方を調べる）
    bool left_first = win(pos, 0), right_first = win(pos, 1);
    string by_search = left_first && !right_first   ? "Left"
                       : !left_first && right_first ? "Right"
                       : !left_first && !right_first ? "Second"
                                                     : "First";
    assert(by_value == by_search);
    cout << by_value << '\n';
}
