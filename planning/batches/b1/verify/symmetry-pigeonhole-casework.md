# pigeonhole（対称性・鳩の巣原理・場合分け）の検証

- 対象：docs/thinking/symmetry-pigeonhole-casework.md（指示のパス docs/thinking/pigeonhole.md はなく、catalog の merged_keys で統合されたこのページが担当。執筆者の報告のとおり）、snippets/symmetry-pigeonhole-casework/pair-sum.{cpp,yaml}・pigeonhole-subsets.{cpp,yaml}、docs/img/symmetry-pigeonhole-casework/pair-table.svg・pigeonhole-boxes.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page symmetry-pigeonhole-casework`：エラー 0・警告 0
- `npx textlint docs/thinking/symmetry-pigeonhole-casework.md`：エラー 0・警告 15（文の長さ・助詞の重なり。執筆者の報告と同じ）
- **コード片**（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
    - `python3 tools/check_snippets.py -v snippets/symmetry-pigeonhole-casework`：2 本とも全 case 一致（4・6 case）
    - `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で 2 本ともコンパイルし、乱数の試験を 300 回ずつ（作業用の場所の t.py）。pigeonhole-subsets は n ≤ 12・m ≤ 300・a_i ≤ 10^9 で、全部分集合の素朴な判定と Yes/No が一致。pair-sum は n ≤ 50 で素朴な O(N^2) の mod 1e9+7 と一致。サニタイザの報告なし
    - cases の期待値を手で確かめた：`3\n1 2 3` → 2+3+6 = 11、`2 0 3 4` → 0+6+8+0+0+12 = 26、10^9 ≡ −7 なので 10^18 ≡ 49
    - 取り込みの印 `core` は本文と一致。`bits/stdc++.h`・`using namespace std;`・`'\n'`・マクロなし・0-indexed で手引き §9 に合う
- **台帳**：6 問とも `tools/ap.py show` で実在・題名・diff が本文と一致（abc177_c 386・arc091_a 514・abc200_d 1217・abc174_c 902・abc471_e 990・abc462_e 1226）。例題 3・練習 3 は thinking の目安に合う。abc471_e・abc462_e の台帳の summary は「（執筆時に確かめる）」のままで、本文は執筆者の提案の値で書かれている（メインが提案を反映すれば一致する）
- **参考の URL**：10 件とも取得し題名が書かれたとおりであることを確かめた。ドメインはすべて付録 B にある（qiita.com・blog.hamayanhamayan.com・oraclesqlpuzzle・zenn.dev・ikatakos.com・drken1215.hatenablog.com）。atcoder.jp・codeforces.com の URL は参考にない
- **evidence で照らした方針**
    - abc471_e：hyouri の式 Σ(a_i^2 C(n−1,k−1) + a_i(sum − a_i) C(n−2,k−2)) は本文の C(N−1,K−1) S2 + C(N−2,K−2)(S1² − S2) と同じ
    - abc462_e：comet725 の解答は |X|,|Y| にしてから A,B と X,Y を並べ替え、偶数なら min(2AY, A(X+Y) + (B−A)(Y−X)/2)、奇数なら最後の 1 手を除いた 2 通りを比べる。本文の要約のコストの決まり（奇数回目は横 A・縦 B、偶数回目は横 B・縦 A）から、2 手の組のコストは「横横・縦縦 = A+B、横縦 = 2A、縦横 = 2B」となり、この式がそのまま出る。要約と解答は矛盾しない
- **執筆者の未解決の点**
    - abc200_d の重なり：本文は「異なる 2 つの部分列」とだけ書き、コードは mask が異なることだけを保証する。evidence（m193h）で重なりを除かずに通っているので、本文の書き方で問題ない。直す必要なし
    - abc177_c の法：本文は法の値を書いていない。コード片の MOD = 1e9+7 は「剰余で求める例」としてのもので、問題の法だとは述べていないので問題ない
    - abc462_e の練習の方針：「A > B なら A と B、X と Y を一緒に入れ替える」は正しい対称性である（A↔B と縦横の入れ替えを同時に行うと、奇数回目・偶数回目のコストの表が元に戻る）。残りの式を書かずに「偶奇に注意して候補を比べる」にとどめたのは、方針として妥当
    - 3 つ組の確認問題 (S1³ − 3 S1 S2 + 2 S3) / 6：n ≤ 8・値 −20〜20 の乱数 200 回で素朴な和と一致（作業用の場所の t.py）
