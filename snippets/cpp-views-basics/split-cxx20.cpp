#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    vector<string> words;
    // --8<-- [start:core]
    for (auto w : s | views::split(' ')) {
        words.emplace_back(w.begin(), w.end());  // C++20 ではイテレータの組から文字列を作る
    }
    // --8<-- [end:core]
    for (const string& w : words) cout << '[' << w << ']';
    cout << '\n';
}
