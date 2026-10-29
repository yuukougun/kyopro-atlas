# display-math の検証（工程11 グループ mobile-layout・Issue #55 の数式の部分）

作業ツリー：`kyopro-atlas-wt/mobile-layout`（ブランチ fix/mobile-layout、HEAD af7ee6c に未 commit の変更）。検証したのは display-math の担当が直した math・comb の 58 ページ（137 本の別行の数式）と、その報告 `display-math.md`。ファイルは直していない（この報告だけを書いた）。日付：2026-10-29。

## まとめ

| Issue | 判定 | 一言 |
| --- | --- | --- |
| #55（数式の部分） | 直しが要る（2 点。どちらも小さい） | 幅 390px で画面幅を超える別行の数式は 119 本 → 0 本（横に送れるかの判定では 137 本 → 0 本）になったことを、担当とは別に書いたスクリプトで確かめた。KaTeX のエラーは 0、check_pages・textlint のエラーも 0。137 本の式の意味はどれも元と同じである。ただし、counting-dedup の `\substack` の 2 行が重なり、⊆ が ⊂ に見える。また expectation-of-square の「右の形」が、縦に積んだ後の並びと合わない |

## 直しが要る点

### 1. counting-dedup#min-index：和の添字の 2 行が重なり、⊆ が ⊂ に見える

- **ファイル・行**：`docs/comb/counting-dedup.md` 116 行（`\sum_{\substack{v \in Y \subseteq X \\ Y \text{ がグループにできる}}}`）
- **理由**：`\substack` は行の間をほとんど空けない。KaTeX は日本語の字の高さを知らず、M の字の高さ（0.683em）として行を詰める。実際の和文の字はそれより高いので、2 行目の「グループにできる」の上端が 1 行目の下端に届く。幅 390px で 4 倍・8 倍に拡大して撮ると、⊆ の下の横棒が「プ」の上の横画と重なって 1 本に見え、1 行目が「v∈Y⊂X」と読める（`shots-light/comb__counting-dedup__01.png`、`zoom-dedup8-crop.png`、`var-dedup-all.png` の 0 番）。ダークモードでも同じである。和文の字が M より高いのはどの和文の書体でも同じなので、手元の書体だけで起きることではない。直す前は添字が 1 行だったので、この重なりは今回の直しで生じた。⊆ と ⊂ は意味が違う（Y = X も許すかどうか）
- **直し方の案**：行の間を空ける `\substack{v \in Y \subseteq X \\[0.3em] Y \text{ がグループにできる}}`。同じページの中で描き直して確かめた。KaTeX のエラーはなく、2 行は離れ、⊆ の横棒も見え、幅も 390px に収まった（`var-dedup-all.png` の 1 番）。もう 1 つの案は、条件「グループにできる」を地の文に出し、式を `\sum_{v \in Y \subseteq X}` だけにすることである。担当の約束「日本語の説明は地の文に出す」に合う。この案にするなら、直前の段落の「$X$ の最小番号の要素 $v$ を含むグループ $Y$」に「（条件を満たすグループにできるもの）」を足す

### 2. expectation-of-square#variance：「右の形」が縦に積んだ後の並びと合わない

- **ファイル・行**：`docs/comb/expectation-of-square.md` 196 行「右の形は分子が整数なので、…」
- **理由**：直前の式（189〜194 行）は、1 行の `A = B` を `aligned` で 2 行に積んだ。そのため「分子が整数の形」は右ではなく 2 行目にある。この積み方はどの画面幅でも同じである。1 行目にも $\frac{1}{N}$ という分子が整数の分数があるので、「分子が整数」だけでは指す形が決まらない。担当は geometric-series-mod#matrix の「右の式は」を「2 つ目の式は」に直したが、ここは直し漏れている
- **直し方の案**：「右の形は」を「2 行目の形は」にする（「後の形は」でもよい）

## 確かめたこと

### 式の意味（直す前と後の突き合わせ）

- HEAD を `git archive` で作業用フォルダに出してビルドした（直す前）。作業ツリーもビルドした（直した後）。組み上がった HTML から、58 ページの `div.arithmatex` の TeX を取り出して比べた
  - 直す前にだけある式は 137 本、直した後にだけある式は 130 本だった。差の 7 本は、定義だけの式を地の文に出したもので、報告と合う。別行の数式の数は 293 本から 286 本になった
  - 137 本のうち 111 本は、組み方の命令を除くと直す前の TeX と 1 字も違わない。除いたのは `aligned`・`gathered`・`&`・`\\`・`\\[1ex]`・`\quad`・`\qquad`・`{}`・`\,` である。並べ替え・書き写しの誤りはない
  - 残る 26 本は、意図して文や項を変えたものである。1 本ずつ読み、元と同じことを言っているかを確かめた。内訳は、文を地の文に出したもの、例示の中間の項を省いたもの 4 本、`\substack` 1 本、μ の値の並びを 2 行にしたもの 1 本で、次のとおりである
    - 文を地の文に出したもの：cayley-pruefer 3、counting-labeled-graphs 2、counting-mindset、expected-value-dp、grundy-number の定義、inclusion-exclusion-dp 4、inclusion-exclusion 2、lgv-lemma、minimax、mobius-function#gcd-one、probability-dp、harmonic-sum、xor-basis
    - 例示の中間の項を省いたもの：euler-phi、gcd-properties、grundy-number#sum、stirling-first。どれも省いた後の書き方が標準的で、規則も読み取れる
