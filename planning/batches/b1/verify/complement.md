# complement（余事象）の検証

- 対象：docs/thinking/complement.md、snippets/complement/two-conditions-mod.{cpp,yaml}、docs/img/complement/whole-minus-complement.svg・two-conditions.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page complement`：エラー 0・警告 0
- `npx textlint docs/thinking/complement.md`：エラー 0・警告 10（文の長さ 5・`[0, \mathrm{MOD})` の括弧の対 2・助詞の重なり 2・読点の数 1）。どれも数式を含む文か半開区間の記法による誤検出で、執筆者の報告（11 件）とほぼ同じ
- **front matter**：`git diff HEAD` で変わったのは complexity・stage（stub→draft）と本文だけ。summary・signs・sections・aliases は catalog と一致。要点の計算量と complexity は一致。別名の行に aliases 5 つがすべてある
- **コード片**（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
    - `python3 tools/check_snippets.py -v snippets/complement`：4 case 一致
    - `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、n = 1・2・3・6・10^6・10^18 で実行。警告なし、サニタイザの報告なし。main の assert（n ≤ 5 で全列挙と一致）も通る
    - cases の期待値を手で確かめた：n = 2 → 100 − 162 + 64 = 2、n = 3 → 1000 − 1458 + 512 = 54。n = 6 の 199262 も 10^6 − 2·531441 + 262144 と一致
    - `all - no0 - no9 + none` の範囲は (−2MOD, 2MOD)、`%` の後は (−MOD, MOD)、負なら +MOD で [0, MOD)。本文の説明・コメントと一致。long long であふれない（|値| < 2.1·10^9）
    - 取り込みの印 `core` は本文と一致。`bits/stdc++.h`・`using namespace std;`・`'\n'`・マクロなしで手引き §9 に合う。取り込みは関数 1 つで、`pow_mod`・`main` は見せていない
- **台帳**：5 問とも `tools/ap.py show` で実在・題名・diff が本文と一致（abc178_c 653・abc162_d 757・abc193_c 379・abc131_c 518・abc455_e 1157）。参考だけに挙がる abc156_d（1014）も実在。例題 2・練習 3 は thinking の目安（例題 2〜4）に合う。abc455_e の台帳の summary は「（執筆時に確かめる）」のままで、本文は執筆者の提案の値で書かれている（メインが提案を反映すれば一致する）
- **参考の URL**：7 件とも取得し、題名・内容が書かれたとおりであることを確かめた（drken 5 件・qiita 2 件。ドメインはどちらも付録 B にある）。atcoder.jp・codeforces.com の URL は参考にない
- **evidence で照らした方針**
    - abc178_c：drken の解説は N ≤ 10^6、法 10^9 + 7、答え 10^N − 2·9^N + 8^N。本文と一致
    - abc162_d：N ≤ 4000、全体 r·g·b から k = 2j − i の等間隔の組を引く O(N^2)。本文と一致
    - abc193_c：N ≤ 10^10、a² ≤ N の a について累乗を集合に入れ、N − 集合の大きさ。本文と一致
    - abc131_c：A, B ≤ 10^18、C, D ≤ 10^9、f(B) − f(A − 1)、L = C / G · D。本文と一致（L ≤ 10^18 で long long に収まる）
    - abc455_e：Authns の記事は「S は A・B・C からなる」とし、答えを n(n+1)/2 − P(X) − P(Y) − P(Z) + 2·P(X,Y,Z)（2 つの等しさの共通部分は 3 つとも等しいに同じ）とする。comet725 のコードも同じ式。本文の練習の方針と一致
    - abc156_d：drken の解説は 2^N − 1 − C(N,A) − C(N,B)。参考の「空集合を全体から除く例（2^n − 1）」と合う
- **本文の主張を確かめた**
    - 確認問題 1：長さ N ≤ 8 の 0/1 列を全列挙し、隣が等しい箇所のあるものが 2^N − 2 個であることを確かめた（N = 1 で 0 も一致）
    - 確認問題 2：1〜100 で 2・3・5 のどれでも割れない数は 26 個、各倍数の個数 50・33・20・16・10・6・3 も一致
    - N = 1・2 の 0/9 の検算（0・2、09 と 90）、lcm の例（4 と 6 → 12）、3 条件の包除の符号、等しさ 3 つの包除で −3T + T = −2T になり答えが「全体 − 和 + 2T」になること、`(a − b − c + MOD) % MOD` が a − b − c < −MOD で負のままになること、C++ の `%` の符号、modint の引き算が [0, MOD) に戻ること（ACL document_ja の modint）。どれも正しい
    - 本文のリンク先の anchor（integer-division#cpp-vs-math・#count-multiples、mod-arithmetic#negative・#no-compare、modint#what-is-automatic、counting-mindset#verify-small・#exactly-vs-at-most、probability-basics#independence、prefix-sum-counting#equal-k）はすべて相手のページの見出しにある
