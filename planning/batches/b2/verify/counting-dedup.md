# counting-dedup（重複の除き方）の検証

- 対象：docs/comb/counting-dedup.md、snippets/counting-dedup/{leftmost,partition-dp}.{cpp,yaml}、docs/img/counting-dedup/leftmost-embedding.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 実行したもの
    - `python3 tools/check_pages.py --page counting-dedup` → エラー 0・警告 0
    - `python3 tools/check_snippets.py snippets/counting-dedup` → コード片 2・期待と違う 0（g++-15、ACL は third_party/ac-library）
    - `python3 tools/ap.py show <id>`：arc077_b（1715）・abc171_f（1795）・abc180_f（2419）・abc311_f（1984）・abc310_d（1368）・abc130_e（1676）。本文の diff と一致
    - `python3 tools/render_svg.py`（360・720 幅、ヘッドレス Chrome）で図を目で確かめた
    - 作業用の Python（scratchpad）で、ARC077 D の答え $\binom{n+1}{k} - \binom{n+l-r}{k-1}$ を n ≤ 7 の乱択 300 列・全 k で全列挙と比べた → すべて一致
- 手で確かめた値：順序を区別した 3 人の分け方 1 + 3·2 + 1·6 = 13（Fubini 数）、名前なし 5（ベル数）、$4^6/6$ は整数でない、確認問題の 3 通り、leftmost の cases（51 = 26²−25²、76 = 1+3·25、6376 = 1+5·25+10·625）、確認問題 4 の式の変形
- 読んだ資料：drken ABC180 F・ABC171 F・ABC311 F・AGC031 B の記事、kmjp ARC077 D の記事（どれも付録 B のドメイン）

## 指摘

### 1. 直すべき｜事実（F5）｜力試し ABC180 F の要約（#challenge の問題の行）

- **問題**：要約が「N 頂点 M 辺の**単純**無向グラフ」となっているが、この問題は自己ループを持たず、**多重辺は許す**グラフを数える。方針の 3 つ目で「サイクルなら $k = 2$（2 本の辺）で 1 通り」と書いており、単純グラフでは 2 頂点のサイクルはありえないので、ページの中で食い違っている
- **根拠**：drken「AtCoder ABC 180 F - Unbranched」（https://drken1215.hatenablog.com/entry/2020/10/21/145700 、台帳の evidence）。問題の概要に「自己ループなし・多重辺あり」とあり、頂点 2 個のサイクル（平行な 2 本の辺）を 1 通りと数えている
- **直し方**：要約を「自己ループのない（多重辺は許す）N 頂点 M 辺の無向グラフで、各連結成分がパスかサイクルで、最大の連結成分の頂点数がちょうど L のものの数を求める。」などに直す。台帳 `data/problems.yaml` の abc180_f は summary と alternatives の 2 つの summary がすべて同じ「単純無向グラフ」なので、メインで台帳を直す（counting-mindset・counting-labeled-graphs の行も同じ要約のはずなので合わせて直す）

### 2. 直すとよい｜分かりやすさ（U3・U6）｜#in-dp の 2 つ目の型「直前と違うものだけを数える」

- **問題**：「たとえば区間を塗る操作で、両端が隣り合っていれば何も変わらないので数えない」は、AGC031 B の操作（同じ色の 2 か所を選び、間をその色で塗る）を知らない読者には「両端」「何も変わらない」が何を指すか分からない。型の名前「直前と違うものだけ」と、中身（何も変えない操作を遷移から除き、操作の列を 1 通りに絞る）も結び付きにくい
- **根拠**：drken の AGC031 B の記事（https://drken1215.hatenablog.com/entry/2019/03/17/130800）で内容を確かめた。遷移元は「操作しない dp[i−1]」と「直前の同じ色の位置で挟む」の 2 つで、直前の要素と同じ色なら挟む区間が空で変化しないので数えない、という扱い。本文の説明は記事と食い違わない（執筆者の未解決の点 1 は解消）
- **直し方**：「たとえば『同じ色の 2 か所を選び、間をその色で塗る』操作で作れる列を数えるとき、隣り合う 2 か所を選んでも何も変わらないので遷移に入れない」のように操作を一言書く。型の名前は「何も変えない操作・同じ結果になる操作を除く」の方が中身に合う

### 3. 直すとよい｜分かりやすさ（U7）｜練習 ABC311 F の方針

- **問題**：方針が、状態（各列の上から続く白の数）・隣の列の条件（≤ 左 + 1）・上限・累積和・計算量 $O(NM)$ までそろっており、解き方の全部になっている。手引きの「方針が答えそのもの」にあたる
- **根拠**：clarity.md U7。内容自体は drken の記事（https://drken1215.hatenablog.com/entry/2023/07/24/182416）の DP と一致する
- **直し方**：「塗り終えた盤面を、各列の上から続く白いマスの数の列で表すと 1 対 1 に対応し、塗る順序の重複が出ない。隣の列どうしの条件を考える」程度で止め、条件の式と計算量は外す

