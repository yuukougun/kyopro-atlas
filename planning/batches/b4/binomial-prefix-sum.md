# binomial-prefix-sum の報告と提案（b4）

- 書いたファイル：docs/comb/binomial-prefix-sum.md、snippets/binomial-prefix-sum/mover.{cpp,yaml}（図はなし。visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点, anchor: library}` を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 12 は数式を含む文の読点の数・文の長さ・要点の囲みの長い計算量の行で、誤検出として残した）
- コード片の確認：手元で乱数の (n_max ≤ 30, Q ≤ 20, K は -1 から) 300 回、愚直な和と一致を確かめた
- 使った出典：kmjp（例題の方針と実装）、ikatakos（更新式の導き方と包除の式。解法の節だけ）、github.com の library-checker-problems（enumerative_combinatorics に部分和の問題がないこと）。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc235_g | summary | N 個の庭に 3 種類の苗（それぞれ A 本・B 本・C 本まで）を、1 つの庭に同じ種類は 1 本までとして植える方法のうち、どの庭にも 1 本以上植えるものの数を求める。 | https://kmjp.hatenablog.jp/entry/2022/01/17/0900 |
| abc235_g | evidence | 2 つ目に https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0115_abc235 を足す | 同左（解法の節） |

（本文の行は §14-16 の形で自分の要約を書き、fix_problems で label を埋めた。台帳の summary の「（植え方の条件は執筆時に確かめる）」を外す直し）

## 用語集への提案

なし（オフラインは既存の #offline にリンクした）。

## 手引きへの提案

- §4 の overview の「ライブラリでの使い方」は、ACL も Library Checker も対応がない手法では「自作するときの要点」の節で代えてよい、と明記するとよい（このページは `{#library}` の節を足して、Library Checker に対応がないことと、二項係数の部分だけ Binomial Coefficient (Prime Mod) で確かめられることを書いた）

## 問題の補充の候補

- 見つからなかった。Web 検索で「二項係数の部分和を 1 ずつ動かす」AtCoder の問題を第三者の解説から探したが、裏付けの取れる候補は abc235_g のほかになかった（Mo の順で (n, K) を動かす型の代表は codeforces の問題が多く、noai 指定のため調べていない）。発展の概要なので例題 1 問のままでよいと考える

## 未解決の点

- 例題の制約（N の上限）は第三者の解説に数値で書かれておらず、本文では「N が大きいので O(N) が要る」とだけ書いた
- 「学ぶための資料」に、ABC235 G の解説以外でこの手法を一般に説明した記事（日本語・AI 可）を見つけられなかった。Mo の順に動かす話は、サイト内の mo-algorithm#two-prefixes へのリンクで代えた

## 検証の指摘への対応

- 指摘 1〜7 はすべて直した（採らなかったものはない）。mover.cpp には n_max ≤ 60 のとき愚直な和と `assert` で比べる処理を足し、cases の 1・2 つ目と乱数 100 回（n_max ≤ 40）で通ることを確かめた。伸縮の順は「どの順でもよい」に直した。包除の節は一般形（t 種類）に絞り、解法の詳細は本文にない点だけにした
- 台帳への追加の提案：検証役の提案どおり、abc235_g の `checked` に 2026-10-22 を入れる（上の summary・evidence の提案とあわせて）
- 再検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 11）
