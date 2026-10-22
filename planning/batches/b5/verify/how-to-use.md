# b5 how-to-use の検証（2026-10-22）

- 対象：docs/start/how-to-use.md（作業ツリーの版。HEAD との差分）
- 観点：fact.md・code.md・clarity.md・figure.md
- 確かめたこと
  - `python3 tools/check_pages.py --page how-to-use`：エラー 0・警告 0。`npx textlint`：エラー 0・警告 4（執筆者の報告どおり。「か」の重なり 2 件・$[l, r)$ の括弧 1 件・参考の行の長さ 1 件。どれも誤検出として残してよい）
  - リンク先の anchor：reverse-index-signs#by-phrase・#by-shape、reverse-index-constraints#constraint-table、problem-sets#sets-to-pages・#recent-abc、cpp-reverse-index#how-to-read、knowledge-map#focus・#progress、roadmap#not-a-syllabus・#reading-order・#progress、practice-method#choosing-problems・#records、contest-strategy#difficulty-by-position・#ai-rules、glossary#difficulty・#typical90・#acl はすべてある
  - 15 の分野・分野の並び：tools/check_pages.py の FIELD_TITLES と一致
  - 生成ブロック fields・lists・version：`gen_site.py --list-blocks` にある名前。リポジトリの写しを一時置き場に作り `gen_site.py --root <写し>` で中身を確かめた（本物のリポジトリでは流していない）。fields は「分野｜中身｜ページ｜準備中」の表、lists は「- レベル別：…（数）」「- 種類別：…（数）」の 2 行、version は「索引の版：`<hash>`（ページの updated の最大：…）」で、本文の前置き（「かっこ内はページの数である」「準備中の数は分野の一覧に出る」「Claude が書く版と見比べる」）と合う。version の hash は docs/llms.txt の「版」と同じ関数（Site.version）から出るので、Claude が書く版と比べられる
  - レベルの位置の目安：`tools/ap.py show` で abc400〜abc480 の E・F・G（各 81 問）を数え直した。E は基礎 31%・水 59%・青以上 9%、F は水 26%・青 49%・黄 19%・発展 6%、G は青以下 12%・黄 38%・発展 49%。表の「E と易しい F」「F と難しい E」「難しい F と易しい G」「G の上半分」と contest-strategy#difficulty-by-position の数字に一致
  - abc319 以降・7 問体制・2019 年以前は高めに出る：planning/design.md 106 行と一致
  - 典型90 の★：E869120 氏の Qiita の記事（参考の URL、noai なし）に「★4＝800〜1199、★5＝1200〜1599、★6＝1600〜1999、★7＝2000〜」の表がある（指摘 6）
  - 問題の行の例：`tools/ap.py show abc340_e` は「E. Mancala 2」diff 1157。台帳の summary と本文の text の行が一字一句同じ。表示名（典型90・EDPC・鉄則本・アルゴ数学）は check_pages.py の CONTEST_NAMES と一致
  - UI の記述：overrides/main.html（バッジの行き先、「理解した」の欄がページの level と上位の節の level の数だけ出ること、「青の節」の title に節の題名、下部の前提・次に読む・知識マップへのリンクと欄の再掲、準備中の帯）と overrides/assets/js/progress.js（キー `kyopro-atlas:v1`、JSON の形、storage イベントでのほかのタブの反映、保存の拒否で壊れないこと、書き出す → 「コピーする」、「今の記録と合わせる」は和集合、「今の記録を置き換える」は記録があれば 10 秒以内にもう一度押す）を 1 つずつ照らした。roadmap#progress にも `kp-progress-io` があり「同じ欄はロードマップにもある」は正しい
  - 準備中のページ：tools/make_skeleton.py の説明（要点は summary・signs・prerequisites を写し、計算量は「（執筆時に書く）」）と一致
  - claude.ai の節：claude/project-instructions.md（v0.2）・claude/explain.md・claude/record-format.md と照らした。開催中かの確認・ADT と AWC を断る対象に含めること・atcoder.jp と codeforces.com を開かないこと・ヒントか解説かを最初に聞くこと・根拠のページと節の URL・stub を根拠にしないこと・原因の 4 分類・索引の版を最後に書くこと・記録用まとめは頼まれたときだけ、はすべて一致
  - Projects の仕組み：code.claude.com「Let Claude coordinate ongoing work with Projects」（noai なし）で「歯車 → Project settings → Memory > Project instructions」「up to 16,000 characters」「every cloud thread clones」のとおり。クラウドのスレッドはリポジトリの skills を読まない、とも書いてあり、記録用スキルを手元でだけ使う本文と合う
  - 記録用スキル：.claude/skills/record-problem/SKILL.md（`disable-model-invocation: true`、`printenv CLAUDE_CODE_REMOTE` が true なら書かずに終える、1 問 1 ファイルで追記、手書きの部分を変えない、集計しない、ap.py で確かめ difficulty が null なら「未定」）と一致。code.claude.com の Skills のページで、`disable-model-invocation: true` は「Claude が自分では呼ばず、/name で手動で呼ぶ」設定であることを確かめた
  - AtCoder生成AI対策ルールの版：planning/decisions.md 27 行（20261014 版）・atcoder-system#ai-rules・contest-strategy#ai-rules と同じ書き方。AWC を「確かめきれていないので安全な側に倒す」とする扱いは atcoder-system（AWC を Beta の平日のコンテストとだけ書き、ルールの対象かを書いていない）と食い違わない（執筆者の未解決の点 1 は、このままでよい）
  - Safari：webkit.org のブログ（noai なし）で「seven days of Safari use without user interaction on the site」に script-writable storage（LocalStorage を含む）を消すこと、ホーム画面のウェブアプリは Safari と別に「actual use」で日数を数えることを確かめた。本文の要約は正しい（未解決の点 5 は指摘 9）
  - USACO Guide：usaco.guide の「Using this Guide」に「This guide is NOT a syllabus!!」がある。参考の書き方（構成の参考だけ）どおりで、文章は使っていない
  - 図：Mermaid の流れ図 1 枚。mermaid@10.9.1 を読む HTML を作り、ヘッドレスの Chrome（chrome-headless-shell 146、幅 720px）で PNG にして目で確かめた（手元の環境に日本語のフォントがないため文字は豆腐になったが、ノードと矢印の配置・重なり・ループの向きは正しい。縦長の TD で、幅 360px でも横にはみ出さない）。図の後に 3 段の文章があり、JS や CDN がなくても流れが分かる（G7）。静的な SVG（docs/img/how-to-use/）はない
  - code.md：コード片（snippets/how-to-use/）はなく、本文のコードブロックは text だけ（問題の行の書式・JSON の例・頼み方の定型文）。当てはまる項目なし
  - atcoder.jp・codeforces.com は開いていない。本文と参考にそれらの URL はない

