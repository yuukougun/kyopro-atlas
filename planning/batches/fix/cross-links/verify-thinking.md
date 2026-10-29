# verify-thinking の報告（バッチ cross-links）

- 検証した担当：thinking（報告は planning/batches/fix/cross-links/thinking.md）
- Issue：#65・#70（`gh issue view` で読んだだけ。コメント・編集・クローズはしていない）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links）。ファイルは直していない（書いたのはこの報告だけ）。git は読むだけ
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/verify-thinking（ビルド site/、撮影 shots/、描画後の DOM dom/、直す前の写し head/、textlint の比較、直し方の案を試した写し trial/、gen_site の差分 gen-diff.txt）

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #65 考察の章と発想リスト（本文の部分） | 合格 | 0（考察の章の入口の 1 行は gen_site の側で、この担当の範囲外） |
| #70 重なる説明の持ち主 | 直しが要る | 1（comb/permutation-cycles。担当のファイルの外） |

## 直しが要る点

### 1. #70 comb/permutation-cycles#vs-adjacent が、隣接 swap の最小回数の証明を繰り返している（必須。担当のファイルの外）

- **場所**：docs/comb/permutation-cycles.md 97 行目（`## 隣接 swap（転倒数）との違い {#vs-adjacent}` の最初の段落）
- **理由**：
  - 「隣接 swap 1 回では転倒数がちょうど 1 だけ変わるので、転倒数より少ない回数ではソートできない。逆に、ソートされていなければ $P_i > P_{i+1}$ となる隣り合う組があり、それを swap すれば転倒数は 1 減るので、転倒数の回数で足りる。」は、下限と作り方の 2 方向を書いた証明である。持ち主 ds/inversion-number#adjacent-swaps（96 行目）と同じ構成である。今回 reformulation#operations から消した 2 文（直す前の 142 行目）ともほぼ同じ文で、Issue の背景が「同じ証明を書き」と挙げた形そのものである
  - リンクは `[転倒数](../ds/inversion-number.md)` でページの先頭を指していて、持ち主の節 #adjacent-swaps を指していない
  - そのため、完了の条件「上の 3 つの考え方のそれぞれで、証明を書くページが 1 つになり、ほかのページはその節へリンクしている」を、隣接 swap の考え方がまだ満たさない。担当の報告は「3 つのどれも、証明を書くページは持ち主の 1 つになり…（完了の条件）」としているが、持ち主でないページの一覧（patterns/permutation 103・comb/permutation-parity 74 ほか）にこのページが入っていない
  - docs/ を「転倒数」「隣接 swap」「バブルソート」で grep した。隣接 swap の最小回数に触れるほかのページは、どれも 1 文の理由か結論だけである（patterns/permutation 103・comb/permutation-parity 74・thinking/invariant 101・guide/method-comparison 384・458・guide/thinking-checklist 107・232）。2 方向とも書いているのはこのページだけである
