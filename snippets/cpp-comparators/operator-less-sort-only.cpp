#include <bits/stdc++.h>
using namespace std;

// const のない operator< でも、std::sort だけなら通ってしまうことを確かめる
struct Seg {
    int l, r;
    bool operator<(const Seg& o) { return r < o.r; }
};

int main() {
    vector<Seg> v = {{1, 5}, {2, 3}};
    sort(v.begin(), v.end());
    cout << v[0].r << '\n';
}
