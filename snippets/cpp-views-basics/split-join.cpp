#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    // --8<-- [start:split]
    vector<string> words;
    for (auto w : s | views::split(' ')) {
        words.emplace_back(string_view(w));  // 部分 w は view なので string_view を経て文字列にする
    }
    // --8<-- [end:split]
    cout << words.size() << '\n';
    for (const string& w : words) cout << '[' << w << ']';
    cout << '\n';

    // --8<-- [start:join]
    vector<vector<int>> g = {{1, 2}, {}, {3}};
    for (int x : g | views::join) cout << x << ' ';  // 1 2 3
    cout << '\n';
    // --8<-- [end:join]
}
