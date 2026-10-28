# guide-start の報告（バッチ minor-content）

- 担当の Issue：#4・#43・#44・#47・#48
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content）。git は読むだけで、commit などはしていない
- 直したファイル：docs/index.md、docs/guide/roadmap.md、docs/guide/contest-strategy.md、docs/guide/thinking-checklist.md、docs/guide/reverse-index-signs.md、docs/start/how-to-use.md
- front matter：本文を直した 5 ページ（roadmap・contest-strategy・thinking-checklist・reverse-index-signs・how-to-use）の `updated` を 2026-10-29 にした。stage とほかの項目は変えていない。docs/index.md には front matter がない
- 生成物（gen:begin〜gen:end の中）には触れていない

## #4 トップページの「制作中」の説明（完了）

- **場所**：docs/index.md 6 行目（info「制作中」の本文）
- **直した内容**：「多くのページは『準備中』で…本文はまだない」を、「このサイトは制作中である。全ページに本文があり、全体の検証を済ませた。作者が目を通したページから順に完成にしていく。」にした。info そのものと題名「制作中」は残した（s10 の決定）
- **確かめたこと**：「準備中」「本文はまだない」の語がなくなった。README 6 行目（全ページを書き終え、全体の検証を済ませ、作者が目を通したページから「完成」にしていく）と、how-to-use#stub の「いまは、すべてのページに本文がある」と合う。全ページの stage が reviewed であることは `check_pages.py` の集計（reviewed 353）で確かめた。作業用フォルダへのビルドを幅 390px で撮り、info が崩れずに出ることを見た
- **残った点**：下の「判断してほしい点」の 3 を参照（読者には段階が見えない）

## #43 ロードマップの「F を 4 回に 3 回」（完了）