- **本文の主張を手で確かめた**：i < j の和の式、XOR で N が偶数のとき B の XOR が T になること、自分以外の和の総和が (N−1) 倍、累積和と鳩の巣で N の倍数の区間があること、2^9 − 1 = 511 < 1001 ≤ 1023 = 2^10 − 1、2^7 − 1 = 127 < 201 ≤ 255、arc091_a の 3 つの場合（1・M−2・(N−2)(M−2)）、abc174_c で K 回以内に 0 が出なければ −1、7・77・777・7777 の mod 3 が 1・2・0・1。どれも正しい
- **図**：puppeteer の chrome-headless-shell 146 で 600 幅の PNG にして目で見た（作業用の場所の pair-table.png・pigeonhole-boxes.png）。この環境には日本語のフォントがなく和文は豆腐になったが、配置・はみ出し・重なりはない。どちらも viewBox あり、背景は白の rect、文字はテキスト（sans-serif）。斜線の対角・塗った上三角・凡例は catalog の visual（static, priority 2）の指定どおり。箱の図の値は本文・代替テキストと一致

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2・F3 | #pitfalls「2 乗のオーバーフロー」（133 行） | 「剰余を取らない問題なら `__int128` を使うか、累積和で 1 つずつ足す書き方にする」とあるが、挙げた例（A_i ≤ 10^9、N = 2×10^5）では答えそのものが約 (2×10^14)² / 2 = 2×10^28 で `long long` を超える。累積和の書き方は S1² という中間値を避けるだけで、答えのあふれは防げない。累積和で済むのは「答えは収まるが S1²（答えの約 2 倍 + S2）だけが超える」狭い場合に限る | S1² = 2·Σ_{i<j} A_i A_j + S2 なので、S1² がはみ出すなら答えも半分程度の大きさ。例の値で 2×10^28 > 9.2×10^18 | 「この例では答え自体が `long long` に収まらないので `__int128`（または多倍長）が要る。累積和で 1 つずつ足す書き方は S1² の中間値を避けるだけで、答えが収まる場合にしか効かない」と書き分ける。または累積和の書き方への言及を消す |
| 2 | 直すべき | figure G5・fact F7 | pair-table.svg と #symmetry の本文 | 図は 0-indexed の小文字（a0a0…a3a3、題に (a_0 + a_1 + a_2 + a_3)^2）、本文の式は 1-indexed の大文字（A_1 + … + A_N）。チェックリストの「図と本文で添字がずれる」に当たる | 本文 51 行・67 行は A_1…A_N・B_1…B_N。図の題と各マスは a_0…a_3 | 図のラベルを A_1…A_4（i, j = 1〜4）にそろえる。または本文の例を 0-indexed にして図と合わせる（数式は 1-indexed のままの方が他の節と合う） |
| 3 | 直すとよい | fact F2 | #casework「操作の順序によらないこと」（123 行） | 「反転・加算・XOR のように…『各場所が何回操作されたか』だけで結果が決まる」は、加算・XOR で値が操作ごとに違うときは言い過ぎ（何回かではなく、足した値・XOR した値の合計で決まる）。回数だけで決まるのは反転のように毎回同じ操作のとき | 例：場所 1 に +3 と +5 の 2 回と、+1 と +1 の 2 回は回数が同じで結果が違う | 「各場所に何がかかったかの合計（反転なら回数、加算なら足した量の和、XOR なら XOR した値の XOR）だけで決まる」とする |
| 4 | 直すとよい | fact F2・clarity U3 | #pigeonhole の 3 つ目の型（99 行） | 「区間の幅が法 M 以上なら、余りが 0 になる数を必ず含む」の「幅」が R − L か R − L + 1（含む整数の個数）か曖昧。必要十分に近いのは「連続する M 個以上の整数を含む（R − L + 1 ≥ M）」。また鳩の巣原理そのものより「連続する M 個の整数は余りを一巡する」ことによる | [L, R] の整数が M 個あれば余りは 0〜M−1 をすべて取る。R − L = M − 1 でも成り立つ | 「区間が連続する M 個以上の整数を含む（R − L + 1 ≥ M）なら」と書き、理由（連続する M 個は余りが一巡する）を一言添える |
| 5 | 直すとよい | clarity U6・fact F6 | #pigeonhole 末尾（109 行）のリンク | [整数の証明の型](../math/proof-patterns.md) と [次数で分ける](../graph/degree-sqrt.md) が節を指していない。front matter の related は `proof-patterns#pigeonhole-remainder`。4-サイクルの節は degree-sqrt の `#four-cycles` で level 黄 | docs/math/proof-patterns.md の sections に `pigeonhole-remainder`、docs/graph/degree-sqrt.md の sections に `{title: 4-サイクルの検出（鳩の巣原理で打ち切る）, anchor: four-cycles, level: 黄}` | `../math/proof-patterns.md#pigeonhole-remainder`、`../graph/degree-sqrt.md#four-cycles` にし、4-サイクルの方に「（黄）」など上位の帯であることを添える |
| 6 | 直すとよい | clarity U3 | #symmetry の XOR の段落（67 行） | N が偶数の場合だけを述べ、奇数のときに何が起きるかがない。読者は「奇数なら？」で止まる | N が奇数なら各人の値は偶数回現れ、B の XOR は 0 になって T が求まらない | 「N が奇数なら B の XOR は 0 になり、この方法では T が求まらない」と 1 文足す |
| 7 | 直すとよい | clarity U7・U9 | #practice の練習の方針 ABC471 E（202 行） | 方針が最終の式までそのまま書いてあり、答えそのものに近い。1 文 178 字で textlint の文の長さの警告も出ている | 手引き §10・clarity U7「方針が答えそのもの」 | 「和の 2 乗を A_i^2 の項と i ≠ j の項に分け、それぞれを含む選び方の数を二項係数で数える。i ≠ j の和は S1² − S2」程度にとどめ、文を 2〜3 に分ける |
| 8 | 直すとよい | code C8・C3 | snippets/symmetry-pigeonhole-casework/pigeonhole-subsets.cpp の `r = (r + a[i]) % m` | 負の a_i があると r が負になり `seen[r]` が範囲外になる。pair-sum.cpp は「a_i ≥ 0」とコメントで前提を書いているが、こちらにはない | C++ の `%` は被除数の符号を持つ。例：a = {−1}, m = 3 で r = −1 | コメントに「a_i ≥ 0」を足すか、`((r + a[i]) % m + m) % m` にする |
| 9 | 直すとよい | figure G3 | pair-table.svg・pigeonhole-boxes.svg | 固定 600 幅の図で文字が 12〜14px。幅 390px の画面では約 0.65 倍になり、題や下の注は 8px 前後になる。題の 1 行も長い | viewBox 0 0 600 330／260、font-size 12〜14 | 題を短くするか 2 行に分け、注の font-size を 14 程度に上げる（任意） |

## 台帳への提案

- abc471_e・abc462_e の `checked` に 2026-10-21 を入れる（evidence の hyouri・comet725 の解答で、本文の要約と方針が矛盾しないことを確かめた）。summary は執筆者の提案の値でよい

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（1：オーバーフローの落とし穴で累積和の書き方が答えのあふれを防ぐように読める、2：積の表の図と本文で添字の付け方が違う）で、どちらも数行の修正で済む。事実の主張・コード片・問題の方針はほかに誤りが見つからなかった。
