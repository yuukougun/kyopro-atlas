# 検証：動く図 aho-corasick

工程11・バッチ f1、Issue #51 のうち aho-corasick の分。検証の担当 verify-f1-viz2（作った担当 f1-viz-aho とは別）。2026-10-29。

対象：`overrides/assets/js/viz/aho-corasick.js`・`tests/viz/aho-corasick.test.mjs`・`docs/string/aho-corasick.md`（73 行の図の前の 2 文、142・143 行の長い `\text` を数式の外に出した直し、front matter の `updated`）・`docs/img/aho-corasick/fail-tree.svg`（360px での文字の重なりの直し）。作った担当の報告は `planning/batches/viz/aho-corasick.md`、仕様は `planning/batches/b2/aho-corasick.md` の「動く図の仕様」。観点は `planning/checklists/figure.md`（G1〜G7）、`code.md`（試験に当てはまる C2・C3）、`fact.md`（書き換えた文の F2・F3・F7）。

## 結論

**合格**。直すべき指摘は 0 件、直すとよい指摘は 1 件（いくつかのステップで、辺の文字が輪の下に隠れる）。状態の列は定義どおりで、caption・本文・静的な図と食い違わない。Issue #51 の完了の条件のうち、このページの分（「図を表示できなかった」が出ない・data-viz の名前の JS がある）を満たす。

## 確かめたこと

- **状態の列（G1）**：試験とは別に、定義だけから期待値を作る検査を書いた（作業用フォルダの `scripts/aho-check.mjs`）。Trie の節点はパターンの接頭辞の集合、link(v) は真の接尾辞のうちその集合にある最長のもの、nxt[v][c] は v + c の接尾辞のうちその集合にある最長のもの、BFS は子を文字の順に入れる、受け継いだ印は「接尾辞にパターンがある」、後半の状態は読んだ部分の接尾辞のうち集合にある最長のもの、出現は読んだ部分の接尾辞になっているパターン（長い順）、とした。states のすべての値（popped・from・queue・row・fromRow・kids と子の失敗リンク・その時点の link と mark・inherited・cur・prev・via・chain・found・counts）と、**すべての caption の文字列**（期待する文を別に組み立てて完全一致で比べた）を突き合わせた
  - 範囲：a・b の 3 文字以下の文字列から作ったパターン集合（1〜3 個のすべて）× a・b・c の 4 文字以下のテキスト（間引き）と、乱数 30,000 通り（パターンに現れる文字 2〜6 種類、パターン 1〜6 個・長さ 1〜5、テキスト 1〜8 文字で、パターンにない文字 x・y・z を含む）。描ける 60,284 通り・834,216 状態で食い違いは 0 件（描けない 5,045 通りは「葉が多い」「節点が多い」の Error）
  - あわせて、子の失敗リンク nxt[link(v)][c] が定義の link(u) と等しいこと、連鎖の上の終端が素朴に求めた出現と等しいことを全状態で確かめた
