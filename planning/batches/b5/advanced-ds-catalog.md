# advanced-ds-catalog の報告と提案（b5）

- 書いたファイル：docs/ds/advanced-ds-catalog.md、snippets/advanced-ds-catalog/leftist-heap.{cpp,yaml}、snippets/advanced-ds-catalog/pbds-join.{cpp,yaml}（図はなし。visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 件とも期待どおり、textlint エラー 0（警告 3：Kinetic Segment Tree の表の行と参考の 1 行の文の長さ、leftist heap の段落の助詞「が」。表の行・参考の題名と数式を含む文なので残した）
- 構成：hub として「表 → 補足（仕組みの要点）→ Library Checker」、併合可能なヒープの節（種類の表・マージテクで足りるか・要る場面 3 つ・leftist heap のコード片・pb_ds の join・確認問題 1）、ほかのページにあるものの表（区間・列／クエリ処理／木の 3 つ、計 33 行。すべて draft のページの節かページへのリンクで、check_pages で存在を確かめた）
- 問題：載せていない（catalog の problems が空で、hub は 0〜3 問）
- 使った出典：OI Wiki（seg-merge-split・kdt・divide-combine・leftist-tree）、cp-algorithms（randomized_heap・sqrt-tree）、en.wikipedia.org（Skew heap）、koosaga.com/307、github.com/maspypy/library（fastset.hpp）、gcc.gnu.org（pb_ds の design）、Library Checker（GitHub の task.md で問題の存在と内容を確認）
- 新しく noai を確かめたドメイン：koosaga.com（tools/check_noai.py で noai・noimageai の指定なし）

## 台帳への提案

- なし（このページに載せる問題はない）

## 用語集への提案

- 併合可能なヒープ｜meldable-heap｜2 つのヒープを $O(\log N)$ ほどで 1 つにまとめられるヒープ。skew heap・leftist heap・ランダム化ヒープ・pairing heap など。ページの節 `ds/advanced-ds-catalog#meldable-heap` があるので、用語集に入れずリンク先にするだけでもよい
- 連続段｜common-interval｜順列の区間で、値の集合も連続した整数の範囲になるもの（析合木が表す対象）。本文では短く定義した（リンクは張っていない）

## 手引き・front matter・catalog への提案

- aliases に `Sqrt Tree`・`pairing heap`・`ランダム化ヒープ`・`permutation tree`・`64 分木` を足す案（本文の表と節で扱っている。term-index から引けるように）
- 張り替え：docs/graph/spanning-tree-advanced.md:106 の `../ds/advanced-ds-catalog.md` を `../ds/advanced-ds-catalog.md#meldable-heap` に（b4 の申し送りどおり）。docs/ds/priority-queue.md:196 も同じく `#meldable-heap` に。docs/ds/cdq-divide-and-conquer.md:119 は `#table` に（2 次元セグ木の行）。docs/dp/slope-trick.md:125 の「併合できるヒープ（meldable heap）」に `#meldable-heap` へのリンクを張り、語を「併合可能なヒープ」にそろえる案。docs/graph/k-shortest-paths.md:87 の「併合できるヒープ」も同じ
- priority-queue・cdq-divide-and-conquer の本文のリンクの題名が「発展的なデータ構造の一覧」で、このページの題名「見慣れないデータ構造の名前と用途」と食い違う。題名にそろえる案
- 付録 A に「併合可能なヒープ」を足す案（本文には「併合できるヒープ」との揺れがある。prh.yml で「併合できるヒープ」→「併合可能なヒープ」）

## 問題の補充の候補

- 探していない。hub は問題 0〜3 で、catalog の problems も空のため。併合可能なヒープが要る ABC の問題は調査レポート 05-ds §4.E でも見つかっていない

## 未解決の点

- Kinetic Segment Tree の計算量は koosaga 氏のブログ（韓国語）だけで確かめた。元の解説の多くは codeforces.com にあり、開いていない。更新があるときの $O(N \log^2 N \alpha(N))$ は本文に書かず、「更新がなければ全体でならし $O(N \log^2 N)$」だけを書いた
- 2 次元セグ木の「1 回 $O(\log H \log W)$、メモリ $O(HW)$」と「先読みして各ノードを圧縮するとメモリ $O(N \log N)$」は、一般に知られた値として書いた（一次資料での確認は cp-algorithms の Segment Tree の節が候補。今回は開いていない）
- 析合木の代わりの手（最大値 − 最小値 −（右端 − 左端）の最小値と個数を遅延セグ木で持つ）は、本文に問題 ID を出さず型だけを書いた。教材に対応する節がなく、lazy-segment-tree-patterns に節を足すかはメインの判断
- pairing heap の取り出しの「ならし $O(\log N)$」は GCC の文書では「worst-case は高い」としか書かれていない。ならし $O(\log N)$ は一般に知られた結果として書いた
- 使用量の目安：道具の呼び出し 40 回ほど、Web 取得 12 回ほど

## 検証の指摘への対応（b5 の直し）

- 直した：1（K-D tree の最近点を「最悪 $O(N)$、それより速い保証はない」に。参考の行も）・2（析点の定義に「子の並び全体を除き」）・3（Kinetic Segment Tree の時刻を部分木での最小値に）・4（表を「長方形の集約は $O(\sqrt{N})$、列挙なら $+K$」に、補足にも集約の前提を書いた）・5（オンラインのときは内側を動的セグメント木にした入れ子、メモリは更新 1 回につき $O(\log H \log W)$。動的セグメント木のリンクは 59 行の 1 か所だけ）・6（Fast Set の探索は上りと下りで段ごとに高々 2 語。表に「全段で $N/63$ 語ほど」）・7（`## 確認問題 {#quiz}` を参考の前に立て、問いを「全体への加算があるときマージテクで併合できるか」「skew heap を再帰で書くと何が困るか」に差し替えた）・8（表の外の段落の重ね、59 行のマージテクと 61 行の CDQ 分割統治のリンクを外した）・9（leftist-heap.cpp の入力の説明に「a ≠ b」）・10（参考に Wikipedia「Pairing heap」を足した。開いて、delete-min ならし $O(\log n)$・meld $O(1)$ の記述を確かめた）
- 採らなかったもの：8 のうち表の行ごとの重ね（sweep-line-2d の 47・49 行など）は、引く表として各行にリンクがあるほうが使いやすいので残した。hub の表を例外にするかはメインの判断
- textlint：エラー 0・警告 3（67 行の析合木の段落の文の長さ、94 行の助詞「が」、参考の koosaga の行の文の長さ。前回と同じく残した）
