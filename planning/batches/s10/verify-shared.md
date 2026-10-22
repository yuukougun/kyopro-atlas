# s10 共有ファイルの直しの検証

対象：fixed-shared.md の 31 件（git diff tools/ data/ prh.yml README.md planning/）。検証役は直した担当とは別。atcoder.jp・codeforces.com は開いていない。直したファイルはない（重大な誤りが見つからなかったため）。commit はしていない。

結論：**重大な誤りは残っていない**。軽い注意を末尾に 5 件書いた。

## 既存の検査（2026-10-22 の作業ツリー）

- `python3 tools/check_pages.py`：エラー 0・警告 0
- `python3 tools/fix_problems.py --check`：直すべき行 0・直せない行 0・逆向きの警告 6、終了コード 0（警告が終了コードに入らないことを確かめた）
- `python3 tools/check_svg.py`：414 枚・警告 120 件・エラー 0、終了コード 0
- `prh.yml` は YAML として読める。textlint で「セグツリー => セグメント木」「セグメントツリー => セグメント木」になる（一時ファイルで確かめた）

## 道具（1・2・4〜10）

自分で書いた小さな試験（一時置き場。リポジトリには置いていない）：

- **PROBLEM_LINE_RE・LINK_TAIL_RE**（1・2）：`[ABC411 E. E [max]]` から label・id・diff・summary を読める。ふつうの行、`（diff —）`、要約の中のリンク `[注](x)` も前と同じに読める。角かっこの数が合わない行と 2 段の入れ子は読まない（直せない行として出る。今はそういう題名はない）。gen_site.py は check_pages の正規表現を使っており、作り直した graph.json に abc411_e（label「ABC411 E. E [max]」）が入ることを `--root` の一時コピーで確かめた
- **逆向きの検査**（4）：`body_problem_ids` に、囲みの中の URL の行・ID だけの行・フェンスの中の囲み・囲みの外の URL を混ぜた本文を与え、囲みの中の 2 問だけを返すことを確かめた。`ledger_not_in_body` は、フェンスの中にしかない確認済みの問題だけを警告にし、未確認の問題と、見ていないページへの参照は数えない
- **gen_site.py**（5〜9）：`--check --diff` と、一時コピーへの作り直しで確かめた。llms.txt の「（準備中 0）」が消え、段階の説明が「本文あり・未検証」になる。詳細索引の冒頭の stub の文が全分野で消える。how-to-use の分野の表から「準備中」の列が消える（stub が 0 なので）。ロードマップの「最小全域木（2）」が「最小全域木」になる。STAGE_JA を使う stage-summary はどのページにも置かれていないので、表の見出しの変化は今は出ない。`docs/<field>/index.md` の「（準備中 n）」は前から n が 0 なら出さない
- **差分のそのほか**（32 ファイル）：道具の変更以外の差分は、並行しているページの直し（要約の書き換え、「上位ビット→上位 bit」「ワーシャルフロイド法」「歩道→ウォーク」など）と、ページに足した問題（典型90 054・076、EXAWIZARDS2019 D、PANASONIC2020 C、ZONE2021 E・F、subset-enumeration-dp#vs-zeta の行の追加でロードマップの番号がずれる）によるもので、意図どおり
- **check_svg.py**（10）：font-size 8 の `<g>` の中の文字（幅 400 の図で 6.6px）、style 属性の font-size 10px（8.2px）を警告し、`baseline-shift` の tspan を数えないこと、width・height の欠けと em の font-size（6.0px）を警告することを確かめた。docs/img の SVG に `<style>` はないので、クラスの font-size を読まないことは今は問題にならない

## 台帳（11〜19）