- **本文の例を手で**：19 ステップ（初期 1・取り出し 10・読み始め 1・6 文字・読み終わり 1）。取り出す順は 根, h, s, he, hi, sh, her, his, she, hers。失敗リンクは sh → h・she → he・his → s・hers → s、ほかは根で、静的な図 failure-links.svg と本文 67 行に合う。sh を取り出すステップは link(sh) = h の行（e: he, h: h, i: hi, r: 根, s: s）を写して e の欄だけ she にし、caption は仕様の例「子 she の失敗リンクは nxt[link(sh) = h][e] = he」を含む。she を取り出すと he の印を受け継ぐ（本文 inherit-terminal）。ushers の状態は 根 → s → sh → she → her → hers（u は根のまま、r は she に子がなく nxt[she][r] = her）、4 文字目の連鎖は she・he・根 で出現は she と he、6 文字目の連鎖は hers・s・根 で出現は hers、回数は he 1・she 1・his 0・hers 1 で、本文 77 行と fail-tree.svg の「計」に合う。手順は `snippets/aho-corasick/count.cpp` の build（取り出したときに印を受け継ぎ、子があれば link(u) = nxt[link(v)][c]、なければ nxt[v][c] = nxt[link(v)][c]）と同じである
- **描画が状態と合うか**：ブラウザの中で `def.render` を直接呼び、1,280 通りの config の 20,449 状態で調べた（`scripts/aho-sweep.mjs`）。決まった失敗リンクだけが描かれる（根を指すものは「根」の札、ほかは曲線）、太い失敗リンクは前半ではそのステップで決まった子・後半では連鎖、節点の塗り（取り出した節点・取り出し済み・リンク未定／いまの状態・連鎖）、出現の太い輪、移動の矢印（子へ進まず別の節点へ移るときだけ）、表の欄の値、状態の行、出現の括弧の数が、どれも状態と合う。食い違いは 0 件
- **図の前の 2 文（73 行）**：図と合う。「BFS 順に取り出し」「失敗リンク先の行から写しながら」（下の段の link(v) の行と v の行。写した欄は破線のマス）、「子の失敗リンク（破線の矢印）」（根を指すものも短い破線の矢印と「根」）、「着いた状態（濃い丸）」（is-answer の塗り）、「失敗リンクの連鎖（薄く塗った丸）」（is-yes。ライトでは薄い塗りと太い輪）、「終端（二重丸）を出現として拾う」（拾った終端は外側の輪が太くなる）が、凡例・描画と一致する。行の説明「各文字を読んだ後の状態の並び」は build の節の nxt[v][c] の定義と同じで、リンク先の `#build` もある。図の後の 77 行とも食い違わない。元の 1 文（「BFS 順に張っていく様子と、ushers を流したときの状態の移動を示す」）の内容をすべて含み、読み方を足した言い換えである
- **142・143 行**：意味は元と同じである。num[v] = num₀[v] + num[link(v)] で num₀[v] を「ちょうど v で終わるパターンの数」と後ろの文で定義し、mask も同じ形にした（元の `\text{ちょうど } v \text{ で終わる…}` と同じ量）。OR は手引き §6 の `\text{ OR }` で、check_pages の「長い \text」の警告は消えた。幅 390（ライト）・360（ダーク）で KaTeX のエラーはなく、横にはみ出さない（scrollWidth = clientWidth）。textlint の警告も出ない
- **fail-tree.svg**：差分は、下の段の she・his・hers とその「止・計」を右へずらし（120・210・300）、子から親への矢印 3 本の端を計算し直しただけで、値と木の形は変わらない。`tools/render_svg.py` の 360px・720px（倍率 2）で、文字と円の重なりはなく、矢印は子から親へつながる（sh の文字と she の輪、she の文字と his の輪、his の文字と hers の輪の間が空いた）。代替テキスト（木の形と部分木の和）もそのまま当てはまる。背景は白
- **試験（C2）**：`node --test tests/viz/aho-corasick.test.mjs` は 11 件すべて通る。`node --test "tests/viz/*.test.mjs"` は 213 件すべて通る（約 2 秒）。試験は、各状態で保つ性質（BFS の順とキュー、link(u) = nxt[link(v)][c]、決まったリンクだけが値を持つ、印）と、定義どおりの素朴な方法（接尾辞を直接探す）との一致を、乱数 3,000 通りと全列挙で見ている。本文の例の値と caption、端の場合（1 文字・パターンにない文字だけ・入れ子・同じ節点にとどまる移動・上限ちょうど）、誤った config 20 通り、偽の h での描画、本文の例の線と文字の位置も見ており、状態の数だけの試験ではない
- **検査**：`python3 tools/check_pages.py --page aho-corasick` はエラー 0・警告 0（全ページでもエラー 0・警告 0）。`python3 tools/check_svg.py --page aho-corasick` はエラー 0・警告 1（failure-links.svg の幅 480。前からのもので、今回は触っていない）。`npx textlint docs/string/aho-corasick.md` は警告 25 件で、HEAD の版と同じ行・同じ内容（書き換えた 73・142・143 行からは出ない）
- **ビルド**：`uv run mkdocs build -d <作業用フォルダ>/site` で WARNING・ERROR なし。`python3 tools/gen_site.py --check` は docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が古いと出る（updated を 2026-10-29 にしたため。メインが gen_site.py で作り直す）
- **ブラウザ（G2〜G4）**：chrome-headless-shell 146.0.7680.76 を CDP で操作した（Node 24 の WebSocket で書いた小さな道具）。日本語は /mnt/c/Windows/Fonts を足した fonts.conf。ビルドしたサイトを `python3 -m http.server`（127.0.0.1:52817。使い終えて止めた）で配った
  - 幅 390（ライト・ダーク）・1280（ライト・ダーク）・360（ライト）、deviceScaleFactor 2 で、「次へ」のボタンを実際のマウスのクリックで押して 1 / 19 → 19 / 19 と送り、各ステップを撮った。最後で「次へ」「最後へ」が無効になる。全ステップで横スクロールがなく、svg の中の全要素の getBBox が viewBox に収まる。ボタンは 44×44px。最小の文字は 390 で 10.5px、1280 で 10.9px（高さ 22em の上限で縮む）、360 で 9.6px（凡例の 12.5px）。JS の例外と console のエラーは 0
  - スクリーンショットで、前半の塗り・太いリンク・写す元の輪・表・キュー、後半のいまの状態・連鎖・太い辺・移動の矢印（she → her）・括弧・状態の行・回数が、各ステップの caption と合うことを目で確かめた。ダークでも破線・「根」の札・表の破線のマス・括弧・二重丸が読める
  - キーボード（図にフォーカスして → → End ← Home で 2・3・19・18・1）、Space で自動再生（4× で 1.6 秒後に 6 / 19、最後で止まる）、スライダー、横のスワイプ（タッチの左・左・右で 2・3・2）
  - **instant navigation**：手元の http.server では、sitemap.xml の URL が本番（https://yuukougun.github.io/kyopro-atlas/）のままなので Material が内部のリンクとみなさず、クリックでページ全体を読み直していた（JS の変数が残らないことで分かった）。作業用フォルダのビルドの sitemap.xml の URL を手元のものに書き換え、本当に instant navigation で移る（変数が残る）ことを確かめてから試した。本文の KMP 法へのリンクで移って「戻る」と、図は 1 つで 1 / 19 から出て、ボタンも働く。「進む」「戻る」をもう一度しても図は 1 つ
  - 誤った config（同じパターン 2 回・葉 5 個・大文字のテキスト・閉じ括弧のない JSON）では「図を表示できなかった：…」が出て、console に同じ内容の error が 1 行出る
  - 実際のフォントでの重なり（`scripts/geom.mjs`、全 19 ステップ）：文字どうしの重なり、文字にかかる失敗リンクの曲線、viewBox の外の文字はない。見つかったのは下の指摘 1 だけ
