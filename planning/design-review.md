# 設計の見直しへの対応

工程4の記録。3本の見直し（[review/01-learner.md](review/01-learner.md)・[review/02-requirements.md](review/02-requirements.md)・[review/03-catalog.md](review/03-catalog.md)）の指摘ごとに、対応を決めた。指摘の番号は「01-4」のように「見直しの番号-指摘の番号」で書く。

- 指摘は合計76件（01：重大2・中7・軽8、02：重大2・中15・軽10、03：重大3・中15・軽14）。要件・決定事項の照合は112項目で、満たす87・不足15・矛盾6・未定4
- ほぼすべてを採用した。採用しなかったもの・形を変えたものは理由を書いた（§5）
- §1〜§3 は設計書（design.md）と catalog の規則（catalog/README.md）に反映する。§4 は目次（catalog）の直しで、分野ごとの担当が行う。§6 は工程5でユーザーに確かめる

---

## 1. 設計の大きな変更

| # | 決定 | 指摘 |
| --- | --- | --- |
| D1 | **節を構造化する**。catalog と front matter の `sections` を `{title, anchor, level}` の列にする（level は省略でページと同じ）。節の level はページの level 以上（低い節は作らず、下位のページへの導線にする）。基礎のページの節は青まで。アンカーは英小文字とハイフン（本文の見出しに `{#anchor}`）。生成スクリプトは上位の節を「ページ#節」としてその色のロードマップに出す。「理解した」はページ×レベルで持つ。知識マップの点はページで、上位の節を持つページに印を付ける | 01-1・01-8・03-14・03-32・02-9 |
| D2 | **レベルの規則を足す**：(a) 帯は abc319 以降（7問体制、2023-09 以降）の根拠を主に数え、古い問題は最近の根拠がないときだけ使う。(b) ACL を呼ぶだけで解ける問題も帯の根拠に数える。ただし S・F の設計や縮約後の処理など ACL の外の考察が本体なら数えない | 01-2・03-12・03-13 |
| D3 | **問題の台帳** `data/problems.yaml` を作る（git で追跡、サイトには出さない）。1問1項目：ID・元のコンテストと記号・タイトル・difficulty（取得日付き）・問い（`summary`。手法名を書かない）・方針（`approach`。執筆者向け、サイトでは折りたたみ）・使う手法のページ・裏付けの URL・確認の状態（確認済み／未確認／不採用）・使うページ。調査レポートと catalog から機械的に下書きを作る。未確認の問題は本文に使えない。CI と tools は API ではなく台帳のスナップショットを見る。difficulty の更新は `tools/ap.py` で意図して行い、別の commit にする | 02-2・02-13・03-16 |
| D4 | **問題の載せ方**：例題は1問につき1ページ（その手法の持ち主）だけ。ほかのページでは練習か本文の参照にする。代表問題は並び順と切り離し、`representative: true` を帯の中の例題1問に付ける。水・青のページは abc319 以降の問題を1問以上入れる（ないときは理由を残す）。練習が目安に足りないページは `problems_note` に理由を書き、工程8b の前に「問題の補充」を作業として行う。本文の一覧は目印の付いた囲み（`<div class="kp-problems" data-role="practice" markdown>`）に入れ、1行の書式を決めて検査する | 01-13・01-14・03-10・03-15・03-17・03-28・02-12 |
| D5 | **最近の ABC のデータ** `data/recent-abc.yaml`：research/00 §2.3.8 の abc451〜480 の D〜G 120問を、使う手法のページ id に対応させる。これからロードマップの「位置ごとの頻出手法（最近30回）」と「最近の ABC → ページ」の表を生成し、`frequency` を機械的に付け直す（`frequency_evidence` に回数を残す）。cpp・hub・guide・patterns は frequency を持たない | 01-3・01-7・03-29 |
| D6 | **入口・比較・地図のページの type `hub`** を足す。level は持たない（null）、frequency なし、問題0〜3で例題なしを許す。写像12相・DP の高速化の入口・グラフへの帰着・発展のデータ構造の一覧などが候補。最短路の使い分けは横断の「似た手法の使い分け」に吸収する | 03-11・01-10・03-8 |
| D7 | **考察の入口は横断の「詰まったときの発想リスト」1つ**。observation-hub の表はそこへ移し、observation-hub は小さな型（対称性・鳩の巣原理・場合分け）の普通の thinking のページにする | 01-9 |
| D8 | **動く図に優先度**：catalog の `visual` を `{kind: dynamic|static, priority: 1|2|3, text}` にする。priority 1 は全体で25前後（§4 の分野ごとの枠）。ほかの dynamic は priority 2〜3（余力があれば）か静的な図に直す。図ごとに状態の列を作る関数の単体試験（Node）と、ヘッドレスのブラウザでの取り付けの検査を置き、コードの検証役が図も確かめる | 02-15・03-18 |
| D9 | **signs に `shape`（立てた式・遷移の形）を足す**。逆引き辞典に「立てた式の形から」の表を生成する。候補を絞れないサインは消す。sign の文に手法名を入れない。数のない constraint は phrase にする。技法の特徴が制約に出るページは constraint を1つ以上置く | 01-12・03-27 |
| D10 | **summary の規則**：1文目は何ができるか（いつ使うか）。2文・120字以内。「このページ」「ここ」「まとめる」「扱う」「紹介する」、帯の名前を使わない | 01-17・03-26 |
| D11 | **題名・別名・id の規則**：正式名は「セグメント木」（本文・補足は「セグ木」可）。数の K は大文字。人名の連結は ASCII のハイフン（Aho-Corasick・Sprague-Grundy など）。半角英数字と全角文字の間は空白を入れる（「2 次元」「K 番目」）。題名に長いかっこの補足を付けない（補足は別名・summary に回し、必要なら `nav_title` を置く）。英語の定まった名前がある手法は英語名を別名に入れる。ほかのページの名前と紛らわしい別名を持たない。id の `segtree-` は `segment-tree-` にそろえる | 03-22・03-23・03-24 |
| D12 | **前提の規則**：catalog の `prerequisites` は直接の前提だけ（推移的に冗長なものは消す）。前提と related に同じページを置かない。related は調査の key ではなくページの id（節なら `id#anchor`）で書く。同じ分野の前提はナビゲーションでそのページより前に置く | 03-19・03-20・03-21・01-11・03-4 |
| D13 | **章**：発展の概要は話題の章に置き、「発展」の章は作らない。1ページだけの章は隣と合わせる。cpp も4〜5章に分ける | 03-30 |
| D14 | **`verify`**（Library Checker の問題名）を catalog の形式に入れ、ACL に対応のあるページと Library Checker を節に書いていたページで埋める | 03-31 |
| D15 | **kind の語彙に「計算量」を足す**（計算量の見積もり・ならし計算量・調和級数・定数倍） | 03-25 |
| D17 | **ロードマップの並び**：色ごとに、前提の順に並べた1本の列にする（同順は分野の並び、次に frequency の順）。各行に分野を示す。分野をまたぐ同じ色の前提も順に並ぶ | 01-16 |
| D18 | **並び順のキー `order`**（分野の中の順。10刻み）を front matter に持たせる。8a 以降の nav は chapter と order から生成する | 設計書第2版の編集で判明 |
| D19 | **図の画像は `docs/img/<page-id>/`** に置き、本文から相対リンクで参照する（strict の検査に掛かる）。claude.ai では docs/img/ を除いて選ぶ | 設計書第2版の編集で判明 |
| D16 | **題材別を足す**：「部分列と部分文字列」「約数と倍数」。題材別の問題は「表の行の代表」のリンクだけ（例題0〜1、練習0〜3、ほかのページと重ならないもの）。thinking の例題は2〜4まで | 01-14・01-15・03-17 |

