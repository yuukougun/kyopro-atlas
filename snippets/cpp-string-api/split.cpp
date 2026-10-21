#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    // --8<-- [start:core]
    vector<string> a;                       // 1 文字の空白で区切る（連続した空白で空の部分ができる）
    for (auto w : s | views::split(' ')) a.emplace_back(string_view(w));

    vector<string> b;                       // 空白をまとめて読み飛ばす
    istringstream iss(s);
    for (string w; iss >> w;) b.push_back(w);
    // --8<-- [end:core]
    cout << a.size() << ' ' << b.size() << '\n';
}