- 値も計算し直した。μ(1)〜μ(12) の 6 個ずつの分け方は、1, −1, −1, 0, −1, 1 と −1, 0, 0, 1, −1, 0 で正しい。561 を法とする 2 の累乗は 263・166・67・1・1 で、Python の `pow` と合う。burnside は 6k³ + 6k³ = 12k³ で正しく、第 1 種スターリング数の行も正しい
- 地の文を変えた 20 か所と geometric-series-mod を読んだ
  - 新しい記号（$A_t$・$n(\sigma)$・$n_q$・$f(k)$・$C(d)$・$r_k$・$F(x)$・$\mathrm{dp}[\cdot]$）は使う前に定義され、ページの中のほかの意味とぶつからない。$c(n)$ はページの冒頭で定義済みである
  - 消した別行の式を指していた「この式」「右辺」は、担当がすべて言い換えていた（counting-labeled-graphs#complement）
  - 直した式の前後の「上の式・この式・右辺・左辺・1 つ目・2 つ目・行目」などの参照を機械で拾い、全部読んだ。合わないのは上の 2 番だけである
- 見出し・anchor・リンクは変わっていない。差分で、消えたリンクと増えたリンクはどちらも同じ 6 件だった

### 390px での計測

担当の `measure.mjs` は使わず、別にスクリプト（`scripts/probe.mjs`）を書いて測った。

- 作業用フォルダで `python3 -m http.server` を立て、`http://127.0.0.1:<ポート>/site-…/` で開いた
- ヘッドレスの Chrome を CDP で動かし、幅 390px・モバイルの表示で開いた。測るのは、すべての `.arithmatex` に `data-kp-rendered` が付き、フォントを読み終え、details をすべて開いた後である
- 判定は 2 つにした
  - 横に送れる：`div.arithmatex` の scrollWidth > clientWidth + 1
  - 式が入れ物より広い：`.katex-html` の中身の Range の幅 > clientWidth + 1。調査の判定に近い
- 対象は math・comb の 93 ページ（分野の入口 2 ページを含む）である

| ビルド | 別行の数式 | 横に送れる | 式が入れ物より広い | 最大の幅 |
| --- | --- | --- | --- | --- |
| 直す前（HEAD） | 293 | 137（58 ページ） | 119（54 ページ） | 876px（inclusion-exclusion-dp#tree） |
| 直す前の本文に今の kp.css | 293 | 137（58 ページ） | 119（54 ページ） | 876px |
| 直した後（作業ツリー） | 286 | 0 | 0 | — |

- 数は Issue の調査（54 ページ・119 本・最大 876px）と担当の報告（137 本・119 本）に合う
- 直す前に横に送れた 137 本のうち、`\text` の中に日本語のある式は 40 本である。判定 A では 30 本で、これも報告と合う。直した後は 0 本である
- details を閉じたまま測っても、直す前 137・119 本、直した後 0・0 本で同じだった
- ページ全体の横ずれは、直す前も後も 0 である
- 参考：375px では 147 本（61 ページ）→ 15 本（14 ページ）、360px では 161 本（67 ページ）→ 43 本（32 ページ）だった（横に送れる判定）。担当の報告の数と同じである。Issue の基準は 390px なので、残りは判定に入れていない

### KaTeX のエラー

- http で配って描いた DOM で `.katex-error` を数えた
  - math・comb の 93 ページでは、直す前も後も 0 件だった。描かれずに残った `.arithmatex`（`data-kp-rendered` のないもの）も 0 だった
  - ほかの分野の 277 ページも 0 件だった（下の「参考」の計測で一緒に見た）
- 直し方の案 1 の `\\[0.3em]` を入れた式も、ページの中で描き直してエラー 0 だった

### 書き換えない検査

