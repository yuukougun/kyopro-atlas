# 動く図 aho-corasick（Aho-Corasick 法）

工程11・バッチ f1 の担当 f1-viz-aho（Issue #51 のうち aho-corasick の分）。2026-10-29。仕様は `planning/batches/b2/aho-corasick.md` の「動く図の仕様」、catalog（`planning/catalog/string.yaml`）の visual、本文の failure-links の節と静的な図 `docs/img/aho-corasick/` に合わせた。

## 作ったもの

- `overrides/assets/js/viz/aho-corasick.js`：見本（z-algorithm・zero-one-bfs・euler-tour）と同じ形。`states(config)` は DOM を使わない純粋な関数、`render(svg, state, config, h)` が描き、`viewBox(config)` は全ステップで同じ大きさを返す（配置は config ごとに 1 回だけ計算して WeakMap に置く）
  - 手順は `snippets/aho-corasick/count.cpp` の `build` と同じ：根をキューに入れ、取り出した節点 v で終端の印を link(v) から受け継ぎ、パターンに現れる文字 c を順に見る。子 u があれば nxt[v][c] = u、link(u) = nxt[link(v)][c]（v が根なら根）、なければ nxt[v][c] = nxt[link(v)][c]。パターンに現れない文字はどこからも根へ移る
  - 上の段：Trie。静的な図 failure-links.svg と同じ配置（h の枝が左、s の枝が右。子は文字の順）で、終端は二重丸、辺の文字は斜体、失敗リンクは破線の矢印。根を指す失敗リンクは、根まで矢印を引くと Trie の辺と重なって読めないので、節点の横の短い破線の矢印と「根」の札で示す（静的な図の「描いていない節点のリンクは根を指す」の代わり。凡例に「根を指す失敗リンク」と書いた）。根以外を指す失敗リンクの曲線は、2 次のベジェ曲線の制御点の候補（75 通り）から、ほかの節点・辺の文字・既に引いた線・札に近づかず交わりの少ないものを選ぶ。本文の例では sh → h はほぼ直線、his → s は直線、she → he は his の下を回る弧、hers → s は静的な図と同じく右下を回る弧になる
  - 前半（初期状態と取り出し 1 回ごと。本文の例で 11 ステップ）：取り出した節点を濃い塗り、写す元 link(v) を破線の輪、取り出し済みを薄い塗りと太い輪、失敗リンクが未定の節点を点線の円で描く。このステップで決まった子の失敗リンク（矢印か「根」の札）を太くする。下の段に「キュー（先頭 → 末尾）」と、2 行の表（上が link(v) の行、下が v の行。列はパターンに現れる文字）を置く。v の行は子の欄を塗り・太字、写した欄を破線のマスにし、link(v) の行で子の欄の値（＝子の失敗リンク）を太枠にする。根を取り出すときは写す元の行を空の点線のマスにする
  - 後半（読み始め・1 文字ごと・読み終わり。本文の例で 8 ステップ）：いまの状態を濃い塗り、失敗リンクの連鎖を薄い塗り・太い輪・太字、連鎖の失敗リンク（最後の「根」の札を含む）を太くする。連鎖の上の終端（出現）は二重丸の外側の輪を太くする。子へ進んだときはその辺を太線にし、子がなく遷移表の値へ移ったとき（she → her）は実線の矢印を引く。下の段に、テキストのマス（いまの文字は太枠、未読は薄く）、各文字を読んだ後の状態の行（根 s sh she her hers）、出現の括弧（このステップで見つけたものは太い青、前のものは細い灰。重ならない段に分ける）、パターンごとの出現回数（このステップで増えたものは太字）を置く
  - 凡例は 2 行：1 行目は二重丸・失敗リンク・根を指す失敗リンク、2 行目は節点の塗り（前半と後半で入れ替える）・今回の移動・出現の括弧
  - caption（だ・である調）の例：「sh を取り出す。sh の行は link(sh) = h の行を写し、子のある欄（e）だけ自分の子にする。子 she の失敗リンクは nxt[link(sh) = h][e] = he である。」（仕様の caption 例を含む）、「she を取り出す。…link(she) = he が終端の印を持つので、she もその印を受け継ぐ。」、「4 文字目の e を読む。sh に子 e があるので、she へ進む。失敗リンクをたどると she・he・根 で、ここで終わる出現は she と he の 2 つである。」、「5 文字目の r を読む。she に子 r はない。遷移表では nxt[she][r] = her（link(she) = he の行から写した値）なので、her へ移る。…」。読み終わりの caption で、連鎖を毎回たどると遅くなることがあり、まとめて数える方法は出現回数の集計の節にあると案内する
  - 状態の項目：`phase`（init / pop / scan / read / done）、前半は `popped`・`from`・`kids`（{c, u, link}）・`row`・`fromRow`・`inherited`・`queue`・`done`・`link`・`mark`、後半は `pos`・`char`・`prev`・`cur`・`via`（child / root / jump）・`chain`・`found`・`all`・`counts`・`trail`。節点は文字列で表す（根は ""）
