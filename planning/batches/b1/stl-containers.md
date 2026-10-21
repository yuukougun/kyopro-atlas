# stl-containers の報告と提案

- 書いたファイル：docs/ds/stl-containers.md、snippets/stl-containers/count-pairs.{cpp,yaml}、snippets/stl-containers/multiset-erase.{cpp,yaml}（図の画像はなし）
- front matter で変えたもの：complexity・stage（draft）・updated。sections の pitfalls の title を短くした（見出しと一致させるため。anchor は同じ）。節 `next-steps`（順序付き集合・ヒープの応用へのつながり）を足した
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 5（要点の計算量の行が長い・助詞の重複。数式を含む列挙なので残した）
- 図：catalog の visual（static・priority 2「操作 × コンテナの計算量の表」）は、Markdown の表（早見表の節）で代えた。SVG は作っていない
- 使った出典：kyo-pro.hatenablog.com（abc253_c）、drken1215.hatenablog.com（abc166_e）、github.com の kyopro-tessoku 第 8 章（A54・A55 のコードで問いを確認）、cpprefjp（multiset::erase・count）、en.cppreference.com（std::lower_bound の移動回数）。新しいドメインはなし

## 台帳への提案

- なし（4 問とも evidence で問いを確かめ、summary はそのまま使えた）
- tessoku_book_bb・tessoku_book_bc の evidence はディレクトリの URL なので、ファイルの URL（.../chap08/answer_A54.cpp・answer_A55.cpp）にすると確かめやすい

## 用語集への提案

- ならし計算量｜amortized｜操作を何回も続けたときの合計を回数で割った、1 回あたりの計算量である。vector の末尾への追加のように、ときどき重い操作があっても合計が抑えられる場合に使う（本文ではリンクしていない。リンクするならこの anchor）
- イテレータの無効化｜iterator-invalidation｜コンテナの変更によって、それまで持っていたイテレータ・参照が使えなくなること。使うと未定義動作になる（本文は cpp-container-idioms#invalidation へリンクした）

## 手引きへの提案

- §13.1 で「落とし穴」は定型の節とされているが、catalog と多くのページで sections に `pitfalls` が載っている。載せるかどうかの決まりを明記するとよい（ここでは sections に残し、見出しと title を一致させた）

## 問題の補充の候補

- abc233_d：和がちょうど K の連続部分列の個数（map で累積和を数える）。05-ds §5 の候補。ただし prefix-sum-counting の例題なので、ここに足すなら練習扱い。裏付け https://drken1215.hatenablog.com/entry/2024/11/23/150237
- abc234_d（priority-queue の例題）を「容器を選ぶ」練習として触れる案もあるが、例題の重複になるので見送った

## 未解決の点

- unordered_map が「AtCoder ではまれだが、入力を参加者が作れるコンテストでは狙われる」と書いた。AtCoder の after_contest のテストで狙われた実例は確かめていない（hash-safety の執筆時に合わせて確かめたい）
- vector の伸長が 2 倍なのは libstdc++ の実装（規格は定めない）として書いた。g++-15 で容量が 1・2・4・…・128 と倍になることを一時置き場で確かめた（コード片は置いていない）