- `python3 tools/check_pages.py --page <58 ページ>` はエラー 0・警告 0 だった。`--field math`・`--field comb`、全ページでも 0・0 だった
- `npx textlint <58 ファイル>` はエラー 0 だった
  - 警告は 819 → 855 で、sentence-length が +37、max-comma が −1 である。直す前の 58 ファイルは `git archive` で出し、同じ設定で流した
  - 増えた sentence-length は、どれも `$$…$$` の中の行だった
  - 地の文の警告は全体で 752 → 753 である。+1 は inclusion-exclusion#general の no-doubled-joshi「破っても破らなくてもよい」である。直す前は式の注記の中で数えられていたものが、文と一緒に地の文へ移った。「〜ても〜なくてもよい」の言い回しへの誤検出なので、直さなくてよい。担当の報告の「地の文の警告の数はどのページも変わっていない」は、この 1 件の分だけ正確でない
- front matter：58 ページとも、HEAD との差は `updated: 2026-10-29` の行だけで、stage は reviewed のままだった
- ビルド：`uv run mkdocs build -q -d <作業用フォルダ>/site-after` は警告なしで通った
- `python3 tools/gen_site.py --check` は「生成物が古い：3 ファイル」を出した（`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md`）。`updated` を変えたためで、報告のとおりである。メインが gen_site を流せば消える。生成物は手で直されていない

### 見た目（390px・2 倍で撮影）

- 直した後の 130 本を、1 本ずつ画面の横幅いっぱいで撮って見た（ライト）。ダークモードでも、counting-basics・counting-dedup・expected-value-dp・floor-sum・inclusion-exclusion-dp の 18 本を撮った
- 次の組み方がどれも崩れていないことを確かめた
  - `=`・`\equiv` でのそろえ、`\iff`・`\Longrightarrow` を左に出した鎖、`&\quad +` の字下げ
  - gathered の条件の行、分子を積んだ分数（expected-value-dp#self-loop）
  - ラベル付きの行列（matrix-power）、`\Bigl(` と `\Bigr)` を行をまたいで置いた式（reflection-principle#two-sided）
  - 囲みの中の式。囲みの枠の線は切れていない
- 崩れていたのは上の 1 番（counting-dedup）だけである

## 気づいた点（直さなくてよい）

- crt#garner の 1 行目の末尾 `+ \dots` は、後ろに演算子がないので下付きの点（…）で出る。元の `+ \dots +` は中央の点（⋯）だった。`\cdots` にすると元の見た目に近づくが、好みの範囲である
- miller-rabin#miller-rabin と mod-arithmetic#why-mod は、並べた合同式の `\pmod{…}` が最後の行にだけ付く。元の 1 行の式でも末尾に 1 つだったので、意味は変わらない

## 参考（担当の範囲の外。メインの判断の材料）

- **math・comb 以外の別行の数式**：ほかの分野の 277 ページを同じ方法で 390px で測った。横に送れる別行の数式は 165 本（98 ページ）あり、うち `\text` に日本語を含むものは 70 本である
  - 分野ごとの本数は、dp 52・basics 29・tree 15・ds 15・graph 14・string 14・geometry 14・patterns 5・thinking 4・start 2・misc 1 である
  - Issue の調査は math・comb だけを測っていた。担当の範囲も math・comb である
  - Issue の完了の条件（続きがある手がかり）は、tables の担当の kp.css の影でこれらにも効く。#55 を閉じるか、残りを別の Issue にするかはメインが決める
- **インラインの数式によるページ全体の横ずれ**（390px）：dp/knapsack-undo#prefix-and-suffix（9px）と graph/degree-sqrt#push-pull（4px）である。どちらも長いインラインの式が折り返せないためで、今回の変更の前からある
- math/miller-rabin#deterministic-bases の表のセルのインラインの式（決定的な底の並び）は、本文の幅の外まで伸びる。表の枠の中で横に送れるので、ページはずれない。表の担当の範囲である

## 作ったもの（作業用フォルダ）

`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/verify-display-math/`

- `scripts/probe.mjs`・`scripts/run.sh`：計測。`scripts/summ.py`：集計
- `scripts/texlist.py`・`scripts/flatcmp.py`：式の突き合わせ。`scripts/ctx.py`：前後の参照を拾う
- `scripts/shots.mjs`・`scripts/zoom.mjs`・`scripts/variant.mjs`・`scripts/montage.py`：撮影と描き直し
- 計測の結果の JSON：`before-open-390.json`・`beforenew-open-390.json`・`after-open-390.json`・`*-closed-390.json`・`*-375.json`・`*-360.json`・`after-other-390.json`
- 画像：`shots-light/`（130 本）・`shots-dark/`・`montage-*/`・`zoom-dedup8-crop.png`・`var-dedup-all.png`
- textlint の結果：`tl-before.json`・`tl-after.json`
- ビルド：`site-before/`（HEAD）・`site-before-newcss/`・`site-after/`。HEAD の木は `base-head/`
