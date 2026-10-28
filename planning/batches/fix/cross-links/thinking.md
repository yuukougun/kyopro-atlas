# thinking の報告（バッチ cross-links）

- 担当の Issue：#65（本文の部分。完了）・#70（完了。手引き §5 の 1 行は提案）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links）。git は読むだけで、commit などはしていない。Issue にはコメント・編集・クローズをしていない
- 直したファイル（11）：docs/thinking/complement.md、docs/thinking/construction.md、docs/thinking/contribution.md、docs/thinking/fix-variable.md、docs/thinking/invariant.md、docs/thinking/parity.md、docs/thinking/reformulation.md、docs/thinking/reverse-thinking.md、docs/thinking/symmetry-pigeonhole-casework.md、docs/basics/difference-sequence.md、docs/ds/inversion-number.md
- front matter で変えたもの：11 ページとも本文を直したので `updated` を 2026-10-29 にしただけ。stage・related などは変えていない（related の直しは下の提案）
- 生成物（docs/thinking/index.md など）には触れていない。考察の章の入口の 1 行は別のグループが gen_site で足す
- 同じ作業ツリーで、ほかの担当が comb・dp・ds・graph・math・tree などのページを直している（git diff に出る）。それらには触れていない

## #65 考察の章と「詰まったときの発想リスト」を行き来できるようにする（本文の部分は完了）

### 導入に合図の段落を置いた（9 ページ）

reverse-thinking の「使える合図は 3 つある。…である。」の形にそろえ、導入（題名を主語にした段落）の後に 2 段落目として置いた。合図は問題文の言い回しを「」で引き、front matter の signs・要点の「いつ使うか」と食い違わない内容にした。

| ページ | 行 | 合図（要旨） |
| --- | --- | --- |
| complement | 46 | 「少なくとも 1 つ含む」「1 つでも満たす」・「A でも B でもない」・「すべて異なる」 |
| contribution | 48 | 「すべての組（区間）について」の総和・足す値が「区間の最小値」「2 番目に大きい値」・$N \le 2 \times 10^5$ で列挙できない |
| fix-variable | 47 | 「$i < j < k$ を満たす組の数」・「$A_i + A_j$ が $M$ の倍数」・「選んだ値の最小値 × 個数」 |
| invariant | 46 | 「0 回以上好きな回数行える」・「$B$ にできるか」「最後に残る値の最大値」・「操作できなくなるまで繰り返す」「最小の操作回数」 |
| parity | 48 | 「ちょうど $K$ 回の操作で」「時刻 $t$ に」・「上下左右に 1 マス動く」・「2 つの値の和が偶数」 |
| reformulation | 46 | 「区間の和が $M$ の倍数」・「平均が $x$ 以上」・「区間に 1 を足す」「隣と入れ替える」の最小回数 |
| reverse-thinking | 45 | 「$i$ の倍数番目の和」・「結果から操作列を求めよ」・「辺を削除する」「区間を塗る」 |
| construction | 46 | 「1 つ出力せよ（なければ −1）」・「$N - 1$ 回以下の操作で」・最大値に自然な上界が見える |
| symmetry-pigeonhole-casework | 47 | 「$i < j$ の組すべてについての積の和」・「余りが等しい 2 つ」・制約が $N = 1$ を許す |

- reverse-thinking は、導入の段落の末尾にあった合図の文（「決める順に依存の向きがあること、…」）を 2 段落目に移し、各合図に問題文の言い回しを添えた。「依存の向き」の説明は #decide-from-back の本文にあるので、導入では「各条件が自分以降の値だけを参照する」と言い換えた
- 合図の文は textlint の文の長さ（120 字）と読点（3 個）に収まるように削った。新しい警告は出ていない

### 発想リストの対応する表へのリンク（9 ページすべてから 1 クリック）

