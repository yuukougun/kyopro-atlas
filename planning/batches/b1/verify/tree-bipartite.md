# tree-bipartite の検証（工程8b・バッチ b1）

- 対象：docs/tree/tree-bipartite.md、snippets/tree-bipartite/coloring.{cpp,yaml}、docs/img/tree-bipartite/depth-parity.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page tree-bipartite`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/tree-bipartite`：coloring 5 case 一致（g++-15・run）
- 手で `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined`（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）：警告なし
- 試しのプログラム（一時置き場の t.py）：ランダムな木（N ≤ 9、重み 1〜4、頂点番号を混ぜる）400 個で、サニタイザ付きの coloring を動かし、コード片の中の assert（距離の偶奇と、奇数距離の組の総数）がすべて通ることを確かめた。重みなしの塗り分けでは、次も総当たりで一致した
    - 辺のない組のうち色の違う組の数 = $ab - (N - 1)$
    - $N \ge 2$ なら、少ない方の色の頂点だけで全頂点に「自分か隣」が届く（執筆者の未解決の点 2。正しい）
    - 一方の色だけで全辺の端点を押さえる（どの辺も両端の色が違うので自明。正しい）
- 手計算：図の木（辺 0-1・0-2・1-3・1-4・2-5・3-6・5-7）の深さは 0:0、1・2:1、3・4・5:2、6・7:3。白 0・3・4・5、黒 1・2・6・7、$d(6,4) = 3$（6-3-1-4）、$d(2,7) = 2$（2-5-7）、$4 \times 4 - 7 = 9$。cases の 3 つめ（同じ木の 1-indexed）とも一致。確認問題 2 つの答え（6 頂点の木で白 0・4・5、黒 1・2・3、葉 4 枚の独立集合）も正しい
- `npx textlint docs/tree/tree-bipartite.md`：エラー 0・警告 4（執筆者の報告どおり。許容の範囲）
- front matter：骨格との差は `complexity`（null から）・`stage`（stub → draft）・`updated` と、sections への「上位の手法とのつながり」（next-steps）の追加だけ。要点の計算量と `complexity` は一致。「いつ使うか」は signs と一致。別名の行に aliases がすべてある
- リンク先：tree-traversal#recursion-depth・lca#distance・parity#alternating・tree-dp#vertex-states・game-basics#move-parity・bipartite-graph#count-by-color はすべて相手の本文に anchor がある。leaf-first・bipartite-matching・konig-theorem・tree-distance のページもある。glossary#independent-set はまだない（手引き §219 のとおり提案済みなのでよい）
- 問題：`python3 tools/ap.py show` で abc209_d（D. Collision、686）・typical90_z（026. Independent Set on a Tree（★4）、diff なし）・abc126_d（D. Even Relation、1279）・abc398_e（E. Tree Game、1238）の実在・題名・diff を確認。囲みの label・diff と一致。役割と数は catalog・台帳のとおり（例題 1・練習 2・力試し 1）
- evidence と参考の URL（atcoder.jp・codeforces.com は開いていない）
    - hamayan（ABC209 D）：距離が偶数なら頂点、奇数なら道の上で出会う。本人の実装は HLD で距離を求め、公式は二部グラフ（深さの偶奇）とある。本文・参考の注記と一致
    - E869120 026.cpp：頂点 1 から DFS で 2 色に塗り、多い方の色から先頭 N/2 個を出力。本文と一致
    - drken（ABC126 D）：N ≤ 10^5、辺の重みが奇数なら色を反転、偶数なら同じ色、O(N)、各頂点の色を出力。本文と一致
    - gotoki_no_joe（ABC398 E）：色の違う組のうち既存の辺を除いたものが候補、その数の偶奇で先手・後手を選び、相手の手は候補から消す。本文の方針と一致。N の上限は書かれていない
    - 追加で読んだ：zenn.dev/nakst_hide（距離が 3 以上の奇数の組の数の偶奇で手番を選ぶ。同じ結論）、cnblogs.com/Melville（両側の大きさ x, y で最終の辺数 xy）、junkobayashi.hatenablog.com（`tools/check_noai.py` で noai の指定なしを確認。「木の頂点が最大でも100しかないという制約」とある）。これで執筆者の未解決の点 1（足せる組を列挙できる大きさか）は裏付けが取れた。N ≤ 100 なら組は約 5000 で、列挙して集合で持つ方針で足りる
    - 台帳の abc398_e の evidence の kmjp（2025/03/25）は ABC398 **G**（Not Only Tree Game）の記事で、E ではない（指摘 2）
    - いずれも文の並び・言い回し・例の写しはない。図の木は独自のもの
- 図：この環境にはヘッドレスのブラウザ・SVG の描画の道具（chromium・playwright・rsvg-convert・cairosvg・ImageMagick）がなく、画像にして目では確かめていない。SVG の座標を読んで確かめた：節点・辺・深さの目盛り・破線（6-3-1-4）と太線（2-5-7）の経路は上の手計算と一致し、代替テキスト・本文とも一致。背景は白、`viewBox` あり、文字はテキスト（`font-family="sans-serif"`）、赤と緑は破線と太さでも区別している。ラベル「太線」（x=430）・「破線」（x=95〜121）は節点・辺と重ならない位置。下の 4 行の説明文も幅 600 に収まる見積もり。catalog の visual（static・priority 2「深さの偶奇で色分けした木。2 点を選ぶと距離と色の組み合わせが表示される」）は、2 組の例を書き込むことで静的な図として満たしている

