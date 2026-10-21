# manhattan-chebyshev の報告（工程8b・バッチ b1）

- 書いたファイル：docs/geometry/manhattan-chebyshev.md、snippets/manhattan-chebyshev/{farthest-pair,chebyshev-sum,diamond-count,segtree-farthest}.{cpp,yaml}、docs/img/manhattan-chebyshev/{rotate,diagonal}.svg
- front matter で変えたもの：complexity（`変換は 1 点 O(1)。最遠点対 O(N)、全ペアの距離の和 O(N log N)、ひし形の範囲の点の数は前計算 O((H+W)^2)・1 回 O(1)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 定型でない見出しとして `## 必要になる場面 {#motivation}` と `## ACL では {#acl}` を置いた（sections には載せていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 片・期待と違う 0）、textlint（エラー 0・警告 29。数式を含む文の長さ、数式の中の半開区間 `[0, S)`・`[l, r)` を括弧の対応の誤りと見るもの、数式の中の読点、見出しの `r+c` の英字。いずれも誤検出か、数式を分けると読みにくくなるもの）
- コード片は 4 つとも main の中で全組の素朴な計算と assert で突き合わせている（cases に 1 点・空の範囲・座標 ±10^9 を含む）
- 図：静的な SVG 2 枚（ひし形 → 正方形と回転後の偶奇、盤面の斜めの番号）。描画の道具が手元になく、見た目は目で確かめていない。文字のはみ出しがないか、検証役に描画の確認を頼みたい
- 動く図：catalog の visual は priority 2（static）なので作らず、div も置いていない

## 使った出典

- drken ABC178 E：例題の方針（x+y と x−y の最大・最小）
- testcampus（zenn.dev）ABC366：例題の方針（x と y に分け、候補の範囲を全部計算してソートと二分探索）。merom686 ABC366 で x・y の独立と候補の範囲を確かめた
- merom686 ABC351：例題の方針（偶奇で分け、半分の和と差に直してソートと寄与）
- ikatakos ABC184・ABC437・ABC210・ABC476・ABC457・ABC377（どれも解説の部分だけ）、drken ABC330 F・ABC265 F：練習・力試しの方針
- ACL document_ja の segtree.md（ローカルの ~/lib/ac-library-master/document_ja/ で確認）
- 新しく noai を確かめたドメイン：なし（zenn.dev は付録 B にある）。cses.fi/book/book.pdf は check_noai で指定なしだったが、サイトが保守中で本文を読めなかったので出典には入れていない

## 台帳への提案

- abc476_f｜summary｜N×N のグリッドの各マスについて、全住民をそのマスに集めるときのチェビシェフ距離の総和を求める。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0919_abc476
- abc476_f｜approach｜「距離を縦の差・横の差の成分に分け、行ごとの前計算と四隅からの累積和で全マスの和を O(N^2) で求める」｜同上
- abc457_g｜summary｜時刻と位置で決まる N 個のリンゴを、速さ 1 以下で直線上を動くロボットで全部回収するのに要る最少の台数を求める。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0509_abc457
- abc437_f｜summary｜点の座標の更新と、番号が区間 [L, R] の点のうち与えられた点から最も遠い点までのマンハッタン距離を求めるクエリに答える。（今の summary には区間の指定が抜けている）｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1220_abc437
- abc377_f｜summary｜N×N の盤面で、M 個のクイーンのどれにも取られないマスの数を求める。（本文はこの形で書いたが、fix_problems は台帳から作るので台帳も直してほしい。今は「クイーンに取られないマスの数を求める。」）
- abc366_e｜evidence｜usaco.guide の 6 件（hashing・hashmaps・geo-pri・bitsets・interactive・random）はこの問題と無関係に見える（機械的に写ったものと思われる）。外して https://zenn.dev/testcampus/articles/27ae3c0e7917bc を足すとよい
- abc330_f｜title｜台帳の題名 `Minimize Bounding  Square` に空白が 2 つある。ap.py の値をそのまま写したものなら問題ないが、表示上は 1 つが自然（AtCoder Problems の題名どおりかを確かめたい）
- abc210_d・abc366_e・abc351_e・abc178_e・abc184_c・abc330_f・abc476_f・abc457_g・abc377_f・abc265_f｜checked｜2026-10-21｜各 evidence（と上の追加の URL）で問いと方針を確かめた
- abc265_f｜pages の approach（alternatives）｜「斜め方向の累積和で DP を高速化する（節 diamond-range）」は、ひし形を正方形にする 2 次元累積和ではなく、斜めの線分に沿った 1 次元の累積和である。本文では diamond-range の節の最後で「斜めの線ごとの累積和」として触れた。節の指定を外すか「（節 diamond-range の最後）」とするとよい