## 指摘

### 1. 直すとよい｜分かりやすさ（U6）・事実（F7 のリンク）｜#levels・#page-anatomy・#ai-rule-version

- 問題：notation・atcoder-system は同じバッチで draft になったが、本文はページ全体へのリンクのまま（執筆者の未解決の点 2）。thinking-checklist も draft になった
- 根拠：docs/start/notation.md の sections に half-open・indexing・complexity、docs/start/atcoder-system.md に difficulty・levels・contests・ai-rules がある
- 直し方：メインがバッチの終わりに張り替えるときの候補として、156 行の「AtCoder の仕組み」→ atcoder-system.md#difficulty、188 行の「記法と用語の約束」→ notation.md#half-open（か残す）、302 行の「ABC・ARC・AGC の区分は AtCoder の仕組み」→ atcoder-system.md#contests（ルールの版は #ai-rules）

### 2. 直すとよい｜事実（F2 の言い過ぎ）｜#claude（281 行）

- 問題：「食い違うときは、Claude が古い版を読んでいる」と言い切っている
- 根拠：Claude はリポジトリの main を clone して docs/llms.txt を読み、サイトは push の後のビルドで公開される。push の直後には、Claude の読む版の方がサイトより新しいこともある。どちらが古いかは版の hash だけでは決まらない
- 直し方：「食い違うときは、Claude とサイトが別の時点の教材を見ている。ページの updated の最大の日付が古い方が古い」のように、どちらの向きもありうる書き方にする

### 3. 直すとよい｜事実（F2）・分かりやすさ｜#problems の役割の表

- 問題：力試しを「ページより上の帯の使い方」と定義しているが、設計書 §5.3 は「そのページの手法を、言い換えや組み合わせで使う難しめの問題」で、帯の上下で定義していない。また「例題には方針があり、解法の詳細は折りたたんである」（180 行・表）は、考察（thinking）のページでは方針も折りたたむ（手引き §10）ことに触れていない
- 根拠：planning/design.md 337 行、style-guide §10。台帳を数えると力試しの 230 件のうち 225 件はページより上の帯だが、5 件は同じか下の帯で、定義としては合わない
- 直し方：表の力試しを「手法を言い換え・組み合わせで使う難しめの問題（多くはページより上の帯）」にする。例題の行に「考察のページは方針も折りたたむ」を足す

### 4. 直すとよい｜事実（F2 の言い過ぎ）｜#page-anatomy（186 行）

- 問題：「手法のページには……保つ性質・各操作の手順・境界の小見出しがある」と、手法のページ全体に当てはまるように書いている
- 根拠：手引き §14-8 で、3 つの小見出しはデータ構造そのもののページだけ（使い方・応用のページでは要らない）と決めている
- 直し方：「データ構造のページには、ACL を使わずに自分で書く人向けに……」にする

### 5. 直すとよい｜分かりやすさ（U3）｜#progress（228 行）・#page-anatomy の種類の表

