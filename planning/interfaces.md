# 部品どうしの約束（インターフェース）

工程6（土台作り）で、サイト・生成スクリプト・検査・CI・執筆の手引きを別々の担当が作るので、その間の約束をここに決める。上位の決定は設計書（[design.md](design.md)）と [design-review.md](design-review.md)。この文書と食い違ったら、この文書を直してから作る。

- 版：2026-10-21 初版。2026-10-29 ページの部品を足した（§2 の related の表示、§7 の段階と更新日・誤りの報告・関連・節のレベルの印。Issue #9・#10・#54・#56）

## 1. ファイルの置き場所と URL

| もの | 置き場所 | 公開される URL |
| --- | --- | --- |
| ページ | `docs/<field>/<id>.md` | `https://yuukougun.github.io/kyopro-atlas/<field>/<id>/`（`use_directory_urls: true`） |
| 分野の入口 | `docs/<field>/index.md`（生成） | `…/<field>/` |
| ホーム | `docs/index.md`（手書き＋生成部分） | `…/` |
| 生成した一覧 | `docs/lists/<name>.md`（生成） | `…/lists/<name>/` |
| Claude 用の索引 | `docs/llms.txt`・`docs/index/<field>.md`（生成） | `…/llms.txt`・`…/index/<field>/` |
| 図の画像 | `docs/img/<page-id>/<name>.svg` | 本文から相対リンク |
| JS・CSS・同梱ライブラリ | `overrides/assets/{js,css,vendor}/` | `…/assets/…` |
| サイト用のデータ | `overrides/assets/data/graph.json`（生成） | `…/assets/data/graph.json` |
| ナビゲーション | `nav.yml`（生成。mkdocs.yml が `INHERIT: nav.yml`） | — |
| コード片 | `snippets/<page-id>/<name>.cpp` と `<name>.yaml`（設定） | 本文に取り込む |
| 問題の台帳 | `data/problems.yaml` | 出さない |
| 最近の ABC | `data/recent-abc.yaml` | 出さない |
| ACL（同梱） | `third_party/ac-library/`（v1.6、CC0） | 出さない |

- field は設計書 §2.1 の15個（start・guide・basics・thinking・dp・graph・tree・ds・math・comb・string・geometry・misc・patterns・cpp）
- 生成物はすべてコミットする。`tools/gen_site.py --check` で、作り直しても差分がないことを確かめる

## 2. front matter

形式は `schema/page.schema.json`（JSON Schema）で検査する。catalog の第2版の項目を写し、制作の項目を足したもの。

```yaml
---
id: lazy-segment-tree                  # 必須。ファイル名と同じ
title: 遅延セグメント木                 # 必須
nav_title: null                        # 任意
aliases: [遅延セグ木, Lazy Segment Tree]
type: technique                        # 必須：technique / thinking / pattern / hub / overview / cpp / guide
field: ds                              # 必須
chapter: 区間クエリ                     # 任意（小さい分野と、分野の先頭の入口ページは省く）
order: 120                             # 必須。分野の中の並び順（10刻み）
level: 水                              # 基礎 / 水 / 青 / 黄 / 発展 / null
kind: [データ構造, 区間クエリ]           # 必須（1〜3個。catalog/README §4 の語彙）
prerequisites: [segment-tree]          # 必須（空でもよい）。ページの id
related: [lazy-segment-tree-patterns, range-set-management#merge-intervals]
summary: 区間への一括更新と区間の集約を、どちらも O(log N) で行う。   # 必須
complexity: null                       # 本文を書くときに入れる（骨格では null）
signs:
  - {type: phrase, text: 区間に一括で加算・代入し、区間の和や最小値を何度も答える}
acl: [lazy_segtree]
verify: [range_affine_range_sum]
frequency: A                           # technique・thinking・overview だけ
frequency_evidence: "recent 3（…）"
sections:                              # 上位の帯の節の扱いと、アンカーの一覧
  - {title: 区間の長さを S に持たせる, anchor: size-in-node}
  - {title: 保つ性質と push の手順（自作するとき）, anchor: invariants, level: 青}
stage: stub                            # 必須：stub / draft / reviewed / done
updated: 2026-10-21                    # 必須
cpp_std: null                          # cpp だけ（17・20・23）
gcc_min: null                          # cpp だけ（13・14・15）
atcoder: null                          # cpp だけ（true / false）
---
```

