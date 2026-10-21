# integer-root の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/integer-root.md、snippets/integer-root/{isqrt,kth-root,perfect-powers,sqrt-ng}.{cpp,yaml}、docs/img/integer-root/correction.svg
- front matter で変えたもの：complexity（平方根 O(1)（sqrtl の後の補正は数回）、K 乗根 O(min(K, 63) log N)、N 以下の累乗数の数え上げ O(N^(1/3) log N)）・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 約数列挙・商の列挙・素因数の指数へのつながり, anchor: next-steps}` を足した（基礎の目安の「上位の手法とのつながり」）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（このページの直すべき行 0。全体では string/hashing-for-sets.md の abc424_f の行に二重空白が 1 件あり、担当外なので触れていない）、check_snippets（4 件すべて一致）、textlint（エラー 0・警告 4）
  - 残した警告：max-comma 2 件（数式 $a = 2, 3, \dots$・$1, 4, \dots, 81$ の中の読点）、sentence-length 2 件（例題の囲みの問題の行と、力試しの方針の数式を含む文）
- 動く図：作っていない（catalog の visual は static・priority 2）。静的な SVG を 1 枚描いた（補正の流れと、N が半開区間 [r², (r+1)²) にある数直線）
- 確かめた事実（手元の g++ で実行）：`(long long)sqrt((double)(r*r-1))` が初めて 1 大きくなるのは r = 67108865（n ≈ 4.5×10^15、n 自体は 2^53 未満で double で正確に表せる。sqrt の値の丸めでずれる）。r = 3×10^9〜3037000499 の r²−1 では `sqrtl` はずれなかった。⌊√(2^63−1)⌋ = 3037000499、⌊(2^63−1)^(1/3)⌋ = 2097151、⌊(2^63−1)^(1/4)⌋ = 55108。累乗数の個数の期待値は Python のメビウス関数による別の数え方で求めた（10^12 → 1010196、2^62 → 2149152709）。10^18 の値は問題の入出力例と重なるおそれがあるので cases に入れていない
- 使った出典：台帳の evidence（yuulis・torus711・drken 2 本・kazun のはてなブログ）、at274.hatenablog.com（√ の不等式を整数に直す方法。本文の compare-sqrt 節と参考に入れた）。新しく noai を確かめたドメイン：yuulis.hatenablog.com・at274.hatenablog.com・qiita.com/shun310（どれも指定なし。qiita は付録 B にあるので確認のみ）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| （追加）panasonic2020_c | 新規 | 下の「問題の補充の候補」を参照。integer-root の practice | https://at274.hatenablog.com/entry/2020/03/15/122125 |

- abc400_c・abc193_c・abc361_f・abc243_g の summary・approach は evidence の解説と食い違いがなかった
- abc193_c の本文の行は台帳の本体の summary（制約なし）で作られる。integer-root 向けの alternatives の summary には（N ≤ 10^10）が付いているが、fix_problems は本体を使うので、制約を出したいなら本体の summary に足すか、alternatives を使う仕組みかをメインで決めてほしい
- abc361_f の evidence（drken）は指数ごとの包除原理で解いており、台帳の approach「平方数は isqrt で数え、b ≥ 3 は列挙して重複を除く」の裏付けにはなっていない。本文の練習の方針では両方を書いた（列挙の方法は本文の perfect-powers 節のコード片と、Python の別の数え方との一致で確かめた）。列挙の方法を明記した第三者の解説を evidence に足すのが望ましい（見つけられなかった）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 累乗数 | perfect-power | $a^b$（$b \ge 2$）の形で書ける正の整数。$a \ge 1$ とするか $a \ge 2$ とするかで 1 を含むかが変わるので、問題ごとに定義を確かめる。 |

- 本文は `../guide/glossary.md#perfect-power` でリンクしている

## 手引きへの提案

- 基礎の technique の「上位の手法とのつながり」の定型の見出しがない点は integer-division・binary-search の報告と同じ。今回も sections に `next-steps` を足した
- 数学のページの「このページで使う記法」の 1〜2 行は、見出しを立てずに導入の段落の後に置いた。置き場所を定型にするなら手引きに書くとよい

## 問題の補充の候補

- **panasonic2020_c**（C. Sqrt Inequality、diff 701、ap.py で実在を確認）：正の整数 a, b, c（≤ 10^9）について √a + √b < √c かを判定する。c − a − b の符号を見てから 2 乗し、4ab < (c − a − b)² を整数で比べる。本文の [√ を含む式の大小を整数で比べる](#compare-sqrt) 節の例にちょうど合う（今は台帳にないので問題 ID を出さずに型だけ書いた）。役割は practice（基礎のページの例題は 1 問なので）。裏付け：https://at274.hatenablog.com/entry/2020/03/15/122125 （問い・制約・式変形）、https://qiita.com/shun310/items/6bb8bde789a6f2d9ee47 （検索結果の要約で同じ変形を確認。本文は読んでいない）
- abc420_g（G. sqrt(n²+n+X)、diff 1427、ap.py で実在を確認）：題名から平方数の判定に関わる問題と思われるが、第三者の解説で問いを確かめていない。候補の手掛かりとしてだけ挙げる
- abc319 以降の問題は abc400_c（例題）だけ。基礎のページの要件ではないので深くは探していない

## 未解決の点

- 図 correction.svg は描画して目で確かめる道具（rsvg-convert・cairosvg）がなく、座標の計算だけで文字の重なりを避けた。表示の確認を検証役に頼みたい
- 「Apple Silicon の macOS では long double が double と同じ 64 bit」は記憶に基づく（Apple の arm64 の ABI）。一次資料で確かめていないので、検証役に確認してほしい。外すなら「long double の精度は環境で変わる」だけにしてよい
- kth-root 節の「pow(n, 1.0 / k) の近い値は 1 より大きくずれることもあると考える」は安全側の書き方で、実際にずれが 2 以上になる例は確かめていない
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 6 回・Web 検索 3 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜7 はすべて直した（1：`sqrt` で二重計上すると言い切るのをやめた／2：図の右上の 2 行の y を入れ替えた／3：`odd` を `non_square` に／4：参考に Apple「Writing ARM64 code for Apple platforms」を足した。`tools/check_noai.py` で developer.apple.com に noai の指定がないことを確認／5：「正の整数 $a, b, c$ について」を先に置いた／6：記事の題名を実物に合わせた／7：「刻みの半分」に）
- 指摘 8 はメインへの連絡：用語集に `perfect-power` を足す提案（上の「用語集への提案」）を採らない場合は、本文の `[累乗数](../guide/glossary.md#perfect-power)` のリンクを外す必要がある
- 共有ファイルへの提案：style-guide のドメインの記録に developer.apple.com（noai の指定なし、2026-10-21 に確認）を足す
