#include <bits/stdc++.h>
using namespace std;

// Link-Cut Tree（頂点の値の加算とパスの和）。頂点は 0-indexed
// 各優先パスを、深さの順に並べた splay 木で持つ。
// par[x] は splay 木の中の親か、splay 木の根なら「パスの親」（軽い辺の上の頂点）を指す
// --8<-- [start:node]
struct LinkCutTree {
    vector<array<int, 2>> ch;  // splay 木の左右の子（-1 は空）
    vector<int> par;
    vector<char> rev;          // 反転の保留（自分の左右は入れ替え済みで、子にはまだ）
    vector<long long> val, sum;

    LinkCutTree(int n) : ch(n, {-1, -1}), par(n, -1), rev(n, 0), val(n, 0), sum(n, 0) {}

    // x が自分の splay 木の根か（親がいないか、親から見て子でない＝パスの親）
    bool is_root(int x) {
        int p = par[x];
        return p == -1 || (ch[p][0] != x && ch[p][1] != x);
    }
    void pull(int x) {
        sum[x] = val[x];
        for (int c : ch[x]) {
            if (c != -1) sum[x] += sum[c];
        }
    }
    // x の部分木の列を反転する。印を立てるときに自分の左右を入れ替える
    // （非可換な演算なら、ここで正向きと逆向きの合成値も入れ替える）
    void toggle(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void push(int x) {
        if (!rev[x]) return;
        for (int c : ch[x]) {
            if (c != -1) toggle(c);
        }
        rev[x] = 0;
    }
    void rotate(int x) {
        int p = par[x], g = par[p];
        int d = (ch[p][1] == x);
        int b = ch[x][d ^ 1];
        if (!is_root(p)) ch[g][ch[g][1] == p] = x;  // p が根ならパスの親を引き継ぐだけ
        par[x] = g;
        ch[p][d] = b;
        if (b != -1) par[b] = p;
        ch[x][d ^ 1] = p;
        par[p] = x;
        pull(p);
        pull(x);
    }
    void splay(int x) {
        vector<int> st = {x};  // 根から順に保留を降ろす
        for (int y = x; !is_root(y); y = par[y]) st.push_back(par[y]);
        for (int i = (int)st.size() - 1; i >= 0; i--) push(st[i]);
        while (!is_root(x)) {
            int p = par[x];
            if (!is_root(p)) {
                int g = par[p];
                if ((ch[g][0] == p) == (ch[p][0] == x)) rotate(p);  // zig-zig
                else rotate(x);                                      // zig-zag
            }
            rotate(x);
        }
    }
    // --8<-- [end:node]

    // --8<-- [start:expose]
    // 根から x までのパスを 1 本の優先パスにし、x をその splay 木の根にする
    // x より深い側は切り離す（右の子を空にする）ので、sum[x] が根から x までの和になる
    void expose(int x) {
        int last = -1;
        for (int y = x; y != -1; y = par[y]) {
            splay(y);
            ch[y][1] = last;  // y より深い側を、今まで作ったパスに付け替える
            pull(y);
            last = y;
        }
        splay(x);
    }
    // x を根にする：根から x のパスの向きを反転する
    void evert(int x) {
        expose(x);
        toggle(x);
    }
    // 別の木にある u と v を辺で結ぶ（u の木を u で根付け直して v の下に付ける）
    void link(int u, int v) {
        evert(u);
        par[u] = v;
    }
    // 辺 (u, v) を切る。u を根にして v を expose すると、v の左の子が u だけになる
    void cut(int u, int v) {
        evert(u);
        expose(v);
        assert(ch[v][0] == u && ch[u][0] == -1 && ch[u][1] == -1);
        ch[v][0] = -1;
        par[u] = -1;
        pull(v);
    }
    long long path_sum(int u, int v) {
        evert(u);
        expose(v);
        return sum[v];
    }
    void add(int x, long long a) {
        expose(x);
        val[x] += a;
        pull(x);
    }
    // --8<-- [end:expose]
    int find_root(int x) {
        expose(x);
        while (true) {
            push(x);
            if (ch[x][0] == -1) break;
            x = ch[x][0];
        }
        splay(x);
        return x;
    }
    bool connected(int u, int v) { return find_root(u) == find_root(v); }
};

// 愚直な森：隣接集合と DFS
struct NaiveForest {
    int n;
    vector<set<int>> g;
    vector<long long> val;
    NaiveForest(int n) : n(n), g(n), val(n, 0) {}
    vector<int> path(int u, int v) {  // u から v のパス（つながっていなければ空）
        vector<int> from(n, -2);
        vector<int> st = {u};
        from[u] = -1;
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (int y : g[x]) {
                if (from[y] == -2) {
                    from[y] = x;
                    st.push_back(y);
                }
            }
        }
        if (from[v] == -2) return {};
        vector<int> res;
        for (int x = v; x != -1; x = from[x]) res.push_back(x);
        return res;
    }
};

void random_test(int n, int ops, unsigned seed) {
    mt19937 rng(seed);
    LinkCutTree lct(n);
    NaiveForest nf(n);
    vector<pair<int, int>> edges;
    for (int t = 0; t < ops; t++) {
        int type = rng() % 4;
        int u = rng() % n, v = rng() % n;
        if (type == 0) {  // つながっていなければ結ぶ
            bool conn = !nf.path(u, v).empty();
            assert(lct.connected(u, v) == conn);
            if (!conn) {
                lct.link(u, v);
                nf.g[u].insert(v);
                nf.g[v].insert(u);
                edges.push_back({u, v});
            }
        } else if (type == 1 && !edges.empty()) {  // 辺を 1 本切る
            int i = rng() % edges.size();
            auto [a, b] = edges[i];
            if (rng() % 2) swap(a, b);
            lct.cut(a, b);
            nf.g[a].erase(b);
            nf.g[b].erase(a);
            edges.erase(edges.begin() + i);
        } else if (type == 2) {
            long long x = rng() % 1000;
            lct.add(u, x);
            nf.val[u] += x;
        } else {
            vector<int> p = nf.path(u, v);
            if (p.empty()) continue;
            long long s = 0;
            for (int x : p) s += nf.val[x];
            assert(lct.path_sum(u, v) == s);
        }
    }
}

int main() {
    random_test(1, 200, 1);
    random_test(8, 20000, 2);
    random_test(60, 20000, 3);

    // 入力：N Q、値 a、辺 N-1 本、クエリ
    // 0 u v w x：辺 (u, v) を切って (w, x) を結ぶ。1 p x：a_p に x を足す。2 u v：パスの和
    int n, q;
    cin >> n >> q;
    LinkCutTree lct(n);
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        lct.add(i, a);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int p;
            long long x;
            cin >> p >> x;
            lct.add(p, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << lct.path_sum(u, v) << '\n';
        }
    }
}