- `status` は使わない（Material の予約キー）
- 本文の見出しには、sections の anchor を `## 区間の長さを S に持たせる {#size-in-node}` の形で付ける。stage が draft 以降なら、sections の全 anchor が本文にあることを検査する
- 骨格（stub）のページの本文は、冒頭の要点の囲みだけ（§4）
- related は、知識マップのほかに、ページの下の「関連」の欄に書いた順で出る（§7）。書いた順が表示の順になるので、近いものから書く。`id#anchor` は「ページの題名 › 節の題」で節へリンクする（節の題は相手の sections の title。相手が stub の間は、節ではなくページへリンクする）
- sections の level は、見出しと目次の項目のレベルの印と、「理解した」のチェック欄になる（§7）。見出しに色の印を手で書かない
- stage と updated は、ページの最後の行に出る（§7。stage の表示名は stub＝準備中・draft＝下書き・reviewed＝検証済み・done＝完成）

## 3. 問題の一覧の書式

例題・練習・力試しは、目印の囲みの中に1問1行で書く。JS（解いたチェック）と検査と生成スクリプトは、この囲みだけを見る。

```markdown
<div class="kp-problems" data-role="practice" markdown>

- [ABC300 E. Dice Product 3](https://atcoder.jp/contests/abc300/tasks/abc300_e)（diff 1354）：サイコロを振り続けて積が N になる確率を求める。

</div>
```

- `data-role` は example・practice・challenge のどれか
- 1行の形（正規表現）：`^- \[(?P<label>[^\]]+)\]\((?P<url>https://atcoder\.jp/contests/(?P<contest>[^/]+)/tasks/(?P<id>[A-Za-z0-9_]+))\)（diff (?P<diff>\d+|—)）：(?P<summary>.+)$`
- label・url・diff は台帳（`data/problems.yaml`）から機械的に作れる形にする。label は「コンテストの表示名＋空白＋記号. 題名」。表示名：abcNNN → `ABCNNN`、arcNNN → `ARCNNN`、agcNNN → `AGCNNN`、typical90 → `典型90`、dp → `EDPC`、tdpc → `TDPC`、math-and-algorithm → `アルゴ数学`、tessoku-book → `鉄則本`、ほかは contest id を大文字にしたもの
- 例題は、ページの中で1問ずつ小見出しを立て、その下に1行だけの囲み（`data-role="example"`）を置き、続けて方針を書く。解法の詳細は折りたたみ（`??? note "解法の詳細"`）
- 本文の atcoder.jp の問題へのリンクは、すべてこの囲みの中に置く（本文中で問題に触れるときは、ページの id かその小見出しへのリンクにする）
- 台帳で確認済みの問題だけを書ける。difficulty は台帳の値と一致させる（`tools/fix_problems.py` で直せる）

## 4. 冒頭の要点

全ページの本文の最初に置く（ユーザーの決定。decisions.md 2026-10-21 工程5）。

```markdown
!!! abstract "要点"
    - **何ができるか**：…
    - **いつ使うか**：…（問題のサイン）
    - **計算量**：…
    - **前提**：[セグメント木](../ds/segment-tree.md)
```

- 骨格では「何ができるか」に summary、「いつ使うか」に signs、「前提」に prerequisites を機械的に入れ、計算量は「（執筆時に書く）」とする（新しい事実を骨格に載せない。design-review T13）
- guide・start・patterns・hub は、項目を内容に合わせて変えてよい（何のページか・使い方）

## 5. graph.json

`tools/gen_site.py` が書き、知識マップ・ロードマップ・進捗の集計の JS が読む。

```json
{
  "version": "<入力の内容のハッシュ>",
  "updated": "<front matter の updated の最大値>",
  "levels": ["基礎", "水", "青", "黄", "発展"],
  "fields": [{"id": "basics", "title": "基本テクニック", "order": 3}],
  "pages": [{
    "id": "lazy-segment-tree", "title": "遅延セグメント木", "nav_title": null,
    "field": "ds", "chapter": "区間クエリ", "order": 120, "type": "technique",
    "level": "水", "kind": ["データ構造", "区間クエリ"], "frequency": "A", "stage": "stub",
    "url": "ds/lazy-segment-tree/", "summary": "…",
    "prerequisites": ["segment-tree"], "related": ["lazy-segment-tree-patterns"],
    "sections": [{"anchor": "invariants", "title": "…", "level": "青"}],
    "problems": [{"id": "abc340_e", "role": "example"}]
  }],
  "problems": {"abc340_e": {"label": "ABC340 E. Mancala 2", "url": "https://atcoder.jp/…", "difficulty": 1157}}
}
```

