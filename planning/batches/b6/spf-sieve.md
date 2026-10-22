# spf-sieve：問題の補充（工程9）

- ページ：docs/math/spf-sieve.md（レベル 基礎）
- 今の問題：例題 abc177_e、練習 abc368_f（1 問）、力試しなし
- difficulty は 2026-10-22 に `python3 tools/ap.py show` で確かめた。atcoder.jp・codeforces.com は開いていない

## 結論

練習の候補を 2 問（abc215_d・abc342_d）、力試しの候補を 1 問（abc152_e）見つけた。練習の 2 問を足すと練習は 3 問になり、目標（2〜4 問）に届く。どれも「多数の数をそれぞれ素因数分解する」型で、節 many-numbers・after-factor の演習になる。

## 候補

| 問題 ID | 題名 | diff | 役割 | 要約 | 方針の要点 | 裏付け |
| --- | --- | --- | --- | --- | --- | --- |
| abc215_d | D. Coprime 2 | 736 | practice | 数列のどの要素とも互いに素であるような M 以下の正の整数をすべて列挙する。 | 各 A_i を分解して現れた素数を集め、その素数の倍数を 1〜M から消して残ったものを出力する。 | https://qiita.com/sano192/items/00f6b70dab3bd3323ae6 ・ https://qiita.com/okm-uv/items/240b3fd3d2ff5f9561ab |
| abc342_d | D. Square Pair | 944 | practice | 0 以上 2×10^5 以下の N 個の整数から、積が平方数になる組 i < j の個数を数える。 | 各 A_i を分解して指数が奇数の素因数だけを掛けた値（平方因子を除いた核）に直し、核が等しい組を数え、0 を含む組は別に数える。 | https://drken1215.hatenablog.com/entry/2024/11/23/160056 ・ https://programming-hiroba.com/abc342-d/ |
| abc152_e | E. Flatten | 1348 | challenge | 10^6 以下の N 個（N ≤ 10^4）の正の整数 A_i に対し、A_i B_i がすべて等しくなる正の整数列 B の和の最小値を 10^9+7 で割った余りで求める。 | 共通の値は lcm(A_1, …, A_N) でよく、lcm を素因数ごとの最大の指数で持ち（各 A_i は最小素因数の表で分解）、mod 上で lcm / A_i の和をとる。 | https://drken1215.hatenablog.com/entry/2020/01/22/071000 |

### 各候補の注意

- **abc215_d**：b1 の報告で提案済みで、台帳にはまだない。確かめた 2 つの解説はどちらも試し割り（1 個 $O(\sqrt{A_i})$）で分解しており、最小素因数の表は使っていない。A_i の上限は 2 つの記事に明記がなく（記事は N, M ≤ 10^5 とだけ書く）、表で分解できる大きさかは記事からは確かめられなかった。本文に載せるなら「最小素因数の表でも試し割りでも解ける」型の練習とし、制約の数字は書かないか、検証役に別の解説で確かめさせる。後半の倍数を消す処理は調和級数（harmonic-sum）の形でもある
- **abc342_d**：台帳では prime-exponent-vector の example（approach は「平方因子を除いた核が等しい組を数える」）。drken 氏の記事は試し割りで分解しているが、「2×10^5 までの最小素因数の表を前計算して各 A_i を速く分解する」方法も挙げている。programming-hiroba の記事は試し割り。台帳の pages に `{id: spf-sieve, role: practice}` を足す案になる。他ページの例題との重複になるので、嫌うなら abc254_d（D. Together Square、diff 1191、台帳では fix-variable・prime-exponent-vector の practice、1〜N の各整数の核を求める）が代わりの候補だが、こちらは今回解説を開いていない
- **abc152_e**：台帳では prime-exponent-vector の practice。drken 氏の記事が試し割り $O(N\sqrt{M})$ と、最小素因数の表 $O(M \log\log M + N \log M)$ の両方を挙げており、このページの手法の裏付けがはっきりしている。diff 1348 は水の帯で、基礎の帯から離れるので力試しの候補とした。逆元を使うので、modint のページへの前提のリンクが要る。台帳の pages に `{id: spf-sieve, role: challenge}` を足す案になる

## 見送ったもの

- **abc170_d**（1033、harmonic-sum の example）・**abc250_d**（797、sieve-eratosthenes の example）：倍数をたどる篩・素数の列挙が本体で、各数の素因数分解は使わない
- **abc383_d**（884）：素数の列挙と数え上げが本体で、最小素因数の表で分解する問題ではない（解説は開いていない）
- data/problems.yaml でこのページを pages に持つ問題は abc177_e・abc368_f だけで、どちらも本文にある

## 使った出典

- https://qiita.com/sano192/items/00f6b70dab3bd3323ae6 （abc215_d の要約と解法）
- https://qiita.com/okm-uv/items/240b3fd3d2ff5f9561ab （abc215_d の解法）
- https://drken1215.hatenablog.com/entry/2024/11/23/160056 （abc342_d の言い換えと、最小素因数の表で分解する方法）
- https://programming-hiroba.com/abc342-d/ （abc342_d の解法）
- https://drken1215.hatenablog.com/entry/2020/01/22/071000 （abc152_e の制約・帰着・最小素因数の表）
- 新しく noai を確かめたドメインはない（どれも付録 B にある）

## 未解決の点

- この作業中に Web 検索の上限に達したため、検索での追加の探索（例：線形篩・φ の表を使う青の帯の問題）はしていない。節 linear-sieve（青）の演習になる問題は見つけていない
- abc215_d の A_i の上限は確かめられていない（上の注意）
