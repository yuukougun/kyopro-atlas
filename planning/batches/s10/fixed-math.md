# 工程10 math の直しの記録

5 つの一覧（audit-facts・audit-figure・audit-relations・audit-shared・audit-structure）の「## math」の項目を直した。直した数 64、残した数 4（＋ほかの分野のページの分 2）。残したものは left-math.md。

検査：`python3 tools/check_pages.py` エラー 0・警告 0、`npm run lint:text` エラー 0（warning のみ）、`python3 tools/fix_problems.py --check --field math` 直すべき行 0・台帳にあって本文にない 0。コード片は変えていない（check_snippets は不要）。

## audit-facts（4 件、すべて直した）

- matrix-power：「歩道」を「ウォーク」に（定義の文も「ウォークは…」に。本文 10 か所と図 adjacency-power.svg の題）
- spf-sieve L200：`\mathrm{lcm}` を `\operatorname{lcm}` に（graph/time-dependent-dijkstra は left）
- mod-inverse L224・L228、spf-sieve L148・L154：「閉区間」と明記（guide/method-comparison は left）
- convolution-ntt L287：`|S|` を `\lvert S \rvert` に

## audit-relations（3 件、すべて直した）

- spf-sieve の linear-sieve：「φ と μ の定義を前提にする」をやめ、乗法性と素数冪での値を節の中で 1 文で書き、リンクは参照にした
- euler-phi L153：「バーンサイドの補題」を「Burnside の補題」に
- 手法の名前のリンクの文字を相手の題名に：gaussian-elimination（閉路のある期待値 ×2）、modint（確率・期待値を mod 998244353 で答える ×2）、mod-pow（和・積の法則と順列・組合せ）、matrix-power（照合オートマトン上の DP ×2）、gcd-properties（約数包除 ×2）、integer-root（約数包除）

## audit-shared（4 件、すべて本文に足した）

- mod-arithmetic：練習に abc266_b と方針
- crt：力試しの節を作り abc371_g と方針、参考に ikatakos 氏の記事（permutation-cycles と同じ出典）
- xor-basis：練習に agc045_a・zone2021_f と方針、参考に maspy 氏・fairy_lettuce 氏の記事（どちらも台帳の evidence。check_noai で noai の指定がないことを確かめた。fairy-lettuce.hatenadiary.com は付録 B にないので、メインが付録 B に足す）
- integer-root：練習に panasonic2020_c と方針。参考の at274 氏の行を練習の出典にした

## audit-structure（26 件のうち 22 件を直した）

- fft-ntt：`## ACL の convolution と自作するときの要点 {#library}` を立て、ACL の囲み・自作の要点・Library Checker での確かめ方を集めた（sections に足した）。練習問題に §16-5 の 1 文
- fps-basics：library の節を立て、ACL の囲み・ニュートン法のコード・自作の要点を移した（sections に足した）
- multiplicative-function：`## 公開ライブラリと自作するときの要点 {#library}` に公開ライブラリの文と Lucy DP・杜教篩の要点を集め、`## 学ぶための資料 {#resources}` を足した。参考の「（学ぶための資料）」を外した。練習問題に §16-5 の 1 文
- online-convolution：library の節を立て、ACL の囲み・自作の要点・Library Checker を移した（sections に足した）
- stern-brocot：段落だった資料の案内を `## 学ぶための資料 {#resources}` にした。要点の「何ができるか」を summary に合わせ「実数に最も近いもの（実数を挟む最も近い 2 つ）など」にした（summary は変えていない）
- miller-rabin：`acl: []` なのにあった「ACL では」の囲みを acl-internal の本文にした。`## 例題` を消し、§16-5 の 1 文を練習問題の節へ
- determinant：練習問題の 1 文を §16-5 の言い方に（案内の文は残した）
- floor-sum：`why-log` を H2 に上げた（anchor はそのまま）
- modint：static-dynamic の節に「ACL では」の囲み（宣言・set_mod・val・pow・inv と計算量）
- sigma-manipulation：節 formulas の見出しと sections の title から波かっこの式を外した（anchor はそのまま）
- divisor-enum・mod-inverse・prime-factorization・sieve-eratosthenes・spf-sieve：定型の `## 上位の手法へのつながり {#next-steps}` を落とし穴の後に足した（リンク先の anchor はすべてあることを確かめた）
- euler-phi：練習の方針の箇条書きの句点をそろえた
- 残した 4 件：linear-recurrence-fast の anchor、modint・mod-pow の next-steps、floor-sum の練習（left-math.md）

## audit-figure（31 件、すべて直した）

どの図も、幅を 328 以下（360px の画面で縮まない）にするか 2 枚に分け、文字を 360px 表示で 9px 以上にした。width・height を viewBox と同じ値で付けた。`python3 tools/render_svg.py` で 360px を撮って重なり・はみ出しを確かめた。

- 2 枚に分けた（本文は画像を 2 つ並べ、代替テキストも分けた）：
    - exponent-mod：powers-mod-7-base3.svg・powers-mod-7-base2.svg
    - integer-division：floor-ceil-negative.svg・floor-ceil-positive.svg（a = −7 と a = 7）
    - multiplicative-order：powers-mod7-base2.svg・powers-mod7-base3.svg
    - gaussian-elimination：steps-1.svg（①②）・steps-2.svg（③④）
    - mod-arithmetic：clock-congruence.svg・clock-addition.svg
    - mod-inverse：mult-table-mod7.svg・mult-table-mod6.svg
    - sigma-manipulation：swap-grid-rows.svg・swap-grid-cols.svg
- 縦に組み直した（ファイル名はそのまま）：matrix-power/fast-power、mod-pow/binary-expansion、prime-factorization/trial-division（2 段）、segmented-sieve/window（数を縦、素数を列に。本文の「各行」を「列」に直した）、convolution-ntt/anti-diagonal・reverse、digit-and-mod/suffix-pairs、divisor-count-bound/dfs-tree（字下げの木）、divisor-enum/pairs、ext-gcd/table（確かめの式を各行の 2 行目に）、floor-quotient-enum/staircase、gaussian-elimination/outcomes（3 つを縦に）、gcd-lcm/euclid-squares、gcd-properties/staircase（横棒）、harmonic-sum/multiples-grid、integer-root/correction、matrix-power/adjacency-power、prime-exponent-vector/exponent-bars、sieve-eratosthenes/grid100
- 文字だけ大きくした：base-conversion/ladder（上付きを ⁰¹² に）、crt/grid-4-6（あわせて、説明にある「太枠」のマスが描かれていなかったので足した）、geometric-series-mod/halving、miller-rabin/rho
- width・height を足した：crt/grid-3-5、xor-basis/insert、xor-basis/xor-walk