### 4. 直すとよい｜事実（F7）｜#in-dp の 3 つ目の型のリンク

- **問題**：「最初に通った障害物で分ける（[包除原理を DP に載せる](../comb/inclusion-exclusion-dp.md)）」はページの先頭へのリンクだが、該当の節がある
- **根拠**：docs/comb/inclusion-exclusion-dp.md の sections に `最初に踏む障害物で分類する（ソート順と終点の扱い）`, anchor `first-obstacle`
- **直し方**：`../comb/inclusion-exclusion-dp.md#first-obstacle` にする

### 5. 直すとよい｜コード（C3）｜snippets/counting-dedup/leftmost.cpp の core（binom と pow）

- **問題**：`binom` が呼ぶたびに `fact[a] / (fact[b] * fact[a - b])`（mint の割り算＝逆元を毎回 $O(\log \mathrm{mod})$）を計算し、`pow` も j ごとに呼んでいる。本文の計算量「階乗の前計算 $O(N)$ の後に O(1)〜O(N)」や ABC171 F の詳細「25 と 26 の累乗も前計算すれば $O(N + K)$」と、取り込んだコードの計算量が違う（$O((N+K)\log)$）。正しさには影響しない
- **根拠**：コード片の 229 行目付近と 235 行目付近（core の中）。code.md C3「本文の計算量とコードの計算量が違う」
- **直し方**：逆階乗を前計算する形にするか、core のコメントに「簡単のため毎回割る。前計算すれば各項 O(1)」と添える

### 6. 直すとよい｜図（G3）｜leftmost-embedding.svg（360 幅）

- **問題**：360 幅に縮めると右側の注記（「1 と 4 の間に b（位置 3）がある」など）が 6〜7px 相当になり、スマホでは読みにくい。720 幅では重なり・はみ出しはなく、値・添字（1-indexed）・代表の判定は本文と一致する。背景は白で塗られており、ダークでも読める。赤緑に頼らず、太枠と点線で区別している
- **根拠**：render_svg.py の出力 leftmost-embedding-360.png を目で確認
- **直し方**：注記の font-size を 1〜2 段上げるか、注記を 2 行に分けて viewBox の幅を詰める（右の余白が 40px ほどある）。必須ではない

## 確かめて問題がなかった点（抜粋）

- 最も左の埋め込みの局所条件と式 $\sum_j \binom{L-j-1}{N-1}(\sigma-1)^{L-N-j}\sigma^j$：コード片が σ = 3・6 通りの S・K ≤ 3 で全列挙と一致し、S の中身によらないことも確かめている。drken の ABC171 F の記事の解法 (1) の式と一致。法 $10^9+7$ も一致
- 確認問題 4 の別の式 $\sum_{i=0}^{K}\binom{L}{i}25^i$：drken の記事の解法 (2) の式と一致
- ARC077 D：本文の答えの式は kmjp の場合分けの式と同値（上の全列挙でも一致）。$k = 1$ で $n$
- ABC180 F：パス $k!/2$（$k = 1$ で 1）、サイクル $(k-1)!/2$（$k = 2$ で 1）、最小番号の頂点を含む成分から決める $\binom{N-n-1}{k-1}$ の DP は drken の記事と一致（要約の「単純」だけが誤り。指摘 1）
- partition-dp.cpp：ベル数と対合の数の assert で確かめている。n = 0 も通る。O(3^n)
- 落とし穴の 13 通り、確認問題 1〜3 の数値
- リンクの anchor：lcs#count-pairs、dp-sequence-partition#agc031_b、recursive-enumeration#partition・#abc310_d、counting-mindset#verify-small・#exactly-vs-at-most・#pitfalls、glossary#representative はすべて存在する
- 参考の題名と URL：kmjp ARC077 D、drken ABC171 F・ABC180 F・ABC311 F は開いて題名・内容を確かめた。本文の文章・例は記事と並びも例も違う（F8 の問題なし）

## 台帳への提案（メインが反映）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc180_f | summary（本体と alternatives 2 つ） | 自己ループのない（多重辺は許す）N 頂点 M 辺の無向グラフで、各連結成分がパスかサイクルで、最大の連結成分の頂点数がちょうど L のものの数を求める。 | https://drken1215.hatenablog.com/entry/2020/10/21/145700 |
| abc180_f・arc077_b・abc171_f・abc311_f | checked | 2026-10-21 | 各 evidence（検証役が開いて確かめた） |

## 執筆者の未解決の点について

- 1（AGC031 B の型）：drken の記事で確かめ、本文の説明は正しい。書き方は指摘 2
- 2（ARC077 D の制約）：本文に書かなくてよい。方針は $O(n)$ で制約によらない
- 3（related に足すか）：メインの判断。リンク先はどれも存在する

## 総合の判定

**小さな直しで可**。直すべき 1 件（ABC180 F の要約の「単純無向グラフ」）、直すとよい 5 件。