- **本文との一致**：仮の summary を置き換えた 15 問（16 か所）と agc002_d の各ページについて、本文の行の要約と台帳の summary（そのページ向けの alternatives があればそれ）を機械的に比べ、すべて一字一句一致した（abc445_g・abc479_f・abc470_f の 2 ページずつ、agc002_d の 3 ページを含む）
- **abc458_g**（14）：ikatakos 氏の ABC458 の記録（check_noai で指定なしを確かめた）を読んだ。問い（メダルを回収して s + A_i 枚を配り直す、B_i 枚未満は脱落・以上は B_i 枚を失う、C_i 枚以上は脱出を選べる、脱出できる人数の最大）と、解き方（人数 m で二分探索、DP[i, j] =「j 人が脱出済みのときの残りの最大」が上に凸な折れ線、A は平行移動・B は傾きの一律の変更・C は傾きの下限を −C_i にそろえる、判定 O(N)）が台帳の summary・approach と合う。記事は「slope trick が使える」と書いており、slope-trick の力試し（diff 2831、ap.py で確かめた。ページは発展）は妥当
- **keyence2019_e**（15）：ap.py で diff 2623（ページは発展）。spanning-tree-advanced の本文は 61 行目で重み D|i−j| + A_i + A_j の完全グラフを Borůvka 法の例に使い、67 行目で「辺の候補を O(N log N) 本に減らしてクラスカル法」に触れている（fixed-shared の「72 行目」は並行の直しで行がずれたもの）。練習として足すのは妥当
- **abc311_h**（13）：static-top-tree の 71 行目と練習の方針（174 行目）が「重軽再帰 DP の問題で、Static Top Tree そのものではない」と区別して書いており、台帳の approach「重軽再帰 DP」・出典（luogu の解説）と合う。残す判断は妥当
- **agc002_d**（12）・abc189_c（16）・abc197_c（17）・abc455_f と abc470_g（19）：記録の理由に矛盾はない。abc189_c・abc197_c は逆向きの警告に出ていない
- **冒頭のコメント**（11）：内容は CLAUDE.md（8a 以降は台帳が正）と合う

## 共有ファイルの文書（20〜31）

- 用語集の表に「セグメント木 ｜ セグ木 ｜ セグメントツリー・セグツリー」「ビット反転」「杜教篩」の行がある（20・21）。prh のコメント（22）は表の置き場と合う
- progress.md・tools/README.md・README.md（23〜30）：内容は実際の道具の挙動と合う。README の「見るだけなら uv だけ」は、続くコマンドが uv だけで、npm は検査の行にだけあることと合う
- 付録 B（31）：足したドメインから 4 つ（koosaga.com・oeis.org・snuke.hatenablog.com・gdst.dev）を選んで check_noai をやり直し、どれも指定がないことを確かめた

## 軽い注意（直していない。メインかページの担当へ）

1. **逆向きの警告の残り 6 組**：abc458_g→slope-trick と keyence2019_e→spanning-tree-advanced（left-shared 9 に記録あり）、abc467_f→exchange-argument と abc475_f→inclusion-exclusion（left-shared 14 に記録あり）のほかに、**abc116_c→basics/difference-sequence（practice）** と **abc130_e→dp/dp-prefix-sum（practice）** がある。この 2 組は left-shared に書かれていない。ページの担当と「本文に足すか、台帳から外すか」を決める
2. **abc458_g の monge の行**：台帳の summary を書き直したので、dp/monge.md 197 行目の要約（「日ごとの収入と費用が決まっている中で…」）と一致しなくなった。left-shared 4 の「一字一句は一致しない行」の規則を決めるときに合わせて直すとよい
3. **agc002_d の summary**「x と y の成分の頂点数の合計」は、x と y が同じ成分にあるときに 2 回数えるとも読める（実際は訪れる頂点の数なので 1 回）。3 ページの本文と一致しているので台帳だけは直していない。直すなら本文の 3 行と同時に「x と y を含む成分の頂点数（同じ成分なら 1 回）」のようにする
4. **check_svg.py の取りこぼし**：em の font-size を持つ tspan は大きくする指定でも下付きとして数えない。`<text>` の中で tspan の後に続く文字（tail）を見ない。SVG の `<style>` のクラスの font-size を読まない。どれも今の図では影響が小さい（`<style>` は 0 枚）
5. **fixed-shared の数字のずれ**：逆向きの警告は記録の 18 から 6 に、図は 406 枚・警告 646 件から 414 枚・120 件に変わっている（並行の直しによる。誤りではない）
