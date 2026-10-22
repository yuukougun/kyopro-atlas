# hadamard-transform の報告（b4）

- 書いたファイル：docs/math/hadamard-transform.md、snippets/hadamard-transform/xor-convolution.{cpp,yaml}（図はなし。visual が null のため。動く図の置き場もなし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `library`（自作するときの要点と Library Checker）を足した（既存の 3 つの anchor は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（1 本）、textlint エラー 0・警告 7（数式を含む文の長さ・読点の数、助詞の重なり。どれも数式の中の記号か、言い換えると不自然になるもの）。学ぶための資料の 2 行は、他者の記事の題名（「Hadamard 変換とbitwise XOR convolution」「xor畳み込みと高速Hadamard変換」）の空白の規則のエラーを避けるため textlint-disable で囲んだ
- 使った出典：drken1215.hatenablog.com（例題の方針。台帳の evidence）、kmjp.hatenablog.jp（例題の方針。2 つ目の裏付け）、sapphire15.hatenablog.com・kazuma8128.hatenablog.com（新しく check_noai で確かめた。どちらも noai・noimageai の指定なし）、qiita.com の izu_nori の記事、github.com の library-checker-problems（task.md と info.toml で N ≤ 20・法 998244353 を確かめた。raw.githubusercontent.com から取得）

## 台帳への提案

- abc212_h｜evidence｜https://kmjp.hatenablog.jp/entry/2021/08/03/0930 を追加｜同じ問題の解法（指示関数を変換し、各点で等比数列の和、値が 1 の点を別に扱う）を確かめた。evidence を 2 つにする（§15-6）
- abc212_h の summary・approach はそのままで正しい（問い：長さ 1 以上 N 以下、各要素は K 種類の整数のどれか、XOR が 0 でないものの個数。drken・kmjp の両方で確かめた）

## 用語集への提案

- アダマール変換｜hadamard-transform｜長さ 2^n の列 a を、\hat{a}_s = Σ_i (−1)^{popcount(i AND s)} a_i に移す変換。XOR 畳み込みを各点の積に変え、もう一度かけて 2^n で割ると元に戻る。（用語集から本ページへリンクする形でもよい）

## 手引きへの提案

- §5 math に「XOR の逆変換（アダマール変換）は 2^n で割るので、偶数の法（2^64 など）では使えない。AND・OR（ゼータ変換）は足し算だけなので使える」を足すか検討（持ち主は hadamard-transform#index-operations。zeta-mobius-subset#vs-xor にも同じ趣旨の 1 文がある）
- textlint の空白の規則が他者の記事の題名（英字と和字が空白なしで並ぶもの）でエラーになる。題名は原文のまま書くのが出典の規則なので、学ぶための資料の行ではリンクにする（リンクの題名は検査されない）か textlint-disable で囲むか、どちらかに決めるとよい

## 問題の補充の候補

- 例題は abc212_h の 1 問（catalog の representative）で足りる（発展の概要の目安は 0〜2）
- abc265_h（Ex. No-capture Lance Game、diff 3319）：catalog の problems_note どおり手法の分類（タグ）だけの確認で、第三者の解説で問いと解き方を確かめていないので載せていない。力試しに足すなら nyaannyaan 氏の解説などで裏付けが要る

## 未解決の点

- 等比数列の和を割り算なしで偶奇の分割統治で求める方法（drken 氏の記事の方針）は本文で 1 文触れただけで、コード片にしていない
- 例題の計算量 O(16·2^16 + 2^16 log N) は手元で数えた見積もり（drken 氏の記事は O(V log V log N) と書いている。各点の等比数列の和を O(log N) とすれば同じ程度）

## 検証の指摘への対応

- 1（直すべき）：#power の「指示関数」から用語集 #indicator（指示確率変数）へのリンクを外した。定義は括弧の中にある
- 2（直すべき）：コード片の補助関数 `print` を `print_vec` に改めた（取り込みの外なので本文は変わらない）
- 3・4（直すとよい）：#index-operations の段落を「AND・OR の変換と逆変換は足し算と引き算だけ…法は奇数に限る（#library へのリンク）」に縮め、998244353・10^9 + 7 の例は #library の「偶数の法では戻せない」に移した
- 5（直すとよい）：例題の計算量を「公式で逆元も求めるなら O(2^16 (log N + log p))、分割統治なら O(2^16 log N)」とした
- 6（直すとよい）：逆変換の証明を `??? note` に折りたたみ、本文には 1 文を残した
- 採らなかったものはない

## 追加の提案（検証から）

- 用語集に「指示関数」がない。足すなら「指示関数｜集合の要素なら 1、そうでなければ 0 をとる関数（列）」とするか、「指示確率変数」の項に指示関数を一言足す
- `print` という名前の補助関数が zeta-mobius-subset・zeta-mobius-divisor・fps-basics・cpp-templates-constexpr（2 本）のコード片にも残っている（手引き §9：std の名前と同じ関数名を作らない）。そろえるかはメインが決める
