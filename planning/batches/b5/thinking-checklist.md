# thinking-checklist の報告と提案（b5）

- 書いたファイル：docs/guide/thinking-checklist.md（コード片・SVG はなし。図は Mermaid のフローチャート 1 枚）
- front matter で変えたもの：complexity（「目安は 1 秒に 10^8 回前後（制約から計算量を逆算する節）」）・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、textlint エラー 0・警告 3（191・200・257 行の助詞の重なり。「最大か最小か」「〜なら…まで、…なら」など文の意味を変えずに直しにくいので残した）
- 構成：手引き §4 の hub に合わせ、「問題の形 → 試す問い → ページ」の表（shape-* と other-types）と、上から当てる問いの列（q-*）を本体にした。型の説明は考察の章と手法のページに任せ、リンク先はどれも draft のページの節の anchor（stub の stress-testing・reverse-index-signs・reverse-index-constraints・patterns/interval・patterns/permutation はページへのリンク）
- 問題：catalog の problems が空なので載せていない（hub は 0〜3 問）
- 使った出典：マイナビ出版の鉄則本の目次（6 章の節の題名）、kumonosu のアルゴリズム×数学の目次（5 章の節の題名）、Motsu_xe「解法キーアイデア集」、kmyk「競技プログラミングの問題の解き方、そのマニュアル」、algo-logic「競技プログラミングで解法を思いつくための典型的な考え方」
- 新しく noai を確かめたドメイン（どれも指定なし。付録 B への追加の提案）：book.mynavi.jp、kumonosu.cloudsquare.jp、gihyo.jp、motsu-xe.hatenablog.com、kmyk.github.io、algo-logic.info（chokudai.hatenablog.com も確かめたが使っていない）

## 台帳への提案

- なし（このページは問題を載せない）

## 用語集への提案

- なし。リンクしたのは既存の naive-solution・necessary-condition・invariant だけ
- 検討の余地：「十分条件」「必要十分条件」は本文で使ったが用語集にない。necessary-condition の項に「必要十分条件」の一文を足すとよい（語｜anchor｜定義の案：必要十分条件｜necessary-condition 内で説明｜条件を満たすことと答えが「はい」であることが同値になる条件。必要条件を並べて、それを満たすものが実際に作れると示すと得られる）

## 手引きへの提案

- §4 の hub の構成に「表で決まらないときに順にたどる問いの列」を置いてよいことを書くとよい（このページは表と問いの列の 2 段）。guide の type で hub の形を取るページの扱いも明記するとよい
- 問いの表の「試す問い」の列は疑問文（？で終わる）にした。表の中の疑問文を許すことを §6 か §7 に書くとそろう

## 問題の補充の候補

- なし（catalog の problems が空で、型ごとの例題は各考察のページにある）。もし入口に 1〜2 問置くなら、複数の問いを順に当てて解ける問題が向く。各考察のページの例題（contribution#abc186_d、invariant#abc125_d など）は持ち主が別なので、ここでは本文からの参照にとどめた

## 未解決の点

- 鉄則本 6.5「個数を考える」は節の題名だけでは中身が分からず、対応のページを「—」にした。本の該当節（例題）を確かめて、近いページ（数え上げの考え方・鳩の巣原理など）を決めたい
- アルゴリズム×数学 5.5「ギリギリを考える」と 5.8「上界を考える」の対応は題名からの推定（上界と構築・単調量）。5.4「集合を上手く扱う」も余事象に当てたが、包除原理まで含む可能性がある
- 00-curriculum §4.1 の「典型90問の考察・実装の15項目」は一次資料を確かめられず、対応表に入れていない
- design-review I・review/01-learner 指摘9 の「observation-hub の表を受ける」は、observation-hub が symmetry-pigeonhole-casework に改められているので、表を shape-* の節で持ち、thinking の章の先頭（thinking/index は生成）からの入口リンクはメインの判断に任せる
- contest-strategy#when-stuck の 5 段の手順と、このページの問いの列（8 段）は順序をそろえてある（誤読 → 制約 → 小さいケース → 言い換え → … → 一度離れる）。片方を直すときはもう片方も確かめる
- graph-modeling・contest-strategy・practice-method・cheatsheet は同じバッチで並行して直されている。節の anchor（what-to-vertex・what-to-edge・switching・when-stuck・when-to-read・records）が変わったら張り替えが要る
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 7 回

## 検証の指摘への対応（b5 直し）

- 直した：1（6.4 → 区間スケジューリング・貪欲法）、2（上界・下界の分け方と「0 以上の整数・1 以上減る」の条件）、3（$O(N\sqrt{N})$ 程度まで）、4（6.5 → map で数えながら走査する・二項係数）、5（6.9 → global-offset#flip-flag）、6（5.4 に包除原理、5.5 は候補の数で見積もるに「推定」と添えて当てる、5.8 は上界と構築だけ）、7（Mermaid の図を消し、表に任せた。前後の文も直した）、8（用語集の不変条件へのリンクの文を削除）、9、10、11、12、13（complexity を null に戻した）、14(a)（stress-testing#experiment に張り替え。reverse-index-constraints・patterns/interval・patterns/permutation へのリンクは、ページ全体を指す使い方なのでそのままにした）
- 出典に kyopro-tessoku・math-algorithm-book（GitHub）を足した（検証役が対応の根拠に使った解答のコード）。#book-mapping の「対応は…から決めた」に解答のコードを加えた
- 採らなかった：14(b)（アルゴリズム×数学の目次を技術評論社のページに替える）。この直しでは Web を取得しておらず、gihyo.jp の書籍ページに 5 章の節の題名が載っているかを確かめられないため。検証役が kumonosu の目次の内容を確かめて一致しているので、そのままにした。メインで gihyo.jp のページを確かめられれば差し替えたい
- 提案（メインへ）：related の stl-containers・game-basics は本文の別の節で引き続き使っているので残した。global-offset・interval-scheduling・inclusion-exclusion を related に足すかはメインの判断
- 提案（用語集）：「不変量」（操作で変わらない量）を「不変条件」とは別の語として足すとよい（anchor 案 invariant-quantity、定義案：操作を何回しても値が変わらない量。初めと目標で値が違えば目標に届かないことを示せる）
