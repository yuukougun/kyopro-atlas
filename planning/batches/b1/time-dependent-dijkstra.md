# time-dependent-dijkstra（時刻で変わる辺の最短路）の報告

- 書いたファイル：docs/graph/time-dependent-dijkstra.md、snippets/time-dependent-dijkstra/{earliest-arrival,last-train,best-departure}.{cpp,yaml}、docs/img/time-dependent-dijkstra/fifo.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 3 本とも期待どおり、textlint エラー 0（警告 9：「に」「が」「は」の重複 8 件と、折りたたみの確認問題の行の文の長さ 1 件。数式を含む文や「時刻 $t$ に…に着く」の言い回しで、読みにくさは小さいと判断して残した）
- 使った出典：
  - https://miscalc.hatenablog.com/entry/2022/10/10/115348 （ダイクストラ法が使える 2 条件。新しいドメインの記事として check_noai で確かめた：noai・noimageai の指定なし。miscalc.hatenablog.com を付録 B に足すことを提案）
  - https://blog.hamayanhamayan.com/entry/2021/02/20/233838 （abc192_e）
  - https://www.cnblogs.com/Lanly/p/18032259 （abc342_e。負の数の割り算の注意もここの指摘と一致）
  - https://blog.hamayanhamayan.com/entry/2021/06/07/024520 （abc204_e）
  - 候補探しで https://programming-hiroba.com/abc319-e/ を読んだ（本文には使っていない）
- 図：静的な SVG 1 枚（catalog の visual は static・priority 2）。画像に描き出して目で確かめる手段（rsvg-convert など）が手元になかったので、座標の計算だけで配置した。検証のときに表示を確かめてほしい
- 事故の報告：`tools/fix_problems.py --page time-dependent-dijkstra --field graph` と打ったところ、`--field graph` で graph 分野の全ページが対象になり、ほかの執筆者の docs/graph/union-find-connectivity.md の 5 行（abc229_e・abc120_d・abc264_e・abc040_d・abc181_f）を台帳の形に書き換えてしまった。すぐに同じ 5 行を元の「- 問題ID：要約」の形に戻した（ほかの部分には触れていない）。そのページの執筆者が同時に編集していた場合は確かめてほしい

## 台帳への提案

- abc192_e｜summary｜「線路 i は K_i の倍数の時刻にだけ出発して T_i かかるとき、都市 X から都市 Y へ最も早く着く時刻を求める。」（末尾に「。」を足す。ほかの台帳の要約にそろえる。内容は変えない）
- abc342_e・abc204_e｜summary｜同じく末尾に「。」を足すかどうかをそろえる（台帳全体で句点の有無が混ざっている）
- abc204_e｜summary｜「時刻 t に出発すると通過に C + ⌊D/(t+1)⌋ かかる道路で、各都市で整数の時間だけ待てるとき、都市 1 から都市 N への最も早い到着時刻を求める。」（待てることが解き方の要なので、問いに含める。根拠：https://blog.hamayanhamayan.com/entry/2021/06/07/024520）
- abc192_e・abc342_e・abc204_e｜checked｜2026-10-21（evidence の解説で問いと方針を確かめた）

## 用語集への提案

- FIFO 性｜fifo-property｜時刻で変わる辺について、始点に早くいるほど終点にも早く（同時以前に）着けるという性質。到着時刻が出発時刻について減らないことで、待てる辺は必ず満たす。本文ではページの節（#fifo）へのリンクで済ませたので、用語集に載せるなら節へ誘導する形でよい

## 手引きへの提案

- §9 の `fix_problems.py --page <id>` の例に「`--field` を付けると分野の全ページが対象になる（自分のページだけなら `--page` だけ）」と一言足す。今回の事故の原因
- 付録 B に miscalc.hatenablog.com を足す

## 問題の補充の候補

練習が 1 問しかない（catalog の problems_note のとおり）。時刻で変わる辺を直接使う ABC の問題は、ap.py の題名検索（Train・Bus・Rush・時刻など）と第三者の解説で探した範囲では、次の 1 問だけが近い。

- abc319_e（E. Bus Stops、diff 1353）｜家からバス停を順に進み、バス停 i からは P_i の倍数の時刻に出るバスで T_i かかるとき、各クエリの出発時刻に対して会社へ最も早く着く時刻を求める｜役割の案：練習（[次の出発時刻まで待つ遷移](#wait)の切り上げと、分岐のない道で周期 840 を前計算する点。グラフの探索は要らないので、periodicity が持ち主になりそうなら、こちらは「使い分け」の参照だけにする）｜裏付け：https://programming-hiroba.com/abc319-e/ 、https://merom686.hatenablog.com/entry/2023/09/10/022053 （後者は検索結果に出ただけで未読）
- 参考：miscalc の記事は、同じ型の問題として TKPPC4-1 H「don't be late」（abc192_e とほぼ同じ）、abc170_f（Pond Skater。この形に落とし込むまでの考察が要る）、arc150_c を挙げている。abc170_f は ap.py で difficulty を確かめていない。台帳に入っているかと、このページの練習に向くかを確かめる価値がある（abc170_f は grid-graph や extended-dijkstra の持ち主の方が自然かもしれない）

## 未解決の点

- abc204_e の道路が有向か無向かを解説から確かめきれなかった（hamayan 氏の記事の要約では有向とも読めた）。本文では向きに触れないように書いた
- abc192_e の時刻の上限（`long long` が要る根拠）は解説のコードが `long long` を使っていることから判断した。制約の値そのものは確かめていない
- 本文の「時刻を状態に持つのは、時刻の幅が小さく FIFO 性が崩れる問題に限る」は一般論として書いた。例となる確認済みの問題はない
- 使用量の目安：道具の呼び出し約 40 回、Web 取得 6 回・検索 3 回