- **既存の図の書き方**：見本と同じ包み方（module.exports と KPViz.register）、states は DOM を使わない純粋な関数で入力を書き換えない、viewBox は config ごとに 1 つ（配置を WeakMap に置く）、誤った config は Error（viz.js が表示）、caption はだ・である調。色は kp.css の `.kp-v-*` と、線の inline style の Material の CSS 変数（`var(--md-accent-fg-color)` など。z-algorithm と同じ書き方）だけで、色の直書きはない
- **catalog の visual（G7）**：「Trie に失敗リンク（破線）を BFS 順に張るステップ送りと、テキストを流すときの状態の移動」を満たす。3 つ目の「出現の集計を失敗リンクの木で葉から根へ足す図」は、count-occurrences の節の静的な図 fail-tree.svg に任せている（読み終わりの caption が集計の節へ案内する）。集計は 2 節後で導入するので、この分け方でよい。図の前後の文章だけでも流れが分かる

## 指摘

| 番号 | 重さ | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい（G3） | aho-corasick.js の render：辺の文字（751〜756 行）を、節点（777〜806 行。drawNode の 705〜716 行が写す元の輪と終端の輪を描く）より先に描いている | 辺の文字（斜体の 1 文字）は親と子の円のすぐ間にあり、輪がその上に描かれるので、輪が大きいか太いステップで文字が隠れる。本文の config では、10 / 19（she を取り出す。写す元 he の点線の輪、半径 25）で he → her の「r」がほぼ隠れ、9 / 19・11 / 19（his・hers を取り出す。写す元は s）で s → sh の「h」の上半分が隠れ、16 / 19（出現として拾った he の外側の輪が太い）で「r」の上が欠ける。caption は読めるので意味は通る | 4 倍で撮った `shots/zoom-aho-10-he.png`・`zoom-aho-11-s.png`・`zoom-aho-16-he-light.png`（1 / 19 の `zoom-aho-01-he-light.png` では「r」は輪に接するが読める）。getBBox で、9〜11 のステップで写す元の輪（r = 25）が辺の文字の外接にかかる | 辺の文字を節点の後に描く（`G.labels` の描画を節点のループの後へ移す。文字には HALO があるので、輪の線を局所的に消して読める）。あるいは写す元の輪だけを辺より先に描く。試験に「本文の config の全ステップで、辺の文字が節点より後に描かれる（または見積もりの外接が写す元の輪・太い輪と重ならない）」を足す |