- **直し方の案**：2 文を 1 文の理由に縮め、リンクを持ち主の節にする。新しい reformulation 142 行目と patterns/permutation 103 行目と同じ形になる。表・偶奇の段落・anchor は変えない（guide/method-comparison 384 行目が #vs-adjacent を指している）。front matter の updated を 2026-10-29 にする。作業用フォルダの trial/permutation-cycles-97.md で textlint を通した（エラー・警告とも 0）。

  > swap できるのが隣り合う 2 要素だけなら、ソートの最小回数は巡回では決まらず、[転倒数](../ds/inversion-number.md#adjacent-swaps)（$i < j$ かつ $P_i > P_j$ となる組の数）になる。隣接 swap 1 回で転倒数はちょうど 1 だけ変わり、ソートされていなければ隣り合う転倒した組を swap して 1 減らせるからである。隣接 swap は任意の swap の特別な場合なので、任意の swap の最小回数は転倒数以下になる。

- **頼み方**：このファイルは担当の 11 ファイルに入っていない。同じ作業ツリーのほかの担当も触っていない（git status に出ない）。メインが担当のファイルに足して直させるか、バッチの終わりに直す。Issue の範囲を「basics と thinking の重なり」に限ると判断するなら、pull request は `Closes #70` ではなく `Refs #70` にする

## Issue ごとに確かめたこと

### #65 考察の章と「詰まったときの発想リスト」を行き来できるようにする（本文の部分は合格）

**完了の条件 1（9 ページから 1 クリックで発想リストへ）**：9 ページすべての本文に、guide/thinking-checklist の節へのリンクがある。リンク先の anchor は front matter の sections にあり、strict のビルドが通る。本文で引いている表の名前は、見出しの文字と同じである。表には、どれもそのページの節を指す行がある。

| ページ | 置き場 | 行き先の表 | 表の中のそのページの行 |
| --- | --- | --- | --- |
| complement | 使い分け 143 | shape-count「個数を数える」 | whole-minus-complement・two-conditions |
| contribution | 使い分け 163 | shape-sum「総和を求める」 | swap-roles・sort-signs・digits-divisors・max-min-count |
| fix-variable | 使い分け 149 | shape-count と shape-optimize「最大・最小」 | fix-middle・fix-maximum |
| reformulation | 使い分け 249（既存） | q-rephrase | separate-indices・independence・operations |
| invariant | 合図の段落の末尾 46 | shape-operation「操作できるか・最小回数」 | necessary-and-sufficient・monovariant・order-independence |
| parity | 合図の段落の末尾 48 | shape-operation | exactly-k |
| reverse-thinking | 合図の段落の末尾 45 | shape-operation | undo-last・delete-to-add |
| construction | 合図の段落の末尾 46 | shape-construct「1 つ作る（構築）」 | small-cases・necessary-conditions・bound-and-construct・checker |
| symmetry-pigeonhole-casework | 合図の段落の末尾 47 | other-types「ほかの型の行き先」と shape-sum | pigeonhole・casework・symmetry |

- 「使い分けに足す。なければ導入の末尾」の置き方は Issue のとおりである。invariant・parity・reverse-thinking・construction・symmetry-pigeonhole-casework には `## 使い分け` がない（見出しを数えて確かめた）
- 使い分けに足した 3 項目は、同じ箇条のほかの項目と同じく句点なしである（§15-2）
- 考察の章の入口（docs/thinking/index.md。生成物）には、まだ発想リストへのリンクがない。tools/gen_site.py はこの作業ツリーで変わっていない。担当の報告のとおり範囲外なので、この担当の指摘にはしない。`Closes #65` にするには、gen_site の 1 行が同じ pull request に入っている必要がある（入らなければ `Refs #65`）

**完了の条件 2（9 ページの導入に合図の文）**：9 ページとも、導入の段落の次（最初の `##` より前）に「使える合図は 3 つある。…である。」の段落がある。ビルドした HTML でも各ページに 1 つずつある。合図が問題文の言い回しかどうかと、ページの手法・front matter の signs・要点の「いつ使うか」と合うかを、1 つずつ確かめた。

| ページ | 合図 | 対応する節・signs |
| --- | --- | --- |
| complement | 「少なくとも 1 つ含む」「1 つでも満たす」・「A でも B でもない」・「すべて異なる」 | signs の 3 行。「すべて異なる → どこかが等しい」は whole-minus-complement の表（67 行目）と練習 ABC455 E |
| contribution | 「すべての組（区間）について」の総和・「区間の最小値」「2 番目に大きい値」・$N \le 2 \times 10^5$ | signs の 4 行。max-min-count（135 行目）と力試し ABC140 E |
| fix-variable | 「$i < j < k$ を満たす組の数」・「$A_i + A_j$ が $M$ の倍数」・「選んだ値の最小値 × 個数」 | fix-middle・fix-parts の余り・fix-maximum の最小の例（105 行目） |
| invariant | 「0 回以上好きな回数行える」・「$B$ にできるか」「最後に残る値の最大値」・「操作できなくなるまで繰り返す」「最小の操作回数」 | signs の 2 行と monovariant |
| parity | 「ちょうど $K$ 回の操作で」「時刻 $t$ に」・「上下左右に 1 マス動く」・「2 つの値の和が偶数」 | exactly-k・alternating・例題 ARC089 C（時刻 $t_i$）・components |
| reformulation | 「区間の和が $M$ の倍数」・「平均が $x$ 以上」・「区間に 1 を足す」「隣と入れ替える」の最小回数 | 一覧表の行と operations |
| reverse-thinking | 「$i$ の倍数番目の和」・「結果から操作列を求めよ」・「辺を削除する」「区間を塗る」 | decide-from-back（例題 ABC134 D）・undo-last・delete-to-add。「依存の向き」の説明は 59 行目に残っている |
| construction | 「1 つ出力せよ（なければ −1）」・「$N - 1$ 回以下の操作で」・自然な上界 | signs の 3 行。bound-and-construct |
| symmetry-pigeonhole-casework | 「$i < j$ の組すべてについての積の和」・「余りが等しい 2 つ」・$N = 1$ を許す制約 | symmetry（例題 ABC177 C）・pigeonhole（例題 ABC200 D）・casework |

- どのページも、3 つのうち 2 つ以上が問題文の言い回しを「」で引いている。残りの 1 つは制約の形（contribution・symmetry）か状況（construction の上界）である。手引き §2.2 の「問題文の言い回し・制約の形・立てた式の形」に収まる。手法名は入っていない
- front matter の signs・要点と食い違う合図はない。reformulation の合図は signs（独立に分解など）と別の組を選んでいるが、どれも一覧表の行にあり、矛盾しない
- 読点は各文 3 個以下で、textlint の新しい警告はない（下の検査）

### #70 basics と thinking で重なる説明の持ち主を決める（直しが要る：1）

**持ち主の節に証明がそろっているか**

- 区間加算の最小回数：basics/difference-sequence#min-operations。$+1$ だけの型の下限と作り方（83 行目。終える本数が足りなくなることはないことまで）、$\pm 1$ の型（85 行目）、長さ $K$ の型の可否と最小回数（87〜90 行目）がある
- 隣接 swap の最小回数：ds/inversion-number#adjacent-swaps。2 つの事実、下限、作り方、等しい値の扱いがある（91〜98 行目）。証明の本文は変わっていない（差分は 96 行目の末尾に 1 文を足しただけ）
- 片方を固定して数える：何を固定するかとその正しさ（重複と漏れがない理由）は thinking/fix-variable#fix-middle・#fix-parts・#fix-maximum にある。二分探索で相手を数える理由は basics/binary-search#fix-one-side（132 行目）、分け目の手順は basics/brute-force#half-enumeration にある

**縮めた側から正しい節へリンクしているか**

- reformulation 138 行目 → difference-sequence#min-operations。リンクの文字は見出しと同じである。結論の「両端の外を 0 として差分を取ったときの正の差分の和」は、持ち主の式 $\sum_{i=0}^{N} \max(d_i, 0)$ と手引き §5 の basics の項目（両端の外も含めて $N + 1$ 個）に合う。消した確認問題の例 $a = (1, 3, 2, 2, 4)$ で計算し直すと、$d = (1, 2, -1, 0, 2, -4)$ で正の和は 5 になる
- reformulation 142 行目 → inversion-number#adjacent-swaps。理由の 1 文「1 回の隣接 swap で転倒数は高々 1 しか変わらず、…ちょうど 1 減るからである」は正しい。invariant 101 行目・patterns/permutation 103 行目と同じ書き方になった
- reformulation 140 行目 → basics/imos#range-flip（見出し「区間反転を切り替え点 2 つで表す」。節の中身は切り替え点の XOR）
- reformulation 65 行目（表）→ difference-sequence#to-point-operations。表のほかの行と同じく手法のページを指す。表から #operations へのリンクがなくなった分は、75 行目の「（[操作の言い換え](#operations)）」で補われている
- 持ち主の側から戻る道：inversion-number 96 行目 → invariant#monovariant（「下限を出し、それを達成する手順を示す」は monovariant の 97〜99 行目の論法と合う）。difference-sequence 250 行目 → inversion-number#adjacent-swaps と reformulation#operations。fix-variable 129 行目 → brute-force#half-enumeration（#13 で付いた逆向きの brute-force 128 行目 → fix-variable#speed-up と合わせて両向きになった）

**ほかのページに証明が残っていないか**

- 区間加算：docs/ を「正の部分の和」「正の差分」「本始め」「本を終え」などで grep した。作り方の証明は difference-sequence 83 行目だけである。patterns/interval 188 行目は下限の理由 1 文と #min-operations へのリンク、imos 119・123・212・219 行目と invariant 142 行目は要点とリンクである
- 片方を固定して数える：binary-search 136 行目は 1 文と fix-variable#fix-middle へのリンク、patterns/subsequence-and-substring 142 行目も同じ節へのリンクである。証明の重なりはない
- 隣接 swap：comb/permutation-cycles 97 行目だけが 2 方向の証明を書いている（直しが要る点 1）

**消した節・anchor の影響**

- 消した確認問題「差分列で数える」は anchor を持たない。docs/・data/ のどこからも参照されていない（名前が出るのは planning/batches/b1/verify/reformulation.md だけ）
- #operations の anchor は残っている。参照元（thinking-checklist 111・219 行目、difference-sequence 250 行目、reformulation 243 行目、problem-sets 113・133・160・213 行目）の文は、縮めた節の中身（差分列・切り替え点・転倒数の 3 つと各持ち主へのリンク）と食い違わない
- check_pages は、本文の相対リンクの anchor も検査する。11 ページ・全ページのどちらもエラー 0・警告 0 だった。strict のビルドも通る

**手引き §5 の 1 行**：Issue の「やること」にあるが、担当の報告で提案（提案 1）になっている。完了の条件には入っていないので、メインが手引きに足せばよい。

## 検査（書き換えない検査）

- `python3 tools/check_pages.py --page complement,construction,contribution,fix-variable,invariant,parity,reformulation,reverse-thinking,symmetry-pigeonhole-casework,difference-sequence,inversion-number -v`：エラー 0・警告 0。全ページ（引数なし）もエラー 0・警告 0
- `npx textlint`（11 ファイル）：エラー 0、警告 119。直す前の写し（`git show HEAD:<ファイル>`）は 120 である。行番号を除いて文言で比べると、違いは次の 3 つだけで、新しい警告はない
  - 行のずれ
  - reformulation の max-comma が 3 → 2（消した確認問題の分）
  - reformulation 138 行目の文の長さが 365 → 277
- reformulation 138 行目の文の長さの警告（任意・直しは要らない）
  - 担当の報告は「$[l, r)$ の『[』の誤検出に引きずられたもの」としている
  - しかし $[l, r)$ を言葉に置き換えて試しても、最後の文「たとえば、すべて 0 の列から…）。」が 123 字と数えられる（trial/s4.md）。この字数には数式の原文（`$\pm 1$` など）が入る。表示上は 114 字である
  - よって §13-8 の「数式を含む文の長さ」の誤検出にあたり、残してよい
- `python3 tools/fix_problems.py --check --page <id>`（11 ページ）：直すべき行 0。問題の行は変わっていない
- check_snippets・check_svg：コード片と図は差分にないので流していない
- `uv run mkdocs build --strict -q -d <作業用フォルダ>/site`：終了コード 0
- 数式：作業用フォルダで `python3 -m http.server`（127.0.0.1、使い終えて止めた）を立てて 11 ページをヘッドレスの Chrome で開き、描画後の DOM を出した。katex-error は 0 で、`katex` の数は `arithmatex` の数と一致した（全部の数式が描画された）
- 撮影（幅 390px、ライトとダーク）
  - 撮ったもの：symmetry-pigeonhole-casework・invariant・reverse-thinking の冒頭、reformulation の一覧表と #operations（shots/）
  - 合図の段落の数式とリンク、「[総和を求める](…)」のかぎかっこの中のリンクは崩れていない
  - 縮めた #operations の段落も崩れていない
- `python3 tools/gen_site.py --check --diff`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が変わると出る。差分は版のハッシュの 1 行だけである（作業用フォルダの gen-diff.txt）。メインが作り直す

## 担当の「判断してほしい点」への所見（参考）

1. difference-sequence（黄）を区間加算の証明の持ち主にした点：直す前の reformulation 138 行目も、imos 123・219 行目・patterns/interval 188 行目も、同じ #min-operations へ証明を任せていた。今回の直しで新しく黄へ飛ばすことになったわけではない。#min-operations の中身は水の読者でも追える
2. invariant#monovariant の確認問題「止まることの証明」は、最小回数の証明ではなく停止性の最小の例である。thinking の受け持ち（最小の例）に当たるので、残してよい
3. fix-variable#fix-maximum と greedy-priority-queue#fix-max-keep-k の重なりは、Issue の 3 つの考え方の外である。別の Issue にするのが妥当である

## 任意（直さなくてよい）

- basics/brute-force.md 113 行目の「二分探索」の項目は `[二分探索](../basics/binary-search.md)` でページの先頭を指している。#fix-one-side を指すと、「ほかのページはその節へリンク」に文字どおり合う。証明は書いていない 1 文の要約で、担当のファイルの外なので指摘にはしない
- 担当の提案 3（related に発想リストを足す。symmetry-pigeonhole-casework の q-invariants を other-types に替える）は、本文のリンクと合っていて妥当である
