# counting-mindset の報告（工程8b・バッチ b1）

- 書いたファイル：docs/comb/counting-mindset.md、snippets/counting-mindset/verify-small.{cpp,yaml}、docs/img/counting-mindset/decision-order.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（1 片・期待と違う 0）、textlint（エラー 0・警告 19。数式を含む文の長さ、数式の中の読点、助詞の重複の誤検出に近いもの）、fix_problems --check（このページの直すべき行は 0。全体では counting-fix-order.md の 3 行が残るが、ほかの執筆者の書きかけ）
- 図：catalog の visual（static・priority 2）を静的な SVG にした（3 マス A・B・C を隣が違う色で塗る樹形図を、決める順 A→B→C と A→C→B で比べる）。手元に SVG を画像にする道具がなく、見た目は座標の計算でだけ確かめた。検証で表示を見てほしい
- 動く図：作っていない（static 指定のため div も置いていない）

## 使った出典

- kmjp（hatenablog.jp）ABC167 E・ABC156 E、drken ABC127 E・ABC150 E・ABC180 F、hamayan ABC173 F：例題・練習・力試しの方針（台帳の evidence）
- comet725（qiita）と ikatakos の ABC460 の記事（解説の部分だけ）：abc460_e の問いと方針。comet725 の記事は問題文がなく、問いは ikatakos の記事の解説部分で確かめた
- 新しく noai を確かめたドメイン：なし（どれも付録 B にある）

## 台帳への提案

- abc460_e｜summary｜N 以下の正の整数の組 (x, y) のうち、x と y を 10 進法でつないだ数が M を法として x + y と合同になるものの個数を求める（複数のテストケース）。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460（解説の部分）
- abc460_e｜approach｜y の桁数 d で場合分けすると条件が (10^d − 1)x ≡ 0 (mod M) になり y が消える。d ごとに x の個数 × y の個数を足す｜同上
- abc173_f｜summary｜catalog の文（「N 頂点の木で、すべての区間 [L, R] について頂点 L〜R だけを残した森の連結成分の数を求め、その総和を求める。」）にそろえる。台帳の今の文は句点がなく、言い回しも catalog と違う。本文はこの文で書いた
- abc156_e｜approach｜末尾に「k = 1 では何もしない状態を作れないので、空き部屋 0 の項を除く」を足す｜https://kmjp.hatenablog.jp/entry/2020/02/23/0900

## 用語集への提案

- 排反｜mutually-exclusive｜2 つの場合が同時には起きない（共通部分がない）こと。場合分けが排反かつ網羅的なら、各場合の個数を足すと全体の個数になる（本文ではリンクしていない。足されたらリンクを張るとよい）

## 手引きへの提案

- `tools/fix_problems.py --page <id> --field <field>` と両方を渡すと、ページだけでなく分野の全ページを直す（OR で効く）。§10 の例「`python3 tools/fix_problems.py --page <id>`」のとおり `--page` だけを渡すよう、手引きか道具の説明に注意を書くとよい（下の「未解決の点」を参照）

## 問題の補充の候補

- なし（catalog の例題 3・練習 3・力試し 1 がすべて確認済みで、abc319 以降の問題も abc460_e がある）

## 未解決の点

- 最初に `fix_problems.py --page counting-mindset --field comb` と実行したため、ほかの執筆者のページ docs/comb/multinomial-coefficient.md の問題の行 4 つ（abc234_f・abc470_f・abc266_g・arc067_c）を `- ID：要約` の形から台帳の形に書き換えてしまった。中身は台帳から作る正しい形への置き換えだけだが、担当外のファイルなので戻そうとしたところ、権限で止められたので戻していない。メインで確かめてほしい
- 作業中に、このページの問題の行が一度 `- ID：要約` の形に戻っていた（原因は分からない。ほかの執筆者の作業と重なった可能性がある）。最後に `--page counting-mindset` だけで直し、検査を通した
- ABC156 E の「k ≥ 2 なら余った移動を使い切れる」は kmjp の記事の「k = 1 だけ特別」に基づき、本文では往復で消費できるとだけ書いた（k − z が奇数のときの消費の仕方は、別の部屋を経由させる遠回りで 1 回増やせると自分で確かめた。本文には書いていない）
- 寄与の節の「最大値の総和 Σ a_i C(i−1, K−1)」と同じ値の扱い、確認問題の答えは自分で確かめた事実で、出典はない
- 図の見た目（文字の重なり）を画像で確かめていない
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 8 回

## 検証の指摘への対応（2026-10-21）

- 直すべき 1（ABC156 E の往復）：#pitfalls・例題の本文・解法の詳細を「偶数は往復 2 回、奇数は 3 部屋をめぐる 3 回。部屋が 3 つ以上のとき」に直し、部屋が 2 つでは式が成り立たないことを添えた。問題の制約（n ≥ 3 か）は ap.py にも台帳にも kmjp の記事にもなく確かめられなかったので、「制約で 3 つ以上と決まっている」とは書かず条件として書いた
- 直すべき 2（ABC127 E のあふれ）：「距離の総和は long long に収まるが、二項係数を掛ける前に mod を取らないとあふれる」に直した
- 直すべき 3（図の幅）：2 つの木を上下に積み、viewBox を 400×660 にした
- 直すとよい 4〜8：すべて採った（破線に「C ≠ A」、C=1 側に「C = A」のラベル／$N-1$ 個の組の説明／サイクルは $k \le 2$ で 0 通り／$K = 0$ を $j = n - 1$ の例に／`mint(0).pow(0)`）

## 台帳への提案（追加）

- abc156_e｜approach｜末尾の提案に「部屋が 3 つ以上なら k ≥ 2 で余りの移動を使い切れる（奇数は 3 部屋をめぐる移動）」も添える。制約の n の下限はメインで確かめてほしい（3 以上なら本文の「部屋が 3 つ以上あれば」を制約の言及に置き換えてよい）
