# b5 提案：how-to-use（この教材の使い方）

- 書いたファイル：docs/start/how-to-use.md（snippets・図の画像はなし。図は Mermaid の流れ図 1 枚を本文に置いた）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は guide なので null のまま
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0・警告 4（「何ができるか・いつ使うか」の助詞「か」の重なり 2 件、数式 $[l, r)$ の括弧の対 1 件、参考の行の長さ 1 件。どれも誤検出として残した）。mkdocs build で how-to-use の警告なし
- 使った出典：planning/research/00-curriculum §4.1・§2.1.3・§6.5.4・§6.11、10-tech §3.5・§3.6・§3.10、design §1.1・§1.2・§2・§3.1・§9、decisions（20261014 版・新しい Projects）、claude/*.md、.claude/skills/record-problem/SKILL.md、overrides/assets/js/progress.js・overrides/main.html（UI の文言と動作）、WebKit のブログ、code.claude.com の Skills と Projects のページ
- 新しく noai を確かめたドメイン：webkit.org（指定なし）・code.claude.com（指定なし）。付録 B への追加を提案する

## 台帳への提案

- なし（問題は載せていない。hub・guide の目安どおり 0 問）。問題の行の書式の例として、本文の text の囲みに abc340_e の行（台帳の summary のまま、リンクなし）を置いた

## 用語集への提案

- 語：準備中（stub）｜anchor：stub-page｜定義：本文がまだなく、冒頭の要点を目次から機械的に作っただけのページ。解法の根拠にしない
- 語：localStorage｜anchor：local-storage｜定義：ブラウザがサイトごとに持つ保存領域。この教材は「解いた」「理解した」の記録をここに置き、端末どうしでは同期しない
- （どちらも本文ではリンクしていない。足したらリンクを張れる）

## 手引きへの提案

- 生成ブロックの追加：本文に `<!-- gen:begin fields -->`（章の構成の節）、`<!-- gen:begin lists -->`（色ごとに学ぶときの節）、`<!-- gen:begin version -->`（claude.ai の節。Claude が書く索引の版とサイトの版を見比べるため）を空の状態で置いた。どれも gen_site.py の --list-blocks で置き場所の決まっていないブロックである。メインが gen_site.py を流して中身を入れてほしい。置かないと決めたら、マーカーを消して前後の文（「次のとおりである」など）を直す必要がある
- lists のブロックは箇条書きの途中に置いたので、生成後に前後の箇条書きが別のリストに分かれる。表示を見て気になれば、ブロックを箇条書きの後へ移す
- 書き出し・読み込みの欄（`<div class="kp-progress-io"></div>`）を、設計書 §9.1 のとおり使い方のページにも置いた（ロードマップにもある。同じページに 2 つあっても progress.js は動く作りに見えるが、2 ページに置くことは実機で確かめていない）

## 問題の補充の候補

- なし（このページは問題を載せない）

## 未解決の点

- AWC（AtCoder Weekday Contest）が AtCoder生成AI対策ルールの対象かは確かめていない（atcoder.jp を開けない）。本文は project-instructions.md v0.2 に合わせて「開催中は頼まない（安全な側に倒す）」と書いた。atcoder-system#ai-rules の執筆者と表現をそろえてほしい
- notation・atcoder-system・thinking-checklist は stub なので、節ではなくページへリンクした（draft になったら notation#half-open・atcoder-system#ai-rules・atcoder-system#difficulty などへ張り替える）
- claude.ai の Projects のプロジェクトの指示は v0.2（仮）で、工程 9c で確定する。確定したら claude の節（頼み方の定型文・ヒントか解説か・原因の 4 分類）を見直す
- 「保存を拒否する設定では記録はそのページを開いている間だけ残る」は progress.js の表示文に合わせた。instant navigation ではページを移ってもメモリの記録が残るので、厳密には「再読み込みするまで」である。UI の文言と一緒に直すかはメインが決める
- Safari の 7 日の条件は WebKit の 2020 年のブログによる。今の Safari でも同じかは確かめていない（ロードマップと同じ書き方にそろえた）

## 検証の指摘への対応（2026-10-22）

- 直したもの：指摘 2（版の食い違いはどちらの向きもありうる書き方に）・3（力試しの定義、考察のページは方針も折りたたむ）・4（3 つの小見出しはデータ構造そのもののページ）・5（「理解した」の欄はレベルのあるページだけ、種類の表に「案内」の行、基礎の構成を表の後に 1 文）・6（★4 以下が基礎、★7 が黄以上）・7（lists のブロックを箇条書きの最後へ移した）・8（タブを閉じるか再読み込みするまで）・9（2020 年に発表した仕様と時点を添えた）・10（Projects はベータで Pro・Max から）・11（分野の並びを分野の題名どおりに）
- 指摘 1：notation・atcoder-system が draft になったので、atcoder-system は #difficulty（レベルの節）・#contests（ルールの版の節）へ張り替えた。notation は半開区間・添字・計算量の 3 つを指すので、ページ全体へのリンクのまま残した（#half-open だけでは添字と計算量の節を外す）
- textlint はエラー 0・警告 4（前回と同じ 4 件）

## 検証の指摘からの提案（共有ファイル）

- roadmap の Safari の記述も「WebKit が 2020 年に発表した仕様」と時点を添えてそろえる（指摘 9）
- overrides/assets/js/progress.js の保存拒否時の注意の文「このページを開いている間だけ」を「タブを閉じるか再読み込みするまで」に直すか、メインが決める（指摘 8）
