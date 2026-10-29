# guide-start の検証（バッチ minor-content）

- 検証した担当：guide-start（#4・#43・#44・#47・#48）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content、未 commit の差分を見た）。ファイルは直していない（この報告だけを書いた）。git は読むだけ
- 見たもの：Issue の本文（`gh issue view`）、担当の報告 guide-start.md、6 ファイルの差分（docs/index.md・docs/guide/roadmap.md・docs/guide/contest-strategy.md・docs/guide/thinking-checklist.md・docs/guide/reverse-index-signs.md・docs/start/how-to-use.md）と、その前後の節・リンク先
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/verify-guide-start（再計算 vcalc.py と出力 vcalc.out、textlint の結果、gen_site の差分 gencheck.txt、撮った画像）

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #4 トップの「制作中」 | 合格 | 0 |
| #43 ロードマップの「何回に何回」 | 合格 | 0 |
| #44 原因の分類を 4 つに | 合格 | 0 |
| #47 言い回しの表の群の分け方 | 合格 | 0 |
| #48 分布へのリンク先 | 合格 | 0 |

直しが要る点はない。担当の範囲の外で気づいたことを最後の節にまとめた（メインの判断）。

## #4 トップページの「制作中」（合格）

- 完了の条件：info の文が今の段階を表しており（「全ページに本文があり、全体の検証を済ませた。作者が目を通したページから順に完成にしていく。」は Issue の例どおり）、「準備中」「本文はまだない」がない。docs/index.md のほかの行にも「準備中」はない
- info そのものと題名「制作中」は残っており、s10 の決定（planning/batches/s10/decisions.md 42 行目）と合う。README 6 行目、how-to-use#stub の「いまは、すべてのページに本文がある」とも食い違わない。check_pages の集計も reviewed 353 である
- 表示：作業用フォルダへのビルドを幅 390px で、ライトとダークの両方で撮った（index-light.png・index-dark.png）。info は崩れない
- 直さなくてよい点：「完成」という段階は今は読者に見えないが、#9（page-template のグループ。段階と更新日の表示）で見えるようになる予定なので、今の文でよい（担当の判断してほしい点 3 と同じ見方）

## #43 ロードマップの「F を 4 回に 3 回」（合格）

### 計算し直した数

担当の recalc.py は読まずに、自分でスクリプトを書いた（vcalc.py）。データは .cache/atcoder-problems の problem-models.json・contest-problem.json（取得 2026-10-24T23:33）。対象は abc400〜abc480 の 81 回で、81 回とも A〜G の 7 問がそろう。解く確率は 1/(1+exp(−discrimination·(P − difficulty)))、時間は exp(slope·P + intercept) 秒である。

| P | 位置 | 中央値 | 平均 | 本文の言い方 | 判定 |
| ---: | --- | ---: | ---: | --- | --- |
| 1200 | E | 40.5% | 41.9% | 5 回に 2 回（40%） | 合う |
| 1600 | E | 80.3% | 75.7% | 8 割の回で落とさない | 合う（下の注） |
| 1600 | F | 34.4% | 33.6% | 3 回に 1 回 | 合う |
| 2000 | F | 75.9% | 65.5% | 3 回に 2 回ほど（3 回に 1 回は落とす） | 合う |
| 2000 | G | 14.8% | 21.1% | 5 回に 1 回ほど | 合う |

- Issue の数（F は中央値 0.76・平均 0.65、G は中央値 0.15・平均 0.21）と一致した
- discrimination は 81 回の全問題で同じ値（0.004479398673）なので、確率は difficulty について単調で、81 個（奇数）の中央値は「難しさが中央値の問題（D 821・E 1286・F 1744・G 2391）を解く確率」とちょうど一致する。6 つの P のすべてで一致を確かめた。足した断りの文の言い方は正しい
- 表のほかの値も一致した：A〜D は 41.6・30.2・22.0 分、A〜E は 72.3・55.6・42.7 分（78 回）、A〜F は P = 2000 で 70.1 分（71 回）、E・F の確率は 40.5・8.0／80.3・34.4／96.1・75.9%。「約 40 分」「約 55 分」「約 45 分」「約 70 分」もこれに合う。47〜50 行目の位置ごとの帯の割合（D 基礎 93%、E 水 59%・基礎 31%・青以上 10%、F 青 49%・水 26%・黄 19%・発展 6%、F の 75% が 2000 未満、G 黄 38%・発展 49%）も一致した

### 文の確かめ