## 2. 技術・運用の変更

| # | 決定 | 指摘 |
| --- | --- | --- |
| T1 | front matter の制作の段階は `status` ではなく `stage`（stub／draft／reviewed／done）。`status` は Material の予約キーと衝突する | 02-6 |
| T2 | **知識マップ**：既定は「分野ごとの表示」。ページから開くと「そのページの祖先と子孫だけ」。全体は分野を頂点にした15頂点の図。related は配置に使わず、選んだページの周りに後から薄く足す。重ければビルド時に座標を計算する。同じ内容を表（レベル別一覧）でも出す | 02-3 |
| T3 | **検索**：題名と別名から「用語の索引」（語 → ページ）を生成し、ホームと逆引きから開けるようにする。別名が本文の冒頭にあるかを検査する。骨格（8a）の後に実際の題名・別名で検索の試験（30問以上）を行い、手順を tools/ に残す。search の pipeline 設定を書き足す | 02-4・02-27 |
| T4 | **Zensical の評価**を2回に決める：0.1.0（2026-11-05 予定）が出た後の工程6の終わりと、8b の前。結果をユーザーに諮る | 02-4 |
| T5 | **索引**：`docs/llms.txt` は1行「[タイトル](URL)（id・レベル・分野・段階）：要約」に絞る（約8万字）。別名・サイン・kind・節（アンカー付き）は分野ごとの詳細索引 `docs/index/<field>.md` に分ける。版は「入力の内容のハッシュ」と「updated の最大値」（決定的で `--check` と両立する）。デプロイで各ページの Markdown 版（snippets を展開）を出し、方式 B で読めるようにする | 02-5 |
| T6 | **固定テンプレートにしない**：全ページ必須はメタデータと冒頭の「要点」だけ（要点を必須にすることは工程5でユーザーに確かめる）。style-guide に分野ごとの節（research の各 §7 から、その分野で効く構成と書き方）を作る。骨格（8a）は front matter と要点だけで、節の見出しを生成しない。見本は性質の違う2枚を渡し「構成をまねない」と書く。分かりやすさの検証に「目安を埋めるためだけの薄い節がないか」を入れる | 02-7・02-18 |
| T7 | **解説と記録の仕組みの時期を3つに分ける**：9a 記録用スキル（工程6の中。本文に依存しない）、9b claude.ai の実機確認（工程7と並行。試作のページと仮の索引で、GitHub 連携・RAG での索引の引かれ方・web fetch の連続取得・トークン数を確かめ、索引と冒頭の形式を決めてから 8a へ）、9c 解説手順の確定（8a の後） | 02-8 |
| T8 | **解説の手順**：守るべき規則（開催中のコンテストは断る・atcoder.jp と codeforces.com を開かない・最初にヒントか解説かを聞く・教材の用語と記法に合わせる・索引の版を回答に書く）はプロジェクトの指示そのものに短く書き、版の番号を付ける。explain.md は1つの断片に収まる長さにする。開催中かは利用者に確かめる。ADT・AWC は判断がつくまで断る。ルールの版を how-to-use と指示に書く。方式 C を試すときは解説用の指示を CLAUDE.md と分ける | 02-9 |
| T9 | **並列の執筆の規則**：執筆者が書くのは担当ページ（`docs/<field>/<id>.md`）・`snippets/<id>/`・図の画像 `docs/img/<id>/` だけ（動く図の JS と試験は頼まれたときだけ。工程6で範囲を広げた）。用語集・prh.yml・早見表・使い分け・catalog・台帳への追加は報告に「提案」として書き、メインがバッチの終わりにまとめて反映する。`gen_site.py` の実行と commit・push はメインだけ。CLAUDE.md と執筆の手引きに書く | 02-10 |
| T10 | **骨格（8a）以降は front matter と台帳が正**。catalog は凍結し、執筆の指示（sections・visual・sources）としてだけ使う。8a 以降は id と URL を変えない（変えるときは転送と localStorage の鍵の読み替え表）。ページの追加・統合・削除は decisions.md に残し、ユーザーに知らせる | 02-11 |
| T11 | **コード片**：本文の ```` ```cpp ```` は `--8<--` の取り込みだけを許し、擬似コードは ```` ```text ```` で書く（検査する）。snippets ごとに設定（コンパイラ・フラグ・期待：実行して出力が一致／コンパイルエラー／警告、入力と期待出力）を置く。cpp ページの `gcc_min` は g++-13 と g++-15 で確かめる。push では変わった snippets だけ、週1回すべてを検査する。ACL v1.6（CC0）をリポジトリに同梱して版を固定する。工程6の最初に CI のコンテナで1本通す | 02-14 |
| T12 | **検証のチェックリストと記録**：工程6で `planning/checklists/`（事実・コード・分かりやすさ・図）を作る。バッチごとに `planning/batches/<番号>.md`（ページ・担当・検証の結果と指摘・直したか・未解決・使用量）を書き、progress.md から参照する | 02-16・02-1 |
| T13 | **骨格に載せるもの**：catalog から機械的に作れるもの（題名・別名・要約・前提・レベル・サイン）だけ。計算量などの新しい事実は 8b の執筆と検証で入れる。stub には「準備中」の印をテンプレートで出し、索引にも段階を載せる。Claude に stub を根拠にしないよう手順に書く | 02-17 |
| T14 | **ナビゲーション**は `gen_site.py` が front matter の順と chapter から `nav.yml` を生成し、mkdocs.yml は `INHERIT: nav.yml`。レベル別・種類別の一覧、ホーム、分野の入口ページも生成物に入れる | 02-19 |
| T15 | **前提・次に読む**はテンプレートの上書き（`nav.pages` の meta を読む）で出す。次に読むは同じレベルと1つ上を優先して8件まで、続きは知識マップの焦点の表示へ | 02-20 |
| T16 | **静的ファイルは `overrides/assets/` に置く**（JS・CSS・同梱ライブラリ・graph.json）。docs/ は Markdown と索引だけにし、claude.ai では docs/ を丸ごと選べるようにする | 02-21 |
| T17 | **手書きのページの中の生成部分**は目印（`<!-- gen:begin 名前 -->` 〜 `<!-- gen:end -->`）の間に `gen_site.py` が直接書く | 02-22 |
| T18 | **記録用スキル**：問題がキャッシュにないときは `ap.py fetch --force` を1回だけ行い、difficulty がなければ「未定」。ファイルは `notes/<問題ID>.md` の1問1ファイルで、同じ問題は追記する。「記録用まとめ」の形式は `claude/record-format.md` の1か所に書き、explain.md と SKILL.md の両方から参照する | 02-23 |
| T19 | **用語集**：各ページで用語の最初の出現だけを用語集のアンカーへリンクする。用語集と prh.yml はメインが更新し、更新したら全ページに textlint をかけ直す | 02-24 |
| T20 | **noai の確認の道具** `tools/check_noai.py`（robots の meta と X-Robots-Tag を読む）を作り、新しいドメインを使う前に実行する。確かめたドメインを style-guide に記録する | 02-25 |
| T21 | **使用量と期間**：工程7の試作で、ページの種類ごとに入出力のトークン・道具の呼び出し回数・Web 取得の回数・所要時間を記録し、全体の見込みを出してユーザーに示す。試作に黄の手法ページを1つ加える。執筆者には設計書の全文ではなく「執筆の手引き」（style-guide の中の数千字）を渡す。並列数と止める基準を progress.md に書く。規模を下げる手段（発展の概要を短い型に固定、動く図を priority 1 に絞る、問題の枠を減らす）を先に決めておく | 02-1 |
| T22 | **ユーザーに確かめる場面**：ページの追加・統合・削除、レベルの変更、要件から外れる表示や機能、使用量が見込みを超えるとき、8b の最初のバッチの出来、Zensical への移行 | 02-26 |
| T23 | 細かい不整合：localStorage は1つのキー（`kyopro-atlas:v1`）に JSON で持つ（書き出し・読み込みと storage イベントを扱う）。ページのバッジに kind も一覧へのリンク付きで出す。部品の class の接頭辞は `kp-`。§2.2 の列名は「分量の性格（上限ではない）」にする | 02-27・02-18 |