- url はサイトのルートからの相対パス（JS が base の URL を付ける）
- pages[].problems は本文の問題の一覧から拾ったもの（骨格では空）
- related は配置に使わない（design-review T2）。`id#anchor` の anchor は外して持つ

## 6. ブラウザに保存するデータ

- localStorage のキーは1つ：`kyopro-atlas:v1`。値は JSON
```json
{"solved": {"abc340_e": true}, "understood": {"lazy-segment-tree": {"水": true, "青": false}}, "updatedAt": "2026-10-21T12:00:00+09:00"}
```
- 「理解した」はページ×レベル（ページの level と、sections にある上位の level の数だけチェックがある）
- 書き出し：この JSON をテキストで表示してコピーできるようにする。読み込み：貼り付けた JSON で置き換えるか、合わせる（解いた・理解したのどちらかが true なら true）
- 別のタブの変更は storage イベントで反映する。localStorage が使えない環境でもページは壊れないこと（try/catch）

## 7. テンプレートと JS の受け持ち

| 表示 | 作り方 |
| --- | --- |
| ページ上部のバッジ（レベル・分野・kind・準備中） | `overrides/main.html` が `page.meta` から出す。レベルは AtCoder の色。kind は種類別の一覧（`lists/kind-<…>`）へのリンク。stage が stub なら「準備中」の帯 |
| 「理解した」のチェック | テンプレートがページ×レベルのチェック欄の HTML を出し、`progress.js` が localStorage と結ぶ。チェック欄（`label.kp-check`）はどれも（ページのレベルの欄も）`span.kp-understood__item` で包む。上の帯の節の欄（「青の節」など）にだけ、横にその帯の最初の節（sections の順）へ移るリンク（`a.kp-check__jump`。矢印は CSS で、上では↓・下では↑）を置く。準備中のページは本文に節の見出しがないので置かない |
| 節のレベルの印 | sections に level のある節の見出しと目次の項目に、テンプレートが `span.kp-mini.kp-lv-<色>.kp-sec-lv` を入れる。見出しは本文の HTML の `<a class="headerlink" href="#<anchor>"` の前（toc の permalink が前提）、目次は `site_nav` ブロックの HTML の `<a href="#<anchor>" class="md-nav__link">` の直後（CSS の order で題の後ろに出す）。どちらも文字列の置き換えで、JS を使わない（HTML に書かれるので instant navigation でも出る。目次の部分テンプレートは上書きしない） |
| 前提・次に読む・関連 | テンプレートが `nav.pages` の各ページの meta を引いて出す（次に読むは同じレベルと1つ上を優先して8件まで。残りは知識マップの焦点の表示へのリンク）。関連は related を書いた順に20件まで（超えた分は知識マップの焦点の表示へのリンク）。`id#anchor` は「ページの題名 › 節の題」で、レベルの印は節の level（なければページの level）。相手のページが stub なら、本文に節の見出しがないので、節ではなくページへのリンクにする（印はページの level）。前提・出した次に読む・関連にすでに出たページは、関連に重ねて出さない（節への関連は出す） |
| 段階・更新日・誤りの報告 | テンプレートがページの最後の行（`div.kp-page-info`）に出す。段階と更新日は id のあるページだけ（段階は「この教材の使い方」の #stub へのリンク）。「このページの誤りを報告する」はどのページにも出し、GitHub の新しい Issue を `?template=page-error.yml&title=誤りの報告：<題名>&page-title=<題名>&page-url=<URL>&page-updated=<updated>` で開く（ひな形は `.github/ISSUE_TEMPLATE/page-error.yml`。項目の id が引数の名前。題名は front matter の title、URL は page.canonical_url）。labels などの引数は権限のない人には 404 になるので付けない |
| 解いたチェック | `progress.js` が `.kp-problems` の各行の先頭にチェック欄を付ける |
| 知識マップ | `docs/guide/knowledge-map.md` の `<div id="kp-map"></div>`。`map.js` が graph.json を読み、既定は分野ごとの表示、`?focus=<id>` で祖先と子孫だけ、全体は分野を頂点にした図。理解したページを塗る |
| ロードマップの集計 | `progress.js` が graph.json と localStorage から、レベル・分野ごとの解いた数・理解した数を出す（`<div class="kp-roadmap-stats"></div>`） |
| 動く図 | `<div class="kp-viz" data-viz="<名前>" data-config='{…}'></div>`。`viz.js`（共通の部品）が `overrides/assets/js/viz/<名前>.js` を読み、`window.KPViz.register(名前, {states(config) → 状態の配列, render(svg, state, config)})` で登録された図を、ステップ送りの操作（最初・前・次・最後・自動再生・速度、キーボード、スワイプ）付きで描く |
| 初期化 | すべての JS は Material の `document$` を購読して、instant navigation のたびに取り付け直す |