## 用語集への提案

- チェビシェフ距離｜chebyshev-distance｜2 点の座標の差の絶対値のうち大きい方 max(|Δx|, |Δy|)。キングが 8 方向に動くときの最小の手数に等しい。ページの用語の正規形（付録 A）にあり、用語集にもあるとよい
- マンハッタン距離｜manhattan-distance｜2 点の座標の差の絶対値の和 |Δx| + |Δy|。上下左右に 1 マスずつ動くときの最小の手数に等しい
- （本文では用語集へのリンクを張っていない。どちらもこのページが持ち主なので、用語集からこのページへ向けるだけでよい）

## 手引きへの提案

- §4 の technique の構成に「ACL では」があるが、§13.1 の定型の見出しの一覧に「ACL では」がない。本文から `[ACL では](#acl)` とリンクしたかったので `## ACL では {#acl}` を置いた。定型の見出しに `## ACL では {#acl}` を足すか、囲みだけにするかを決めてほしい
- 同じく「必要になる場面」の見出しの anchor（`{#motivation}` など）も定型にしてよいと思う

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- typical90_aj（036. Max Manhattan Distance（★5）、diff なし）：N 点と Q 個の問いで、指定した点から最も遠い点までのマンハッタン距離を答える。x+y と x−y の最大・最小の 4 通りの差。最遠点対の節の「ある点から最も遠い点」の練習によい（role 案：practice）｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/036.cpp （research 08 §に記載。今回は開いていない）
- abc127_e（E. Cell Distance、diff 1938）：グリッドから K マスを選ぶすべての選び方について、選んだマスの全ペアのマンハッタン距離の和の総和を求める。x と y を独立にして、差 d ごとの寄与を数える（role 案：practice。axis-independence）｜research 08 §1081 付近に記載。今回は裏付けの解説を開いていないので、追加するなら第三者の解説で確かめが要る
- arc103_b（D. Robot Arms、diff 2677）：発展。45 度回転で 2 軸を独立にして 2 の冪の腕で構成する。水のページには難しすぎるので、載せるなら challenge か advanced-geometry 側（https://drken1215.hatenablog.com/entry/2018/09/30/002900、research に記載。今回は開いていない）

## 未解決の点

- ABC366 E の制約（N・D・座標の上限）は第三者の解説に明記がなく、本文には具体的な数を書かなかった（候補の範囲は「座標の範囲から D だけ広げた範囲」と論理で書いた）
- ABC437 F の区間の与え方（1-indexed の閉区間か）は確かめられなかったので、練習の方針では触れていない
- ikatakos の ABC457 のページの題名は「E,F問題メモ」だが、WebFetch では G（Catch All Apples）の解説が読めた。ページの題名と中身の対応を検証役に見てほしい
- ABC476 F の方針は ikatakos のメモの要約の粒度でしか確かめていない（成分の分け方の細部は未確認）。本文の方針も同じ粒度にとどめた
- related の `reformulation` へは本文でリンクしていない（stub で、合う箇所がなかった）。`contribution`（stub）へは全ペアの差の和の箇所でページへリンクした

## 使用量の目安

- 道具の呼び出し：約 40 回。Web 取得：WebFetch 13 回（うち 1 回は保守中で失敗）、WebSearch 1 回、curl での題名の取得 12 件