## 指摘

### 1｜直すべき｜事実（F2）｜#majority-color の 1 段落目・2 段落目と、#cross-pairs の表の 3 行目

- **問題**：#by-depth で「重みの偶奇で塗る」塗り方を導入し、「この塗り方では、両端が同じ色の辺もできる」と書き、コード片もその塗り方で $a$・$b$ を数えている。ところが #majority-color の「同じ色の 2 頂点は辺で結ばれていない」「一方の色だけで、すべての辺の端点を…」と、#cross-pairs の「二部グラフのまま足せる辺 $ab - (N - 1)$」「木の $N - 1$ 本の辺はすべて色の違う組を結んでいる」は、深さの偶奇（重みを見ない）で塗ったときにだけ成り立つ。条件が書かれていないので、コード片の $a$・$b$ をそのまま使うと誤る
- **根拠**：反例。2 頂点を重み 2 の辺で結んだ木では、重みの偶奇で塗ると $a = 2$・$b = 0$ で、「同じ色どうしは隣り合わない」が崩れ、$ab - (N - 1) = -1$ になる（深さで塗れば $a = b = 1$、足せる辺 0）。表の 1・2 行目は、距離を重みの和と読めば重みの塗り方でも成り立つ（コード片の assert で確認）
- **直し方**：#majority-color の冒頭に「この節と次の節の 3 行目は、重みを見ずに深さの偶奇で塗ったときの話である」と 1 文足す。表の 3 行目か直後の文にも「（深さで塗ったとき）」を添える。1・2 行目は「重みがあれば距離は重みの和」と添えてもよい

### 2｜直すべき｜事実（F5）｜台帳 data/problems.yaml の abc398_e の evidence（メインが直す）

- **問題**：evidence の https://kmjp.hatenablog.jp/entry/2025/03/25/0930 は ABC398 G「Not Only Tree Game」の解説で、E の裏付けになっていない
- **根拠**：記事の本文（G の問題の要旨と、N の偶奇・成分の数 X で分ける解法）
- **直し方**：この URL を evidence から外し、E の裏付けとして https://www.cnblogs.com/Melville/p/18787412 （両側の大きさ x, y と既存の辺から足せる本数の偶奇）か https://junkobayashi.hatenablog.com/entry/2025/03/23/224334 （N ≤ 100 の記述あり。noai の指定なしを確認済み）を足す。kmjp の記事は、置くなら game-basics など G を扱うページの資料にする

### 3｜直すとよい｜分かりやすさ（U6・U3）｜#cross-pairs の 1 段落目

- **問題**：節の最初で $a$・$b$ を定義なしに使う（定義は #majority-color にある）。また「前の節の事実と合わせると」が指すのは、直前の #majority-color ではなく #distance-parity の「色が同じなら距離は偶数」である。節だけ取り出して読むと何の数か分からず、通して読んでも参照先がずれる
- **根拠**：本文の並び
- **直し方**：「深さの偶奇で塗ったときの白の数を $a$、黒の数を $b$ とすると、色の違う頂点の組は $ab$ 個、…。[距離の偶奇](#distance-parity)の事実（色が同じなら距離が偶数）と合わせると」のように書き換える（指摘 1 の条件もここで入れられる）

### 4｜直すとよい｜記法（F7）｜#distance-parity の最後の段落「歩道の長さの偶奇も」

- **問題**：「歩道」は前提のページで定義されていない。graph-basics の #terms は同じものを「ウォーク」と呼んでいる（thinking/parity は「歩道」で、サイト内で揺れている）
- **根拠**：docs/graph/graph-basics.md 91 行目、docs/thinking/parity.md 137 行目
- **直し方**：「ウォーク（頂点の繰り返しを許す道。[用語](../graph/graph-basics.md#terms)）」と書く。サイト全体でどちらにそろえるかは prh.yml への提案としてメインに上げる

### 5｜直すとよい｜図（G5）｜depth-parity.svg の「黒」の節点

- **問題**：見出しと本文・説明文は「白」「黒」と書くが、黒の節点の塗りは濃い青（#1f4e9a）で、白の節点の枠も同じ青。読者は「黒はどれか」を一瞬迷う
- **根拠**：SVG の `<circle … fill="#1f4e9a"/>`（1・2・6・7）
- **直し方**：黒の節点を濃い灰か黒（例：#333）で塗るか、図の 1 行目を「白は深さが偶数、黒（濃い青）は奇数」とする

## 執筆者の未解決の点への答え

- abc398_e の N の制約：junkobayashi 氏の記事に「木の頂点が最大でも100」とあり、列挙して集合で持つ方針で足りる。本文の方針はそのままでよい（指摘 2 で evidence に足すことを提案）
- 少ない方の色での「自分か隣」と全辺の押さえ：上の総当たりで確かめ、正しい。本文の 1 文の理由（どの頂点も反対の色の隣を持つ・どの辺も両端の色が違う）で足りる

## 台帳への提案

- abc209_d・typical90_z・abc126_d の `checked` に 2026-10-21 を入れる（上の evidence で問いと解き方を確認した）
- abc398_e の evidence の差し替え（指摘 2）

## 総合の判定

小さな直しで可（直すべき 2 件：本文の条件の 1 文〔指摘 1〕と、台帳の evidence の差し替え〔指摘 2、メインの作業〕。直すとよい 3 件）
