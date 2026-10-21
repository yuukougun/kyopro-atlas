# dp-segment-tree の報告と提案（b2）

- 書いたファイル：docs/dp/dp-segment-tree.md、snippets/dp-segment-tree/{split-abs,interval-cover,window-row}.{cpp,yaml}、docs/img/dp-segment-tree/{values-steps,split-abs}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 本とも一致（各コード片は素朴な DP と assert で照合）、textlint エラー 0・警告 34（数式を含む文の長さ・`[` の対の誤検出・数式の中の読点、折りたたみの中の長い文、「に」の重複 3 か所は言い換えると不自然なので残した）。図は render_svg で 360・720 幅を目で確かめた
- 構成：sections の 5 節 → 定型の落とし穴・例題・練習問題・力試し・確認問題・参考。sections の which-tool が使い分けの役を兼ねるので、定型の `## 使い分け {#comparison}` は立てていない（下の「手引きへの提案」）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc410_g | approach | 円を 2 周分に開いて各弦を 2 つの区間にし、入れ子の深さの最大を、右端の順に区間 max のセグメント木で求める DP | https://kmjp.hatenablog.jp/entry/2025/06/14/0930 |
| typical90_ak | evidence | 画像の解説に加え、解答コード https://github.com/E869120/kyopro_educational_90/blob/main/sol/037.cpp を足す（状態・前の段の区間最大・作れない状態の扱いを確かめた） | 同 URL |
| dp_q | checked | 2026-10-21（Series_205 氏と drken 氏の記事で問い・制約 h_i ≤ N で相異なること・遷移を確かめた） | evidence の 2 件 |
| abc353_g・arc026_3 | checked | 2026-10-21（drken 氏の記事で状態・遷移・初期値を確かめた） | evidence |

## 用語集への提案

なし（identity-element だけを使った）。

## 手引きへの提案

- **which-tool と comparison**：§14-2 は sections の `choosing`・`comparison` を外して定型の `## 使い分け {#comparison}` にそろえるとするが、このページの sections には `which-tool`（中身は使い分けそのもの）がある。anchor を変えない規則に従って `which-tool` のまま残し、定型の使い分けは立てなかった。§14-2 の対象に `which-tool` も入れるか（入れるなら anchor を comparison に変え、docs/index/dp.md の行を張り替える）をメインが決めてほしい
- catalog の sections にあった「落とし穴：初期値（−∞）・更新と取得の順番」（anchor pitfalls）は、§14-1 のとおり定型の `## 落とし穴 {#pitfalls}` に入れた

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc334_f（F. Christmas Present 2、diff 1813、ap.py で確認） | 家を順に回り、容量 K の袋が空になる前に拠点へ戻って補充しながら全員に配る最短距離。直近 K 軒からの遷移で、コストの「i だけの項」（累積の距離）を外に出すと窓の最小になる | dp-sliding-window の節の例題か練習（本文では問題 ID を出さず「容量 K の袋で荷物を順に配り、拠点との往復を挟む最短距離」とだけ書いた） | https://kazun-kyopro.hatenablog.com/entry/ABC/334/F （この記事は遅延セグメント木で解く。i の項を外に出してスライド最小値でも解けるのは式から分かるが、記事では確かめていない） |

- dp-sliding-window の節には例題がない（abc359_e は単調スタックの持ち主 monotonic-stack の例題で、ここでは練習）。abc334_f を足せば、窓の最小の遷移の例題になる
- 水・青のページには abc319 以降を 1 問以上という目安は、例題の abc353_g・練習の abc339_e・abc359_e・力試しの abc410_g で満たしている

## 未解決の点

- abc410_g：ikatakos 氏の記録は取得時に 503 で読めなかった。kmjp 氏の記事（2 周分に開く・区間 max の DP）と台帳の summary から、方針の折りたたみを自分で組み立てた。「新しい弦と交わり互いに交わらない弦は、どこかで切ると入れ子に並ぶ」の向きは自分で確かめたが、検証役にも見てほしい
- abc353_g：C・P_i の上限は記事で確かめられなかったので、本文は「大きくなりうるので long long」とだけ書いた
- typical90_ak：N・W の上限は確かめられなかった（解答コードの配列の大きさからの推測だけ）。本文に数値は書いていない
- 参考の drken 氏の ABC353 G・ARC026 C の記事の題名は、取得結果の要約から書いた（h1 の正確な文字を検証役に確かめてほしい）
- 動く図（visual priority 2）は作らず、静的な SVG 2 枚にした。作るなら仕様は「dp 配列を値を添字にした区間 max のセグメント木の葉に並べ、各花で区間 [0, h) の max を取るノードを光らせてから 1 点更新するステップ送り（図 values-steps と同じ入力 h = (1, 3, 0, 2)・a = (5, 3, 4, 6)）」と「前の段の窓 [j − R, j − L] に合わせて deque に添字を出し入れするステップ送り」。置き場の div は本文に入れていない

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 11 回（うち検索 1 回、503 が 1 回）

## 検証の指摘への対応（直し）

- 指摘 1〜7（すべて「直すとよい」）をすべて採った。採らなかったものはない
  - 1：「区間の重なりの深さを数える DP」→「区間の入れ子の深さを求める DP」
  - 2：区間を覆う節の冒頭に「費用は $c_i \ge 0$ とする」と、負の費用では求まらない理由を足した
  - 3：処理の流れの擬似コードを「v ← seg.prod(l, r)。v が −∞ なら更新しない」「cur ← v + c_i」の 2 行に分けた
  - 4：「値の上限を $V$ として」を足した
  - 5：abc353_g の方針の計算量を節にそろえ「木の構築が $O(N)$、市場 1 つにつき $O(\log N)$ で、全体 $O(N + M \log N)$」とした
  - 6：values-steps.svg を幅 440 の viewBox に組み直した（題を 2 行、各段の見出しを配列の上、注記を配列の右に寄せ、文字を 14〜15px）。render_svg の 360px で読めることを目視した
  - 7：参考の drken 氏 dp_q の記事の参考にした点を「例題 dp_q を重み付き LIS として見る見方」に直した
- 台帳への提案は検証の報告（planning/batches/b2/verify/dp-segment-tree.md の「台帳への提案」）のとおり。dp_q・typical90_ak・arc026_3 の checked を 2026-10-21 に、typical90_ak の evidence に E869120 氏の sol/037.cpp を足す