## 3. レベルと規模についての判断（論点への回答）

| 論点 | 決定 | 指摘 |
| --- | --- | --- |
| 遅延セグ木 | **水**に下げる（2024年以降の根拠 abc340_e 1157・abc473_f 1303・abc382_f 1443・abc455_f 1549）。本体は ACL での使い方と「S に長さを足す」。保つ性質と push の手順（自作ライブラリ用）は青の節。前提は segment-tree だけ（segment-tree-monoids は related）。S・F の設計は lazy-segment-tree-patterns（青）に残す | 01-2・03-12 |
| セグ木上の二分探索・木の構築・平均の最大化 | 最近の根拠で数え直し、水にする（入口の節だけ水にする選択も可。担当が根拠で決める） | 01-2 |
| 行列累乗 | **青**（abc458_f 1744・abc456_f 1888・abc305_g 1989）。dp-matrix-power を統合 | 01-5・03-3 |
| 挿入 DP・部分列 DP | 黄のまま。挿入 DP の level_evidence に「今後も青の帯に出続けたら下げる」と残す | 01 論点2 |
| 動的 DP | 発展の概要のまま。abc456_f は segment-tree-monoids の行列の節の例題に移す | 01-5 |
| 黄の薄いページ | complement-graph-bfs は短い独立のページ（黄）のまま（bfs は基礎のページで、D1 により黄の節を置けないため。訂正）、xor-path → xor-basis の節、reachability-bitset → bitset-speedup の節、lowlink と biconnected-components → 1ページ、位数・原始根・離散対数（と mod-sqrt）→ 1ページ、lucas-theorem と「法が素数でない二項係数」の扱いは comb で1ページか節に、game-mirror-strategy → game-basics の節、fft-string-matching → convolution-ntt の節、long-path-decomposition → tree-diameter の節。euler-path と divide-and-conquer は残す | 01-6・03-10 |
| ページより低い節 | 認めない（D1） | 01-8 |
| 考察の入口 | 1つにする（D7） | 01-9 |
| 写像12相 | hub（D6） | 01-10 |
| 発展の概要（55ページ） | 1手法1ページの短い概要を続ける（ユーザーの回答）。ただし ABC の問題がない概要が多いので、工程5で量をユーザーに示す | 01-6 |