- `tests/viz/aho-corasick.test.mjs`：試験 11 件
  - 試験の config が本文の div と同じこと
  - 本文の例：取り出す順（根, h, s, he, hi, sh, her, his, she, hers）、最終の失敗リンク（静的な図と同じ sh → h・she → he・his → s・hers → s、ほかは根）、sh の行と h の行、仕様の caption 例、she が he の印を受け継ぐこと、状態の列 根 → s → sh → she → her → hers と移り方、4 文字目の連鎖 she・he・根 と出現 2 つ、5 文字目の遷移表の caption、6 文字目の連鎖 hers・s・根、回数 he 1・she 1・his 0・hers 1（静的な図 fail-tree.svg の部分木の和と同じ）
  - 本文の inherit-terminal の例（bc・abcd と abcx）：abc が bc の印を受け継ぎ、状態が a → ab → abc → 根 と動く
  - 端の場合：1 文字、パターンに現れない文字だけ、入れ子のパターン（a・aa・aaa と aaaa で回数 4・3・2）、同じ節点にとどまる移動（aaa のまま）、上限ちょうどの config
  - 乱数の config 3000 通り（描けないものを除いて 2000 通り以上）と、2 つのパターン集合 × a・b の 6 文字以下のテキストすべてで、定義どおりの素朴な方法（接尾辞で Trie にある最長のものを直接探す）と一致すること。各状態で、取り出す順とキュー、link(v)・行・子の失敗リンク（link(u) = nxt[link(v)][c]）、写した欄、決まった失敗リンクだけが値を持つこと、終端の印、状態の列、連鎖、ここで終わる出現（＝連鎖の上の終端）、回数を確かめる。caption で「根」の後に余分な空白がないこと
  - 決定的であること・入力を書き換えないこと・誤った config 20 通り・viewBox
  - 偽の h で render を呼び、新しい失敗リンクと「根」の札が太いこと、写す元の輪、表の子の欄・写した欄・太枠、点線の円、後半のいまの状態・連鎖・太線の辺・出現の輪・括弧・状態の行・回数、移動の矢印を確かめる。本文の例の全ステップで、失敗リンクと移動の曲線がほかの節点の円から 4 以上離れ、文字（幅の見積もり）が枠に収まること

## config

`{"patterns": ["he", "she", "his", "hers"], "text": "ushers"}`（執筆者の仮のまま変えていない）

- patterns：1〜6 個、各要素は英小文字 1〜5 文字、同じ文字列は不可。text：英小文字 1〜8 文字（パターンに現れない文字を含んでよい）
- 幅 360 で読めるよう、Trie の節点は根を含めて 16 個まで、葉は 4 個まで、パターンに現れる文字は 6 種類まで。超えると Error（viz.js が「図を表示できなかった：…」と出す）
- viewBox は幅 400。高さは Trie の深さと出現の括弧の段数で決まり、本文の例は 403（幅 390 の画面で図は約 337×339px で、22em の上限にかからない）

