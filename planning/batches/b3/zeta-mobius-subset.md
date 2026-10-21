# zeta-mobius-subset の報告（b3）

- 書いたファイル：docs/comb/zeta-mobius-subset.md、snippets/zeta-mobius-subset/transforms.{cpp,yaml}、snippets/zeta-mobius-subset/or-plus-max.{cpp,yaml}、docs/img/zeta-mobius-subset/cube-axes.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 本とも一致）、textlint（エラー 0・警告 11。数式を含む文の長さ・図の代替テキストの長さ・数式の中の読点と、「が」「で」の重複の誤検出に近いもの）
- 図：cube-axes.svg を render_svg.py で 360px・720px の PNG にして目で確かめた（2×2 の 4 枚。ラベルと矢印が重ならない）
- 動く図：作っていない（catalog の visual は static・priority 2 なので、静的な SVG で代えた）
- 使った出典：drken（arc100_c・abc213_g）、kmjp（abc295_h）、merom686（abc349_f の型）、convexineq（Qiita、h1 を確かめた）、Library Checker。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc295_h | summary | H×W のマス目の各マスが 0・1・? のどれかで与えられる。? を 0 か 1 に決める方法のうち、全部 0 のマス目から「ある行の左から何マスかを 1 にする」「ある列の上から何マスかを 1 にする」操作で作れるマス目になるものの数を、998244353 で割った余りで求める。 | https://kmjp.hatenablog.jp/entry/2023/03/26/0930 |
| abc295_h | approach | 列ごとに「上から 1 が途切れずに続いているか」を bit の集合で持つ DP。1 マスずつ更新すれば O(HW 2^W) | 同上。evidence の kmjp の解説はゼータ変換を使っていない（台帳の「上位集合のゼータ変換で速くする」は確かめられなかった） |
| abc295_h | pages | zeta-mobius-subset の challenge から外し、broken-profile-dp（または bit-dp）の challenge に移すことを検討 | 上と同じ。ゼータ変換を使う解法の第三者の解説が見つからなかった。本文では「1 マスずつの DP で変換なしに済む」と正直に書いて残した |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 高速ゼータ変換 | zeta-transform | 集合（または約数）を添字にした列から、各添字について部分集合（約数）にわたる和を、軸ごとの累積和として一度に求める変換。部分集合の版は O(n 2^n) |
| メビウス変換 | mobius-transform | ゼータ変換の逆。各軸の累積和を差分に戻す。和にだけ使え、max・min で累積したものは戻せない |
| OR 畳み込み | or-convolution | h(U) = Σ_{A∪B=U} f(A) g(B)。部分集合ゼータ → 各点の積 → メビウスで O(n 2^n) |

（本文では用語集へのリンクを張っていない。ページの題名が用語そのものなので、用語集からこのページへ送る形を想定）

## 手引きへの提案

- §5 comb に「ゼータ変換は和なら戻せるが、max・min（上位 k 個）で累積したものは戻せない」を約数・部分集合の 2 ページ共通の落とし穴として明記してはどうか（持ち主をどちらかに決める）
- 執筆の道具の注意：Python で `open(p, 'w').write(... + open(別のファイル).read())` と書くと、後者が見つからないときに先にページが空になる。執筆者向けの注意として §14 に足す価値がある（今回は git から骨格を戻した）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc349_f（Subsequence LCM、diff 2169） | 列から空でない部分列を選び、その lcm がちょうど M になる選び方の数。M の約数でない要素を除き、各要素を「指数が M と等しい素数の集合」の bit に潰して、部分集合ゼータ → 2 の冪 → メビウス変換で数える。本文の inverse の節の応用の型の代表。練習（practice）にしたい（このページには練習がない） | https://merom686.hatenablog.com/entry/2024/04/14/011833 （本文を読んで確かめた）、https://www.cnblogs.com/MoyouSayuki/p/18134468 （未読） |
| abc215_h（Cabbage Master、diff 3101） | 台帳では dilworth-path-cover の練習。Hall の定理の条件を全部の部分集合で確かめるのにゼータ変換を使う。発展なので力試しの候補にとどまる | https://kmjp.hatenablog.jp/entry/2021/08/22/0930 （台帳の evidence。今回は読んでいない） |

- ABC の青〜黄の帯で、ゼータ変換が主役になる問題は見つからなかった（catalog の problems_note と同じ）。b2 の divisor-inclusion-exclusion・zeta-mobius-divisor の提案にも abc349_f があるので、まとめて台帳に足すとよい

## 未解決の点

- abc295_h がこのページの力試しにふさわしいか（上の台帳への提案）
- 練習の囲みがない（確認済みの問題がない）。abc349_f が台帳に入れば `## 練習問題 {#practice}` を足す
- related の hadamard-transform・counting-labeled-graphs・chromatic-number は stub なので、節ではなくページへリンクした
- 部分集合の畳み込み（ランク付きゼータ、O(n^2 2^n)）は vs-xor の節で 1 段落だけ触れた。持ち主のページがないので、発展のページを作るか、subset-enumeration-dp#vs-zeta の記述とどちらに寄せるかを決めてほしい

## 検証の指摘への対応（b3 直し）

- 直したもの：1（「いつ使うか」の「。」を消した）、3（inverse の「$T$ の要素だけを使う数」に揃えた）、4（lcm の帰着に「$M$ の約数でない要素を除いてから」を足した）、5（部分集合の畳み込みの手順を「要素数ごとに変換 → 各点で $\sum_{a+b=k}$ → 逆変換 → 要素数 $k$ だけ取る」と書き、dp の形は要素数の小さい層から順に求めると添えた）、6（or-plus-max.cpp を `top2_zeta`（印 `top2`）と `or_plus_max`（印 `answer`）に分け、`core` は両方を囲むまま。top-two の節は `top2` だけ、例題は `core` を取り込む）、7（cube-axes.svg の 2 進ラベルを 13 → 15 にし、360px で重なりがないことを確かめた）、8（`\hat{\mathrm{cnt}}` を `\widehat{\mathrm{cnt}}` に、同じ理由で `\check{\mathrm{cnt}}` を `\widecheck{\mathrm{cnt}}` に）、9（「値が $2^{20}$ 未満なら」）
- 採らなかったもの：2（abc295_h を力試しから外す）。台帳 `data/problems.yaml` の pages にこのページの challenge として載っており、ページから外すと台帳と食い違う。台帳は共有ファイルなので書けない。移す先（broken-profile-dp か bit-dp）と台帳の approach の直しはメインの判断に任せ、本文は今の「変換を使わずに済む」の正直な記述のまま残した

## 台帳への提案（直しの追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc295_h | pages | `{id: zeta-mobius-subset, role: challenge}` を外し、broken-profile-dp（または bit-dp）の challenge にする。外したら本文の力試しの囲みと方針の行も消す | 検証の指摘 2（kmjp の解説はゼータ変換を使わない O(HW 2^W) の DP） |
| abc295_h | approach | 上の報告の「列ごとに上から 1 が途切れずに続いているかを bit の集合で持つ DP。1 マスずつ更新すれば O(HW 2^W)」 | 同上 |
| arc100_c・abc213_g・abc295_h | checked | 2026-10-21 | 検証役が drken（arc100_c・abc213_g）・kmjp（abc295_h）の解説で内容を確かめた |
| abc349_f | 新しい行（practice） | 上の「問題の補充の候補」のとおり。入ったら本文に `## 練習問題 {#practice}` を足す | merom686 の解説（検証役も読んで確かめた） |