## 4. 目次（catalog）の直し

分野ごとの担当（A〜I は工程3と同じ割り当て）が、catalog/README.md（第2版）の形式と §1〜§3 の決定に従って直す。分野をまたぐ統合は、送る側が `moved`、受ける側が `merged_keys` で処理する。

### 4.1 すべての担当に共通

1. 形式を第2版に変える：`sections` を `{title, anchor, level}` に、`visual` を `{kind, priority, text}` に、`problems` の各要素を `{id, role, summary, approach, representative}` に（summary は問いだけ、手法名なし。手法名だけの要約は approach に移し、summary は「（執筆時に確かめる）」にする）
2. 節のレベルを D1 の規則に合わせる（低い節は下位のページへ移すか導線の1行に、基礎のページの黄・発展の節は上位のページへ移す）
3. 最近の根拠で level を確かめ直す（D2）。変えたら level_evidence に理由を書く
4. 例題は1問1ページ（D4）。代表問題に `representative: true`。水・青のページに abc319 以降の問題を1問以上（候補は research/00 §2.3.8 と各調査）。練習が2問未満なら `problems_note`
5. 前提を D12 に合わせる（直接の前提だけ、related は id か `id#anchor`、同じ分野の前提はナビゲーションで前）
6. summary・signs・aliases・title を D9〜D11 に合わせる。英語名の別名を足す
7. `verify`（D14）、kind の「計算量」（D15）、章（D13）
8. 調査で「未確認」とされた問題が入っていたら外す（例：tree の abc138_d、math・graph の abc253_h）。research の各レポートの未確認の一覧と照らす
9. `frequency` は仮の値のままでよい（D5 のデータから後で機械的に付け直す）。cpp・hub・guide・patterns の frequency は消す

