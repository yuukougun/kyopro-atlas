# trie の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/trie.md、snippets/trie/{basic,lcp-sum,max-lcp}.{cpp,yaml}、docs/img/trie/lcp-sum.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 1：prerequisites の dfs が未作成という既存の警告）、fix_problems --check（trie の行は直すべき行なし。geometry/argument-sort.md に 6 行あるが担当外）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 4）
  - 残した警告：38 行（要点の囲みの箇条書きを 1 文と数える。見本と同じ）、105 行の max-comma（数式 $1, 2, \dots, k$ の中の読点）、249 行の sentence-length（折りたたみの中の箇条書きを続けて数えた誤検出。文は 3 つに分けてある）、308 行（参考の記事の題名が長い）
- 図：静的な SVG 1 枚（abc・abd を入れた後と、ab・b も入れた後の 2 枚組。通過数・終端の二重丸・C(通過数, 2)）。catalog の visual は priority 2・static なので動く図は作っていない。描画して確かめる道具がなく、XML として読めることと座標の計算だけを確かめた
- 使った出典：merom686（abc287・abc353・abc403・abc268）、programming-hiroba（abc287_e・abc353_e）、ikatakos（abc437・abc377 の解法の節だけ）、kmjp（abc268_g）。題名は title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc287_e | evidence | https://programming-hiroba.com/abc287-e/ を足す（merom686 の記事は方針の一言だけで、問いの裏付けとして弱い） | 左の URL |
| abc353_e | evidence | https://programming-hiroba.com/abc353-e/ を足す（Trie と通過数による解法、長さの総和の上限 3×10^5 が書かれている。merom686 の記事はソートと再帰による方法） | 左の URL |
| abc268_g | evidence | trie の alternatives の approach に合う式 1 + f + (N − 1 − f − g)/2 は kmjp の記事にある（すでに evidence にある）。変更なし | https://kmjp.hatenablog.jp/entry/2022/09/10/0900 |

ほかの使った問題（abc437_e・abc403_e・abc377_g）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- なし（本文で用語集へのリンクは使っていない）。「通過数」「終端」は本文で定義した。ほかのページ（aho-corasick・binary-trie）でも使うなら、用語集に「通過数｜pass-count｜Trie の節点を通る文字列の数。その節点の接頭辞を持つ文字列の数に等しい」を足すとよい

## 手引きへの提案

- technique（水）の目安にある「必要になる場面」は独立した見出しにせず、最初の節（basic-operations）の冒頭に入れた。定型の見出しにしない運用でよいか確かめたい
- 「計算量とその根拠」も独立させず、basic-operations（挿入・検索）と lcp-sum（O(L)）の中に書いた

## 問題の補充の候補

- arc087_c（E. Prefix-free Game、diff 2431、ap.py で実在を確認、台帳になし）：接頭辞の関係にならないよう文字列を足していくゲームの勝敗。Trie の空いた部分木ごとに Grundy 数を求めて XOR する型で、節 dp-on-trie の「ゲーム」の段落の代表になる。発展の難しさなので力試しか、grundy-number の練習が向く。裏付け：drken「AtCoder 版！蟻本 (上級編)」で文字列（Trie）の章の問題として挙がっている（https://qiita.com/drken/items/9b311d553aa434bb26e4）。解法の詳しい第三者の解説は見つけられておらず、台帳に入れるなら evidence を探す必要がある
- abc319 以降の水の問題は、abc353_e・abc403_e・abc437_e がすでにあるので探していない

## 未解決の点

- abc287_e の制約（N と長さの総和の上限）は確かめられなかったので、本文には書いていない
- 「`stable_sort` なら文字列のソートが O(L log N)」はマージソートの各段で比較 1 回の費用を出力される側の長さで抑える議論による（自分で確かめた）。`std::sort` の上限には触れていない
- `array<int, 26>` で L = 5×10^5 のときの約 52 MB は計算による。メモリ制限 1024 MB は「なら」と条件にして書いた
- 節 dp-on-trie の「節点に値を持ち、入れながら答える」の段落は、abc377_g の解き方とほぼ同じ内容である（練習の方針と重なる）。練習の答えが本文で見えてしまうのを避けたいなら、本文の例を一般的な形に弱めるか、abc377_g を例題に上げることをメインで判断してほしい

## 検証の指摘への対応（2026-10-21）

- 直したもの：指摘 1（stable_sort の理由を、比較の費用を出る側の長さで抑える議論にし、合計を $O((L + N) \log N)$ と書いた）、2（Suffix Array を使う理由を接尾辞の長さの総和 $N(N+1)/2$ に）、3（座標圧縮しても種類数が多ければ配列にできないと明記し、確認問題と合わせた）、4（2 か所に「根以外の」）、5（約 4.6 万）、6（自分以外・$S$ と等しいものを含む、真の接頭辞だけなら $\mathrm{cnt} - \mathrm{ed}$）、7（約 2.4 倍・約 124 MB）、8・9（lcp-sum.svg を描き直した。円の中に接頭辞、辺の横に斜体で文字、注記は 15、下の 2 行の説明を外して凡例 1 行に、viewBox を 580×370 に縮めた。chrome-headless-shell で描画して重なりがないことを確かめた）、11（ゲームの段落を「接頭辞の関係にならない文字列を足していくゲームで、空いた部分木ごとに Grundy 数を求めて XOR する」型に具体化）
- 指摘 10 は案 (b) を採った：本文の例を「$v$ を通る、これまでの文字列の重みの最小値」の一般の形に弱め、末尾の削除・追加の話は練習の方針にだけ残した。案 (a)（abc377_g を例題に上げる）は問題の役割（台帳・囲みの data-role）の変更を伴うので執筆者の範囲では行わない。メインが (a) を採るなら、abc377_g を例題に移し、本文の段落から例題へリンクする形に戻せる
- 指摘 11 の arc087_c は台帳になく evidence も未確保なので、本文に問題へのリンクは付けていない。上の「問題の補充の候補」の提案はそのまま
- 採らなかったもの：なし
