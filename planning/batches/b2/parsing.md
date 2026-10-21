# parsing（構文解析）の報告

- 書いたファイル：docs/misc/parsing.md、snippets/parsing/{eval,eval-ext,stack-eval,shortest-formula,substring-sum}.{cpp,yaml}、docs/img/parsing/call-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は本文の順に並べ替えた（deep-nesting を grammar-dp の前へ。title・anchor・level は変えていない）
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 5 件すべて一致／textlint エラー 0・警告 7（要点の囲みの箇条書き・図の代替テキスト・別行の数式・折りたたみの中の長い文・区間 $[l, r)$ の括弧の誤検出・「で」の重複 1 件）
- 図：call-tree.svg を render_svg.py で 360px・720px にして確かめた。横長（880×420）なので 360px では文字が小さい。動く図は作っていない（catalog の visual は static・priority 2）
- コード片の確かめ方：shortest-formula は長さ 9 以下のすべての文字列（1・+・*・括弧）を評価した最短の長さと DP が一致すること（34 個の値）と、N ≤ 2000 のすべてで DP の式が N を表すことを assert で確かめた。substring-sum はランダムな式 3000 個で全部分文字列の素朴な評価と一致することを、stack-eval はランダムな式 20000 個で再帰下降と一致することと、入れ子 10^5 段を確かめた
- 使った出典：参考の節の 6 件（drken ×3、qiita、merom686、cnblogs Melville）。ikatakos（abc403 の evidence）は 503 で読めなかったので、代わりに qiita・merom686・cnblogs で abc403_f を確かめた。新しく noai を確かめたドメインはない（すべて付録 B にある）

## 台帳への提案

- abc403_f｜evidence｜ikatakos の URL に加えて https://qiita.com/Shizen_Tota/items/21f5f4f1bdfb55e26055 と https://merom686.hatenablog.com/entry/2025/04/28/015126 を足す｜ikatakos が 503 で読めなかった（読めるようになっていれば不要）
- 4 問とも summary・role は台帳のままで、本文の行は fix_problems が作った

## 用語集への提案

- 構文木｜syntax-tree｜式の計算の順を表す木。演算子を節、数を葉とし、各節は下の部分の値を求めてから自分の演算を施す。
- BNF｜bnf｜文法の規則を「式 ::= 項 { + 項 }」のように書く記法（バッカス・ナウア記法）。くり返しの { } などを足したものを拡張 BNF（EBNF）という。
- 左結合｜left-associative｜同じ優先順位の演算子を左から順に結ぶこと。8-3-2 は (8-3)-2 と読む。
- 本文では、check_pages が未登録の anchor をエラーにするので、構文木と BNF は用語集へリンクせずに書いた。用語集に足したら、本文の最初の「構文木」（why-it-works）と「BNF」（bnf）をリンクにしてほしい

## 手引きへの提案

- §13-5 は「用語集のリンクはまだなくても書いてよい」だが、check_pages はエラーにする。執筆者がリンクを外すか、check_pages を警告に下げるかを決めてほしい

## リンクの張り替え（メインへの控え）

- bracket-sequence:171・stack-techniques:160・string-basics:199 は parsing へのページのリンク。節へ張るなら、bracket-sequence:171 は #bnf（括弧の対応だけならスタック、の文脈）、stack-techniques:160 は #deep-nesting（再帰とスタックの文脈）が合う。string-basics:199 はページのままでよい
- related の cpp-environment#stack-depth は相手が stub なので、本文ではページへリンクした

## 問題の補充の候補

- arc122_a（A. Many Formulae、diff 783）｜練習の候補｜数の間に + か − を入れ、− が続かない式すべての値の和を mod で求める。左から読みながら「最後の演算子が + か − か」ごとに式の数と値の和を持つ DP で、本文の式の部分文字列の総和（A と x の更新）の易しい版に当たる｜https://zenn.dev/hal_mat/articles/0c3857b22b6ff1 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0612_arc122（どちらも検索の要約で確かめただけなので、追加するなら本文を読んで確かめる）
- joi2020_yo2_e（E. じゃんけん式、diff なし）｜練習の候補｜はまやん氏の JOI 解説まとめで「構文解析」に分類されている。式の ? を埋めて結果が指定の手になる方法の数を、再帰下降で数える問題と記憶しているが、問いを第三者の解説でまだ確かめていない｜https://blog.hamayanhamayan.com/entry/2019/11/09/180622（一覧の行だけ確かめた）
- 練習の候補が abc380_b だけなのは変わらない。ABC の構文解析は少なく、上の 2 問も ABC ではない

## 未解決の点

- abc403_f の N の上限は、qiita の解答コードが 2001 要素の配列を取ることから 2000 と判断した（本文には上限を書いていない。コード片は 2000 までを確かめた）
- abc338_g の入力に演算子が 2 つ並ぶことがあるか・数字に 0 が含まれるかは確かめられなかった。本文は「演算子が並ぶなら状態を空に戻す」と書き、コード片は 1〜9 の数字で式として正しい入力を仮定した（0 があっても DP の更新式は変わらない）
- 例題 arc061_a は難しさが基礎（1089）で青のページには易しいが、catalog の役割どおり例題にした。易しい順なので先頭に置いた

## 検証の指摘への対応（b2 verify）

- 直したもの：1（89 行と代替テキストに「数を読む factor は葉」を足した）・2（call-tree.svg を縦並びの 480×865 にし、360px で読めることを render_svg で確かめた。凡例の点線を「演算子を読まない呼び出し」に直した）・3（`s[s.size()]` は規格で `'\0'`、`vector<char>` は範囲外）・4（落とし穴を「単項マイナスを expr で読む」に書き直した）・5（substring-sum.cpp に演算子が 2 つ並ぶと状態を空に戻す処理を足し、照合用の素朴な評価と乱数の入力も並ぶ場合に広げ、yaml に `1+*2` → 3 を足した。本文 179 行の記述とコードが一致した）・6（$N$ を文字列の長さと定義）・8（stack-eval の後に単項マイナスの扱いを 1 文足した）
- 採らなかったもの：7（abc403_f の N の上限）。上限を第三者の記事で確かめられず、ikatakos も読めないので、確かめられない数を本文に書かない。メインのセッションで ikatakos が読めるときに上限を確かめ、「$N \le 2000$ なので $O(N^2)$ で間に合う」を足すことを提案する
- 提案（共有ファイル）：検証の「台帳への提案」（abc338_g・arc061_a・abc380_b を checked、abc403_f の evidence に qiita・merom686 を足す）に賛成
