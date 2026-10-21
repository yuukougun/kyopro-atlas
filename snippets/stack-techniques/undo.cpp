// 取り消し：括弧の文字の末尾への追加（1 c）と末尾の削除（2）のクエリのたびに、
// 今の文字列が正しい括弧列かを答える。各時点の (残高, 接頭辞の残高の最小値) を積んでおき、
// 削除は pop するだけで 1 つ前の状態に戻る。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;

    // --8<-- [start:core]
    vector<pair<int, int>> st = {{0, 0}};  // 空文字列の状態 (残高, 最小値) を番兵として積む
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            char c;
            cin >> c;
            auto [bal, mn] = st.back();
            bal += (c == '(' ? 1 : -1);
            st.push_back({bal, min(mn, bal)});  // 追加は新しい状態を積む
        } else {
            assert(st.size() >= 2);  // 番兵は消さない
            st.pop_back();           // 削除は積んだ状態を捨てるだけ
        }
        auto [bal, mn] = st.back();
        cout << (bal == 0 && mn >= 0 ? "Yes" : "No") << '\n';
    }
    // --8<-- [end:core]
}