### 4.2 分野ごとの直し

| 担当 | 主な直し |
| --- | --- |
| A（basics・thinking・misc） | dp-decision-binary-search を binary-search-answer に受ける（節「判定を DP で作る（青）」、03-7 の問題の入れ替え）。median-binary-search を fractional-binary-search に統合し「平均・中央値の最大化」を水（青の節）に。difference-sequence の基礎の部分を imos の節に戻し、ページは「差分列への言い換え」（黄）に。periodicity の別名「反転フラグ」と abc199_c を global-offset へ。observation-hub を D7 のとおり作り替える（表は guide へ）。contribution と sigma-manipulation の書き分け（abc172_d は sigma だけ、別名「和の順序交換」は sigma だけ）。reachability-bitset・subset-sum の bitset の節を bitset-speedup に受ける。knapsack-01 の区間ナップサックを divide-and-conquer の節に受け、力試しに abc451_g・abc478_g を足す。median-absolute の「中央値の更新」は ds の top-k-multiset へ送る。章の並べ替え（03-19：bit 演算を前へ、ソートと二分探索、二分探索の応用の章など）と1ページの章の統合。thinking の例題は2〜4。visual の priority 1 は3つ（二分探索の境界・尺取り・いもす法） |
| B（dp） | dp-convolution → math、dp-counting-dedup → comb、dp-matrix-power → math、dp-decision-binary-search → basics へ moved。dp-speedup-overview を hub にし、遷移の形 → 道具の表に「多項式の積（→ online-convolution）」「行列（→ matrix-power）」の行。dp-order の前提を dp-basics だけに（dp-dag は related）、interval-dp の冗長な前提を消す。dp-prefix-sum を「DP の考え方」の章の末尾へ。dynamic-dp の例題から abc456_f を外す。subsequence-dp の前提を comb の counting-dedup に。string-automaton-dp の簡易版（abc122_d）を dp-state-design の「末尾の数文字」の節に受ける。knapsack-01 の区間ナップサックは basics の divide-and-conquer へ送る。subset-sum の bitset の節は misc の bitset-speedup へ送る。tree-dp に「根を動かした差分（全方位の入口）（水）」の節を受け、rerooting の水の節は導線にする。visual の priority 1 は4つ（ナップサックの表など） |
| C（graph・tree） | state-space-search を extended-dijkstra に統合（題名「状態を頂点にする」、問題を03-5 のとおり絞る）。graph-modeling を hub にし「何を頂点にするか」は表だけ。shortest-path-overview を guide の method-comparison へ送る。complement-graph-bfs は短い独立のページ（黄）のまま残し、bfs の related から道を作る（訂正）。xor-path を math の xor-basis へ、reachability-bitset を misc の bitset-speedup へ送る。lowlink と biconnected-components を1ページ（「橋・関節点・二重連結成分」、黄。verify に Library Checker）。graph-basics の前提の complexity-estimation を related に。dilworth-path-cover の題名を「最小パス被覆と Hall の定理」にし、別名 Dilworth を外す。bellman-ford の「ポテンシャル」（水）の節を dijkstra の節に。k-shortest-paths に dijkstra から、tree-ratio-greedy に exchange-argument からの道を作る（相手の担当へ提案として open_issues に書く）。tree：long-path-decomposition を tree-diameter の節（黄）に、complete-binary-tree を基礎（青の節）に、tree-construction を最近の根拠で水に、tree-centroid の水の節は導線に、root-path-dfs の別名「版の木」を外す（版の木は ds）、tree-degree に Prüfer の全単射を持たせる、steiner-subtree のクエリ版を auxiliary-tree へ、tree-edge-contribution から abc214_d の例題を外す（ds の union-find-applications の例題）、「発展」の章をなくし話題の章へ。visual の priority 1 は graph 5（BFS の層・ダイクストラ・01-BFS・ワーシャルフロイド・最大流の残余グラフ）、tree 3（オイラーツアー・LCA のダブリング・直径の2回探索） |
| D（ds） | lazy-segment-tree を水に（§3）。lazy-segtree-patterns・segtree-on-values・segtree-binary-search の id を segment-tree- にそろえる。segment-tree-binary-search を最近の根拠で水に。segment-tree-monoids の行列の節に abc456_f を例題で受け、string-automaton-dp からの前提の受け皿にする（matrix-power は math）。top-K の持ち主を整理（2つの multiset は top-k-multiset、値を添字にする方法は segment-tree-on-values、kth-element の「上位 K 個の和」の節は消してリンク）。median-absolute の「中央値の更新」を top-k-multiset に受ける。persistent-data-structures に版の木を持たせる。global-offset に反転フラグと abc199_c を受ける。union-find-applications に abc214_d の例題を持たせ、graph の union-find-connectivity との分担（根に情報を持たせる型は ds、逆順処理・オフライン・Kruskal は graph）を節で明確に。sweep-line-2d の前提に lazy-segment-tree。sqrt-decomposition の「歩幅ごとの場合分け（青）」は下位のページへの導線にする。章名「発展的なデータ構造」を「そのほかのデータ構造」に。cht への related を足す。visual の priority 1 は3つ（セグ木の更新と取得・遅延伝播・Union-Find） |
| E（math） | dp-convolution を online-convolution に、dp-matrix-power を matrix-power（青）に受ける。xor-path を xor-basis の節に受け、xor-basis の前提は bit-operations に（gaussian-elimination は related）。fft-string-matching を convolution-ntt の節に受ける。multiplicative-order・discrete-log・primitive-root（と mod-sqrt）を1ページ「位数・原始根・離散対数」（黄）に。gaussian-elimination を最近の根拠で確かめる（青も検討）。harmonic-sum に「倍数を回して集める（水）」の節を受ける（comb の zeta-mobius-divisor から）。prime-factorization の Pollard's rho（発展）は概要ページへ。sigma-manipulation を「式の規則」に絞る（abc172_d は sigma の例題）。fps-basics から「母関数の考え方」の節と別名「母関数」を外す（comb の generating-function-counting へ）。proof-patterns を GCD の章の末尾へ、multiplicative-function を floor-quotient-enum の後へ。visual の priority 1 は2つ |
| F（comb） | dp-counting-dedup を counting-dedup に受ける（kind に DP、03-2 の節と問題）。twelvefold-way を hub に（例題は各マスのページへ）。inclusion-exclusion の「2〜3 条件（基礎）」は thinking の complement へ送り、代表問題を abc172_e に。zeta-mobius-divisor の「倍数を回して集める（水）」は math の harmonic-sum へ送る。lucas-theorem と binomial-precompute の「法が素数でない・小さい」の扱いを、基礎のページに黄の節を残さない形で決める。game-mirror-strategy を game-basics の節に。optimal-strategy-expectation の基本形を expected-value-dp の節（水）に移し、ページは黄に。permutation-cycles の黄の節（巡回型の数え上げ）を上位のページへ。coupon-collector の min-max 包除を inclusion-exclusion の節（発展）へ。cayley-pruefer の前提に tree-degree。bell-number は数に絞り、集合分割の全列挙は basics の recursive-enumeration に任せる。「全射の数」の持ち主は inclusion-exclusion。generating-function-counting に「母関数の考え方」を受ける。counting-bijection・lattice-paths の水の根拠を確かめる。「数え上げの発展」の章をなくし話題の章へ。visual の priority 1 は2つ |
| G（string・geometry） | fft-string-matching を math へ送る。string-automaton-dp の簡易版（水）を dp へ送り、ページの前提を kmp に（aho-corasick は related）、「遷移行列の累乗」の節を青にして前提に matrix-power。kmp の前提の z-algorithm を related に。palindrome の前提の bfs を related に。subsequence-matching と hash-safety の level を最近の根拠で確かめる（水の問題を足すか、帯を変える）。visual の priority 1 は2つ（Z または KMP など） |
| H（cpp） | 章を4〜5に分ける。長い題名を短くし、必要なら `nav_title`。acl-reading の lazy_segtree の節を水に（遅延セグ木が水になったため）。frequency を消す。signs はそのまま（問題文から分かるものだけ）。コードの見た目からの逆引きは cpp-reverse-index の手書きの表で行い、`code_signs` は足さない |
| I（start・guide・patterns） | thinking-checklist に observation-hub の「問題の形 → 試す型」の表を受ける。method-comparison に shortest-path-overview を受ける（最短路の節）。patterns の問題を減らす（D16）。「部分列と部分文字列」「約数と倍数」の題材ページを足す。roadmap・problem-sets の節に D5 のデータからの生成部分（位置ごとの頻出手法、最近の ABC → ページ）を書き足す。用語の索引（T3）を guide に足す（生成）。how-to-use に「ルールの版」「stub の意味」「書き出し・読み込みは手動の退避」を足す。notation の kind を「案内」に |

