# nim の問題の補充（工程9・b6）

- ページ：docs/comb/nim.md（レベル 水）
- 今の問題：例題 tessoku_book_ag・arc168_b、練習 arc143_c（1 問）、力試し abc172_f・abc212_h
- 結論：練習の候補 3 問（合わせて 4 問になる）と力試しの候補 2 問を確かめた。difficulty・題名はすべて `python3 tools/ap.py show` で確かめた（2026-10-22）

## 練習の候補（practice）

### arc046_b　B. 石取り大作戦（diff 1260・参考値・水）

- 台帳：未登録（新規の追加の提案）
- 要約：N 個の石の山から、先手は 1 個以上 A 個以下、後手は 1 個以上 B 個以下を交互に取り、最後の石を取った方が勝つとき、勝つのはどちらかを求める。
- 方針の要点：N ≤ A なら先手が全部取って勝つ。A = B なら N を A + 1 で割った余りが 0 かどうかで決まり、A > B なら先手、A < B なら後手が勝つ。
- このページとの対応：#bounded（x mod (k+1)）と #asymmetric（先手と後手で取れる数が違う）の両方をそのまま使う。単一の山なので XOR は出てこない
- 裏付け：
  - https://kmyk.github.io/blog/writeups/algo-atcoder-arc_046_b/ （場合分けの結論）
  - https://scrapbox.io/esaka-sandbox/AtCoder_Regular_Contest_046_-_B_-_%E7%9F%B3%E5%8F%96%E3%82%8A%E5%A4%A7%E4%BD%9C%E6%88%A6 （A = B のとき A + 1 の倍数を押しつける理由）

### abc368_f　F. Dividing Game（diff 1180・基礎の上端）

- 台帳：登録済み（spf-sieve:practice・grundy-number:example）。pages に nim:practice を足す提案
- 要約：N 個の整数から交互に 1 つを選んで自分以外の約数に置き換え、置き換えられなくなった方が負けのとき、勝つのはどちらかを求める。
- 方針の要点：約数への置き換えは素因数を 1 個以上取り除く操作なので、各整数の素因数の個数（重複を含む）を山とする Nim になり、その XOR が 0 でなければ先手が勝つ。
- このページとの対応：#bouton（問題を Nim に読み替えて XOR で判定する）。Grundy 数を持ち出さなくても解ける
- 裏付け：
  - https://programming-hiroba.com/abc368-f/ （素因数の個数を石の山とみて XOR する。台帳の evidence にもある）
  - https://qiita.com/hyouri/items/f80a169412d5a969c25d （台帳の evidence。こちらは mex で表を作る方針で、今回は開き直していない）

### arc013_3　C. 笑いをとれるかな？（diff 1831・参考値・青）

- 台帳：未登録（新規の追加の提案）
- 要約：ハバネロの入ったいくつかの直方体の豆腐を、交互に格子面で切って片側を食べ、ハバネロを食べた方が負けのとき、先手が勝つかを求める。
- 方針の要点：ハバネロをすべて含む最小の直方体の外側だけが切れるので、各豆腐の 3 軸の両側の厚み 6 つを山とみなし、全部の XOR が 0 でなければ先手が勝つ。
- このページとの対応：#bouton（1 つの対象が複数の独立な山に分かれることを見抜き、Nim に帰着する）
- 帯について：difficulty は水の帯より上（参考値）。今の練習 arc143_c（1805）と同じくらい。帯から離れるので、力試しに回すかはメインの判断
- 裏付け：
  - https://kmjp.hatenablog.jp/entry/2013/03/23/0930 （6 方向の厚みを山として XOR）
  - https://kmyk.github.io/blog/writeups/algo-atcoder-arc_013/ （6 方向それぞれを独立なゲームとみて XOR）

## 力試しの候補（challenge）

### arc105_d　D. Let's Play Nim（diff 1871・青）

- 台帳：登録済み（game-basics:practice）。pages に nim:challenge を足す提案
- 要約：N 個の袋の硬貨を交互に皿へ移し、袋が空になったら皿から 1 枚以上の硬貨を交互に取り除くゲームで、動けなくなった方が負けのとき、勝つのはどちらかを求める。
- 方針の要点：後半は皿を山とする Nim なので XOR が 0 かどうかで決まり、前半で XOR を 0 にできるか（N の偶奇・同じ枚数の袋が 2 つずつあるか）を、過半数を 1 つの皿に集める戦略と真似戦略で判定する。
- このページとの対応：signs の「先手が勝てるように最初の配置を変えられるか」。帯から離れる（青）ので力試し
- 裏付け：
  - https://drken1215.hatenablog.com/entry/2020/10/14/120100 （N の奇偶と、値が 2 つずつ等しい場合の場合分け。台帳の evidence）

### abc297_g　G. Constrained Nim 2（diff 1834・青）

- 台帳：登録済み（grundy-number:example）。pages に nim:challenge を足すかはメインの判断（本文の #bounded は範囲つきを grundy-number#patterns に任せているので、nim には載せず grundy-number だけでもよい）
- 要約：N 個の山から交互に 1 つを選んで L 個以上 R 個以下の石を取り、取れなくなった方が負けのとき、勝つのはどちらかを求める。
- 方針の要点：個数 x の山は Nim の ⌊(x mod (L+R)) / L⌋ 個の山と同じなので、その値の XOR で判定する。
- このページとの対応：#bounded の「範囲つき」の段落（level 青）
- 裏付け：
  - https://kmjp.hatenablog.jp/entry/2023/04/19/1000 （式は実験で見つけたと書かれており、証明はない。台帳の evidence）

## 見送ったもの

- cf16_exhibition_final_c（C. Cheating Nim、diff なし）：各山から 0 個か 1 個を取って XOR を 0 にする最小の個数を求める型で、#winning-move の練習に向きそうだが、第三者の解説が見つからなかった（検索で出たのは atcoder.jp の提出だけで、開いていない）。atcoder-tags.herokuapp.com の Game/Nim タグに載ることだけ確かめた
- arc091_d（F. Strange Nim、diff 2395）：Grundy 数の規則を探す型で、b2・b3 の提案どおり grundy-number の力試しが合う
- abc317_f（F. Nim、diff 2072）：題名は Nim だが、ゲームではなく XOR が 0 になる組の数え上げ（桁 DP）なので見送った（中身は第三者の解説で確かめていない）
- agc033_c（diff 1758）・ddcc2020_final_a（diff なし）：atcoder-tags の Game/Nim タグにあるが、前者は game-basics の候補として b1 で扱い済み、後者は確かめていない

## 新しく noai を確かめたドメイン

- scrapbox.io/esaka-sandbox：check_noai で「noai・noimageai の指定はない」（HTTP 200、2026-10-22）。付録 B の scrapbox のプロジェクトに足す提案
- atcoder-tags.herokuapp.com・kmyk.github.io・kmjp.hatenablog.jp・drken1215・programming-hiroba.com は付録 B にある