- 76 行目の断りの文は、contest-strategy 86 行目と一字一句同じである（Issue の「contest-strategy と同じ形」を満たす）。80 行目の F の言い方も contest-strategy 90 行目と同じである
- 86 行目「G を解ける回は多くない」：参照先が「5 回に 1 回ほど」になったので、「まれにしか解けない」から弱めたのは妥当である
- サイト全体で「何回に何回」の言い方を探し、古い「4 回に 3 回」「7 回に 1 回」で F・G の到達を言う箇所は残っていない（atcoder-system 105 行目の「7 回に 1 回ほどは解けない」は difficulty より 400 高いレートの話で別物）。roadmap の summary・要点に F・G の数はない
- 「8 割の回」（P = 1600 の E）の注：平均は 75.7% で、10% 単位に丸めれば 8 割になるので、断りの文（「何回に何回」は平均から出した）と矛盾しない。直さなくてよい。厳密にしたいなら、roadmap 79 行目と contest-strategy 89 行目の両方を「4 回に 3 回」にそろえる（担当の判断してほしい点 2。どちらにしても 2 ページで同じ言い方を保つこと）

## #44 解けなかった原因の分類（合格）

- 2 ページの分類が「知識不足／気づけなかった／実装ミス／時間不足」の 4 つ・同じ順になった。次のどれとも名前・数・順が一致する：practice-method#records の表（127〜130 行目）、how-to-use 304 行目、claude/record-format.md の `cause`、claude/explain.md 52 行目、claude/project-instructions.md 18 行目、.claude/skills/record-problem（SKILL.md 35 行目・record_tool.py の CAUSES）
- 誤読の扱いが 1 文で書いてある（2 ページで同じ文「問題文の誤読は、読み直せば防げたミスとして実装ミスに含める。」）。2 ページに「考察不足」「誤読」の分類の語は残っていない（thinking-checklist#q-misreading などの「誤読を疑う」は考察の手順で、分類ではないので残ってよい）
- 実装ミスに含める判断は筋が通る：practice-method の表で実装ミスの「引くページ」は debugging-checklist で、その #partial の表（半分以上落ちる → 誤読）と #wa の「問題文の読み直し」が誤読を WA の原因として扱っている。表の「次にすること」の前半（ミスの種類を書く）も誤読に当てはまる。「気づけなかった」の「手法を連想させた条件を 1 文にする」は誤読には当てはまらない
- 記録の表から規則にたどれる：practice-method 132 行目が [コンテストの戦い方](contest-strategy.md#after-contest) へリンクしており、そこに 1 文がある。contest-strategy の手順 2 に足した「（記録の付け方と同じ 4 つ）」のリンク先 #records もビルドした HTML にある
- thinking-checklist の「どの条件から型を連想できたはずかを記録する」を「気づけなかった」のときだけにしたのは、practice-method の表の「次にすること」と合っており、前より正確になった
- 推奨（メインの判断。直しが要る点ではない）：担当の提案 1 に賛成する。誤読の規則は今は contest-strategy と thinking-checklist にしかないので、表の持ち主である practice-method#records にも同じ 1 文を足すとよい。claude.ai の解説（explain.md・project-instructions.md）と record-format.md に足すかは、記録の形の版も絡むのでメインに任せる

## #47 逆引き辞典（言い回しから）の群の分け方（合格）

- tools/gen_site.py を読んで確かめた：PHRASE_GROUPS（88 行目）を、b_signs_phrase（628〜635 行目）が `p.kind[0]` で引く（kind がなければ「案内」→そのほかの群）。「群は種類の 1 つ目だけで決まる」は正しい
- 例のページの kind と題名：tree-dp「木 DP」[DP, 木]、rerooting「全方位木 DP」[DP, 木]、dp-dag「DAG 上の DP」[DP, グラフ探索]。題名は付録 A の正規形と同じである。生成された表で数えると、tree-dp 4 行・rerooting 2 行・tree-dp-square 1 行・dp-dag 4 行がすべて探索・最適化の群（#signs-phrase-search）にあり、グラフ・木の群（#signs-phrase-graph）には 0 行だった
- 「DP の手法（種類の 1 つ目が DP のページ）」と限ったのは正しい。static-top-tree [木, DP, データ構造]・shortest-path-dag [最短路, DP]・expected-value-dp [確率・期待値, DP] は別の群にある
- リンク `#signs-phrase-search` は生成部分の見出しの anchor で、ビルドした HTML に id がある。43 行目の「ページの種類で 5 つの群に分けてある」とも合う。「kind の 1 つ目」は roadmap の生成部分（「ページの種類（kind の1つ目）」）と同じ言い方である（手書きの本文なので空白の入れ方は §7 に従っている）
- 表示：幅 390px・ダークモードで撮った（signs-byphrase-crop.png）。新しい段落とリンクは崩れない

## #48 位置ごとの difficulty の分布へのリンク先（合格）

- how-to-use 173 行目のリンク先が `atcoder-system.md#difficulty-by-position` になった。atcoder-system 153 行目の節に、箱ひげ図（difficulty-by-position.svg）と四分位の表（C〜G）があり、括弧の「箱ひげ図と四分位の表」は中身どおりである
- ビルドした HTML では `../atcoder-system/#difficulty-by-position` になり、リンク先に id がある。「は [AtCoder の仕組み]」の空白は §7（半角英字と全角文字の間に空白）に合う

## 検査

- `python3 tools/check_pages.py --page <id>`（roadmap・contest-strategy・thinking-checklist・reverse-index-signs・how-to-use）：どれもエラー 0・警告 0。全体の `check_pages.py` もエラー 0・警告 0（353 ページ、docs/index.md は本文の検査だけ）
- `npx textlint`（6 ファイル）：エラー 0・警告 20。HEAD の版（`git show HEAD:<ファイル>` を作業用フォルダに出し、同じ .textlintrc.json で検査）も同じ 20 件で、規則と位置が一致する（roadmap と reverse-index-signs は段落を足した分だけ 2 行ずれる）。新しい警告はない
- `git diff --check`：空白の誤りなし。全角の空白・タブもない。front matter の変更は 5 ページの `updated: 2026-10-29` だけで、stage などは変わっていない
- `python3 tools/gen_site.py --check --diff`（書かない）：14 ファイルが古いと出る。このうち guide-start の変更によるのは版（updated の最大が 2026-10-29 になること）だけで、docs/llms.txt の版の行・overrides/assets/data/graph.json の version と updated・how-to-use の「索引の版」の行に出る。ほかの差分（namori-graph の章と並び、monge のサイン、cht・alien-dp・segment-tree-on-values・segment-tree-monoids など）は同じ作業ツリーのほかの担当の変更による。直した本文は生成物の入力ではない。メインが gen_site.py を流せば済む
- ビルド：`uv run mkdocs build -q -d <作業用フォルダ>/site` は成功し、作業ツリーの git status は変わらなかった。直した 6 か所を HTML から抜き出し、リンク先の id（difficulty-by-position・records・signs-phrase-search・time-targets・targets）がすべてあることを確かめた。`python3 -m http.server`（ポート 37291、使い終えて止めた）で開き、幅 390px で撮った：トップ（ライト・ダーク）、roadmap #targets（ライト）、reverse-index-signs #by-phrase（ダーク）。崩れはない（roadmap の表がスマホで横にはみ出すのは前からで、#55 の範囲）
- 問題の行・コード片・図・動く図は触っていないので、fix_problems・check_snippets・check_svg・node のテストは対象外

## 範囲の外で気づいたこと（メインの判断。この検証の合否には入れない）

1. **contest-strategy.md 125 行目の著者名**：本文が「（blueberry1001 氏）」で、同じページの参考（227 行目）と roadmap（92・788 行目）は「bluebery1001」（Qiita の ID。URL も qiita.com/bluebery1001/…）。b5 の roadmap の検証（planning/batches/b5/verify/roadmap.md 31〜33 行目）で roadmap だけ直り、contest-strategy の本文が残ったものとみられる。Issue にはない。直すなら「（bluebery1001 氏）」にする 1 語の直しで、このバッチで contest-strategy を持つのは guide-start である
2. **roadmap 66 行目「表は abc400〜abc480 の 81 回について」**：確率は 81 回だが、時刻は A〜D が 81 回・A〜E が 78 回（contest-strategy 59・72 行目は回数を分けて書いている）。値は変わらない。担当の「残った点」と同じで、#43 の範囲の外
3. **計算した数字のスクリプト（手引き §16-13）**：tools/numbers/ がリポジトリにまだなく、roadmap・contest-strategy の数字（今回の平均の値を含む）にもスクリプトと「データから計算した値（日付）」がない。サイト全体の未整備で、今回の直しが新しく生んだものではない。作るなら、この報告の vcalc.py の計算（81 回の中央値・平均、時間のモデルがある回の中央値）がそのまま使える
