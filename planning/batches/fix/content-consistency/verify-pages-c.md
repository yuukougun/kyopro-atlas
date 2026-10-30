# content-consistency 第 2 段（担当 pages-c：ds・comb）の検証

- 検証日：2026-10-29。作業ツリー kyopro-atlas-wt/content-consistency（fix/content-consistency、未 commit の差分）
- 見た範囲：docs/ds/・docs/comb/ の 61 ページの差分と、担当の報告 pages-c.md

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #68 平文の数式・法の文字 | 合格 | なし |
| #69 節の並び | 合格 | なし |
| #77 1 次関数の表記 | 合格 | なし |

## 検査

- `check_pages.py --field ds`・`--field comb`：エラー 0・警告 0（37 ページ・49 ページ）
- `npx textlint docs/ds docs/comb`：エラー 0（警告 1294。報告の数と同じ）
- `fix_problems.py --check`：直すべき行 0
- 作業用フォルダへビルドし `render_pages.py --field ds --field comb`（88 ページ、390px ライト・ダーク）：エラー 0、表のはみ出し 0。警告は既存の別行の数式 15 件・8 ページ（報告と同じで、今回の差分の式ではない）
- ds/advanced-ds-catalog#table を 390px・ダークで撮って目で確かめた：3 列で収まり、セルの文字も読める

## 確かめたこと

### 並べ替え（#69）

- 各ページで旧版と新版の行の多重集合を比べた。並べ替えだけのページ（binomial-coefficient・binomial-precompute・counting-basics・counting-mindset・game-basics・nim・stars-and-bars・priority-queue・union-find）は増減 0。ほかのページの増減は、報告にある書き換え（方針の題・表記・updated・参照の直し）の行だけで、節の中身は落ちていない
- 26 ページの h2 の並びが手引き §4 の順（中身 → 落とし穴 → 上位の手法へのつながり → 例題 → 練習 → 力試し → 確認問題 → 使い分け → 参考）になっている
- front matter の sections の並びが本文の anchor の順と一致する（ds・comb の全ページで不一致 0）
- 隣が変わった節の中の位置を指す言い方（「次の節」「上の」「前の節」「ここまで」など）を拾って読んだ。直された 3 か所（kth-element・stl-containers・coupon-collector）のほかに食い違いはない（sparse-table の「ここまでの表の作り方」は build の後のまま、game-basics の「下の表」・multinomial-coefficient の「次の節」は動いていない節どうし）

### 数式・法の文字・閉区間（#68）

- 区間の端：fenwick-tree の `cnt[0, id_j]` → `cnt[0, id_j + 1)` は同じ範囲。sweep-line-2d の「半開区間なら $[t - D + 1, t + 1)$・$[x - W + 1, x + 1)$」は直前の式の閉区間と同じ整数の範囲。offline-queries の要点・signs の `[l, r)` は本文の半開区間に合う。ほかは「閉区間」の語を足しただけで端は変わっていない
- 法の文字：ds・comb に `\mathrm{mod}`・`log mod`・法 $P$ の残りはない。expectation-linear-equations の遷移の総数 $M$（165 行）と 178 行の $M$ は別の節で、紛れない
- 平文の欄（summary・signs・complexity）の Σ の書き換えは、元の式と同じ意味（和の範囲・割る数も同じ）
- 素の $ の 4 か所（stack-techniques 2・inclusion-exclusion・probability-dp）は描画でも地の文の $ が 0

### 問題の行

- 書き換えた 4 行（burnside-lemma abc428_g・permutation-cycles abc377_e・young-tableaux abc378_g・segment-tree-monoids arc008_4）は台帳の summary（abc377_e は permutation-cycles 向けの alternatives）と一字一句同じ
- ds・comb の全 455 行を台帳と比べると 26 行が台帳の文と違うが、どれも今回触っていない行で既存のもの（直しの対象外）

### 表記（#77）

- ds・comb に「一次関数」「1 次方程式」「1 次結合」「1 次独立」は残っていない。front matter（segment-tree-monoids）も直っている
- advanced-ds-catalog の表：10 行とも「**名前**：何ができるか ｜ 計算量 ｜ 代わりになる手」が元の 4 セルと一致（Kinetic Segment Tree の「一次関数」→「1 次関数」だけが違う）

## 直しが要る点

なし。

## メインへの申し送り（直しではない）

- 報告の「メインに判断してほしい点」のとおり、summary・signs・complexity を直したページがあるので、gen_site で生成物を作り直す必要がある