## 参考（数えない）

- ダークでは `.kp-v-cell.is-yes` の塗り（アクセントの 10%）がほとんど見えず、「たどる連鎖」は主に太い輪で見分ける。本文 73 行の「（薄く塗った丸）」はライトでは正確で、ダークでも薄い塗りはある。言い方を両方に合わせるなら「（太い輪の丸）」などにできる。塗りの濃さは kp.css でほかの図と共通なので、inclusion-exclusion-venn を作った担当の提案（塗り用の少し濃い class）と合わせてメインが決める
- 本文以外の config での混み具合（作った担当の「未解決の点」のとおり）：乱数 1,280 通りのうち 41 通り（パターン 6 個・葉 4 個の Trie など）で、失敗リンクの曲線がほかの節点の円の上を通る。m・w のような幅の広い文字の 5 文字の名前（`{"patterns": ["mmmmm"], "text": "mmmmmmmm"}`）では、状態の行の名前どうしが重なり、最後の名前が viewBox を 1px はみ出す。英小文字 a〜h の乱数の config では、文字の重なりは見つからなかった。本文の図には関わらない
- 幅 390 で 142 行の数式がちょうど 1 行に収まり、続く「。」が次の行の先頭に送られる（インラインの KaTeX の後で改行が許されるため。サイト全体で起きうる。はみ出しはない）
- 検証の方法：手元の http.server でビルドしたサイトを配ると、上のとおり instant navigation が効かない。作った担当の報告の「instant navigation で戻ると図は 1 つ」も、ページ全体の読み直しだった可能性がある。今回、本当の instant navigation でも問題がないことを確かめた。ほかの図の検証でも、sitemap.xml の URL を書き換えるか、JS の変数が残ることを確かめるとよい

## 作業の場所

- 検査のスクリプト：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-viz2/scripts/`（aho-check.mjs・aho-sweep.mjs・geom.mjs・steps.mjs・interact.mjs・instant.mjs・swipe.mjs・badcfg.mjs・zoom.mjs・section.mjs・cdp.mjs）
- スクリーンショット：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-viz2/shots/`（aho-390-light-x2-01〜19.png、aho-390-dark-*、aho-1280-light-*、aho-1280-dark-*、aho-360-light-*、zoom-aho-*、sec-aho-mask-*）と、fail-tree.svg の PNG `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-viz2/svg/aho-corasick/`
