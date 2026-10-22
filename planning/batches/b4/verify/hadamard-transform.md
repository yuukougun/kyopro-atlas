# b4 検証：hadamard-transform

- 対象：docs/math/hadamard-transform.md、snippets/hadamard-transform/xor-convolution.{cpp,yaml}（図はなし。catalog の visual は null）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0

## 実行して確かめたこと

- `python3 tools/check_pages.py --page hadamard-transform`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/hadamard-transform`：4 case 一致
- `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined`：警告なし。乱数の n = 4・K = 3 の入力と n = 0 の入力で main の assert（愚直な O(4^n) との一致、2 回の変換で 2^n 倍）が通り、サニタイザの報告なし
- yaml の 4 つ目の case（a = (−1, 0, 0, 1)、b = (2, 0, 0, 0)、K = 5）を手で計算：â = (0, −2, −2, 0)、5 乗で (0, −32, −32, 0)、戻すと (−16, 0, 0, 16)。期待出力 998244337 0 0 16 と一致。c = 2a も一致
- `npx textlint docs/math/hadamard-transform.md`：エラー 0・警告 7（報告どおり。助詞「で」の重なりなど）
- 本文の小さな例（a = (1, 2)、b = (3, 4) → (11, 10)）を手で計算し直して一致
- 本文の証明：χ_s(i)χ_s(j) = χ_s(i ⊕ j)、Σ_s χ_s(i ⊕ k) = 2^n [i = k] の議論は正しい。1 段の (x + y, x − y) をコードの `v[j]`・`v[j + len]` と照らして一致（x が bit が 0 の側）
- 等比数列の和：Python で v ∈ {0, 1, 2, p − 1, 5}、L ∈ {1, 2, 5, 7} について公式 v(v^L − 1)/(v − 1)（v ≡ 1 は L）と愚直な和が一致。偶奇で半分にする分割統治も v, L < 10 で一致
- 例題 abc212_h の解法：Python で長さ 8 の値の範囲・K ≤ 5・N ≤ 4 の乱数 30 通りについて、本文の手順（変換 → 各点で等比数列の和 → 逆変換 → 第 1 項以降の和）と全列挙が一致
- mod を取らないときの見積もり：(2^16 × 10^5)^2 = 4.29 × 10^19 > 2^63 − 1 = 9.22 × 10^18。正しい。2 回目の変換の途中の値も、Parseval から (2^n·max)^2 で抑えられるので、「積が収まれば整数のままでよい」も正しい
- 確認問題：XOR は桁上がりしないので長さ 2^n で足りる。正しい
- `python3 tools/ap.py show abc212_h`：H. Nim Counting、diff 2741（本文と一致）。台帳の summary は drken 氏・kmjp 氏の記事の問題概要（山の個数 1〜N、各山の石は A のどれか、先手必勝の盤面の数）と合う
- Library Checker：library-checker-problems の task.md（raw.githubusercontent.com）で、長さ 2^N の a・b、c_k = Σ_{i⊕j=k} a_i b_j を mod で求める、0 ≤ N ≤ N_MAX を確かめた（N ≤ 20 と法 998244353 は執筆者が info.toml で確かめたとおり）
- 参考・学ぶための資料の URL：6 件とも check_noai で noai・noimageai の指定なし、題名が本文の記載と一致。sapphire15 氏（Kronecker 積・AND と OR への応用の節・剰余で 2^{-n/2} を避ける実装）、izu_nori 氏（帰納法、疎な行列の積への分解、Appendix 1 の Fourier 変換、Appendix 2 の and/or 畳み込み）、kazuma8128 氏（FFT・ゼータ・メビウス・AND・OR・XOR の一覧）、drken 氏（余事象・XOR 畳み込みの累乗・割り算を避けた等比数列の和）、kmjp 氏（変換後に各点で 1 乗〜N 乗の和、値 0・1 の点を別扱い）はどれも本文の記載どおり。本文の文と例は資料の言い回し・数値と重ならない（F8）
- リンク先：nim#counting・zeta-mobius-subset#or-and-convolution・#vs-xor・zeta-mobius-divisor#gcd-lcm-convolution はどれも draft で見出しがあり、中身（1 段の式の表、GCD 畳み込み O(N log log N)）が本文の表と食い違わない
- front matter：変えたのは complexity・stage・updated と sections の library の追加（報告どおり）。要点の計算量と complexity が一致。要点の「何ができるか」と summary が一致。別名の行に aliases がすべてある
- コードの書き方（§9）：bits/stdc++.h と using namespace std、`using mint = atcoder::modint998244353;`（許された例外）、'\n'。取り込みの印 core・power が本文と一致し、取り込みは関数だけ。ACL の `pow(0)` は 1 を返すので K = 0 の単位元も正しい（case 3 で確認）
- 図：ページに図はなく、catalog の visual は null なので figure.md の項目は当てはまらない

## 指摘

### 1. 直すべき｜事実（F7）・手引き §7・§15-1｜#power の「典型の型」の段落（91 行目）

- **問題**：「[指示関数](../guide/glossary.md#indicator)」のリンク先は用語集の「指示確率変数」（事象が起きたら 1 をとる確率変数、期待値の線形性の話）で、本文の「候補の値に 1 を立てた列」とは別の語である。読者は確率変数の説明に飛ばされて戸惑う
- **根拠**：docs/guide/glossary.md の 211 行目は `### 指示確率変数 {#indicator}`。用語集に「指示関数」の項はない。§15-1 は「用語集にまだない語はリンクせず、本文で短く定義して報告の提案に書く」。ほかのページで #indicator を確率変数以外に使っている所はない
- **直し方**：リンクを外して「候補の指示関数 $f$（候補の値に 1 を立てた列）」のままにする（定義は括弧の中にある）。用語集に「指示関数」を足すなら報告の提案に書く（あるいは「指示確率変数」の項に指示関数を一言足す案をメインに出す）