## 5. 採用しなかった・形を変えたもの

| 指摘 | 対応 | 理由 |
| --- | --- | --- |
| 01-6 の後半（ABC の問題がない発展の概要を分野ごとの一覧にまとめる） | まとめない | 「発展は1手法1ページの短い概要」はユーザーの回答。工程5で量を示す |
| 03-24（数字と和文の間は空白なし） | 空白を入れる | 既存の文章（調査・目次）がほぼ空白ありで、機械的に統一しやすい。textlint で検査する |
| 03-24（人名の連結はエンダッシュ＋ASCII の別名） | ASCII のハイフンに統一 | 検索で一致しやすく、別名の二重持ちが要らない |
| H の `code_signs` | 足さない | C++ の逆引きは手書きの表で足りる |
| 01-1 の「理解した」 | ページ×レベルで持つ（提案どおり） | — |
| 03-20（推移的に冗長な前提をスクリプトで簡約） | catalog から消す | データを直接の前提だけに保つほうが検証しやすい |

## 6. 工程5でユーザーに確かめること

1. 冒頭の「要点」を全ページに置く（要件の「全ページ必須はメタデータだけ」を超える）（T6）
2. 解説と記録の仕組みの時期の変更（9a・9b・9c）（T7）
3. Zensical の評価の時期（T4）
4. 規模：367ページ前後（基礎約90・発展約55）。発展の概要は1手法1ページのまま
5. 公開中に stub のページがある（「準備中」の印）（T13）
6. 問題は利用者のスクリーンショットか要約で受け取る（claude.ai に atcoder.jp を開かせない）
7. 「理解した」「解いた」の書き出し・読み込みは手動の退避で、同期ではない
8. 使用量と期間は試作で測ってから示す（T21）
9. 執筆者に渡すのは設計書の全文ではなく「執筆の手引き」（要件 §8 の字面との違い）（T21）
