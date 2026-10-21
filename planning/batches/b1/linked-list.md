# linked-list の報告（工程8b・b1）

- 書いたファイル：docs/ds/linked-list.md、snippets/linked-list/insert-erase.{cpp,yaml}、docs/img/linked-list/insert-erase.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「上位の手法とのつながり（next-steps）」を足した
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（1件・4 case 一致）、textlint（エラー0、警告6：要点の summary の文・数式を含む文の長さと助詞の重なりで、規則の誤検出として残した）
- 使った出典：programming-hiroba.com（abc344_e）、torus711.hatenablog.com（abc344_e の制約・std::list と map）、zenn.dev（abc337_c）、kyo-pro.hatenablog.com（abc237_d）、qiita.com（abc455_d）、kazun-kyopro.hatenablog.com（abc225_d の候補）。どれも付録 B にある。新しく noai を確かめたドメインはない
- 動く図：作らない（visual は priority 2 の static）。静的な SVG を 1 枚置いた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc344_e | evidence | https://torus711.hatenablog.com/entry/2024/03/10/192517 を追加（制約 1 ≤ n, q ≤ 2×10^5・値は相異なり 10^9 まで、を明記している） | 同 URL |
| abc337_c | evidence | 今の zenn の記事は問題の要点が 1〜2 行だけで、入力の意味（A_i = −1 が先頭）を裏付けにくい。プロひろ https://programming-hiroba.com/abc337-c/ の追加を提案（検索結果で見つけた段階で、本文は未読） | 同 URL |

## 用語集への提案

- なし（番兵 `sentinel` は既存のものを使った）

## 手引きへの提案

- §13.1 は定型の「落とし穴 {#pitfalls}」を sections に載せないとするが、catalog では「使い分け（…）{#choosing}」「落とし穴（…）{#pitfalls}」が中身つきの題で sections に入っているページがある（linked-list・stl-containers）。sections の題のまま見出しにした。定型の節と sections の節の扱いを手引きで明記するとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc225_d（D. Play Train、diff 778） | 電車の連結・切り離しと、ある電車を含む編成を前から出力する質問（出力の総数 ≤ 10^6）。前後の電車を配列で持ち、質問では先頭まで戻ってからたどる | 練習（「列車の連結・切り離し」のサインの代表。本文の付け替えの節と「途中で x を含む列を出力」の段落にそのまま当たる） | https://kazun-kyopro.hatenablog.com/entry/ABC/225/D |

- ap.py で実在と diff を確認した（`OK abc225_d D. Play Train diff=778 茶/基礎`）
- 削除だけの列で「消す時点の左右の生き残り」を使う型（本文の「上位の手法とのつながり」）の例として abc140_e（Second Sum）を考えたが、連結リストで解く第三者の解説が見つからなかった（kmjp・ARMERIA・maspypy などは set・BIT）。提案しない

## 未解決の点

- abc455_d で「移す先 p が必ず山の一番上か」は、第三者の解説のコード（c の下とのつながりを切り p の上につなぐ）から読み取ったもので、明文では確かめていない。本文の一般の型では「一番上のカード p の上へ」と条件付きで書き、練習の方針では p の条件に触れていない
- abc237_d の操作（i を i − 1 のすぐ左か右に入れる）は、kyo-pro 氏の記事のコード（逆順に deque の両端へ足す）からの読み取りである
- SVG はレンダラーがなく、見た目を画像で確かめていない（座標は生成スクリプトで計算した。幅 720 に 5 節点が収まる）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 9 回（検索 3 回を含む）