- 問題：「理解した：各ページの上と下のチェック欄で付ける」とあるが、レベルを持たないページ（このページを含む案内・題材別・入口のページ）には欄が出ない。読者はこのページの上に欄がないので迷う。また種類の表に、このページ自身が属する「案内」（guide：逆引き辞典・ロードマップなど）の行がなく、手法の行は水・青・黄の構成だけで、基礎の構成（応用の型 → 落とし穴 → 上位の手法へのつながり → 問題）が出てこない
- 根拠：overrides/main.html は `m.level` が帯のときだけ「理解した」の欄を出す。schema の type は technique・thinking・pattern・hub・overview・cpp・guide の 7 つ。基礎の構成は手引き §4
- 直し方：「レベルのあるページの上と下のチェック欄で付ける（案内のページにはない）」にする。表に「案内｜逆引き・ロードマップなど｜ページごとに違う」の行を足し、手法の行に「基礎のページは応用の型 → 落とし穴 → 上位の手法へのつながり」と添える（列を増やさず、表の後に 1 文でもよい）

### 6. 直すとよい｜事実（F3）｜#levels の「典型90 は★で読む」

- 問題：「★4 が基礎、★5 が水、★6 が青、★7 が黄にあたる」は、★1〜★3 の扱いがなく、★7 は 2000 以上（発展を含む）であることが落ちている
- 根拠：E869120 氏の Qiita の記事の表は ★1 ～149・★2 150～399・★3 400～799・★4 800～1199・★5 1200～1599・★6 1600～1999・★7 2000～
- 直し方：「★4 以下が基礎、★5 が水、★6 が青、★7 が黄以上にあたる」にする

### 7. 直すとよい｜分かりやすさ（U9）・生成ブロック｜#by-color（126〜131 行）

- 問題：lists の生成ブロックが箇条書きの途中にあり、生成後は前後に `<!-- textlint-disable -->` と空行が入るので、1 つの箇条書きが 3 つに分かれる（執筆者の報告どおり）。また生成される 2 行は「- レベル別：…」「- 種類別：…」で、前後の行の「**太字の見出し**：文」の形とそろわない
- 根拠：一時置き場の写しで gen_site.py を流した結果（上の「確かめたこと」）
- 直し方：「同じレベルのページを一覧で見る」の行を箇条書きの最後に移し、その直後（箇条書きの外）にブロックを置く。または「練習する」の行を先に置き、ブロックで箇条書きを終える

### 8. 直すとよい｜事実（F2）｜#progress（236 行）

- 問題：「保存を拒否する設定のブラウザでも……記録はそのページを開いている間だけ残る」
- 根拠：mkdocs.yml で navigation.instant が有効で、progress.js のメモリの記録（`memory`）はサイトの中でページを移っても残り、再読み込みやタブを閉じたときに消える（執筆者の未解決の点 4）
- 直し方：「記録はタブを閉じるか再読み込みするまでしか残らない」にする。progress.js の注意の文（「このページを開いている間だけ」）も同じに直すかはメインが決める

### 9. 直すとよい｜事実（出典の時点）｜#backup（257 行）

- 問題：Safari の 7 日の条件を今の仕様として言い切っているが、根拠は 2020 年の WebKit のブログだけで、今の Safari で同じかは確かめていない（執筆者の未解決の点 5）
- 根拠：参考の webkit.org/blog/10218（2020-03）。内容の要約は正しい
- 直し方：「WebKit が 2020 年に発表した Intelligent Tracking Prevention の仕様である」のように時点を添える（ロードマップの同じ記述もそろえる）

### 10. 直すとよい｜事実（F2）｜#claude（261 行）

- 問題：claude.ai/code の Projects が誰でも使えるように読める
- 根拠：code.claude.com の Projects のページは「public beta on Pro and Max plans and rolling out gradually」「aren't available on Team or Enterprise plans yet」としている
- 直し方：「（2026 年の時点ではベータで、Pro・Max のプランで順に使えるようになっている）」を 1 句足す

### 11. 直すとよい｜分かりやすさ（U3）｜#structure（69 行）

- 問題：手法の分野の並びを「基本テクニック → 考察 → 動的計画法 → グラフ → 木 → データ構造 → 数学 → 文字列・幾何の順」と書くが、実際の並びには「数え上げ・確率・ゲーム」と「その他の技法」があり、「数学」という名の分野はない
- 根拠：FIELD_TITLES の順（basics・thinking・dp・graph・tree・ds・math「整数論・代数」・comb「数え上げ・確率・ゲーム」・string・geometry・misc「その他の技法」）
- 直し方：「… → データ構造 → 整数論・代数 → 数え上げ・確率・ゲーム → 文字列 → 幾何 → その他の技法の順」と分野の題名どおりに書く

## 総合の判定

小さな直しで可。直すべき 0 件、直すとよい 11 件。事実の主張（レベルの帯と位置の目安、UI の動き、localStorage の扱い、Projects とスキルの仕組み、ルールの版、Safari の条件）は一次資料・コード・データで確かめられ、誤りはなかった。直すとよいのは、言い切りの強さ（指摘 2・3・4・8・9・10）、細部の不足（5・6・11）、draft になったページへの節リンク（1）、生成ブロックの置き場所（7）である。
