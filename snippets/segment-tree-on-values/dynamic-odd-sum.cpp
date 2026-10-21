// 値域 [1, 10^9] の動的セグメント木に（個数, 奇数番目の和, 偶数番目の和）を載せる
// 入力：Q、X_1 … X_Q。X_i を追加するたびに、昇順に並べたときの奇数番目（1-indexed）の和を出力する
// 先読みしない（オンライン）形で書いている。前の答えで次の値が決まる問題でもそのまま使える
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long LO = 1, HI = 1000000001;  // 値域は半開区間 [LO, HI)

// ノード 0 は「空の木」の番兵：個数 0、子も 0。新しい子は 0 から作る
vector<int> lch{0}, rch{0};
vector<long long> cnt{0}, odd{0}, even{0};  // odd・even は区間の中での 1-indexed の奇数番目・偶数番目の和

int new_node() {
    lch.push_back(0); rch.push_back(0);
    cnt.push_back(0); odd.push_back(0); even.push_back(0);
    return int(cnt.size()) - 1;
}

void pull(int v) {  // 左の子の後ろに右の子を並べる。左の個数が奇数なら右の偶奇が入れ替わる
    int a = lch[v], b = rch[v];
    cnt[v] = cnt[a] + cnt[b];
    if (cnt[a] % 2 == 0) { odd[v] = odd[a] + odd[b]; even[v] = even[a] + even[b]; }
    else                 { odd[v] = odd[a] + even[b]; even[v] = even[a] + odd[b]; }
}

// ノード v（区間 [l, r)）に値 x を 1 個足し、ノードの番号を返す（v = 0 なら作る）
int insert(int v, long long l, long long r, long long x) {
    if (v == 0) v = new_node();
    if (r - l == 1) {  // 葉：同じ値 x が cnt 個並ぶ
        cnt[v]++;
        odd[v] = x * ((cnt[v] + 1) / 2);
        even[v] = x * (cnt[v] / 2);
        return v;
    }
    long long m = (l + r) / 2;
    // 再帰の中で push_back が起きるので、lch[v] への参照を持ったまま呼ばない
    if (x < m) { int c = insert(lch[v], l, m, x); lch[v] = c; }
    else       { int c = insert(rch[v], m, r, x); rch[v] = c; }
    pull(v);
    return v;
}
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    int root = 0;
    vector<long long> naive;  // 素朴な方法で確かめる
    for (int i = 0; i < q; i++) {
        long long x;
        cin >> x;
        root = insert(root, LO, HI, x);
        naive.insert(upper_bound(naive.begin(), naive.end(), x), x);
        long long expected = 0;
        for (int j = 0; j < (int)naive.size(); j += 2) expected += naive[j];
        assert(odd[root] == expected);
        cout << odd[root] << '\n';
    }
    assert((int)cnt.size() <= 1 + q * 31);  // 1 回の追加で作るノードは深さ + 1 = 31 個まで
}