- **場所**：docs/guide/roadmap.md 76〜80 行目（#targets の表の後）と 86 行目（#yellow の第 1 段落）
- **直した内容**
  - 76 行目に、contest-strategy 86 行目と同じ形の断りを足した：「解く確率の列は『難しさが中央値の問題を解く確率』で、そのまま『何回に何回解けるか』ではない。回ごとの見込みは 81 回の確率の平均で言う方がよく、下の『何回に何回』は平均から出した。」
  - 80 行目（黄）：「F を 4 回に 3 回解く。G を解くのは 7 回に 1 回ほど」→「F は 3 回に 2 回ほど解ける（3 回に 1 回は落とす）。G を解くのは 5 回に 1 回ほどである」。F の言い方は contest-strategy 90 行目と同じにした
  - 78 行目（水）：「E は 5 回に 2 回解く」→「解ける」（contest-strategy 88 行目と同じ言い方。数は変えていない）
  - 86 行目：「[到達の目安](#targets)のとおり G はまれにしか解けない」→「G を解ける回は多くない」。参照先が「5 回に 1 回ほど」になり、「まれ」では強すぎるため。数を繰り返さないのは b5 の検証の指摘 7 に合わせた
- **確かめたこと**：contest-strategy#time-targets に書いてある方法（解く確率は 1/(1+exp(−discrimination·(P − difficulty)))、時間は exp(slope·P + intercept)、abc400〜abc480 の 81 回）で、.cache/atcoder-problems/problem-models.json（取得 2026-10-24）と contest-problem.json から計算し直した（作業用フォルダの recalc.py。結果は recalc.out）

  | P | 位置 | 中央値 | 平均 | 本文の言い方 |
  | ---: | --- | ---: | ---: | --- |
  | 1200 | E | 40.5% | 41.9% | 5 回に 2 回（40%） |
  | 1600 | E | 80.3% | 75.7% | 8 割の回（下の判断してほしい点 2） |
  | 1600 | F | 34.4% | 33.6% | 3 回に 1 回 |
  | 2000 | F | 75.9% | 65.5% | 3 回に 2 回ほど（67%）、3 回に 1 回は落とす |
  | 2000 | G | 14.8% | 21.1% | 5 回に 1 回ほど（20%） |

  - Issue の数（F 中央値 0.76・平均 0.65、G 中央値 0.15・平均 0.21）と一致した
  - discrimination は 81 回の全問題で同じ値（0.004479…）なので、解く確率の中央値は「難しさが中央値の問題を解く確率」とちょうど一致する（E 1286・F 1744・G 2391 での確率が上の中央値と同じ）。断りの文の言い方は正しい
  - 表のほかの値も再計算と一致した：A〜D／A〜E は 1200 で 41.6／72.3 分、1600 で 30.2／55.6 分、2000 で 22.0／42.7 分、A〜F は 2000 で 70.1 分。contest-strategy の表（1000〜2000 の各行、A〜C の約 20 分・約 9 分、回数 81・78・74・49・71）も一致した
  - contest-strategy の「何回に何回」（88〜90・119・124 行目）はすでに平均から出した値で、直す必要はなかった
- **残った点**：66 行目の「表は 81 回について」は、A〜E の時刻だけ時間のモデルがある 78 回の中央値である（contest-strategy は 78 回と書いている）。値は変わらず、担当の範囲（78 行目付近）の外なので直していない

## #44 解けなかった原因の分類を 4 つに（完了）

- **場所**：docs/guide/contest-strategy.md 207 行目（#after-contest の手順 2）、docs/guide/thinking-checklist.md 265 行目（#q-step-away の「終わった後に」）
- **直した内容**
  - 2 ページとも、分類を「知識不足／気づけなかった／実装ミス／時間不足」（thinking-checklist は「・」区切り）にした。順は practice-method#records の表と同じ
  - 誤読の扱いを 1 文で書いた：「問題文の誤読は、読み直せば防げたミスとして実装ミスに含める。」
  - 「考察不足なら…」を「『気づけなかった』なら…」にした。thinking-checklist は「『気づけなかった』なら、どの条件から型を連想できたはずかを記録し、同じ型で続くなら、その型の行から考察の章のページを読み直す」にまとめた
  - contest-strategy の手順 2 に [記録の付け方](practice-method.md#records) へのリンクを足し、同じ 4 つであることを示した（thinking-checklist には前からある）
- **誤読を実装ミスに含めた理由**：誤読は知識や考察の力の不足ではなく、確かめれば防げたミスで、記録で傾向を見るときも「正確さ」の側にまとまる方が次の行動につながる。実装ミスの「引くページ」である debugging-checklist は、#partial の表（サンプルで落ちる・半分以上落ちる）と #wa の「問題文の読み直し」で誤読を WA の原因として扱っている。表の「次にすること」（ミスの種類を書く）とも合う
- **確かめたこと**：practice-method#records の表、claude/record-format.md の cause、claude/explain.md 52 行目、claude/project-instructions.md 18 行目（8 番目の項目）、.claude/skills/record-problem の CAUSES、how-to-use 304 行目がどれも同じ 4 つの名前であることを確かめた。2 ページに「考察不足」「誤読／」の分類の語は残っていない（thinking-checklist の #q-misreading など、考察の手順としての「誤読を疑う」はそのまま）

## #47 逆引き辞典（言い回しから）の群の分け方（完了）

- **場所**：docs/guide/reverse-index-signs.md 79 行目と、5 つの群の箇条の後に足した 87 行目
- **直した内容**
  - 79 行目：「行はページの分野で」→「行はページの種類（kind の 1 つ目）で」
  - 87 行目（新しい段落）：「群は種類の 1 つ目だけで決まる。そのため DP の手法（種類の 1 つ目が DP のページ）は、対象が木やグラフでも[探索・最適化の群](#signs-phrase-search)にある。たとえば木 DP・全方位木 DP・DAG 上の DP の行は『グラフ・木』の群にはないので、木やグラフの問題では両方の群を見る。」
- **確かめたこと**
  - tools/gen_site.py の PHRASE_GROUPS（88 行目）と b_signs_phrase（`p.kind[0]` で群を選ぶ）を読んだ
  - tree-dp・rerooting・tree-dp-square の kind は [DP, 木]、dp-dag は [DP, グラフ探索] で、生成された表ではこの 4 ページの行（4・2・1・4 行）がすべて「探索・最適化」の群にあり、「グラフ・木」の群に 0 行であることを数えた
  - 「DP の手法」と言い切らず「種類の 1 つ目が DP のページ」と括弧で限ったのは、DP を 2 つ目以降に持つページ（static-top-tree [木, DP, …]・shortest-path-dag [最短路, DP]・expected-value-dp [確率・期待値, DP] など）は別の群にあるため
  - 「kind の 1 つ目」の言い方は、roadmap の生成部分（「ページの種類（kind の1つ目）」）と種類別の一覧（「手法の種類（kind）」）に合わせた。リンク先の anchor `#signs-phrase-search` は生成部分の見出しにあり、check_pages とビルドした HTML で確かめた
  - 43 行目の「言い回しの表は、ページの種類で 5 つの群に分けてある」とも合う

## #48 位置ごとの difficulty の分布へのリンク先（完了）

- **場所**：docs/start/how-to-use.md 173 行目
- **直した内容**：「位置ごとの詳しい分布は[コンテストの戦い方](../guide/contest-strategy.md#difficulty-by-position)にある」→「位置ごとの詳しい分布（箱ひげ図と四分位の表）は [AtCoder の仕組み](atcoder-system.md#difficulty-by-position)にある」
- **確かめたこと**：atcoder-system.md 153 行目の `## 位置ごとの difficulty {#difficulty-by-position}` に箱ひげ図（difficulty-by-position.svg）と四分位の表がある。リンクは check_pages で検査され、ビルドした HTML で `../atcoder-system/#difficulty-by-position` になることを見た

## 検査

- `python3 tools/check_pages.py --page <id>`（roadmap・contest-strategy・thinking-checklist・reverse-index-signs・how-to-use）：どれもエラー 0・警告 0。全体の `check_pages.py` もエラー 0・警告 0（docs/index.md は本文の検査だけ）
- `npx textlint`（直した 6 ファイル）：エラー 0・警告 20。警告は 20 件とも HEAD の版にもあるもの（同じ規則・同じ位置。roadmap と reverse-index-signs は段落を足した分だけ 2 行ずれる）で、直した行には出ていない。内訳：index.md 3 行目（助詞「に」）、roadmap 786（「！」の連続。参考の題名）、contest-strategy 59・74（文の長さ）と 138・152・153×2・154・160・172・188（助詞の重なり）、thinking-checklist 176・185・242（助詞）、reverse-index-signs 1249（文の長さ）、how-to-use 136・189（助詞）・217（かっこの対応）・357（文の長さ）
- `python3 tools/gen_site.py --check`：生成物が古いと出る。私の変更によるものは版（入力のハッシュと updated の最大 2026-10-29）だけで、docs/llms.txt・overrides/assets/data/graph.json・how-to-use の version の生成部分に出る。ほかの差分（basics・dp の索引、reverse-index-constraints・reverse-index-signs の生成部分、roadmap の列）は同じ作業ツリーのほかの担当の変更による。メインが gen_site.py を流せば済む
- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`）：成功。直した 6 か所の HTML を抜き出して見た。トップは幅 390px で撮って info の表示を確かめた
- 問題の行・コード片・図は触っていないので、fix_problems・check_snippets・check_svg は流していない

## 提案（メインが共有のファイルに反映するもの）

1. **誤読の扱いを記録の側にもそろえる**：practice-method#records の表の下（「原因が重なるときは、いちばん大きいものを選ぶ。」の後）に「問題文の誤読は、読み直せば防げたミスとして実装ミスに含める。」を足す。claude.ai の解説と記録用スキルが同じ分け方をするよう、claude/explain.md 52 行目・claude/project-instructions.md 18 行目（8 番目の項目）・claude/record-format.md の cause の行にも同じ 1 文を足す（値の種類は変わらないので形の版は上げなくてよいと考えるが、record-format は「形を変えたら版を上げる」とあるので判断を任せる）

## メインに判断してほしい点

1. **誤読をどれに含めるか**：実装ミスに含めた（理由は #44 の節）。「気づけなかった」に含める考え方もある（thinking-checklist の最初の問いが「誤読を疑う」で、表の「気づけなかった」の引くページがそれである）。変えるなら 2 ページの 1 文を差し替えるだけで済む
2. **P = 1600 の E「8 割の回で落とさない」**：平均は 75.7% で、10% 単位に丸めれば 8 割、回数で言えば「4 回に 3 回」である。中央値（80.3%）とも読めるが、roadmap と contest-strategy の両方が同じ言い方なので、そろえたまま残した。厳密にするなら両ページを「4 回に 3 回」にする
3. **トップの info の「完成」**：段階（検証済み・完成）は読者に見える場所がなく、how-to-use#stub も「準備中」だけを説明している。info の文はこのままでも読めるが、「完成」の意味を how-to-use#stub に 1 文足すか、info からそこへリンクするかはメインの判断に任せる