- class の接頭辞は `kp-`
- 数式は KaTeX 0.16.47（同梱）。`pymdownx.arithmatex`（generic）が出す `.arithmatex` だけを描く

## 8. 生成スクリプトが書くもの（`tools/gen_site.py`）

| 生成物 | 中身 |
| --- | --- |
| `nav.yml` | 分野の順（§1）→ 分野の入口 → chapter ごと（order の順）。chapter のないページは分野の先頭。nav_title があればそれを使う |
| `docs/<field>/index.md` | 分野の入口：章ごとのページの一覧（題名・レベル・要約・準備中の印） |
| `docs/lists/` | レベル別（`level-<基礎…>`）と種類別（`kind-<…>`）の一覧。ファイル名は英字の短い名前にし、対応を gen_site.py に持つ |
| `docs/llms.txt` | 1行「- [タイトル](URL)（id・レベル・分野・段階）：要約」。冒頭に使い方と分野ごとの詳細索引への案内、版（入力の内容のハッシュと updated の最大値） |
| `docs/index/<field>.md` | 分野ごとの詳細索引：ページごとに id・URL・別名・サイン・kind・節（`id#anchor` と URL） |
| `overrides/assets/data/graph.json` | §5 |
| 手書きのページの生成部分 | `<!-- gen:begin 名前 -->` 〜 `<!-- gen:end 名前 -->` の間：逆引き辞典（constraint・phrase・shape）、ロードマップの列（色ごとに前提の順の1本の列。上位の節を含む）、位置ごとの頻出手法（recent-abc.yaml から）、問題 → ページ・最近の ABC → ページの表、Library Checker の対応表（verify から）、用語の索引（題名・別名・acl から） |

## 9. コード片

- `snippets/<page-id>/<name>.cpp`：完全なプログラム。本文に取り込む部分を `// --8<-- [start:core]` 〜 `// --8<-- [end:core]` で囲み、本文では `--8<-- "<page-id>/<name>.cpp:core"` と書く（`pymdownx.snippets` の `base_path: [snippets]`）
- `snippets/<page-id>/<name>.yaml`：設定
```yaml
compilers: [g++-15]          # cpp の版の確認なら [g++-13, g++-15]
flags: "-std=gnu++23 -O2 -Wall -Wextra"
expect: run                  # run（実行して出力が一致）／ compile-error ／ warning
                             # ／ crash（0 以外の終了コードかシグナルで終わる。output があれば出力も比べる）
cases:
  - {input: "3\n1 2 3\n", output: "6\n"}
```
- ACL は `third_party/ac-library/` を `-I` で使う
- 本文に ```` ```cpp ```` を直接書かない（取り込みだけ）。擬似コードは ```` ```text ````

## 10. 検査（`tools/check_pages.py` ほか）

| 検査 | 道具 |
| --- | --- |
| front matter の形 | `tools/check_pages.py`（schema/page.schema.json） |
| id の一意・ファイル名との一致・前提と related の解決（`id#anchor` の anchor が相手の sections にあるか）・前提の循環・レベルの逆転 | `tools/check_pages.py` |
| 問題の一覧の書式・台帳で確認済み・difficulty の一致・囲みの外の問題リンク | `tools/check_pages.py` |
| 本文の ```` ```cpp ```` の禁止、sections の anchor が本文にあるか（draft 以降）、要点の囲みがあるか、別名が冒頭にあるか（draft 以降） | `tools/check_pages.py` |
| 生成物の鮮度 | `tools/gen_site.py --check` |
| コード片 | `tools/check_snippets.py`（`--changed` で変わったものだけ） |
| サイトのビルド | `mkdocs build --strict` |
| 表記 | textlint（`.textlintrc.json`・`prh.yml`） |
| noai | `tools/check_noai.py <URL>` |