| ページ | 置き場 | 行き先 |
| --- | --- | --- |
| complement | 使い分け 143 行目 | thinking-checklist#shape-count（個数を数える） |
| contribution | 使い分け 163 行目 | thinking-checklist#shape-sum（総和を求める） |
| fix-variable | 使い分け 149 行目 | thinking-checklist#shape-count と #shape-optimize（最大・最小） |
| reformulation | 使い分け 249 行目（既存） | thinking-checklist#q-rephrase（言い換えの問い）。変えていない |
| invariant | 導入の末尾 46 行目 | thinking-checklist#shape-operation（操作できるか・最小回数） |
| parity | 導入の末尾 48 行目 | thinking-checklist#shape-operation |
| reverse-thinking | 導入の末尾 45 行目 | thinking-checklist#shape-operation |
| construction | 導入の末尾 46 行目 | thinking-checklist#shape-construct（1 つ作る） |
| symmetry-pigeonhole-casework | 導入の末尾 47 行目 | thinking-checklist#other-types（鳩の巣原理・場合分け）と #shape-sum（対称性） |

- Issue の背景は「6 ページにリンクがない」としているが、construction と symmetry-pigeonhole-casework も related に書いているだけで本文にはなかった（related は今のテンプレートでは表示されない。#56）。そのため本文にリンクのなかった 8 ページすべてに足した
- 使い分けの節がある 3 ページは使い分けの末尾の項目に、ないページは合図の段落の末尾に「〈形〉の問題で、ほかにどの型を試すかは[詰まったときの発想リスト](…)の「…」の表で引ける」の 1 文を置いた。表の行には隣の型が並ぶので、外れたときに移る先もそこで見られる
- 使い分けの項目は、その節のほかの項目に合わせて句点なしにした（§15-2 の「既存のページはそろえ直さない」に従い、同じ箇条の中の書き方をそろえた）

### 確かめたこと