### 2. 直すべき｜コード（C5）・手引き §9（§15-9）｜snippets/hadamard-transform/xor-convolution.cpp の `void print(const vector<mint>& v)`

- **問題**：`using namespace std;` の下で、C++23 の `std::print` と同じ名前の関数を作っている。手引き §9 は「std の名前と同じ関数名を作らない」と決めている
- **根拠**：g++-15 `-std=gnu++23` では `<bits/stdc++.h>` だけで `std::print("x{}\n", 1);` がコンパイルできる（手元で確かめた）ので、`std::print` は見えている。今は `std::print` の第 1 引数が format_string なので曖昧にならずに通るが、規則の文面に当たる。なお、同じ名前は zeta-mobius-subset・zeta-mobius-divisor・fps-basics・cpp-templates-constexpr（2 本）のコード片にもある（取り込みの外の補助の関数）
- **直し方**：`print_vec` などに名前を変える（呼ぶ 2 か所も）。取り込みの範囲の外なので本文は変わらない。ほかの 5 本をそろえるかはメインが決める

### 3. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#index-operations の最後の段落（108 行目）

- **問題**：「AND・OR の変換は足し算だけなので整数のまま戻せる」とあるが、逆変換（メビウス変換）は引き算を使う。読者は「戻すのも足し算なのか」と誤解しうる
- **根拠**：zeta-mobius-subset#vs-xor の表は逆変換を $(x, y) \to (x, y - x)$ とし、本文も「ゼータ変換・メビウス変換は足し算と引き算だけなので、割り算は要らない」と書いている
- **直し方**：「AND・OR の変換と逆変換は足し算と引き算だけで割り算がないので整数のまま戻せるが、…」とする

### 4. 直すとよい｜分かりやすさ（U5・U9）｜#index-operations の 108 行目と #library の「偶数の法では戻せない」（117 行目）

- **問題**：「XOR の逆変換は 2^n で割るので法は奇数でなければならない」が 2 つの節でほぼ同じ文で繰り返されている
- **根拠**：clarity.md U9「同じことを言い方を変えて繰り返す」。断片で読む場合も、どちらか一方にあればもう一方からリンクで足りる
- **直し方**：#library の箇条書きに具体例（2^64 で割った余りなど）とともに残し、#index-operations の段落は「XOR の逆変換は $2^n$ で割るので、法は奇数に限る（[自作するときの要点](#library)）」程度に縮める。あるいはその逆

### 5. 直すとよい｜事実（F1）｜例題の解法の詳細の計算量（148 行目）

- **問題**：「各点の等比数列の和が $O(2^{16} \log N)$」は、公式 $v(v^N - 1)/(v - 1)$ を使う手順 2 では各点で逆元（$O(\log p)$）も要るので、その分が抜けている
- **根拠**：手順 2 は割り算の公式を使うと書いている。kmjp 氏の実装も各点で modpow を 2 回呼ぶ（$v^N$ と $(v-1)^{p-2}$）。$\log p \approx 30$ で、$N \le 2 \times 10^5$ の $\log N \approx 18$ と同程度なので結論（間に合う）は変わらない
- **直し方**：「$O(2^{16} (\log N + \log p))$」とするか、「逆元を使わない分割統治なら $O(2^{16} \log N)$」と添える。執筆者の未解決の点 2（drken 氏の記事との比較）は、この直しで足りる

### 6. 直すとよい｜分かりやすさ（U10）・手引き §4（overview）｜#transform

- **問題**：発展の概要（overview）にしては、#transform に「なぜ各点の積になるか」「逆変換」「なぜ速いか」の証明が折りたたみなしで並び、節が長い。§4 は overview を「短く書き、証明や実装の流れは資料に任せる」とする
- **根拠**：clarity.md U10「発展の概要で証明を始める」。ただし各証明は 2〜3 文で正しく、読者の理解には役立つので、削るほどではない
- **直し方**：逆変換の段落（65 行目）を `??? note "証明：2 回かけると 2^n 倍に戻る"` に折りたたみ、本文には「同じ変換をもう一度かけて $2^n$ で割ると戻る」の 1 文だけ残す。なぜ各点の積になるかの直感（χ_s(i)χ_s(j) = χ_s(i⊕j)）は本文に残す

## 執筆者の未解決の点について

- 割り算を避ける分割統治を 1 文で触れただけの点：発展の概要としては 1 文で足りる。nim#counting の例題の解説も同じ方法を 1 文で書いており、食い違いもない。コード片にしなくてよい
- 例題の計算量の見積もり：指摘 5 のとおり逆元の分を足せば正確になる。drken 氏の記事の計算量は数式の画像・MathJax で本文から読み取れなかったが、手順から数えると本文の見積もり（＋逆元）と同じ程度になる

## 台帳への提案

- abc212_h：evidence に https://kmjp.hatenablog.jp/entry/2021/08/03/0930 を足す執筆者の提案に賛成（記事の問題・解法が本文の summary・approach と合うことを確かめた）。`checked: 2026-10-22` を入れる

## 総合の判定

小さな直しで可。直すべき 2 件（用語集へのリンクの誤り、コード片の補助関数の名前）はどちらも 1 か所の書き換えで済む。事実・計算量・コード・出典はほかに誤りがない。
