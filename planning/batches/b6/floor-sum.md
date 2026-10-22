# floor-sum の問題の補充（b6・工程9）

- ページ：docs/math/floor-sum.md（レベル 黄）。今の練習は 0 問。例題は practice2_c・abc443_g、力試しは abc313_g・abc283_h
- 探したところ：
    - (1) b1・b3・b5 の summary/candidates.md には floor-sum の候補なし。各バッチの報告 planning/batches/b*/floor-sum.md はなく、試作の検証 planning/batches/pilot-verify/floor-sum.md の指摘 10 が「練習 0 問。補充で探す」と書くだけ。catalog（planning/catalog/math.yaml）の problems_note も「練習の候補が見つかっていない」
    - (2) data/problems.yaml で pages に floor-sum を持つ問題は practice2_c・abc443_g・abc313_g・abc283_h の 4 問で、どれも本文にある。本文にない問題はない
    - (3) `python3 tools/ap.py search` で題名に Floor・Linear・Mod・Sum などを含む問題を洗い、第三者の解説（drken・kmjp のブログ内検索とアーカイブ、qiita の検索）で何を問うかを確かめた。途中でこのセッションの WebSearch の上限に達したので、一般の検索エンジンでは探せていない
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 結果：練習（帯 黄 2000〜2399 か、その近く）に向く候補は**見つからなかった**。帯から離れた力試しの候補が 1 問（arc111_e）。練習は 0 問のまま

## 候補

### arc111_e（新規。台帳になし）

- 問題ID：arc111_e
- 題名：E. Simple Math 3
- difficulty：2541（橙・発展）
- 役割：challenge（帯の上端 2399 を超えるので練習ではなく力試し）
- 要約：整数 A, B, C, D が与えられ、閉区間 [A + B·i, A + C·i] に D の倍数が 1 つも入らない正の整数 i の個数を求める（複数ケース）。
- 方針の要点：区間の長さ (C − B)·i が D − 1 以上になると必ず倍数が入るので i の上限 m を決め、1 ≤ i ≤ m で「区間に入る D の倍数の個数」⌊(A + C·i)/D⌋ − ⌊(A − 1 + B·i)/D⌋ が 0 か 1 であることを使って、その和を floor sum 2 回の差で求め、m から引く。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2021/01/10/1000 （問いの形と、i の上限を絞ってから floor_sum(m+1, D, C, A) − floor_sum(m+1, D, B, A−1) で倍数を含む i を数える方針を確かめた。i の範囲・A〜D の制約は記事に明記されていない）
- 台帳への追加の提案：pages に {id: floor-sum, role: challenge}。このページの #mod-to-floor の「条件を満たすかどうかを 2 つの floor の差で書く」の型そのもので、例題 abc443_g の次に置ける。ただし力試しは既に 2 問（abc313_g 2454・abc283_h 2682）あるので、足すかどうかはメインの判断に任せる

## 除いたもの

- abc436_g（G. Linear Inequation、diff 2164）：題名からは候補に見えたが、qiita の記事（https://qiita.com/tehom_math/items/2c2d0b919376d8c10650）で Bostan-Mori の関連問題として挙がっており、floor sum の問題ではない
- abc466_f（F. Many Mod Calculation、diff 1887）：洛谷の問題ページで、x に A_1, …, A_N の順に mod を取って 0 になる x の個数を数える問題と分かった。一次式の floor の和の形ではなく、解き方を書いた第三者の解説も見つけられなかったので候補にしない
- abc456_g（G. Count Holidays、diff 2488）：kmjp の記事（https://kmjp.hatenablog.jp/entry/2026/05/02/0930）では包除原理と区間の合成で、floor sum は使わない
- abc356_e（E. Max/Min、diff 1506）：Σ ⌊max/min⌋ の形で、商の値ごとにまとめる floor-quotient-enum の道具の問題（分母が動く形）。このページの手法ではない
- abc230_e（Fraction Floor Sum、diff 969）：Σ ⌊N/i⌋ で floor-quotient-enum の問題
- arc182_e（Sum of Min of Mod of Linear、diff 3098）・abc402_g（Sum of Prod of Mod of Linear、3381）・abc429_g（Sum of Pow of Mod of Linear、3295）・abc465_g（Sum of Mex of Mod of Linear、3082）・abc372_g（Ax + By < C、2925）：一次式の mod・格子点の問題だが、どれも 2900 を超えて帯（黄）から離れすぎる。解説を開いて手法を確かめてもいないので候補にしない（abc372_g は floor sum と下側の包絡線を組み合わせる問題として知られるが、未確認）

## 本文に足すときのメモ

- 練習は 0 問のまま。黄の帯で floor sum が要る AtCoder の問題は abc443_g（例題）のほかに見つからなかった。catalog の level_evidence・problems_note の見立て（「黄の帯で floor sum が要る ABC 問題は abc443_g くらい」）と一致する
- 練習の代わりとして、試作の検証の指摘 10 のとおり、Library Checker の sum_of_floor_of_linear（front matter の verify にある）を参考の節で「自作したコードの確かめ先」として挙げるのは一案（AtCoder の問題ではないので台帳には入れない）
- 検索の上限が戻った後に探し直すなら、「類ユークリッド」「floor_sum」と ARC・ABC の G・Ex を組み合わせた検索がよい。kmjp・betrue12 のブログ内検索は今回 HTTP 429 で取得できなかった