- 行き先の anchor（shape-sum・shape-count・shape-operation・shape-optimize・shape-construct・other-types）が thinking-checklist の sections と見出しにあることを読んで確かめた。どの表にも、そのページの節への行がある（例：shape-operation の「目標の状態にできるか」「ちょうど K 回の操作」「操作の結果から元を復元する」）
- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`、終了コード 0）で、9 ページの HTML に「使える合図は」の段落と、本文から thinking-checklist の対応する #anchor へのリンクがあることを見た

### 残った点

- 考察の章の入口（docs/thinking/index.md、生成物）の 1 行は別のグループの担当で、ここでは触れていない。#65 の完了の条件のうち「考察の章の入口から 1 クリック」はそちらで満たす
- front matter の related に発想リストを足す件は提案に書いた（#56 で related を表示すると下部にも出る）

## #70 basics と thinking で重なる説明の持ち主を決める（完了。手引きの 1 行は提案）

### 持ち主の決定

目安（thinking は気づき方・合図・最小の例、basics と ds は手順・証明・実装・落とし穴）に従って決めた。

| 考え方 | 持ち主 | 持ち主でないページ |
| --- | --- | --- |
| 1 つを固定して相手を速く数える | 何を固定するか（真ん中・共有部分・最大値）と最小の例は thinking/fix-variable。相手を二分探索で数える手順とコードは basics/binary-search#fix-one-side、分け目を全探索して前後の最良を組み合わせる手順は basics/brute-force#half-enumeration | binary-search#fix-one-side の「3 つ組は真ん中を固定する」と brute-force#half-enumeration の末尾は、#13 で要点とリンク（fix-variable#fix-middle・#speed-up）の形になっている。fix-variable#speed-up は道具の選び方の表と、持ち主へのリンクにした（下） |
| 区間加算を差分列の 2 点の操作にすると、最小回数は正の差分の和 | basics/difference-sequence#min-operations（下限と作り方の証明・3 つの型・コード） | thinking/reformulation#operations を要点とリンクに縮めた。invariant#connections・basics/imos 123・219 行目・patterns/interval 188 行目はもともと要点とリンク |
| 隣接 swap の最小回数は転倒数 | ds/inversion-number#adjacent-swaps（2 つの事実と、転倒数回で作れることの証明） | thinking/reformulation#operations を要点とリンクに縮めた。thinking/invariant#monovariant 101 行目はもともと 1 文とリンクで、これで書き方がそろった。patterns/permutation 103 行目・comb/permutation-parity 74 行目ももともと要点とリンク |

3 つのどれも、証明を書くページは持ち主の 1 つになり、ほかのページは持ち主の節へリンクしている（完了の条件）。

### 直した内容

- **docs/thinking/reformulation.md**（#operations、134〜144 行目）
  - 136 行目：節の導入に「ここでは気づき方と結論だけを書く。手順と証明は、それぞれのリンク先の節にある。」を足した
  - 138 行目（区間への加算）：最小回数の下限と作り方の証明（「1 回の操作で $+1$ される $d$ は 1 点だけなので…」「逆に、左から見て…その回数で作れる」）を消し、結論「両端の外を 0 として差分を取ったときの正の差分の和である」と、証明・ほかの型（$\pm 1$・長さ固定）の行き先として difference-sequence#min-operations へのリンクにした。左端だけを 0 とした書き方（$a_{-1} = 0$）は、手引き §5 の「両端の外も含めて $N + 1$ 個」に合わせて「両端の外を 0」にした
  - 140 行目（区間の反転）：持ち主へのリンクがなかったので、[区間反転を切り替え点 2 つで表す](../basics/imos.md#range-flip) を添えた
  - 142 行目（隣接 swap）：下限と転倒数回で済むことの証明の 2 文を、理由 1 文（「1 回の隣接 swap で転倒数は高々 1 しか変わらず、隣り合う転倒した組を入れ替えればちょうど 1 減るからである」）と「証明は[なぜ隣接 swap の最小回数か](../ds/inversion-number.md#adjacent-swaps)」に縮めた。ABC479 F（仮の要素を置くと隣接 swap になる）の気づき方は残した
  - 旧 144〜148 行目の確認問題「差分列で数える」を消した。difference-sequence の確認問題「区間から 1 を引いて 0 にする」と同じ型で、答えの差分列も右端の $d_N$ を落とした 5 個で、持ち主の定義（$N + 1$ 個）とずれていた
  - 65 行目（一覧表の「区間に一律に加算」の行）：行き先を同じページの #operations から持ち主の [区間の操作を 2 点の操作に直す](../basics/difference-sequence.md#to-point-operations) に替えた。表のほかの行（隣接 swap → inversion-number#adjacent-swaps など）と同じく、使う手法のページを指す形にそろえた
  - 75 行目（表の後の「操作を扱いやすい単位に分解する」）：表から #operations へのリンクがなくなるので、ここに「（[操作の言い換え](#operations)）」を足した
- **docs/thinking/fix-variable.md** 129 行目（#speed-up）：「分け目を全探索して、前から作った最良と後ろから作った最良を組み合わせる手順は[片側を全探索して残りを速く求める](../basics/brute-force.md#half-enumeration)にある。」を足した。#13 で brute-force → fix-variable のリンクはできていたが、逆向きがなかった。二分探索の持ち主（binary-search#fix-one-side）へは、同じ節の表の行（124 行目）からすでにリンクしている
- **docs/basics/difference-sequence.md** 250 行目（使い分け）：「転倒数で言い換える」のリンク先を、thinking の節から持ち主の [転倒数](../ds/inversion-number.md#adjacent-swaps) に替え、気づき方の行き先として reformulation#operations へのリンクを 1 文で残した
- **docs/ds/inversion-number.md** 96 行目（#adjacent-swaps）：持ち主から考え方の側へ戻る道がなかったので、「1 回で高々 1 しか減らない量で回数の下限を出し、その下限を達成する手順を示すこの論法は、ほかの操作の問題にも使える（[単調量で操作回数を抑える](../thinking/invariant.md#monovariant)）。」を足した。証明の本文は変えていない

### 消した確認問題・証明の参照の確かめ（grep）

- 消した確認問題「差分列で数える」は anchor を持たず、docs/ のどのページからも参照されていない。名前が出るのは planning/batches/b1/verify/reformulation.md（b1 の検証記録）だけである
- 証明を消した #operations の anchor は残した。参照元は guide/thinking-checklist 111・219 行目、basics/difference-sequence 250 行目、guide/problem-sets（生成物）113・133・160・213 行目、reformulation 243 行目（ABC479 F の方針）。縮めた後も節には差分列・切り替え点・転倒数の 3 つの言い換えと各持ち主へのリンクが残るので、参照元の文と食い違わない
- 持ち主の節（difference-sequence#min-operations・inversion-number#adjacent-swaps・invariant#monovariant）の anchor は変えていない。参照元の文（上の表の「持ち主でないページ」と、guide/method-comparison 384 行目・thinking-checklist 107・232 行目・math/proof-patterns 79 行目）を読み、どれも要点 1〜2 文とリンクの形であることを確かめた（担当外なので変えていない）

### 残った点

- thinking/invariant#monovariant の確認問題「止まることの証明」（107〜111 行目）の答えは、「隣り合う転倒した組を入れ替えると転倒数はちょうど 1 減る」を 1 文で述べている。最小回数の証明ではなく、単調量で停止性を示す最小の例なので残した（同じ節の 101 行目から持ち主へリンク済みで、節の中で同じ先へ 2 回リンクしないため、答えにはリンクを足していない）
- thinking/fix-variable#fix-maximum と basics/greedy-priority-queue#fix-max-keep-k は、どちらも「固定した値が本当の最大（最小）値でなくてよい理由」を不等式で示している。題材の問題が違い、Issue の 3 つの考え方の外なので変えていない
- difference-sequence は level が黄なので、水の reformulation・基礎の imos から証明を読みに行く先が黄のページになる（#min-operations の中身は水の水準で、imos・patterns/interval も以前から同じページへ任せている）

## 検査（書き換えない検査）

- `python3 tools/check_pages.py --page complement,construction,contribution,fix-variable,invariant,parity,reformulation,reverse-thinking,symmetry-pigeonhole-casework,difference-sequence,inversion-number -v`：エラー 0・警告 0。全ページ（引数なし）もエラー 0・警告 0
- `npx textlint`（11 ファイル）：エラー 0。警告は直す前の 120 件から 119 件（新しい警告はない。減った 1 件は消した確認問題の読点の警告）。残る警告は既存のもので、reformulation 138 行目の文の長さ（365 → 277 字）は、$[l, r)$ の「[」を no-unmatched-pair が対のない括弧とみなす誤検出に引きずられたもの（§13-8）
- `uv run mkdocs build -q -d <作業用フォルダ>/site`：終了コード 0。上の HTML の確認に使った
- `python3 tools/gen_site.py --check`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が「変わる」と出る（updated の更新と、同じ作業ツリーのほかの担当の直しによる）。生成はしていない。メインが作り直す
- check_snippets・fix_problems・check_svg：コード片・問題の行・図には触れていないので流していない

## 提案（メインがまとめて反映するもの）

1. **手引き §5 の thinking の項目に足す 1 行（#70）**。§5 の「**thinking**：主客転倒は…」の下に、次の子項目を足す。
   > - basics・ds と同じ考え方を扱うときは、thinking には気づき方（問題文の合図）と最小の例を、basics・ds の持ち主の節には手順・証明・実装・落とし穴を書き、持ち主でない側は要点 1〜2 文と持ち主の節へのリンクにする（持ち主は、区間加算の最小回数が difference-sequence#min-operations、隣接 swap の最小回数が inversion-number#adjacent-swaps、片方を固定して相手を数えるのが fix-variable（何を固定するか）と binary-search#fix-one-side・brute-force#half-enumeration（相手を数える手順））
2. **手引き §4 の thinking の構成に足す 1 行（#65。任意）**。これから書く考察のページもそろうように、§4 の「**thinking**：…」の後に次を足す。
   > 導入の後に「使える合図は N つある。…である。」の段落を置き、問題文の言い回しで合図を 2〜3 個書く。詰まったときの発想リスト（guide/thinking-checklist）の対応する表へのリンクを使い分けに置く（使い分けがなければ合図の段落の末尾）
3. **front matter の related（#65・#56 の表示に向けて）**。本文で足したリンクと合わせる。
   - complement：thinking-checklist#shape-count を足す
   - contribution：thinking-checklist#shape-sum を足す
   - fix-variable：thinking-checklist#shape-count（と #shape-optimize）を足す
   - invariant・parity・reverse-thinking：thinking-checklist#shape-operation を足す
   - symmetry-pigeonhole-casework：thinking-checklist#q-invariants を thinking-checklist#other-types に替える。q-invariants の問いは和・偶奇・gcd・単調量・状態の周期で、このページの 3 つの型の行は other-types（鳩の巣原理・場合分け）と shape-sum（対称性）にある
   - inversion-number：invariant を足す（96 行目の新しいリンクと合わせる。任意）

## 判断してほしい点

- difference-sequence（黄）を区間加算の最小回数の証明の持ち主にしたので、水の reformulation から証明を読みに行く先が黄のページになる。このままでよいか（以前から imos・patterns/interval も同じ節へ任せている）
- invariant#monovariant の確認問題「止まることの証明」は、単調量の最小の例として残した。持ち主の証明の一部（転倒数がちょうど 1 減ること）を 1 文で述べているので、縮めるかどうか
- fix-variable#fix-maximum と greedy-priority-queue#fix-max-keep-k の「固定した値が本当の最大値でなくてよい理由」の重なりは、Issue の範囲外として残した。持ち主を決めるなら別の Issue にするか

## 使用量の目安

- 道具の呼び出し：およそ 75 回（読む 25・検査 15・編集 30 ほど）。Web の取得はしていない

## 検証の指摘への対応（2026-10-29）

- 検証の報告：planning/batches/fix/cross-links/verify-thinking.md（指摘は #70 の 1 件。#65 は合格）
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/fixup-thinking
- この対応で書き換えた作業ツリーのファイルは、この報告だけである。担当の 11 ファイルも docs/comb/permutation-cycles.md も変えていない。git は読むだけで、Issue にはコメント・編集・クローズをしていない

### 指摘 1（#70）comb/permutation-cycles#vs-adjacent の証明の重なり：直していない（担当外のファイル）

- **指摘は正しい**：97 行目の「隣接 swap 1 回では…転倒数より少ない回数ではソートできない。逆に、…転倒数の回数で足りる。」は、下限と作り方の 2 方向の証明である。構成は持ち主 ds/inversion-number#adjacent-swaps の 96 行目と同じである。リンク `[転倒数](../ds/inversion-number.md)` はページの先頭を指し、持ち主の節を指していない。docs/ を「転倒数」と「足りる・少ない回数・以上の交換・回で昇順・回でソート・下限」で grep した。持ち主の外で 2 方向を書いているのは、この行だけである
- **直さなかった理由**：このファイルは、頼まれた 11 ファイル（docs/thinking/ の 9 ページ・basics/difference-sequence・ds/inversion-number）に入っていない。指示の「指摘が担当外のファイルなら直さず、questions に書く」と、共通の指示の「担当外のファイルを書き換えない」に従った。検証の報告の「メインが担当のファイルに足して直させる」は、頼み方の案である。今回の指示で、直してよいファイルの一覧は変わっていなかった
- **すぐ当てられる直しを用意した**（作業ツリーには当てていない）
  - patch：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/fixup-thinking/permutation-cycles.patch（`a/docs/comb/permutation-cycles.md` の形。作業ツリーの根で `patch -p1` か `git apply` で当たる）
  - 中身：97 行目の下限と作り方の 2 文を、検証の案どおり 1 文の理由に縮めた。リンクは持ち主の節 `../ds/inversion-number.md#adjacent-swaps` にした。front matter は `updated` を 2026-10-22 → 2026-10-29 にしただけで、sections・related・stage は変えていない
  - 残したもの：表（99〜103 行目）、読み分けの段落（105 行目）、偶奇の段落（107 行目）、anchor #vs-adjacent。patterns/permutation 110 行目と guide/method-comparison 384 行目が #vs-adjacent を指している
  - 直した後の 97 行目：
    > swap できるのが隣り合う 2 要素だけなら、ソートの最小回数は巡回では決まらず、[転倒数](../ds/inversion-number.md#adjacent-swaps)（$i < j$ かつ $P_i > P_j$ となる組の数）になる。隣接 swap 1 回で転倒数はちょうど 1 だけ変わり、ソートされていなければ隣り合う転倒した組を swap して 1 減らせるからである。隣接 swap は任意の swap の特別な場合なので、任意の swap の最小回数は転倒数以下になる。
  - 当てると、ほかの持ち主でないページ（patterns/permutation 103・thinking/reformulation 142・thinking/invariant 101・comb/permutation-parity 74）と同じ「理由 1 文と #adjacent-swaps へのリンク」の形になる。隣接 swap の考え方も、証明を書くページが inversion-number#adjacent-swaps の 1 つになる
- **確かめたこと**（作業用フォルダの写しで行った。作業ツリーは書き換えていない）
  - patch は、作業ツリーのファイルの写し（sha256 が一致）にそのまま当たり、結果は直した写しと一致した（`patch -p1`・`cmp`）
  - `python3 tools/check_pages.py --root <作業用フォルダ>/tree --page permutation-cycles -v`：エラー 0・警告 0（作業ツリーのままでも 0・0）
  - anchor を `#adjacent-swapz` に変えた写しでは「リンク先に anchor がない」のエラーが出た。--root の検査が写しのリンクを見ていることも確かめた
  - `npx textlint <作業用フォルダ>/tree/docs/comb/permutation-cycles.md`：エラー 0、警告 3。作業ツリーのファイルと同じ 3 件（78 行目の文の長さと読点、130 行目の読点）で、どれも触っていない既存の行である。新しい警告はない
  - 残る数式（$i < j$・$P_i > P_j$）は直す前と同じで、消したのは $P_i > P_{i+1}$ だけである。そのため描画は確かめていない
  - 問題の行・コード片・図は触らないので、fix_problems・check_snippets・check_svg は流していない
- **担当の報告の訂正**：上の #70 の持ち主の表で、隣接 swap の「持ち主でないページ」から comb/permutation-cycles（97 行目）が抜けていた。「3 つのどれも、証明を書くページは持ち主の 1 つになり」は、この patch を当てるまで隣接 swap について成り立たない。#70 の状態は、冒頭の「完了」を「一部」に読み替える。patch を当てれば完了の条件を満たす（手引き §5 の 1 行は提案 1 のまま）

### 検査（作業ツリーの今の状態。書き換えない検査）

- `python3 tools/check_pages.py --page complement,construction,contribution,fix-variable,invariant,parity,reformulation,reverse-thinking,symmetry-pigeonhole-casework,difference-sequence,inversion-number -v`：エラー 0・警告 0。全ページ（引数なし）もエラー 0・警告 0

### メインに判断してほしい点

- permutation-cycles の patch を、メインが当てるか、この担当のファイルに足して当てさせるか。同じ作業ツリーで permutation-cycles を直している担当はいない（git status に出ない。resources は type: overview の 46 ページ、dp-speedup は docs/dp/ の担当）
- この pull request に patch を入れないなら、#70 は `Refs #70` にする