- **図**：puppeteer の chrome-headless-shell 146 で 2 倍の PNG にして目で見た（作業用の場所の whole-minus-complement.png・two-conditions.png）。この環境には日本語のフォントがなく和文は豆腐になったが、配置・はみ出し・重なりは確かめられた。どちらも viewBox あり、背景は白の rect、文字はテキスト（sans-serif）、線の種類（破線・点線・斜線）で区別していて色だけに頼っていない。catalog の visual（static, priority 2、「全体の長方形から数えやすい部分を切り抜くベン図」）どおり。図の値（10^N・9^N・8^N）は本文・代替テキストと一致
- **執筆者の未解決の点**
    - abc455_e で S が A・B・C 以外の文字を含みうるか：Authns の記事は「S は A・B・C からなる」と書いている。本文の要約「含まれる A・B・C の個数が互いに異なる」はこれと矛盾せず、そのままでよい
    - 動く図を作らなかった点：visual は static・priority 2 なので SVG 2 枚で足りる

## 指摘

1. **直すとよい**・観点：figure（G5）・場所：docs/img/complement/two-conditions.svg
   - 問題：重なり A ∩ B を、2 つの楕円の本当の共通部分（レンズ形）ではなく、別に描いた灰色の楕円（cx 265, rx 55, ry 68）で表している。灰色の楕円は上下の端でレンズより少し低く（レンズの頂点は y ≈ 78.5、灰色は y = 82）、左右の端ではレンズの外に少しはみ出す。さらに A の右側の弧が B の白い塗りに、B の左側の弧が灰色の楕円に隠れるので、重なりの境界が図の上ではっきりしない。また A・B の塗りが `fill-opacity="0.92"` なので、楕円の中にも薄く斜線が透けて見え、「斜線の部分＝0 と 9 をどちらも含む」と見分けにくい
   - 根拠：レンダリングした two-conditions.png。x = 215 で灰色の楕円の半分の高さは 68·√(1 − (50/55)²) ≈ 28.3、レンズは B の弧から 85·√(1 − (115/120)²) ≈ 24.3
   - 直し方：A・B の塗りを不透明（`fill-opacity` を外す）にし、重なりは `<clipPath>` で A の楕円に切り抜いた B の楕円（同じ cx・rx・ry）を灰色で塗る。最後に 2 つの楕円の輪郭だけ（`fill="none"`）を上から描き直すと、両方の弧が見える

2. **直すとよい**・観点：figure（G3）・場所：docs/img/complement/ の 2 枚
   - 問題：幅 390px の画面（本文の幅は 358px 程度）では 520・480 幅の図が約 0.69〜0.75 倍に縮み、13px・12px の文字が 9px 前後になる。読めなくはないが小さい
   - 根拠：viewBox の幅と font-size からの計算
   - 直し方：ラベルの font-size を 15〜16 にそろえるか、viewBox を 440 幅程度に詰める。「10^N」は `<tspan baseline-shift="super" font-size="…">N</tspan>` で上付きにすると、本文の数式と見た目がそろう（任意）

3. **直すとよい**・観点：clarity（U2）・場所：#two-conditions、3 条件の包除の式の後の段落
   - 問題：「どの要素も、入っている集合の個数によらず、最後にちょうど 1 回か 0 回数えられる」と結論だけ書いてあり、なぜそうなるかがない。読者は 3 条件の符号の決まりを丸暗記することになる
   - 根拠：2 条件では「2 回引いたので 1 回足し戻す」と理由がある。3 条件ではそれに当たる 1 文がない
   - 直し方：「たとえば A・B・C の 3 つすべてに入る要素は、全体で +1、1 段目で −3、2 段目で +3、3 段目で −1 と数えられ、合計 0 になる」のような 1 文を足す

4. **直すとよい**・観点：clarity（U3）・場所：#practice の練習の方針、ABC193 C
   - 問題：「表せない数は多すぎて数えられないが」は、表せない数の個数こそ答えなので、読者には矛盾して読める。言いたいのは「1 つずつ判定・列挙するには多すぎる」こと
   - 根拠：本文の行 185
   - 直し方：「$N \le 10^{10}$ なので 1 から $N$ までを 1 つずつ調べることはできないが、表せる数は…列挙できるほど少ない」とする

## メインへの申し送り（ページの直しではない）

- 台帳の abc455_e の summary・approach は、執筆者の提案の値で一致する（Authns の記事で S が A・B・C からなることも確かめた）
- 本文と evidence で確かめたので、abc178_c・abc162_d・abc193_c・abc131_c・abc455_e の `checked` に 2026-10-21 を入れる提案

## 総合の判定

小さな直しで可（直すべき：0、直すとよい：4。事実・コード・台帳との一致に誤りはなく、図の重なりの描き方と説明の 2 か所を直すとよい）
