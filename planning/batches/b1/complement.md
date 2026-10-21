# complement（余事象）の報告と提案

- 書いたファイル：docs/thinking/complement.md、snippets/complement/two-conditions-mod.{cpp,yaml}、docs/img/complement/whole-minus-complement.svg、docs/img/complement/two-conditions.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 期待と違う 0。textlint エラー 0・警告 11（数式を含む文の長さ、`$[0, \mathrm{MOD})$` の括弧の対、数式の読点。どれも誤検出）。fix_problems --check はこのページに直すべき行なし（math/sieve-eratosthenes.md に 5 行あるが担当外）
- 使った出典：drken（abc178_c・abc162_d・abc193_c・abc131_c・abc156_d）、qiita の comet725・Authns（abc455_e）。新しいドメインなし
- SVG は描画の道具が手元になく、目で確かめていない。検証で表示を確かめてほしい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc455_e | summary | 文字列 S の空でない部分文字列（位置で区別する）のうち、含まれる A・B・C の個数が互いに異なるものの数を求める。 | https://qiita.com/Authns/items/f01569d1cf0daa9dffe1 ・ https://qiita.com/comet725/items/ef3bf31a249dcf3e48f3 |
| abc455_e | approach | 全区間 N(N+1)/2 から、2 文字の個数が等しい区間（累積の差が一致する組を連想配列で数える）を 3 種類引き、3 文字とも等しい区間を 2 倍して足し戻す | 同上 |

- 本文の abc455_e の行は、台帳の summary が「（執筆時に確かめる）」のため上の値で書いた。台帳を直してから fix_problems を流せば一致する
- abc156_d（Bouquet）は空集合を除く余事象の代表だが、台帳では binomial-precompute の練習だけ。このページでは参考に挙げただけで、問題の囲みには入れていない。complement の練習に足すかはメインの判断（問題数は今 5 で上限内）

## 用語集への提案

- なし（「補集合」はこのページ自身が受ける）

## 手引きへの提案

- §5 thinking「余事象は補集合まで」とあるが、catalog の sections に「2〜3 条件の包除」があるので、「余事象は補集合と 2〜3 条件の包除まで（一般形は comb の包除原理）」と書くと迷わない

## 問題の補充の候補

- abc156_d：1 本以上選ぶ選び方 2^n − 1 から、本数が a・b のものを引く（空集合の扱い）。https://drken1215.hatenablog.com/entry/2020/04/22/013400 （台帳に確認済みで登録あり。pages に complement の practice を足す案）

## 未解決の点

- abc455_e で S が A・B・C 以外の文字を含みうるかは、第三者の解説からは確かめきれなかった（要約では「含まれる A・B・C の個数」とし、どちらでも正しい書き方にした）
- 図の priority は 2（静的）なので、SVG 2 枚で済ませた。動く図は作っていない

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜4（直すとよい 4 件）はすべて直した。採らなかったものはない
    - 1：two-conditions.svg の A・B を不透明にし、重なりは A で切り抜いた B（clipPath）を灰色で塗り、輪郭を最後に描き直した
    - 2：2 枚の図のラベルを 15〜16px にそろえ、10^N・9^N・8^N の N を上付き（tspan）にした
    - 3：3 条件の包除の段落に、3 つすべてに入る要素が +1 −3 +3 −1 = 0 と数えられる例を足した
    - 4：ABC193 C の方針を「1 から N までを 1 つずつ調べることはできないが」に直した
- 検証役の申し送りどおり、abc178_c・abc162_d・abc193_c・abc131_c・abc455_e の台帳の `checked` に 2026-10-21 を入れることを提案する
