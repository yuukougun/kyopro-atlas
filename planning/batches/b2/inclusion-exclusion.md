# inclusion-exclusion の報告（b2）

- 書いたファイル：docs/comb/inclusion-exclusion.md、snippets/inclusion-exclusion/{none-divisible,derangement,surjection}.{cpp,yaml}、docs/img/inclusion-exclusion/venn-net-count.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 本・期待と違う 0）、textlint（エラー 0・警告 11。数式を含む文の長さ・数式の中の読点・数式の中の助詞・台帳の summary の「A も B も」で、§13-8 の誤検出として残した）
- 図：venn-net-count.svg を render_svg.py で 360px・720px の PNG にして目で確かめた
- 使った出典：drken（abc246_f・abc152_f）、kmjp（abc172_e・abc462_g）、kazun（abc297_f）、flkanjin.hatenablog.com（abc242_f）、qiita navel_tos（abc331_g）、ja.wikipedia.org（包除原理）
- 新しく noai を確かめたドメイン：flkanjin.hatenablog.com・ks2m.hatenablog.com・rogi52.hatenablog.jp（どれも noai・noimageai の指定なし。rogi52 はログインへ転送されて読めなかった。ks2m は abc242_f が途中までで使っていない）

## 動く図の仕様（priority 1。JS は作っていない）

- 置き場：`<div class="kp-viz" data-viz="inclusion-exclusion-venn" data-config='{"n": 30, "divisors": [2, 3, 5]}'>`（#general の節）
- 状態の列：(0) 全体 n を数える → (1) 各集合の大きさを引く → (2) 2 つの共通部分を足す → (3) 3 つの共通部分を引く。各段で、ベン図の 8 領域それぞれに「その時点で数えられた回数」と、その領域に入る数（1〜30 の該当する数）を出す。caption にその段で足し引きした値（30、−15−10−6、+5+3+2、−1）と累計（30・−1・9・8）を書く
- 最後の段で、外側の 8 個（1・7・11・13・17・19・23・29）だけが 1 回、ほかの領域が 0 回になることを強調する
- 本文の図の後の段落（「図の段の流れは次のとおりである。…」）は、この 4 段に合わせて書いた。JS を作るときに config と合わせて直してよい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc475_f | pages の inclusion-exclusion（practice） | このページでは使っていない。evidence の ikatakos が 503 で読めず、ほかの解説（chokudai.github.io の観戦記）は「最小の外接長方形が一意」「上下を決めて尺取り」と書くだけで包除に触れず、問いを確かめられなかった。問いと包除を使うかを確かめてから、載せるか外すかを決めてほしい | https://chokudai.github.io/atoco-cp/post/2026-09-12-abc475/ |
| abc331_g | evidence | https://qiita.com/navel_tos/items/9dd39a3c8e3f9f7010c7 を足す。今の evidence の kmjp は「n 回以内にそろう確率の包除と多項式の積」で解いており、min-max 包除の形ではない（同じ値になる式なので approach はそのままでよい） | 左の URL |
| abc242_f | evidence | https://flkanjin.hatenablog.com/entry/abc242 を足す（ikatakos が 503 で読めなかったため、こちらで方針を確かめた） | 左の URL |
| abc297_f | approach（inclusion-exclusion の行） | 「マスごとに長方形に入る確率を求め、入らない場合（選んだマスが上下左右のどれかの側に収まる）を 4 方向の包除で数える」。今の approach（長方形ごとに 4 辺の包除）でも解けるが、evidence の kazun はマスごとの方法で、本文の方針もそちらで書いた | https://kazun-kyopro.hatenablog.com/entry/ABC/297/F |
| abc152_f | checked | 2026-10-21（drken の解説で問いと方針を確かめた） | https://drken1215.hatenablog.com/entry/2020/01/26/164200 |
| abc172_e・abc246_f・abc462_g | checked | 2026-10-21（evidence で問いと方針を確かめた） | 各 evidence |

## 用語集への提案

- なし（popcount・lowbit・fixed-point は既存の anchor を使った）
- 候補（入れるかはメインの判断）：全射｜surjection｜集合 X のどの要素も、写像 f: Y → X のある要素の行き先になっていること。「各色を少なくとも 1 回使う塗り方」は玉の集合から色の集合への全射である

## 手引き・front matter への提案

- sections の `when-to-use`（使い分け：余事象・包除 DP・約数包除）は、§14-2 の趣旨では定型の `## 使い分け {#comparison}` に当たる。既存の anchor を変えないため今回は `{#when-to-use}` のまま中身の節として書いた。sections から外して `#comparison` にそろえるかはメインが決めてほしい（ほかのページからのリンクは今のところない）
- related に binomial-precompute・linearity-of-expectation を足すとよい（対称な和の前計算と、min-max 包除・ABC297 F の前提）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc003_4（AtCoder社の冬、diff 2033 参考値） | R×C の部屋の中の X×Y の区画に、机 D 個とロッカー L 個をすべて置き、区画の 4 辺それぞれに何かが置かれている配置の数を求める。4 辺の条件を 16 通り包除する（#symmetric の「4 辺の条件」の型の最小の例で、練習か本文の参照に向く。古い ABC なので、難しさは解説で判断してほしい） | https://torus711.hatenablog.com/entry/20131212/p1 |

## 未解決の点

- abc475_f は上のとおり確かめられず、練習から外した。練習は 2 問（abc152_f・abc297_f）になった
- abc172_e の制約（N, M の上限）は解説に明記がなく、本文に書いていない（計算量は O(M) とだけ書いた）
- frequency_evidence に abc456_g があるが、台帳にない（このページでは触れていない）
- min-max 包除の恒等式は自分で証明を書いた。出典は ABC331 G の解説（navel_tos）の式変形で、恒等式そのものの解説記事は参考に入れていない
- 撹乱順列の漸化式の説明（p_1 = j とし、p_j = 1 かどうかで分ける）は標準的な議論で、research/07 §4.3 の記述に従った

## 使用量の目安

- 道具の呼び出し約 40 回、Web 取得 15 回（うち 503 が 3 回）、検索 5 回

## 検証の指摘への対応

- 直すべき 1・2、直すとよい 3〜8・10・11 を直した。2 は「4 辺の条件」を #symmetric から外し、マスごとの上下左右の 4 条件として #bit-enumeration の末尾へ移した（練習の方針と同じ方法）。台帳の abc297_f の approach の直しは上の提案のとおり採ってほしい
- 5 はコード片に合わせて本文の和の添字を $j$ にし、色の番号は記号を使わない書き方にした
- 10 は bell-number のページと記号をそろえるため $S(n, k)$ のまま、「条件の集合の $S$ とは別の記号」と断った
- 採らなかったもの：9（`#when-to-use` を `## 使い分け {#comparison}` にそろえて確認問題の後へ移す）。sections と anchor の変更は生成された docs/index/comb.md（`inclusion-exclusion#when-to-use`）と理解度の鍵に関わるので、メインが決める。そろえるなら、sections から when-to-use を外し、見出しを `## 使い分け {#comparison}` にして確認問題の後へ移し、gen_site.py で索引を作り直す