## 本文の変更

`docs/string/aho-corasick.md`：

- 73 行目（div の直前の 1 文）を、図の読み方を述べる 2 文に書き直した。旧「次の動く図は、失敗リンクを BFS 順に張っていく様子と、テキスト ushers を流したときの状態の移動を示す。」→ 新「次の動く図の前半では、節点を BFS 順に取り出し、その行（[次の節](#build)で述べる遷移表の行で、各文字を読んだ後の状態の並び）を失敗リンク先の行から写しながら子の失敗リンク（破線の矢印）を張る。後半ではテキスト ushers を 1 文字ずつ読み、着いた状態（濃い丸）から失敗リンクの連鎖（薄く塗った丸）をたどって、連鎖の上にある終端（二重丸）を出現として拾う。」（図の前に遷移表の「行」を使うので、次の節へのリンクで短く説明した）
- 77 行目（div の直後）は変えていない。状態の列・連鎖・出現の説明が図と一致する
- front matter の `updated` を 2026-10-29 にした（`stage` は変えていない）。div の data-config は変えていない

## 確かめたこと

- `node --test tests/viz/aho-corasick.test.mjs`：11 件すべて通る。`node --test "tests/viz/*.test.mjs"`：213 件すべて通る
- `python3 tools/check_pages.py --page aho-corasick`：エラー 0・警告 1（143 行の「インラインの数式の長い \text」。前からのもの）
- `npx textlint docs/string/aho-corasick.md`：エラー 0・警告 25（HEAD と同じ数。書き直した 73 行からは出ない。一度 4 つ目の読点で max-ten が出たので直した）
- `python3 tools/check_svg.py --page aho-corasick`：エラー 0・警告 1（failure-links.svg の幅 480。前からのもの。SVG は触っていない）
- `python3 tools/gen_site.py --check`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が古いと出る（updated の変更。バッチのほかのページの分も含むとみられる）。gen_site.py は動かしていない
- ビルド：`uv run mkdocs build -q -d <作業用フォルダ>/site` で警告なし（Material の告知だけ）
- ブラウザ：chrome-headless-shell 146.0.7680.76 を CDP で操作（Node の WebSocket。日本語は /mnt/c/Windows/Fonts を足した fonts.conf）。作業用フォルダのサイトを自分の http サーバー（空いているポート）で配った
  - 幅 390 ライト（全 19 ステップ）・幅 1280 ライト・幅 390 ダーク・幅 1280 ダークで、「次へ」を押して 1 / 19 → 19 / 19 と進み、最後で「次へ」「最後へ」が無効になる。ステップごとに Trie の塗り・新しい失敗リンク・表・キュー（前半）、いまの状態・連鎖・移動の矢印・括弧・回数（後半）が caption どおりに変わることを目で確かめた。ダークでも破線・札・表の破線のマス・括弧が見える。幅 390 で図は約 337px、ノードの字は約 11.8px、凡例は約 10.5px で読める。幅 1280 では 22em の高さの上限で約 349px 幅に描かれる
  - 全ステップで svg の中の要素の getBBox が viewBox に収まる。図の中の要素の右端は 374px 以下（幅 390）。ボタンは 44×44px
  - キーボード（→ → End ← Home で 1 → 2 → 3 → 19 → 18 → 1）、スライダー、自動再生（4× で 1.6 秒後に 6 / 19）、instant navigation（本文の KMP 法へのリンクで移って戻ると図は 1 つで 1 / 19 から）。JS の例外・console.error なし（console の 403 2 件は Material の GitHub リポジトリ表示の外部への取得で、図とは関係ない）
  - 別の config を本文のコピーのページに入れて描いた：Wikipedia 風の 6 パターン（葉 4）、aaa（1 本の道。隣の深さへのリンクが見えるように少しふくらむ）、bc・abcd と abcx、abcde・bcd・cde（深さ 5）。誤った config（同じパターン 2 回）では「図を表示できなかった：patterns に同じ文字列が 2 回ある：ab」と出る
- 作業の道具（検証で使える）：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-viz-aho/scripts/shoot.mjs（ステップを送って撮る）と /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-viz-aho/scripts/interact.mjs（はみ出し・キーボード・自動再生・instant navigation）。スクリーンショットは /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-viz-aho/shots/

## 未解決の点

- catalog の visual の 3 つ目「出現の集計を失敗リンクの木で葉から根へ足す図」は、動く図に入れず、count-occurrences の節の静的な図 fail-tree.svg に任せた（動く図は failure-links の節にあり、集計は 2 節後で導入するため）。読み終わりの caption で集計の節へ案内している
- 根を指す失敗リンクは矢印を根まで引かず「根」の札で示す。静的な図（描かずに凡例で断る）と表し方が違う
- 失敗リンクの曲線は候補から自動で選ぶので、本文以外の config（葉 4 個の Trie など）では、根の上を回る弧や交差が増えて混むことがある。本文の例では、線はほかの節点の円から 9px 以上離れる（試験は 4 以上を確かめる）
- 遷移表の行は、本文では次の節（build）で導入する。図の前の文で次の節へリンクし、短く説明した

## 提案・気づいた点（担当外）

- progress.md と Issue #51：aho-corasick の JS と試験ができた。Issue #51 のほかの 3 つ（max-flow-residual・convolution-naive・inclusion-exclusion-venn）と、`data-viz` の名前に JS がないときの検査は、この担当の範囲外
- 生成物：updated を変えたので、メインが `tools/gen_site.py` で作り直す
- 静的な図 `docs/img/aho-corasick/fail-tree.svg`：幅 360 の表示で、sh の「止 1 / 計 1」の文字が隣の she の二重丸に重なって一部が隠れる（render_svg.py の 360px で確認）。Issue #50 の一覧には aho-corasick がない → メインの追加の依頼で直した（下の「追加の依頼への対応」）
- 共通の部品 viz.js・kp.css は変えていない。`.kp-viz__svg` の `max-height: 22em` で、幅の広い画面でも高さ 352px に収まるよう縮む（この図は約 349px 幅）。読めるので変える必要はない

## 追加の依頼への対応（2026-10-29、メインから）

### 1. 143 行目のインラインの数式の長い \text

- 場所：`docs/string/aho-corasick.md` の inherit-terminal の節の箇条書き 2 行（142・143 行）。143 行の `$\mathrm{mask}[v] = (\text{ちょうど } v \text{ で終わるパターンの bit}) \mathbin{\text{OR}} \mathrm{mask}[\mathrm{link}(v)]$` が check_pages の警告「インラインの数式の長い \text」（全角 17 字ぶん）に出ていた。142 行も同じ形（全角 15 字ぶんで警告の手前）なので、#33 と同じく日本語を数式の外に出して 2 行をそろえた
- 新：「個数：$\mathrm{num}[v] = \mathrm{num}_0[v] + \mathrm{num}[\mathrm{link}(v)]$。$\mathrm{num}_0[v]$ はちょうど $v$ で終わるパターンの数である。…」「集合：$\mathrm{mask}[v] = \mathrm{mask}_0[v] \text{ OR } \mathrm{mask}[\mathrm{link}(v)]$。$\mathrm{mask}_0[v]$ はちょうど $v$ で終わるパターンの bit である。…」。OR は手引き §6 の `\text{ OR }` にした（このサイトで `\mathbin{\text{OR}}` はここだけだった）。意味は変えていない
- 定義を括弧で後ろに付けた形では textlint の sentence-length（133 字）が出たので、別の文に分けた

### 2. fail-tree.svg の文字の重なり

- 下の段の節点を横に広げた：she 90 → 120、his 185 → 210、hers 290 → 300（各節点の「止・計」の文字も同じだけ右へ）。子から親への矢印 3 本（she → he、his → s、hers → s）の端を、子の円の外 1・親の円の外 4 の位置で計算し直した。上の段・根・凡例・値は変えていない（代替テキストの内容もそのまま当てはまる）
- 文字と隣の円の間：sh の文字と she の外側の輪 13px、she の文字と his の輪 8px、his の文字と hers の輪 8px（viewBox の単位）。hers → s の矢印は s の「計 2」の左下から 5px 以上離れる

### 確かめたこと

- `python3 tools/check_pages.py --page aho-corasick`：エラー 0・警告 0
- `npx textlint docs/string/aho-corasick.md`：エラー 0・警告 25（HEAD と同じ数。142・143 行からは出ない）
- `python3 tools/check_svg.py --page aho-corasick`：エラー 0・警告 1（failure-links.svg の幅 480。前からのもので、今回は頼まれていないので変えていない）
- `python3 tools/render_svg.py docs/img/aho-corasick/fail-tree.svg --width 360 --width 720`：どちらの幅でも文字と円の重なりがなく、矢印が子から親へつながることを目で確かめた
- ビルドし直したページを chrome-headless-shell の幅 360・390 で開き、scrollWidth = clientWidth（横にずれない）ことと、2 行の数式が = の後で折り返して本文の幅に収まることを撮って確かめた。前に幅 390 で scrollWidth が 392 だったのは、この数式のはみ出しとみられる
- 本文の幅を超える KaTeX は、133 行の別行の数式 $$\mathrm{term}[v] = (\mathrm{str}(v) \text{ がパターン}) \lor \mathrm{term}[\mathrm{link}(v)]$$ だけ（幅 360 で約 382px）。別行の数式は自分の枠の中で横に送れるのでページはずれない。気になるなら別の Issue で短くする

## 検証の指摘への対応（verify-aho-corasick.md）

合格、直すべき 0 件。直すとよい 1 件を直した。

1. 辺の文字が輪に隠れる（9〜11・16 / 19）：render で、Trie の辺の文字（斜体の 1 文字）を節点のループの後に描くようにした。写す元の輪（半径 R + RING + 5）や出現の太い輪がかかっても、文字が上に出る。縁取りは 3px から 4px（`stroke-linejoin:round`）にして、輪の破線を文字の周りだけ切る。文字に `data-edge-label`（子の節点の文字列）を付けた。辺・節点・矢印の位置は変えていない
   - 試験を 1 件足した（12 件）：本文の config の全 19 ステップで、辺の文字 9 個がどれも節点の円・終端の輪・写す元の輪より後に、縁取り付きで描かれること。10 / 19 で、写す元 he の輪より後に he → her の「r」があること
   - 確かめたこと：`node --test tests/viz/aho-corasick.test.mjs` 12 件、`node --test "tests/viz/*.test.mjs"` 216 件すべて通る。作業用フォルダのビルドに新しい JS を入れ、chrome-headless-shell の幅 390 で 1・9・10・11・16・18 / 19（ライト）と 10・16 / 19（ダーク）を撮り、s → sh の「h」（9・11）と he → her の「r」（10・16）が輪の上に読めること、ほかの描画が変わらないことを目で確かめた（拡大は /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-viz-aho/shots/fix-zoom.png）。横スクロールなし
- 参考の 4 点（ダークの is-yes の塗りの薄さ、本文以外の config の混み具合と m・w の 5 文字の名前、142 行の後の「。」の送り、検証での instant navigation の確かめ方）は、kp.css・本文の言い方・ほかの図にかかわるか、本文の図に影響しないので、この直しでは変えていない
